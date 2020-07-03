CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror  -pedantic 
LIBS = 

INCLUDE_DIR = include
SRC_DIR = src

BUILD_DIR = ./test_build
OBJS_DIR = $(BUILD_DIR)/.objs
TEST_EXEC = test_run

_DEPS := $(shell ls $(INCLUDE_DIR) | grep .h)
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJS = main.o list.o unity.o
$(shell mkdir -p $(OBJS_DIR))
OBJS = $(patsubst %,$(OBJS_DIR)/%,$(_OBJS))

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c  $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TEST_EXEC): $(OBJS)
	$(CC) -o $(BUILD_DIR)/$@ $^ $(CFLAGS) $(LIBS)

test: $(TEST_EXEC)
	@$(BUILD_DIR)/$(TEST_EXEC)

.PHONY: clean

clean:
	rm -rf $(OBJS_DIR) $(BUILD_DIR)/$(TEST_EXEC)
