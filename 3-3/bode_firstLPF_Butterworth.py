import numpy as np
import matplotlib.pyplot as plt
import control
wc = 2 * np.pi * 5
LPF = control.tf([wc], [1, wc])
n = 4
a = np.zeros(n+1)
gamma = np.pi/(2.0*n)
a[0] = 1
for k in range(0,n):
    rfac = np.cos(k*gamma)/np.sin((k+1)*gamma)
    a[k+1] = rfac*a[k]
print(a)
c = np.zeros(n+1)
for k in range(0,n+1):
    c[n-k] = a[k]/pow(wc,k)
num = [1]
den = c
LPF_butter = control.tf(num, den)
w = np.logspace(-1.5,3,200)
mag,phase,omega = control.bode(LPF, w, Hz=True, dB=False, deg=True)
mag,phase,omega = control.bode(LPF_butter, w, Hz=True, dB=False, deg=True)
plt.show()
