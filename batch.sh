#!/bin/bash -l
#SBATCH --mem=4g
#SBATCH -o /pine/scr/c/b/cbartram/myOut$1
#SBATCH -e /pine/scr/c/b/cbartram/myErr$1
#SBATCH -t 04:00:00 
#SBATCH -n 1

# run the analysis command
/nas/longleaf/home/cbartram/Caliope_Analysis/AnalysisCodeApril2018/caliope $1 $1
