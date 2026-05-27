# This script is just for visualization purpose to showcase the theoretical difference between ALOE, PLOE, GLOE ans IAD

import numpy as np
import matplotlib.pyplot as plt

t = np.linspace(0, 10, 1000)
u_nom = np.ones_like(t)

# --- PLOE ---
alpha_ploe = 0.4
u_ploe = (1 - alpha_ploe) * u_nom

# --- ALOE ---
alpha_aloe = np.zeros_like(t)
alpha_aloe[t > 3] = 0.6
u_aloe = (1 - alpha_aloe) * u_nom

# --- GLOE ---
alpha_gloe = np.clip((t - 2) / 6, 0, 0.7)
u_gloe = (1 - alpha_gloe) * u_nom

# --- IAD: single pulse dropout ---
alpha_iad = np.zeros_like(t)
t_start, t_end = 5.0, 5.4   # short dropout window
alpha_iad[(t >= t_start) & (t <= t_end)] = 1.0
u_iad = (1 - alpha_iad) * u_nom

# --- Plot ---
plt.figure(figsize=(8, 4))

plt.plot(t, u_nom, linestyle='--')
plt.plot(t, u_ploe)
plt.plot(t, u_aloe)
plt.plot(t, u_gloe)
plt.plot(t, u_iad)

# optional: emphasize vertical edges of the pulse
#plt.vlines([t_start, t_end], ymin=0, ymax=1, linestyles='dotted')

plt.ylim(-0.1, 1.1)
plt.xlim(t[0], t[-1])
plt.xticks([])
plt.yticks([])
# plt.box(False)

plt.tight_layout()
plt.show()