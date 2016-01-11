#
# Time-stamp: <Makefile  30 Oct 12 10:57:02>
#

LATEX=latex
LATEXOPTS=
BIBTEX=bibtex
PSPDF=ps2pdf
DVIPS=dvips

UNDEFINED="((Reference|Citation).*undefined)|(Label.*multiply defined)"
RERUN="There were undefined references|Rerun to get (cross-references|the bars) right"

PREFIXNAME=bibtex
BIBFILE=bibtex.bib
DIRNAME=BibTeX
TARNAME=bibtex.taz
ALLSRCFILES=$(PREFIXNAME).tex

ifneq ($(LATEX),pdflatex)
$(PREFIXNAME).pdf: $(PREFIXNAME).ps
	$(PSPDF) $<
else
$(PREFIXNAME).pdf: $(PREFIXNAME).tex $(PREFIXNAME).bbl
	-$(LATEX) $(LATEXOPTS) $<
endif

$(PREFIXNAME).ps: $(PREFIXNAME).dvi
	$(DVIPS) $<

$(PREFIXNAME).bbl: $(PREFIXNAME).tex $(BIBFILE) $(PREFIXNAME).aux
	$(BIBTEX) $(basename $<)
	-$(LATEX) $(LATEXOPTS) $<
	-$(LATEX) $(LATEXOPTS) $<

$(PREFIXNAME).dvi: $(ALLSRCFILES) $(BIBFILE) $(PREFIXNAME).log $(PREFIXNAME).bbl
	@if egrep -q $(RERUN) $(PREFIXNAME).log ; then $(LATEX) $<; fi
	@if egrep -i $(UNDEFINED) $(PREFIXNAME).log; then echo '*** ERRORS or WARNINGS ***'; fi

%.aux: %.tex
	$(LATEX) $(LATEXOPTS) $<

%.log: %.tex
	$(LATEX) $(LATEXOPTS) $<

clean:
	-rm *.aux *.bbl *.blg *.log

tar: $(TARNAME)

$(TARNAME): clean
	-rm $(TARNAME) $(TARNAME).gpg 
	(cd ..; tar zcvf $(TARNAME) $(DIRNAME) )
	mv ../$(TARNAME) .
