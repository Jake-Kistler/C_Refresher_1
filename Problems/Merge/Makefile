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
	@printf "5\n3.9\n4.1\n4.0\n-2\n0\n"          > tests/t_normal.txt
	@printf "0\n"                                  > tests/t_zero.txt
	@printf "1\n42\n"                              > tests/t_one.txt
	@printf "6\n-1\n-1\n2.5\n2.5\n2.5\n-3\n"       > tests/t_dups_negs.txt
	@printf "5\n9\n7\n5\n3\n1\n"                   > tests/t_rev.txt
	@/usr/bin/printf '%s\n' -5                                 > tests/t_badcount.txt

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

clean:
	rm -f $(PROG) *.o out.tmp
	rm -rf tests
