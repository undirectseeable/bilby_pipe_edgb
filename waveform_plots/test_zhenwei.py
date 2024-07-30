import matplotlib.pyplot as plt
from pycbc import waveform
from pycbc.coordinates import spherical_to_cartesian
import numpy as np



x1, y1, z1 = spherical_to_cartesian(0.31, 3.3, 1.95)
x2, y2, z2 = spherical_to_cartesian(0.5, 3.2, 1.72)
print(x1, y1, z1, x2, y2, z2)
#hp1, hc1 = waveform.get_fd_waveform(approximant='IMRPhenomXPHM', mass1=8.9, mass2=1.9, distance=375, spin1_a=0.31, spin1_azimuthal=3.3, spin1_polar=1.95,spin2_a=0.5, spin2_azimuthal=3.2, spin2_polar=1.72, alpha=2.0, delta_f=1/8, f_lower=20)


#hp2, hc2 = waveform.get_fd_waveform(approximant='IMRPhenomXPHM', mass1=15.3, mass2=1.5, distance=300, spin1x=0.1, spin1y=0.1,spin1z=0.1,spin2x=0.2,spin2y=0.2,spin2z=0.2, alpha=10.0, delta_f=1/1024, f_lower=20)

#hp, hc = waveform.get_fd_waveform(approximant='IMRPhenomXPHM', mass1=8.9, mass2=1.9, distance=300, spin1x=0.1, spin1y=0.1,spin1z=0.1,spin2x=0.2,spin2y=0.2,spin2z=0.2, alpha=2.0, delta_f=1/1024, f_lower=20)

#hp, hc = waveform.get_fd_waveform(approximant='IMRPhenomXPHM', mass1=8.9, mass2=5.0, distance=100, inclination=2.0, coa_phase=3.3, delta_tc=0.0, spin1x=x1, spin1y=y1, spin1z=z1, spin2x=x2, spin2y=y2, spin2z=z2, alpha=0.0, delta_f=1/8, f_lower=20, f_final=1024, f_ref=20)

#hp, hc = waveform.get_fd_waveform(approximant='IMRPhenomXPHM', mass1=4.467332412121908, mass2=2.962877179756423, distance=100, inclination=1.9015099287816928, coa_phase=1.7821966531026714, delta_tc=0.0, spin1x=0.020505251941247676, spin1y=-0.11374922631866559, spin1z= -0.21318087251341347, spin2x=-0.41217929280877846, spin2y= 0.0731433155466104, spin2z= -0.2101131627142761, alpha=0.3191054865831615, delta_f=1/8, f_lower=20, f_final=1024, f_ref=20)

spin1 = np.array([0.3, 0.4, 0.5])
spin2 = np.array([0.1, 0.06, 0.08])
spin1L = np.sqrt(np.sum(spin1*spin1))
spin2L = np.sqrt(np.sum(spin2*spin2))
M_sec = 4.925490947641266978197229498498379006e-6
mass1=35.0
mass2=1.0
f_max = 0.018/(mass1+mass2)/M_sec
'''
hp, hc = waveform.get_fd_waveform(approximant='IMRPhenomXPHM', mass1=35, mass2=1, distance=100, inclination=0.2, coa_phase=0.3, delta_tc=0.0, spin1x=spin1[0], spin1y=spin1[1], spin1z=spin1[2], spin2x=spin2[0], spin2y= spin2[1], spin2z= spin2[2], alpha=10000.0, delta_f=1/8, f_lower=20, f_final=1024, f_ref=20)

hp2, hc2 = waveform.get_fd_waveform(approximant='IMRPhenomXAS', mass1=35, mass2=1, distance=100, inclination=0.2, coa_phase=0.3, delta_tc=0.0, spin1x=spin1[0], spin1y=spin1[1], spin1z= spin1[2], spin2x=spin2[0], spin2y= spin2[1], spin2z= spin2[2], alpha=0.0, delta_f=1/8, f_lower=20, f_final=1024, f_ref=20)
'''

