CC = gcc

SRC = src
TEST_DIR = test

BUILD_DIR = build
TEST_BUILD = $(BUILD_DIR)/test
OBJ_DIR = $(BUILD_DIR)/obj

LDFLAGS = -lsodium

SRCS = $(wildcard $(SRC)/*.c)
TESTS = $(wildcard $(TEST_DIR)/*.c)

OBJS = $(patsubst $(SRC)/%.c,$(OBJ_DIR)/src/%.o,$(SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/test/%.o,$(TESTS))

test: $(OBJS) $(TEST_OBJS)
	@mkdir -p $(TEST_BUILD)
	$(CC) $^ -o $(TEST_BUILD)/test $(LDFLAGS)

$(OBJ_DIR)/src/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: test clean
