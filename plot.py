import h5py
import corner
import numpy as np
import copy
import matplotlib.pyplot as plt


labels = ['chirp_mass', 'mass_ratio', 'chi_1', 'chi_2',"luminosity_distance","psi","dec","ra","phase","theta_jn","alpha"]

data = h5py.File("/scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/inject_edgb_005/outdir_bbh_injection/final_result/bbh_injection_data0_1135136350-637_analysis_H1L1_merge_result.hdf5", 'r')
data = data['posterior']
ndim = len(labels)
corner_model = np.zeros((17159, ndim))
for i in range(ndim):
    corner_model[:, i] = data[labels[i]]

fig = corner.corner(corner_model, labels=labels, color='blue',
                    levels=(0.5,0.9), scale_hist=True, plot_datapoints=False)


axes = np.array(fig.axes).reshape((ndim, ndim))
value1 = [28.192325962244016, 0.8571428571428571, 0.5, 0.1, 200, 0.1, 0.2, 0.4, 0.3, 0.2, 0.05]
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


#corner.overplot_lines(fig, value_inject, color="C1")
#plt.show()
plt.savefig('edgb_inject.pdf',dpi=1000)
