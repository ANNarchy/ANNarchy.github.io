# Documentation for ANNarchy

The documentation is at <https://annarchy.github.io>. 

Generating the documentation requires **Quarto** (<https://quarto.org>) and `quartodoc` (<https://github.com/machow/quartodoc>, `pip install quartodoc`) for the API.

Rendering the quarto files requires a **Python** environment with the following packages (+ their dependencies):
- `ANNarchy`
- `jupyter`

To also render the notebooks, you additionally need:
- `scikit-learn`
- `tensorflow==2.17`
- ... TODO

First remove old files:

```bash
rm -rf .quarto docs reference manual/annarchy notebooks/annarchy
```

Optionally, run all notebooks (with current ANNarchy version) under `notebooks/`:

```bash
jupyter nbconvert --to notebook --execute --inplace notebooks/*.ipynb
```

Build the API:

```bash
quartodoc build
```

Preview the doc (also renders everything):

```bash
quarto preview
```

Push it to github:

```bash
quarto publish gh-pages
```

Optionally, remove untracked files:

```bash
rm -rf .quarto docs manual/annarchy notebooks/annarchy
```

Also push to master branch.
