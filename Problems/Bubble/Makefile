# Makefile for Quick Sort (floats)
# Usage:
#   make            # build prog.x
#   make run        # demo run with tests/t_normal.txt -> tests/out_normal.txt
#   make tests      # generate test inputs
#   make check      # run program on all tests
#   make valgrind   # leak checks on success + failure paths
#   make clean

CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -std=c11 -g
PROG    = prog.x
SRC     = prog.c

.PHONY: all run tests check valgrind clean

all: $(PROG)

$(PROG): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(PROG)

tests:
	@mkdir -p tests
	@printf "5\n3.9\n4.1\n4.0\n-2\n0\n"            > tests/t_normal.txt
	@printf "0\n"                                  > tests/t_zero.txt
	@printf "1\n42\n"                              > tests/t_one.txt
	@printf "6\n-1\n-1\n2.5\n2.5\n2.5\n-3\n"       > tests/t_dups_negs.txt
	@printf "5\n9\n7\n5\n3\n1\n"                   > tests/t_rev.txt
	@printf '%s\n' -5                              > tests/t_badcount.txt

run: all tests
	./$(PROG) tests/t_normal.txt tests/out_normal.txt
	@echo "Wrote tests/out_normal.txt"

check: all tests
	./$(PROG) tests/t_zero.txt tests/out_zero.txt
	./$(PROG) tests/t_one.txt tests/out_one.txt
	./$(PROG) tests/t_normal.txt tests/out_normal.txt
	./$(PROG) tests/t_dups_negs.txt tests/out_dups_negs.txt
	./$(PROG) tests/t_rev.txt tests/out_rev.txt
	@echo "OK: ran all success-path tests."

valgrind: all tests
	# success paths (no leaks)
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_zero.txt tests/out_zero.txt
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_one.txt tests/out_one.txt
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_normal.txt tests/out_normal.txt
	# failure paths (still no leaks)
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_badcount.txt out.tmp || true
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/NOFILE.txt out.tmp || true

	# --- Coverage with gcov ---
COVFLAGS = -fprofile-arcs -ftest-coverage -O0

coverage: clean
	# two-step build so .gcno is definitely produced
	$(CC) $(CFLAGS) $(COVFLAGS) -c $(SRC) -o $(OBJ)
	$(CC) $(CFLAGS) $(COVFLAGS) $(OBJ) -o $(PROG) $(LIBS)
	# reuse your test inputs
	$(MAKE) tests >/dev/null

	# success-path runs (produce .gcda)
	./$(PROG) tests/t_one.txt   tests/out_one.txt
	./$(PROG) tests/t_three.txt tests/out_three.txt
	./$(PROG) tests/t_five.txt  tests/out_five.txt

	# error-path runs (exercise die(...) branches)
	-./$(PROG) tests/t_badcount.txt       out.tmp || true
	-./$(PROG) tests/t_badcount_zero.txt  out.tmp || true
	-./$(PROG) tests/t_badnum.txt         out.tmp || true
	-./$(PROG) tests/NOFILE.txt           out.tmp || true

	# also hit "failed to open output" by writing to a directory
	@mkdir -p tests/out_dir
	-./$(PROG) tests/t_one.txt tests/out_dir || true

	# also hit "usage" path (argc != 3)
	-./$(PROG) || true

	$(MAKE) gcov

gcov:
	@echo
	@echo "==== gcov report ($(SRC)) ===="
	@gcov -b -o . $(SRC) | sed 's/^/  /'

clean:
	rm -f $(PROG) *.o out.tmp
	rm -rf tests
