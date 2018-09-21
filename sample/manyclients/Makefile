ifeq ($(shell if [ -f /opt/compiler/gcc-4.8.2/bin/make ]; then echo "yes"; else echo "no"; fi;), yes)
	export CXX=/opt/compiler/gcc-4.8.2/bin/g++
	export CC=/opt/compiler/gcc-4.8.2/bin/gcc
	export AR=/opt/compiler/gcc-4.8.2/bin/ar
	export MAKE=/opt/compiler/gcc-4.8.2/bin/make
	export BIDL2SL=../../output/gcc482/bidl2sl
else
	export BIDL2SL=../../output/bidl2sl
endif

.PHONY: output-cpp

cpp: manyclients.bidl output-cpp
	$(BIDL2SL) *.bidl
	$(MAKE) -C cpp

clean:
	rm -rf output-cpp
	$(MAKE) -C cpp clean
