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
#freqArr = freqArr[freqArr<f_max]


phase = 0.3
spin1 = np.array([0.3, 0.4, 0.5])
spin2 = np.array([0.1, 0.06, 0.08])

spin1L = np.sqrt(np.sum(spin1*spin1))
spin2L = np.sqrt(np.sum(spin2*spin2))



p = {'chirp_mass': 43.8382568359375, 'mass_ratio': 0.39232388138771057, 'phase': 4.7816548347473145, 'chi_1': 0.59056152552366257, 'chi_2': 0.22444136440753937, 'theta_jn': 1.3895268440246582, 'luminosity_distance': 100.0, 'geocent_time': 0.0}
Mtot = p['chirp_mass'] * (1 + p['mass_ratio']) ** 1.2 / p['mass_ratio'] ** 0.6
mass_1 = Mtot / (p['mass_ratio']+1)
mass_2 = Mtot - mass_1
#theta_jn, phi_jl, tilt_1, tilt_2, phi_12, a_1, a_2 = SimInspiralTransformPrecessingWvf2PE(0.2, 0, 0, p['chi_1'], 0, 0, -0.5, mass_1, mass_2, 20.0, p['phase'])


gw1 = wf(freqArr, mass_1, mass_2, p['luminosity_distance'], p['chi_1'], p['chi_2'], p['theta_jn'], p['phase'], 5.0)

out = np.zeros((8193, 4))
out[:, 0] = np.real(gw1['cross'])
out[:, 1] = np.imag(gw1['cross'])
out[:, 2] = np.real(gw1['plus'])
out[:, 3] = np.imag(gw1['plus'])
np.savetxt("/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/waveform_plots/bilby_wf3.dat", out, delimiter='\t')

'''
#gw1 = wf2(freqArr, mass1, mass2, 100, a_1, tilt_1, phi_12, a_2, tilt_2, phi_jl, theta_jn, phase,  0.0)
#gw2 = wf2(freqArr, mass1, mass2, 100, a_1, tilt_1, phi_12, a_2, tilt_2, phi_jl, theta_jn, phase,  0.1)
gw1 = wf(freqArr, 35, 30, 200, 0.5, 0.1, 0.2, 0.3, 0.0)
gw2 = wf(freqArr, 35, 30, 200, 0.5, 0.1, 0.2, 0.3, 0.1)

dphi = np.angle(gw2['plus']) - np.angle(gw1['plus'])
dphi = np.unwrap(dphi)
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
