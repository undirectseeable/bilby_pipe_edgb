#!/bin/bash
#SBATCH --partition=standard
#SBATCH --ntasks=2
#SBATCH --time=3-00:00:00
#SBATCH --account=kentyagi
#SBATCH --mem=40000
#SBATCH --mail-type=END
#SBATCH --mail-user=nj2nu


module load anaconda
source activate /scratch/nj2nu/dynesty_inf//bilby_pipe_edgb/envs

bash ./outdir_GW151012/submit/bash_GW151012.sh analysis

