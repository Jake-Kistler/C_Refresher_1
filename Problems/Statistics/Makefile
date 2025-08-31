# Makefile for Statistics (min/max/avg/std)
# Usage:
#   make            # build prog.x
#   make run        # demo run with tests/t_three.txt -> tests/out_three.txt
#   make tests      # generate test inputs
#   make check      # run program on success-path tests
#   make valgrind   # leak checks on success + failure paths
#   make coverage   # rebuild with gcov flags, run all tests, show report
#   make clean

CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -std=c11 -g
PROG    = prog.x
SRC     = prog.c
OBJ     = prog.o
LIBS    = -lm

.PHONY: all run tests check valgrind clean coverage gcov

all: $(PROG)

$(PROG): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(PROG) $(LIBS)

run: all tests
	@echo "Demo run: tests/t_three.txt -> tests/out_three.txt"
	./$(PROG) tests/t_three.txt tests/out_three.txt
	@echo "Output written to tests/out_three.txt"

tests:
	@rm -rf tests && mkdir -p tests
	# ---- success-path inputs ----
	# one value
	@printf "1\n5\n" > tests/t_one.txt
	# three values
	@printf "3\n3.9\n4.1\n4.0\n" > tests/t_three.txt
	# another simple case
	@printf "5\n1\n1\n1\n1\n1\n" > tests/t_five.txt

	# ---- failure-path inputs ----
	# non-integer count
	@printf "n\n" > tests/t_badcount.txt
	# zero count
	@printf "0\n" > tests/t_badcount_zero.txt
	# invalid number in data at position 2 of 3
	@printf "3\n1\nx\n2\n" > tests/t_badnum.txt

check: all tests
	./$(PROG) tests/t_one.txt tests/out_one.txt
	./$(PROG) tests/t_three.txt tests/out_three.txt
	./$(PROG) tests/t_five.txt tests/out_five.txt
	@echo "OK: ran all success-path tests."

valgrind: all tests
	# success paths (no leaks)
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_one.txt /dev/null
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_three.txt /dev/null
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_five.txt /dev/null
	# failure paths (still no leaks / graceful exit)
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_badcount.txt out.tmp || true
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_badcount_zero.txt out.tmp || true
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_badnum.txt out.tmp || true
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/NOFILE.txt out.tmp || true

clean:
	rm -f $(PROG) $(OBJ) *.o out.tmp
	rm -rf tests *.gcda *.gcno *.gcov

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
