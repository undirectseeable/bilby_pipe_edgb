#!/bin/bash
#SBATCH --partition=standard
#SBATCH --ntasks=2
#SBATCH --time=3-00:00:00
#SBATCH --account=kentyagi
#SBATCH --mem=40000
#SBATCH --mail-type=END
#SBATCH --mail-user=nj2nu


module load anaconda
source activate /scratch/nj2nu/non_GR/BBH_dataset/gw150914_xas/github_repo/bilby_pipe_edgb/envs

bash ./outdir_bbh_injection/submit/bash_bbh_injection.sh analysis

