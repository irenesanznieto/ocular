#!/bin/bash

latex thesis
bibtex thesis
latex thesis
pdflatex thesis

rm *.aux *.log *.bbl *.dvi *.blg *.toc *.lof *.out

