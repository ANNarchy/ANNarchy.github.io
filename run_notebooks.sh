#!/bin/bash
KERNEL_NAME=base        # which conda environment should be used
KERNEL_TIMEOUT=60       # max time for an individual cell

for nb in notebooks/*.ipynb; do
  mkdir notebooks/runs
  echo "Running $nb"
  jupyter nbconvert --ExecutePreprocessor.kernel_name=$KERNEL_NAME --ExecutePreprocessor.timeout=$KERNEL_TIMEOUT --to notebook --execute --inplace "$nb"
  rm -rf notebooks/annarchy notebooks/runs
done
