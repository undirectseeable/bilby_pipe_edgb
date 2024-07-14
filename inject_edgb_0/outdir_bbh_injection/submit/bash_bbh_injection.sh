#!/usr/bin/env bash

# bbh_injection_data0_1135136350-637_generation
# PARENTS 
# CHILDREN bbh_injection_data0_1135136350-637_analysis_H1L1_par0 bbh_injection_data0_1135136350-637_analysis_H1L1_par1
if [[ "bbh_injection_data0_1135136350-637_generation" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_generation outdir_bbh_injection/bbh_injection_config_complete.ini --label bbh_injection_data0_1135136350-637_generation --idx 0 --trigger-time 1135136350.637 --outdir outdir_bbh_injection"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_generation outdir_bbh_injection/bbh_injection_config_complete.ini --label bbh_injection_data0_1135136350-637_generation --idx 0 --trigger-time 1135136350.637 --outdir outdir_bbh_injection
fi

# bbh_injection_data0_1135136350-637_analysis_H1L1_par0
# PARENTS bbh_injection_data0_1135136350-637_generation
# CHILDREN bbh_injection_data0_1135136350-637_analysis_H1L1_merge
if [[ "bbh_injection_data0_1135136350-637_analysis_H1L1_par0" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_bbh_injection/bbh_injection_config_complete.ini --outdir outdir_bbh_injection --detectors H1 --detectors L1 --label bbh_injection_data0_1135136350-637_analysis_H1L1_par0 --data-dump-file outdir_bbh_injection/data/bbh_injection_data0_1135136350-637_generation_data_dump.pickle --sampler dynesty"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_bbh_injection/bbh_injection_config_complete.ini --outdir outdir_bbh_injection --detectors H1 --detectors L1 --label bbh_injection_data0_1135136350-637_analysis_H1L1_par0 --data-dump-file outdir_bbh_injection/data/bbh_injection_data0_1135136350-637_generation_data_dump.pickle --sampler dynesty
fi

# bbh_injection_data0_1135136350-637_analysis_H1L1_par1
# PARENTS bbh_injection_data0_1135136350-637_generation
# CHILDREN bbh_injection_data0_1135136350-637_analysis_H1L1_merge
if [[ "bbh_injection_data0_1135136350-637_analysis_H1L1_par1" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_bbh_injection/bbh_injection_config_complete.ini --outdir outdir_bbh_injection --detectors H1 --detectors L1 --label bbh_injection_data0_1135136350-637_analysis_H1L1_par1 --data-dump-file outdir_bbh_injection/data/bbh_injection_data0_1135136350-637_generation_data_dump.pickle --sampler dynesty"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_bbh_injection/bbh_injection_config_complete.ini --outdir outdir_bbh_injection --detectors H1 --detectors L1 --label bbh_injection_data0_1135136350-637_analysis_H1L1_par1 --data-dump-file outdir_bbh_injection/data/bbh_injection_data0_1135136350-637_generation_data_dump.pickle --sampler dynesty
fi

# bbh_injection_data0_1135136350-637_analysis_H1L1_merge
# PARENTS bbh_injection_data0_1135136350-637_analysis_H1L1_par0 bbh_injection_data0_1135136350-637_analysis_H1L1_par1
# CHILDREN bbh_injection_data0_1135136350-637_analysis_H1L1_merge_final_result
if [[ "bbh_injection_data0_1135136350-637_analysis_H1L1_merge" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_bbh_injection/result/bbh_injection_data0_1135136350-637_analysis_H1L1_par0_result.hdf5 outdir_bbh_injection/result/bbh_injection_data0_1135136350-637_analysis_H1L1_par1_result.hdf5 --outdir outdir_bbh_injection/result --label bbh_injection_data0_1135136350-637_analysis_H1L1_merge --extension hdf5 --merge"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_bbh_injection/result/bbh_injection_data0_1135136350-637_analysis_H1L1_par0_result.hdf5 outdir_bbh_injection/result/bbh_injection_data0_1135136350-637_analysis_H1L1_par1_result.hdf5 --outdir outdir_bbh_injection/result --label bbh_injection_data0_1135136350-637_analysis_H1L1_merge --extension hdf5 --merge
fi

# bbh_injection_data0_1135136350-637_analysis_H1L1_merge_final_result
# PARENTS bbh_injection_data0_1135136350-637_analysis_H1L1_merge
# CHILDREN 
if [[ "bbh_injection_data0_1135136350-637_analysis_H1L1_merge_final_result" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_bbh_injection/result/bbh_injection_data0_1135136350-637_analysis_H1L1_merge_result.hdf5 --outdir outdir_bbh_injection/final_result --extension hdf5 --max-samples 20000 --lightweight --save"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_bbh_injection/result/bbh_injection_data0_1135136350-637_analysis_H1L1_merge_result.hdf5 --outdir outdir_bbh_injection/final_result --extension hdf5 --max-samples 20000 --lightweight --save
fi

