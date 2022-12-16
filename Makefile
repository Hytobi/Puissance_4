CC := gcc
SRC_DIR ?= src
SRC_INTERFACE ?= interfaces
SRC_JOUER ?= jouer_coup
OBJ_DIR ?= obj
TEST_DIR ?= test
DEBUG ?= 1
LIB ?= -L./lib/lib -lSDL2 -lSDL2_image
INCLU ?= -I./lib/include

ifeq '$(DEBUG)' '1'
CFLAGS ?= -Wall -MMD -g $(INCLU)
else
CFLAGS ?= -Wall -MMD -O3 -DNDEBUG $(INCLU)
endif

LDFLAGS = -lcunit $(LIB)

SRC := $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/$(SRC_INTERFACE)/*.c $(SRC_DIR)/$(SRC_JOUER)/*.c)
OBJS := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o) $($(SRC_DIR)/SRC_INTERFACE:.c=.o) $($(SRC_DIR)/SRC_JOUER:.c=.o))

SRC_TEST := $(wildcard $(TEST_DIR)/*.c)
OBJS_TEST := $(addprefix $(OBJ_DIR)/, $(SRC_TEST:.c=.o))

DEPS := $(OBJS:.o=.d)
DEPS_TEST := $(OBJS_TEST:.o=.d)

TARGET ?= exec
TARGET_TEST ?= runTest

.PHONY: clean mrproper

all: createRep $(TARGET) $(TARGET_TEST)

createRep:
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)/$(SRC_INTERFACE)
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)/$(SRC_JOUER)
	@mkdir -p $(OBJ_DIR)/$(TEST_DIR)

$(TARGET): createRep $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) 
	@echo ""

$(TARGET_TEST):  $(OBJS) $(OBJS_TEST)
	$(CC) -o $(TARGET_TEST) $(filter-out $(OBJ_DIR)/$(SRC_DIR)/main.o ,$(OBJS)) $(OBJS_TEST) $(LDFLAGS) 
	

$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@./$(TARGET_TEST)

clean:
	rm -rf $(OBJ_DIR)

mrproper: clean
	rm -f $(TARGET) $(TARGET_TEST)

-include $(DEPS) $(DEPS_TEST)