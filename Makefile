.PHONY: all
all:
	$(MAKE) -C build

.PHONY: redep
redep:
	cd build/ ; cmake .. ; cd ..
