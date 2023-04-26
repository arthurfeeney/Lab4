#!/bin/bash
#SBATCH --job-name=parcomp-lab4      	## Name of the job.
#SBATCH -A class-eecs120      		## Account to charge
#SBATCH -p standard          		## Partition/queue name
#SBATCH --nodes=1            		## Request 1 node
#SBATCH --cpus-per-task=16  		## Number of threads per task (OMP threads)

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./lab4

