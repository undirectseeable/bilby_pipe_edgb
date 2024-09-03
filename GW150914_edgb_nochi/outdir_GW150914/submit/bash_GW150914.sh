#!/usr/bin/env bash

# GW150914_data0_1126259462-4_generation
# PARENTS 
# CHILDREN GW150914_data0_1126259462-4_analysis_H1L1_par0 GW150914_data0_1126259462-4_analysis_H1L1_par1
if [[ "GW150914_data0_1126259462-4_generation" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_generation outdir_GW150914/GW150914_config_complete.ini --label GW150914_data0_1126259462-4_generation --idx 0 --trigger-time 1126259462.4 --outdir outdir_GW150914"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_generation outdir_GW150914/GW150914_config_complete.ini --label GW150914_data0_1126259462-4_generation --idx 0 --trigger-time 1126259462.4 --outdir outdir_GW150914
fi

# GW150914_data0_1126259462-4_analysis_H1L1_par0
# PARENTS GW150914_data0_1126259462-4_generation
# CHILDREN GW150914_data0_1126259462-4_analysis_H1L1_merge
if [[ "GW150914_data0_1126259462-4_analysis_H1L1_par0" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW150914/GW150914_config_complete.ini --outdir outdir_GW150914 --detectors H1 --detectors L1 --label GW150914_data0_1126259462-4_analysis_H1L1_par0 --data-dump-file outdir_GW150914/data/GW150914_data0_1126259462-4_generation_data_dump.pickle --sampler dynesty"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW150914/GW150914_config_complete.ini --outdir outdir_GW150914 --detectors H1 --detectors L1 --label GW150914_data0_1126259462-4_analysis_H1L1_par0 --data-dump-file outdir_GW150914/data/GW150914_data0_1126259462-4_generation_data_dump.pickle --sampler dynesty
fi

# GW150914_data0_1126259462-4_analysis_H1L1_par1
# PARENTS GW150914_data0_1126259462-4_generation
# CHILDREN GW150914_data0_1126259462-4_analysis_H1L1_merge
if [[ "GW150914_data0_1126259462-4_analysis_H1L1_par1" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW150914/GW150914_config_complete.ini --outdir outdir_GW150914 --detectors H1 --detectors L1 --label GW150914_data0_1126259462-4_analysis_H1L1_par1 --data-dump-file outdir_GW150914/data/GW150914_data0_1126259462-4_generation_data_dump.pickle --sampler dynesty"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_pipe_analysis outdir_GW150914/GW150914_config_complete.ini --outdir outdir_GW150914 --detectors H1 --detectors L1 --label GW150914_data0_1126259462-4_analysis_H1L1_par1 --data-dump-file outdir_GW150914/data/GW150914_data0_1126259462-4_generation_data_dump.pickle --sampler dynesty
fi

# GW150914_data0_1126259462-4_analysis_H1L1_merge
# PARENTS GW150914_data0_1126259462-4_analysis_H1L1_par0 GW150914_data0_1126259462-4_analysis_H1L1_par1
# CHILDREN GW150914_data0_1126259462-4_analysis_H1L1_merge_final_result
if [[ "GW150914_data0_1126259462-4_analysis_H1L1_merge" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW150914/result/GW150914_data0_1126259462-4_analysis_H1L1_par0_result.hdf5 outdir_GW150914/result/GW150914_data0_1126259462-4_analysis_H1L1_par1_result.hdf5 --outdir outdir_GW150914/result --label GW150914_data0_1126259462-4_analysis_H1L1_merge --extension hdf5 --merge"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW150914/result/GW150914_data0_1126259462-4_analysis_H1L1_par0_result.hdf5 outdir_GW150914/result/GW150914_data0_1126259462-4_analysis_H1L1_par1_result.hdf5 --outdir outdir_GW150914/result --label GW150914_data0_1126259462-4_analysis_H1L1_merge --extension hdf5 --merge
fi

# GW150914_data0_1126259462-4_analysis_H1L1_merge_final_result
# PARENTS GW150914_data0_1126259462-4_analysis_H1L1_merge
# CHILDREN 
if [[ "GW150914_data0_1126259462-4_analysis_H1L1_merge_final_result" == *"$1"* ]]; then
    echo "Running: /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW150914/result/GW150914_data0_1126259462-4_analysis_H1L1_merge_result.hdf5 --outdir outdir_GW150914/final_result --extension hdf5 --max-samples 20000 --lightweight --save"
    /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs/bin/bilby_result --result outdir_GW150914/result/GW150914_data0_1126259462-4_analysis_H1L1_merge_result.hdf5 --outdir outdir_GW150914/final_result --extension hdf5 --max-samples 20000 --lightweight --save
fi

