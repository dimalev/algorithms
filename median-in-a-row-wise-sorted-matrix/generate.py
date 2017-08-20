from random import randrange

print(100)
for T in range(100):
    print(100, 100)
    for r in range(100):
        print(" ".join([str(randrange(1000)) for _ in range(100)]))
