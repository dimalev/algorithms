#include <unistd.h>
#include <sys/wait.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

const std::string duble_dash{"--"};

struct ProcessSettings {
  std::string executable;
  std::vector<std::string> arguments;
};

struct Process {
  int in, out, exit_status;
  pid_t pid;
  bool exited = false;
};

struct TableSettings {
  std::unique_ptr<ProcessSettings> world;
  std::unique_ptr<ProcessSettings> player;
};

std::unique_ptr<ProcessSettings>
read_params(std::unique_ptr<ProcessSettings> process, int start, int argc, char **argv, int *end) {
  int i = start;
  std::string exec{argv[i]};
  process.reset(new ProcessSettings);
  process->executable = exec;
  for(; i < argc; ++i) {
    std::string arg{argv[i]};
    if(arg.compare(0, 2, duble_dash) == 0) break;
    process->arguments.push_back(arg);
  }
  *end = i - 1;
  return process;
}

void print_usage(std::string exec_name) {
  std::cerr << "Usage:\n\n"
            << "\t" << exec_name << " --world WORLD_EXEC ...WORLD_ARGS --player PLAYER_EXEC ...PLAYER_ARGS\n\n"
            << "Where\n\n"
            << " - WORLD_EXEC - executable world participant, his exit status will be published as table result,\n"
            << " - ...WORLD_ARGS is arbitrary list of arguments for world executable,\n"
            << " - PLAYER_EXEC - executable player participant. It will get world's output as an input, and it's input "
            << "will be passed to the world as input.\n"
            << " - ...PLAYER_ARGS is arbitrary list of arguments for player executable.\n\n"
            << " Both participants will be able to output errors into std::cerr, and their errors will be displayed "
            << " with prefix \"[ WORLD ]\" for world participant, and \"[ PLAYER ]\" for player.\n\n"
            << "World's exit status will be exit status for table process.\n";
}

void ERROR(std::string message) {
  std::cerr << "[ Table ] " << message << std::endl;
}

void exec_process(std::unique_ptr<ProcessSettings> settings) {
  int argc = settings->arguments.size();
  char **argv = new char*[argc + 1]; // ...args + nullptr
  char *exec_file = new char[settings->executable.size() + 1];
  std::strcpy(exec_file, settings->executable.c_str());
  for(int i = 0; i < argc; ++i) {
    argv[i] = new char[settings->arguments[i].length() + 1];
    std::strcpy(argv[i], settings->arguments[i].c_str());
  }
  argv[argc] = nullptr;
  execv(exec_file, argv);
}

int main(int argc, char **argv) {
  TableSettings settings;
  for(int i = 1; i < argc; ++i) {
    std::string arg{argv[i]};
    if(arg == "--world")
      settings.world = read_params(move(settings.world), i + 1, argc, argv, &i);
    else if(arg == "--player")
      settings.player = read_params(move(settings.player), i + 1, argc, argv, &i);
    else {
      ERROR(std::string{"Ignore "} + std::string{arg});
    }
  }

  if(!settings.world || !settings.player) {
    print_usage(argv[0]);
    exit(EXIT_FAILURE);
  }


  /* Note! [ OUTPUT_STREAM, INPUT_STREAM ] */
  int world_from_player[2], player_from_world[2];
  if(pipe(world_from_player)) {
    ERROR("Failed to create pipe from player to world!");
    exit(EXIT_FAILURE);
  }
  if(pipe(player_from_world)) {
    ERROR("Failed to create pipe from world to player!");
    exit(EXIT_FAILURE);
  }

  Process world;
  world.pid = fork();
  if(world.pid == 0) {
    close(world_from_player[1]);
    dup2(world_from_player[0], 0);
    close(player_from_world[0]);
    dup2(player_from_world[1], 1);
    exec_process(move(settings.world));
  } else if(world.pid < 0) {
    ERROR("Failed to start world process!");
    exit(EXIT_FAILURE);
  }
  world.in = world_from_player[0];
  world.out = player_from_world[1];

  Process player;
  player.pid = fork();
  if(player.pid == 0) {
    close(world_from_player[0]);
    dup2(world_from_player[1], 1);
    close(player_from_world[1]);
    dup2(player_from_world[0], 0);
    exec_process(move(settings.player));
  }
  player.in = world_from_player[1];
  player.out = player_from_world[0];

  while(true) {
    int status;
    pid_t proc_exited = wait(&status);
    if(proc_exited == world.pid) {
      world.exited = true;
      world.exit_status = status;
    } else if(proc_exited == player.pid) {
      player.exited = true;
      player.exit_status = status;
    } else {
      ERROR(std::string{"Unknown process exited. pid = "} + std::to_string(proc_exited));
    }
    if(world.exited && player.exited) break;
  }

  if(player.exit_status != EXIT_SUCCESS) {
    ERROR(std::string{"Player exited with non-successful status "} + std::to_string(player.exit_status));
  }

  exit(WEXITSTATUS(world.exit_status));
}
