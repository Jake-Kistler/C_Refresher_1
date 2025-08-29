# Top-level Makefile to build and test all sorting algorithms
# Usage:
#   make all        # build all prog.x files
#   make check      # run correctness tests in all subfolders
#   make valgrind   # run valgrind checks in all subfolders
#   make clean      # clean all subfolders

SUBDIRS = Bubble Insertion Merge Selection Quick

.PHONY: all check valgrind clean $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

check:
	@for dir in $(SUBDIRS); do \
		echo ">>> Running tests in $$dir..."; \
		$(MAKE) -C $$dir check || exit 1; \
	done

valgrind:
	@for dir in $(SUBDIRS); do \
		echo ">>> Running valgrind in $$dir..."; \
		$(MAKE) -C $$dir valgrind || exit 1; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		echo ">>> Cleaning $$dir..."; \
		$(MAKE) -C $$dir clean; \
	done
