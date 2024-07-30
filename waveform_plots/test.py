import matplotlib.pyplot as plt
import numpy as np
from bilby_tgr.edgb.source import edgb_waveform_generator as wf
from bilby_tgr.edgb.source import edgb_XPHM_generator as wf2
from lalsimulation import SimInspiralTransformPrecessingNewInitialConditions, SimInspiralTransformPrecessingWvf2PE

freqArr = np.arange(8193) * 0.125
M_sec = 4.925490947641266978197229498498379006e-6


mass1=35.0
mass2=1.0
f_max = 0.018/(mass1+mass2)/M_sec
freqArr = freqArr[freqArr<f_max]
print(freqArr)


phase = 0.3
spin1 = np.array([0.3, 0.4, 0.5])
spin2 = np.array([0.1, 0.06, 0.08])

spin1L = np.sqrt(np.sum(spin1*spin1))
spin2L = np.sqrt(np.sum(spin2*spin2))

theta_jn, phi_jl, tilt_1, tilt_2, phi_12, a_1, a_2 = SimInspiralTransformPrecessingWvf2PE(0.2, 0, 0, spin1L, 0, 0, spin2L, mass1, mass2, 20.0, phase)

gw1 = wf2(freqArr, mass1, mass2, 100, a_1, tilt_1, phi_12, a_2, tilt_2, phi_jl, theta_jn, phase,  0.0)
gw2 = wf2(freqArr, mass1, mass2, 100, a_1, tilt_1, phi_12, a_2, tilt_2, phi_jl, theta_jn, phase,  0.1)

dphi = np.angle(gw2['plus']) - np.angle(gw1['plus'])
dphi[dphi < 0] += np.pi*2
np.savetxt("/scratch/nj2nu/result_figures/bilby_dphi.dat", dphi,delimiter='\t')

plt.plot(np.real(gw1['plus']), label="alpha=0")
plt.plot(np.real(gw2['plus']), label="alpha=0.1")
plt.legend()
plt.show()
out = np.zeros((gw1['plus'].shape[0], 4))
out[:, 0] = np.real(gw1['plus'])
out[:, 1] = np.imag(gw1['plus'])
out[:, 2] = np.real(gw2['plus'])
out[:, 3] = np.imag(gw2['plus'])
np.savetxt("/scratch/nj2nu/result_figures/bilby_XPHM_zero.dat", out, delimiter='\t')
'''
fig, ax = plt.subplots(2,2)

ax[0][0].plot(np.real(gw1['plus']), label="alpha=0")
ax[0][0].plot(np.real(gw2['plus']), label="alpha=0.05")
ax[0][0].title.set_text('plus real')

ax[0][1].plot(np.imag(gw1['plus']), label="alpha=0")
ax[0][1].plot(np.imag(gw2['plus']), label="alpha=0.05")
ax[0][1].title.set_text('plus imag')


ax[1][0].plot(np.real(gw1['cross']), label="alpha=0")
ax[1][0].plot(np.real(gw2['cross']), label="alpha=0.05")
ax[1][0].title.set_text('cross real')

ax[1][1].plot(np.imag(gw1['cross']), label="alpha=0")
ax[1][1].plot(np.imag(gw2['cross']), label="alpha=0.05")
ax[1][1].title.set_text('cross imag')

plt.legend()
plt.show()
'''
