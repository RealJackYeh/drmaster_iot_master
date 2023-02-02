from scipy import signal
import control
import numpy as np
import matplotlib.pyplot as plt
w0 = 2 * np.pi * 5  # filter cut-off frequency 5Hz
num = w0; den = [1, w0]
LPF = signal.TransferFunction(num, den)  #連續時間轉移函數
dt = 1/1000   # 採樣時間 1/1000Hz
dLPF = LPF.to_discrete(dt, method='gbt', alpha=0.5) #將連續時間轉移函數數位化，使用雙線性轉換
print(dLPF) 