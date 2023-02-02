from scipy import signal
import numpy as np
import matplotlib.pyplot as plt
signalFreq = [2,50]
wc = 2 * np.pi * 5 # filter cut-off frequency 5Hz
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
butterworth = signal.TransferFunction(num, den)  #連續時間轉移函數
print(butterworth)
dt = 1/1000   # 採樣時間 1/1000Hz
dBWlowPass = butterworth.to_discrete(dt, method='gbt', alpha=0.5) #將連續時間轉移函數數位化，使用雙線性轉換
print(dBWlowPass) 
#b = dBWlowPass.num  #分母係數
#a = -dBWlowPass.den #分子係數
#print('filter coefficient b_i: ' + str(b))
#print('filter coefficient a_i: ' + str(a[1:]))