# Makefile for Histogram
# Usage:
#   make            # build prog.x
#   make run        # demo run with tests/t_small.txt -> tests/out_small.txt
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
LIBS    = 

.PHONY: all run tests check valgrind clean coverage gcov

all: $(PROG)

$(PROG): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(PROG) $(LIBS)

run: all tests
	@echo "Demo run: tests/t_small.txt -> tests/out_small.txt"
	./$(PROG) tests/t_small.txt tests/out_small.txt
	@echo "Output written to tests/out_small.txt"

tests:
	@rm -rf tests && mkdir -p tests
	# ---- success-path inputs ----
	@echo "abcab" > tests/t_small.txt
	@echo "The quick brown fox jumps over the lazy dog" > tests/t_sentence.txt

	# ---- failure-path inputs ----
	@touch tests/empty.txt

check: all tests
	./$(PROG) tests/t_small.txt tests/out_small.txt
	./$(PROG) tests/t_sentence.txt tests/out_sentence.txt
	@echo "OK: ran all success-path tests."

valgrind: all tests
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_small.txt /dev/null
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_sentence.txt /dev/null
	# failure paths
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) NOFILE.txt out.tmp || true

clean:
	rm -f $(PROG) $(OBJ) *.o out.tmp
	rm -rf tests *.gcda *.gcno *.gcov

# --- Coverage with gcov ---
COVFLAGS = -fprofile-arcs -ftest-coverage -O0

coverage: clean
	$(CC) $(CFLAGS) $(COVFLAGS) -c $(SRC) -o $(OBJ)
	$(CC) $(CFLAGS) $(COVFLAGS) $(OBJ) -o $(PROG) $(LIBS)
	$(MAKE) tests >/dev/null

	# success
	./$(PROG) tests/t_small.txt tests/out_small.txt
	./$(PROG) tests/t_sentence.txt tests/out_sentence.txt

	# errors
	-./$(PROG) NOFILE.txt out.tmp || true
	-./$(PROG) || true

	$(MAKE) gcov

gcov:
	@echo
	@echo "==== gcov report ($(SRC)) ===="
	@gcov -b -o . $(SRC) | sed 's/^/  /'
