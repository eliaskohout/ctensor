CC = cc
CC_FLAGS = -Wall -Wextra -pedantic -Ofast
LD_FLAGS = #-pthread

TARGET = .target
DIR_TESTS = tests

FILES = $(addprefix $(TARGET)/build/, $(shell ls ./*.c | sed 's/\.c/\.o/g'))
FILES_TEST = $(shell find $(DIR_TESTS) -name '*.c' | sed 's/\.c/\.o/g' | sed 's/$(DIR_TESTS)/$(TARGET)\/build\/$(DIR_TESTS)/g')

test: $(TARGET)/test
	cd $(TARGET)/ && ./test

build: $(TARGET)/ctensor.o

$(TARGET)/test: $(FILES_TEST) $(TARGET)/ctensor.o | dirs
	$(CC) $(LD_FLAGS) $^ -o $@

$(TARGET)/ctensor.o: $(FILES)
	ld $(LD_FLAGS) -r $^ -o $@

dirs: 
	mkdir -p $(TARGET)/build/$(DIR_TESTS)

# --- Source ---
$(TARGET)/build/%.o: %.c %.h | dirs
	$(CC) $(CC_FLAGS) -c $< -o $@


# --- Tests ---
OBJ_DIR_TESTS = $(TARGET)/build/$(DIR_TESTS)

$(OBJ_DIR_TESTS)/main.o: $(DIR_TESTS)/main.c $(DIR_TESTS)/main.h | dirs
	$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJ_DIR_TESTS)/tensor_test.o: $(DIR_TESTS)/tensor_test.c $(DIR_TESTS)/tensor_test.h | dirs
	$(CC) $(CC_FLAGS) -c $< -o $@


# --- Utils ---
clean:
	rm -rf $(TARGET)
