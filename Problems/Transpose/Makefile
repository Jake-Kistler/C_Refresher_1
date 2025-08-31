# Makefile for Transpose
# Usage:
#   make            # build prog.x
#   make run        # demo run with tests/t_mat1.txt -> tests/out_mat1.txt
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
	@echo "Demo run: tests/t_mat1.txt -> tests/out_mat1.txt"
	./$(PROG) tests/t_mat1.txt tests/out_mat1.txt
	@echo "Output written to tests/out_mat1.txt"

tests:
	@rm -rf tests && mkdir -p tests
	# ---- success-path inputs ----
	@printf "3 4\n1 2 3 4\n5 6 7 8\n9 10 11 12\n" > tests/t_mat1.txt
	@printf "1 3\n-1.5 0 2.5\n" > tests/t_mat2.txt

	# ---- failure-path inputs ----
	@printf "0 5\n" > tests/t_badsize.txt
	@printf "2 2\n1 x\n3 4\n" > tests/t_badnum.txt

check: all tests
	./$(PROG) tests/t_mat1.txt tests/out_mat1.txt
	./$(PROG) tests/t_mat2.txt tests/out_mat2.txt
	@echo "OK: ran all success-path tests."

valgrind: all tests
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_mat1.txt /dev/null
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_mat2.txt /dev/null
	# failure paths
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_badsize.txt out.tmp || true
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) tests/t_badnum.txt out.tmp || true
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
	./$(PROG) tests/t_mat1.txt tests/out_mat1.txt
	./$(PROG) tests/t_mat2.txt tests/out_mat2.txt

	# errors
	-./$(PROG) tests/t_badsize.txt out.tmp || true
	-./$(PROG) tests/t_badnum.txt out.tmp || true
	-./$(PROG) NOFILE.txt out.tmp || true
	-./$(PROG) || true

	$(MAKE) gcov

gcov:
	@echo
	@echo "==== gcov report ($(SRC)) ===="
	@gcov -b -o . $(SRC) | sed 's/^/  /'
