import numpy as np
import matplotlib.pyplot as plt
import control
R = 4700; C = 220e-6
G = control.tf([1], [R*C, 1])
w = np.logspace(-1.5,3,200)
mag,phase,omega = control.bode(G,w,Hz=True,dB=False,deg=True)
plt.show()