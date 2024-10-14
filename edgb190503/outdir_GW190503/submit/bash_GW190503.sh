#!/usr/bin/env bash

# GW190503_data0_1240944862-2_generation
# PARENTS 
# CHILDREN GW190503_data0_1240944862-2_analysis_H1L1_par0 GW190503_data0_1240944862-2_analysis_H1L1_par1
if [[ "GW190503_data0_1240944862-2_generation" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_generation outdir_GW190503/GW190503_config_complete.ini --label GW190503_data0_1240944862-2_generation --idx 0 --trigger-time 1240944862.2 --outdir outdir_GW190503"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_generation outdir_GW190503/GW190503_config_complete.ini --label GW190503_data0_1240944862-2_generation --idx 0 --trigger-time 1240944862.2 --outdir outdir_GW190503
fi

# GW190503_data0_1240944862-2_analysis_H1L1_par0
# PARENTS GW190503_data0_1240944862-2_generation
# CHILDREN GW190503_data0_1240944862-2_analysis_H1L1_merge
if [[ "GW190503_data0_1240944862-2_analysis_H1L1_par0" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW190503/GW190503_config_complete.ini --outdir outdir_GW190503 --detectors H1 --detectors L1 --label GW190503_data0_1240944862-2_analysis_H1L1_par0 --data-dump-file outdir_GW190503/data/GW190503_data0_1240944862-2_generation_data_dump.pickle --sampler dynesty"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW190503/GW190503_config_complete.ini --outdir outdir_GW190503 --detectors H1 --detectors L1 --label GW190503_data0_1240944862-2_analysis_H1L1_par0 --data-dump-file outdir_GW190503/data/GW190503_data0_1240944862-2_generation_data_dump.pickle --sampler dynesty
fi

# GW190503_data0_1240944862-2_analysis_H1L1_par1
# PARENTS GW190503_data0_1240944862-2_generation
# CHILDREN GW190503_data0_1240944862-2_analysis_H1L1_merge
if [[ "GW190503_data0_1240944862-2_analysis_H1L1_par1" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW190503/GW190503_config_complete.ini --outdir outdir_GW190503 --detectors H1 --detectors L1 --label GW190503_data0_1240944862-2_analysis_H1L1_par1 --data-dump-file outdir_GW190503/data/GW190503_data0_1240944862-2_generation_data_dump.pickle --sampler dynesty"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW190503/GW190503_config_complete.ini --outdir outdir_GW190503 --detectors H1 --detectors L1 --label GW190503_data0_1240944862-2_analysis_H1L1_par1 --data-dump-file outdir_GW190503/data/GW190503_data0_1240944862-2_generation_data_dump.pickle --sampler dynesty
fi

# GW190503_data0_1240944862-2_analysis_H1L1_merge
# PARENTS GW190503_data0_1240944862-2_analysis_H1L1_par0 GW190503_data0_1240944862-2_analysis_H1L1_par1
# CHILDREN GW190503_data0_1240944862-2_analysis_H1L1_merge_final_result
if [[ "GW190503_data0_1240944862-2_analysis_H1L1_merge" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW190503/result/GW190503_data0_1240944862-2_analysis_H1L1_par0_result.hdf5 outdir_GW190503/result/GW190503_data0_1240944862-2_analysis_H1L1_par1_result.hdf5 --outdir outdir_GW190503/result --label GW190503_data0_1240944862-2_analysis_H1L1_merge --extension hdf5 --merge"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW190503/result/GW190503_data0_1240944862-2_analysis_H1L1_par0_result.hdf5 outdir_GW190503/result/GW190503_data0_1240944862-2_analysis_H1L1_par1_result.hdf5 --outdir outdir_GW190503/result --label GW190503_data0_1240944862-2_analysis_H1L1_merge --extension hdf5 --merge
fi

# GW190503_data0_1240944862-2_analysis_H1L1_merge_final_result
# PARENTS GW190503_data0_1240944862-2_analysis_H1L1_merge
# CHILDREN 
if [[ "GW190503_data0_1240944862-2_analysis_H1L1_merge_final_result" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW190503/result/GW190503_data0_1240944862-2_analysis_H1L1_merge_result.hdf5 --outdir outdir_GW190503/final_result --extension hdf5 --max-samples 20000 --lightweight --save"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW190503/result/GW190503_data0_1240944862-2_analysis_H1L1_merge_result.hdf5 --outdir outdir_GW190503/final_result --extension hdf5 --max-samples 20000 --lightweight --save
fi

