# === Config ===
CC        = gcc
CFLAGS    = -Wall -g
COVFLAGS  = $(CFLAGS) -fprofile-arcs -ftest-coverage

# Compile all C sources in this folder
SRCS      = $(wildcard *.c)
OUT       = prog.x

.PHONY: all build run coverage-build run-tests-coverage run-tests-leak clean

# Default
all: build

# === Build ===
build: $(OUT)

$(OUT): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# === Coverage build ===
coverage-build: $(SRCS)
	$(CC) $(COVFLAGS) -o $(OUT) $^

# === Run with your test files ===
run: build
	./$(OUT) input.txt output.txt

# === Coverage run (adjust/add more test cases as needed) ===
run-tests-coverage: coverage-build
	./$(OUT) input.txt output.txt
	gcov $(SRCS)

# === Valgrind memory check ===
run-tests-leak: build
	valgrind --tool=memcheck --leak-check=yes \
		--show-reachable=yes --num-callers=20 --track-fds=yes \
		./$(OUT) input.txt output.txt

# === Clean ===
clean:
	rm -f $(OUT) prog *.o *.gcno *.gcda *.gcov
