from scipy import signal
import control
import numpy as np
import matplotlib.pyplot as plt
wc = 2 * np.pi * 5 
n = 2
a = np.zeros(n+1)
gamma = np.pi/(2.0*n)
a[0] = 1
for k in range(0,n):
    rfac = np.cos(k*gamma)/np.sin((k+1)*gamma)
    a[k+1] = rfac*a[k]
#print(a)
c = np.zeros(n+1)
for k in range(0,n+1):
    c[n-k] = a[k]/pow(wc,k)
num = [1]
den = c
butterworth = signal.TransferFunction(num, den)  #連續時間轉移函數
dt = 1/1000   # 採樣時間 1/1000Hz
dBWlowPass = butterworth.to_discrete(dt, method='gbt', alpha=0.5) #將連續時間轉移函數數位化，使用雙線性轉換
print(dBWlowPass) 