#!/bin/bash

for nb in notebooks/*.ipynb; do
  echo "Running $nb"
  jupyter nbconvert --to notebook --execute --inplace "$nb"
  rm -rf notebooks/annarchy notebooks/runs
done
