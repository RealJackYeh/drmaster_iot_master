import numpy as np
import matplotlib.pyplot as plt
import control
wc = 2 * np.pi * 5
LPF = control.tf([wc], [1, wc])
w = np.logspace(-1.5,3,200)
mag,phase,omega = control.bode(LPF, w, Hz=True, dB=False, deg=True)
plt.show()
