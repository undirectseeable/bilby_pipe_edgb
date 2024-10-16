import h5py
import corner
import numpy as np
import copy
import matplotlib.pyplot as plt
from bilby.gw.conversion import chirp_mass_and_mass_ratio_to_total_mass as convFunc

labels = ['chirp_mass', 'mass_ratio', 'chi_1', 'chi_2',"luminosity_distance","psi","dec","ra","phase","theta_jn","alpha"]

data = h5py.File("/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/EDGB150914/outdir_GW150914/final_result/GW150914_data0_1126259462-4_analysis_H1L1_merge_result.hdf5", 'r')
data = data['posterior']
ndim = len(labels)
corner_model = np.zeros((17855, ndim))
for i in range(ndim):
    corner_model[:, i] = data[labels[i]]


labels[-1] = "sqrt(alpha)/km"
fig = corner.corner(corner_model, labels=labels, color='blue',
                    levels=(0.5,0.9), scale_hist=True, quantiles = [0.05, 0.5, 0.95], show_titles = True, plot_datapoints=False)

'''
axes = np.array(fig.axes).reshape((ndim, ndim))
value1 = [28.192325962244016, 0.8571428571428571, 0.5, 0.1, 200, 0.1, 0.2, 0.4, 0.3, 0.2, 0.05*65*1.476625]
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
plt.savefig('edgb_gw150914_new.pdf',dpi=1000)
