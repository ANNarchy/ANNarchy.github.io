# Documentation for ANNarchy

The documentation is at <https://annarchy.github.io>. 

Generating the documentation requires **Quarto** (<https://quarto.org>) and `quartodoc` (<https://github.com/machow/quartodoc>, `pip install quartodoc`) for the API.

Rendering the quarto files requires a **Python** environment with the following packages (+ their dependencies):
- `ANNarchy`
- `jupyter`

To also run the notebooks (e.g. with updated ANNarchy version), you additionally need:
- `scikit-learn`
- `tensorflow==2.17`
- `tensorboardX`
- `hyperopt`

First remove old files:

```bash
git clean -fdx
rm -rf reference
```

Optionally, run all notebooks (with current ANNarchy version) under `notebooks/`:

```bash
./run_notebooks.sh
```

Build the API (directory `reference/`):

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
git clean -fdx
```

Also push to master branch.
