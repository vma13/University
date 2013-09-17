# -*- mode: makefile -*-

MAIN       = main

LATEXMK    = latexmk -r latexmkrc

pdfc:	
	$(LATEXMK) -pdf -pvc $(MAIN)

pdf:	
	$(LATEXMK) -pdf $(MAIN)

clean:
	$(LATEXMK) -C $(MAIN)
