from codecs import encode, decode

count = 12

corpus = [''] * count
frequences = [{} for _ in range(83)]
best = [0] * 83
with open("texts.hex", "r") as input:
    ind = 0
    for line in input:
        hexline = bytes.fromhex(line.replace("\n", ""))[0:83]
        corpus[ind] = hexline
        for i in range(83):
            if hexline[i] in frequences[i]:
                frequences[i][hexline[i]].append(ind)
                if len(frequences[i][hexline[i]]) > len(frequences[i][best[i]]):
                    best[i] = hexline[i]
            else:
                frequences[i][hexline[i]] = [ind]
                best[i] = hexline[i]
        ind += 1
start = 0
length = 83
#       A (privfct-key)  encr_pti
real = [
    "We can factor the number 15 with quantum computers. We can also factor the number 1", # 0
    "Euler would probably enjoy that ___ his theorem becomes a corner stone of crypto - ", # 1
    "___________________________________________________________________________________", # 2
    "___________________________________________________________________________________", # 3
    "___________________________________________________________________________________", # 4
    "___________________________________________________________________________________", # 5
    "___________________________________________________________________________________", # 6
    "___________________________________________________________________________________", # 7
    "A (private-key)  encr_ption _______________ algorithms, namely a procedure for gene", # 8
    "___________________________________________________________________________________", # 9
    "The sec___ message is_ Wh__ _______________cipher__never use the key more than once"  # 10
]
order = ['e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z']
allowed_letters = [' '] + order + [l.upper() for l in order] + ['(', ')', '-']
firsts = [0] * length
pos = [0] * length
res = [(['_'] * length) for _ in range(500)]
target = 11
for i in range(start, start + length):
    have = False
    for k in range(count):
        if real[k][i] != '_':
            code = corpus[k][i] ^ ord(real[k][i])
            res[pos[i - start]][i - start] = chr(corpus[target][i] ^ code)
            if pos[i] == 0:
                firsts[i] = code
            pos[i] += 1
            have = True
            break
        
    if not have:
        for k in range(count):
            mix = corpus[k][i]
            for letter in allowed_letters:
                code = mix ^ ord(letter)
                good = True
                for j in range(count):
                    res_letter = corpus[j][i] ^ code
                    if not (res_letter in [ord(l) for l in allowed_letters]):
                        good = False
                        break
                if not good:
                    continue
                res[pos[i - start]][i - start] = chr(corpus[target][i] ^ code)
                if pos[i] == 0:
                    firsts[i] = code
                pos[i] += 1
        

# print(", \t".join([str(code) for code in firsts]))
for i in range(1):
    print("".join(res[i]))
