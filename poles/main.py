#!/usr/bin/python3

from sys import exit

N, K = map(int, input().strip().split())

if K == 1:
    last_x, total_w = map(int, input().strip().split())
    total_fare = 0
    for i in range(1, N):
        x, w = map(int, input().strip().split())
        total_fare += total_w * (last_x - x)
        total_w += w
        last_x = x
    print(total_fare)
    exit(0)

W = []
X = []

for i in range(N):
    x, w = map(int, input().strip().split())
    W.append(w)
    X.append(x)

W.reverse()
X.reverse()

min_fare = {}

def compute_min_fare_cell(start, end, left_piles, right_piles):
    left_cost = min_fare[left_piles][start][start + left_piles - 1]
    right_cost = min_fare[right_piles][start + left_piles][end]
    min_value = left_cost + right_cost
    for middle in range(start + left_piles, end - right_piles + 2):
        left_cost = min_fare[left_piles][start][middle - 1]
        right_cost = min_fare[right_piles][middle][end]
        # print("test for {} L={} R={}".format(middle, left_cost, right_cost))
        min_value = min(min_value, left_cost + right_cost)
    return min_value

def compute_min_fare(piles):
    print("computing {}".format(piles))
    min_fare[piles] = [[0] * N for i in range(N)]
    if piles == 1:
        for start in range(N):
            total_w = W[start]
            for end in range(start + 1, N):
                min_fare[1][start][end] += min_fare[1][start][end - 1] + total_w * (X[end - 1] - X[end])
                total_w += W[end]
        # print("piles = 1:")
        # print("\n".join(["\t".join(map(str, line)) for line in min_fare[piles]]))
        # print("\n")
        return
    left_piles = piles // 2
    right_piles = piles - left_piles
    if not left_piles in min_fare:
        compute_min_fare(left_piles)
    if not right_piles in min_fare:
        compute_min_fare(right_piles)

    for start in range(N - piles + 1):
        for end in range(start + piles - 1, N):
            min_fare[piles][start][end] = compute_min_fare_cell(start, end, piles_left, piles_right)

    # print("piles = {}:\n".format(piles))
    # print("\n".join([" ".join(line) for line in min_fare[piles]]))
    # print("\n")

K_left = K // 2
K_right = K - K_left

compute_min_fare(K_left)
if not K_right in min_fare:
    compute_min_fare(K_right)
            
print(compute_min_fare_cell(0, N - 1, K_left, K_right))
