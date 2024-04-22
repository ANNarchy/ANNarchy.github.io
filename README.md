# Documentation for ANNarchy

The documentation is at <https://annarchy.github.io>. 

Generating the documentation requires **Quarto** (<https://quarto.org>) and `quartodoc` (<https://github.com/machow/quartodoc>, `pip install quartodoc`) for the API. 

First build the API:

```bash
quartodoc build
```

Preview the doc:

```bash
quarto preview
```

Push it to github:

```bash
quarto publish gh-pages
```
