def read_numbers():
    return map(int, input().strip().split())

[N, P] = read_numbers()

colors = list(range(N)) # all astronauts will get separate color
reverse_colors = {} # per each color, we will keep list of astronauts with given color

for p in range(P):
    [L, R] = read_numbers()
    L_color = colors[L]
    R_color = colors[R]
    if L_color != R_color: # if these astronauts are of different country
        if R_color in reverse_colors: # if right astronaut has family
            R_astronauts = reverse_colors[R_color]
            del reverse_colors[R_color]
        else: # if he is alone
            R_astronauts = [R]
        if not L_color in reverse_colors: # if left astronaut was alone
            reverse_colors[L_color] = [L]
        reverse_colors[L_color].extend(R_astronauts)
        for R_comrad in R_astronauts:
            colors[R_comrad] = L_color

uniq_colors = set(colors)
result = 0
for color in uniq_colors:
    if color in reverse_colors:
        count = len(reverse_colors[color])
        result += count * (N - count)
    else:
        result += N - 1
        
print(result // 2)
