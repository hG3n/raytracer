# -*- Mode:Makefile -*-

%.o:	%.cpp Makefile
	-$(RM) $@
	$(CXX) $(CXXFLAGS) $(CXXINCLUDE) $(CXXDEFINES) -c -o $@ $<

# auto dependency generation; see gnu make manual ch. 4.12
# - set -e makes the rule fail on the first failing pipe stage (sh semantics)
# - compiler generates deps
# - 1st sed script removes *.c[++].o (2.95 cpp buggy!)
# - 2nd sed script transforms <main.o: main.c main.h> into <main.o main.d : main.c main.h>
# - if the resulting .d file is empty it gets removed to be considered at the next make
#   run again
%.d:    %.cpp Makefile
	@if [ -s $@ ]; then \
	  echo "updating $@ from $<"; \
	else \
	  echo "creating $@ from $<"; \
	fi
	@set -e; $(CXX) $(CXXFLAGS) -M $(CXXINCLUDE) $(CXXDEFINES) $< \
	 | sed -e 's/\($*\)\.cpp\.o/\1.o/g' -e 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	 [ -s $@ ] || $(RM) $@

.PHONY:		clean realclean test

# default cleanup target
clean::
	@echo "making clean in $(PWD)..." 
	@if [ ! -z "$(OBJECTS)" ] ; then \
	  $(RM) $(OBJECTS) ; \
	fi

# default real cleanup target
realclean::	clean
	@echo "making realclean in $(PWD)..."
	@if [ ! -z "$(OBJECTS:.o=.d)" ] ; then \
	  $(RM) $(OBJECTS:.o=.d) ; \
	fi
	-$(RM) core core.[0-9]* trace.log par.log log so_locations .depend
	-$(RM) -r ii_files rii_files ti_files *.rpo
	-$(RM) *~ *.pix* *.Counts *.i *.ii *.s

test::		$(PROGRAMS)
	@if [ ! -z "$(PROGRAMS)" ] ; then \
	  for prg in $(PROGRAMS); do \
	    (echo "-> testing $$prg..." ; ./$$prg ; echo "<- done."); \
	  done \
	fi
