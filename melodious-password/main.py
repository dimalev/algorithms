#!/usr/bin/python3

vowels = list("euioa")
consonants = list("qwrtpsdfghjklzxcvbnm")

def multiply(letters, trailers):
    return [letter + trailer for letter in letters for trailer in trailers]

# [l][i] is i-th combination of length = l start from vowel
# naturally, l = 1 is just a vocabulary
vowel_start = [vowels]
consonant_start = [consonants]

T = int(input().strip())

for t in range(1, T):
    vowel_start.append(multiply(vowels, consonant_start[t - 1]))
    consonant_start.append(multiply(consonants, vowel_start[t - 1]))

# for password in vowel_start[T - 1]:
#     print(password)

# for password in consonant_start[T - 1]:
#     print(password)

print("\n".join(vowel_start[T - 1]))
print("\n".join(consonant_start[T - 1]))
