.PHONY: all
all:
	$(MAKE) -C build

.PHONY: kriti
kriti:
	$(MAKE) -C build kriti

.PHONY: redep
redep:
	mkdir -p build/ ; cd build/ ; cmake .. ; cd ..

.PHONY: clean
clean:
	$(MAKE) -C build clean

.PHONY: distclean
distclean:
	$(MAKE) -C build clean
	rm -rf build
