# alpha = 29, beta = 32(4032)
from scipy.integrate import odeint
import numpy as np
import matplotlib.pyplot as plt

stunum = [1, 7, 2 ,3, 6, 0, 8, 2]

alpha = sum(stunum)
beta = 1
for i in range(8):
    if stunum[i] == 0: continue

    beta *= stunum[i]

while beta > 1000:
    beta -= 1000  

print(alpha)
print(beta)

#alpha = 29
#beta = 32

def derivative(x, t):
    dx = [ x[1], -beta * x[0] -alpha * x[1] + 1.0 ]
    return dx

time = np. linspace(0.0, 20.0, 10000)
x_init = [0.0, 0.0]
x = odeint(derivative, x_init, time)

plt.figure()
plt.plot(time, x[:,0])
plt.show()