hp, hc = waveform.get_fd_waveform(approximant='IMRPhenomXPHM', mass1=35, mass2=1, distance=100, inclination=0.2, coa_phase=0.3, delta_tc=0.0, spin1x=0.0, spin1y=0.0, spin1z=spin1L, spin2x=0.0, spin2y= 0.0, spin2z= spin2L, alpha=0.0, delta_f=1/8, f_lower=20, f_final=f_max, f_ref=20)

hp2, hc2 = waveform.get_fd_waveform(approximant='IMRPhenomXPHM', mass1=35, mass2=1, distance=100, inclination=0.2, coa_phase=0.3, delta_tc=0.0, spin1x=0.0, spin1y=0.0, spin1z=spin1L, spin2x=0.0, spin2y= 0.1, spin2z= spin2L, alpha=0.1, delta_f=1/8, f_lower=20, f_final=f_max, f_ref=20)

fig, ax = plt.subplots(2,1,sharex=True)

ax[0].plot(np.real(hp.numpy()), label="alpha=0")
ax[0].plot(np.real(hp2.numpy()), label="alpha=0.1")
ax[0].title.set_text('plus real')

ax[1].plot(np.imag(hp.numpy()), label="alpha=0")
ax[1].plot(np.imag(hp2.numpy()), label="alpha=0.1")
ax[1].title.set_text('plus imag')
      
plt.legend()
plt.show()
#out = {'hp': hp, 'hc': hc}
#np.save('waveform_pycbc.npy', out)
'''
phase = np.angle(hp.numpy())
x = hp.sample_frequencies.numpy()
phase = np.flip(np.unwrap(np.flip(phase)))

#mag = np.absolute(hp.numpy())
phase1 = np.angle(hp1.numpy())
phase1 = np.flip(np.unwrap(np.flip(phase1)))
phase2 = np.angle(hp2.numpy())
phase2 = np.flip(np.unwrap(np.flip(phase2)))

x1 = hp1.sample_frequencies.numpy()
x2 = hp2.sample_frequencies.numpy()
#mag1 = np.absolute(hp1.numpy())
#mag2 = np.absolute(hp2.numpy())

#phase = -np.gradient(phase, x)
#phase1 = np.gradient(phase1, x1)
#phase2 = -np.gradient(phase2, x2)

#choose = x>=1
#choose1 = x1>=1
#choose2 = x2>=1
plt.figure(figsize=(12,8))
plt.plot(x, np.abs(phase),'-.', label='case1')
plt.plot(x1, np.abs(phase1),'-.', label='case2')
plt.plot(x2, np.abs(phase2),'-.', label='case3')

#plt.plot(x1[choose1], mag1[choose1],'-.', label='case2')
#plt.plot(x2[choose2], mag2[choose2],'-.', label='case3')

#plt.plot(hp2.sample_frequencies, hp2,'-.', label='case3')
#plt.plot(hp.sample_times, hp,'-.', label='wf')
plt.ylabel('phase phenom')
plt.xlabel('frequency')
plt.legend()
#plt.xlabel('time')
#plt.xlim(1,2000)
plt.xscale('log')
plt.yscale('log')
#plt.title("angle")
#plt.show()
#plt.grid()
plt.savefig("compare_align.jpg", dpi=200)
'''
dphi = np.angle(hp2.numpy()) - np.angle(hp.numpy())
dphi = np.unwrap(dphi)
np.savetxt("/scratch/nj2nu/result_figures/zhenwei_dphi.dat", dphi, delimiter='\t')
out = np.zeros((hp.numpy().shape[0], 4))
out[:, 0] = np.real(hp.numpy())
out[:, 1] = np.imag(hp.numpy())
out[:, 2] = np.real(hp2.numpy())
out[:, 3] = np.imag(hp2.numpy())

np.savetxt("/scratch/nj2nu/result_figures/zhenwei_XPHM_zero.dat", out, delimiter='\t')

