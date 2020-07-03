CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror  -pedantic 
LIBS = 

INCLUDE_DIR = include
SRC_DIR = src

BUILD_DIR = ./build
OBJS_DIR = $(BUILD_DIR)/.objs
MAIN_EXEC = foo

_DEPS := $(shell ls $(INCLUDE_DIR) | grep .h)
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJS = main.o list.o unity.o
$(shell mkdir -p $(OBJS_DIR))
OBJS = $(patsubst %,$(OBJS_DIR)/%,$(_OBJS))

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c  $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(MAIN_EXEC): $(OBJS)
	$(CC) -o $(BUILD_DIR)/$@ $^ $(CFLAGS) $(LIBS)

run: $(MAIN_EXEC)
	@$(BUILD_DIR)/$(MAIN_EXEC)

.PHONY: clean

clean:
	rm -rf $(OBJS_DIR) $(BUILD_DIR)/$(MAIN_EXEC)
