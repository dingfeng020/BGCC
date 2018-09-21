all:
	$(MAKE) -f Makefile.default clean
	$(MAKE) -f Makefile.default
ifeq ($(shell if [ -f /opt/compiler/gcc-4.8.2/bin/make ]; then echo "yes"; else echo "no"; fi;), yes)
	/opt/compiler/gcc-4.8.2/bin/make -f Makefile.gcc482 clean
	/opt/compiler/gcc-4.8.2/bin/make -f Makefile.gcc482
endif


clean:
	$(MAKE) -f Makefile.default clean

ifeq ($(shell if [ -f /opt/compiler/gcc-4.8.2/bin/make ]; then echo "yes"; else echo "no"; fi;), yes)
	/opt/compiler/gcc-4.8.2/bin/make -f Makefile.gcc482 clean
endif

