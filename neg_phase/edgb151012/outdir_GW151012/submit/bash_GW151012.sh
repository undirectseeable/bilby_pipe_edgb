#!/usr/bin/env bash

# GW151012_data0_1128678900-4_generation
# PARENTS 
# CHILDREN GW151012_data0_1128678900-4_analysis_H1L1_par0 GW151012_data0_1128678900-4_analysis_H1L1_par1
if [[ "GW151012_data0_1128678900-4_generation" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_generation outdir_GW151012/GW151012_config_complete.ini --label GW151012_data0_1128678900-4_generation --idx 0 --trigger-time 1128678900.4 --outdir outdir_GW151012"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_generation outdir_GW151012/GW151012_config_complete.ini --label GW151012_data0_1128678900-4_generation --idx 0 --trigger-time 1128678900.4 --outdir outdir_GW151012
fi

# GW151012_data0_1128678900-4_analysis_H1L1_par0
# PARENTS GW151012_data0_1128678900-4_generation
# CHILDREN GW151012_data0_1128678900-4_analysis_H1L1_merge
if [[ "GW151012_data0_1128678900-4_analysis_H1L1_par0" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW151012/GW151012_config_complete.ini --outdir outdir_GW151012 --detectors H1 --detectors L1 --label GW151012_data0_1128678900-4_analysis_H1L1_par0 --data-dump-file outdir_GW151012/data/GW151012_data0_1128678900-4_generation_data_dump.pickle --sampler dynesty"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW151012/GW151012_config_complete.ini --outdir outdir_GW151012 --detectors H1 --detectors L1 --label GW151012_data0_1128678900-4_analysis_H1L1_par0 --data-dump-file outdir_GW151012/data/GW151012_data0_1128678900-4_generation_data_dump.pickle --sampler dynesty
fi

# GW151012_data0_1128678900-4_analysis_H1L1_par1
# PARENTS GW151012_data0_1128678900-4_generation
# CHILDREN GW151012_data0_1128678900-4_analysis_H1L1_merge
if [[ "GW151012_data0_1128678900-4_analysis_H1L1_par1" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW151012/GW151012_config_complete.ini --outdir outdir_GW151012 --detectors H1 --detectors L1 --label GW151012_data0_1128678900-4_analysis_H1L1_par1 --data-dump-file outdir_GW151012/data/GW151012_data0_1128678900-4_generation_data_dump.pickle --sampler dynesty"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW151012/GW151012_config_complete.ini --outdir outdir_GW151012 --detectors H1 --detectors L1 --label GW151012_data0_1128678900-4_analysis_H1L1_par1 --data-dump-file outdir_GW151012/data/GW151012_data0_1128678900-4_generation_data_dump.pickle --sampler dynesty
fi

# GW151012_data0_1128678900-4_analysis_H1L1_merge
# PARENTS GW151012_data0_1128678900-4_analysis_H1L1_par0 GW151012_data0_1128678900-4_analysis_H1L1_par1
# CHILDREN GW151012_data0_1128678900-4_analysis_H1L1_merge_final_result
if [[ "GW151012_data0_1128678900-4_analysis_H1L1_merge" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW151012/result/GW151012_data0_1128678900-4_analysis_H1L1_par0_result.hdf5 outdir_GW151012/result/GW151012_data0_1128678900-4_analysis_H1L1_par1_result.hdf5 --outdir outdir_GW151012/result --label GW151012_data0_1128678900-4_analysis_H1L1_merge --extension hdf5 --merge"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW151012/result/GW151012_data0_1128678900-4_analysis_H1L1_par0_result.hdf5 outdir_GW151012/result/GW151012_data0_1128678900-4_analysis_H1L1_par1_result.hdf5 --outdir outdir_GW151012/result --label GW151012_data0_1128678900-4_analysis_H1L1_merge --extension hdf5 --merge
fi

# GW151012_data0_1128678900-4_analysis_H1L1_merge_final_result
# PARENTS GW151012_data0_1128678900-4_analysis_H1L1_merge
# CHILDREN 
if [[ "GW151012_data0_1128678900-4_analysis_H1L1_merge_final_result" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW151012/result/GW151012_data0_1128678900-4_analysis_H1L1_merge_result.hdf5 --outdir outdir_GW151012/final_result --extension hdf5 --max-samples 20000 --lightweight --save"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW151012/result/GW151012_data0_1128678900-4_analysis_H1L1_merge_result.hdf5 --outdir outdir_GW151012/final_result --extension hdf5 --max-samples 20000 --lightweight --save
fi

