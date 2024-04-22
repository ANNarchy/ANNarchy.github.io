all: quartodoc quarto

quartodoc:
	rm -rf reference/*
	quartodoc build

reference: quartodoc
	quarto render reference

manual_targets := $(wildcard manual/*.qmd)
manual: $(manual_targets)
	quarto render $?

notebooks_targets := $(wildcard notebooks/*.ipynb)
notebooks: $(notebooks_targets)
	quarto render $?

quarto:
	quarto render .