.PHONY: output-cpp

cpp: manyclients.bidl output-cpp
	../../bidl2sl/bidl2sl *.bidl
	$(MAKE) -C cpp

clean:
	rm -rf output-cpp
	$(MAKE) -C cpp clean
