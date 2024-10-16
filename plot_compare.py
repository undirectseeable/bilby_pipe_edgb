import h5py
import corner
import numpy as np
import copy
import matplotlib.pyplot as plt
from bilby.gw.conversion import component_masses_to_chirp_mass, component_masses_to_mass_ratio
import matplotlib.lines as mlines


labels = ["chirp_mass", "mass_ratio", "chi_1", "chi_2", "luminosity_distance","dec", "ra", "theta_jn"]
label_LIGO = ['m1_detector_frame_Msun', 'm2_detector_frame_Msun', 'spin1', 'spin2', 'luminosity_distance_Mpc', 'declination', 'right_ascension', 'costheta_jn']


data = h5py.File("/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/GR150914/outdir_GW150914/final_result/GW150914_data0_1126259462-4_analysis_H1L1_merge_result.hdf5", 'r')
data_edgb = h5py.File("/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/EDGB150914/outdir_GW150914/final_result/GW150914_data0_1126259462-4_analysis_H1L1_merge_result.hdf5", 'r')
data_LIGO = h5py.File("/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/GW150914_LIGO/GW150914_GWTC-1.hdf5",'r')


data_LIGO = data_LIGO['IMRPhenomPv2_posterior']
data = data['posterior']
data_edgb = data_edgb['posterior']
ndim = len(labels)
corner_model = np.zeros((17732, ndim))
corner_edgb = np.zeros((17855,ndim))
corner_ligo = np.zeros((40836, ndim))
for i in range(ndim):
    if(labels[i]=='theta_jn'):
        corner_model[:, i] = np.cos(data[labels[i]])
        corner_edgb[:, i] = np.cos(data_edgb[labels[i]])
    elif(labels[i]=='chi_1' or labels[i]=='chi_2'):
        corner_model[:, i] = np.abs(data[labels[i]])
        corner_edgb[:, i] = np.abs(data_edgb[labels[i]])
    else:
        corner_model[:, i] = data[labels[i]]
        corner_edgb[:, i] = data_edgb[labels[i]]
    corner_ligo[:, i] = data_LIGO[label_LIGO[i]]


chirp = (corner_ligo[:, 0] * corner_ligo[:, 1]) ** 0.6 / (corner_ligo[:, 0] + corner_ligo[:, 1]) ** 0.2
ratio = corner_ligo[:, 1] / corner_ligo[:, 0]
corner_ligo[:, 0] = chirp
corner_ligo[:, 1] = ratio

#fig = corner.corner(corner_model, labels=labels, color='blue',
#                    levels=(0.5,0.9), scale_hist=True, plot_datapoints=False)

fig = corner.corner(corner_edgb, labels = labels, color='green',
                    levels=(0.5,0.9), scale_hist=True, quantiles = [0.05, 0.5, 0.95], show_titles = True, plot_datapoints=False)

corner.corner(corner_ligo, fig = fig, color='red',
                    levels=(0.5,0.9), scale_hist=True, quantiles = [0.05, 0.5, 0.95], plot_datapoints=False)
sample_labels = ['edgb', 'LIGO_IMRPhenomPv2']
colors = ['green','red']
plt.legend(handles=[
            mlines.Line2D([], [], color=colors[i], label=sample_labels[i])
            for i in range(2)
        ], bbox_to_anchor=(-3,4,3,2), fontsize=20)

'''
axes = np.array(fig.axes).reshape((ndim, ndim))
value1 = [28.192325962244016, 0.8571428571428571, 0.5, 0.1, 200, 0.1, 0.2, 0.4, 0.3, 0.2]
# Loop over the diagonal
for i in range(ndim):
    ax = axes[i, i]
    ax.axvline(value1[i], color="r")

# Loop over the histograms
for yi in range(ndim):
    for xi in range(yi):
        ax = axes[yi, xi]
        ax.axvline(value1[xi], color="r")
        ax.axhline(value1[yi], color="r")
        ax.plot(value1[xi], value1[yi], "sr")

'''
#corner.overplot_lines(fig, value_inject, color="C1")
#plt.show()
plt.savefig('gw150914_quantile.pdf',dpi=1000)
