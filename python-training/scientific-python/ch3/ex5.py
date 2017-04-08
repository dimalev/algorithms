from numpy import e
from matplotlib.pyplot import plot, title, grid, savefig,clf

N = 1000
h = 1.0e-3
a = -0.5

u = [e**0, e**(h*a), e**(2*h*a)]
for i in range(3, N + 1):
    u.append(u[-1] + h * a * (23/12 * u[-1] - 4/3 * u[-2] + 5/12 * u[-3]))

td = list(range(0, N + 1))

plot(td, u)
title("u values")
savefig("us.png")

clf()

plot(td, [e**(a * t) - ut for (t, ut) in zip(td, u)])
title("e^at - u_t values")
savefig("diff.png")
