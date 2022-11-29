CC := gcc
SRC_DIR ?= src
OBJ_DIR ?= obj
DEBUG ?= 1
LIB ?= -L./lib/lib -lSDL2
INCLU ?= -I./lib/include

ifeq '$(DEBUG)' '1'
CFLAGS ?= -Wall -MMD -g
else
CFLAGS ?= -Wall -MMD -O3 -DNDEBUG
endif

LDFLAGS=

OBJS := $(shell find $(SRC_DIR) -name "*.c" |sed 's/.c$$/.o/g' | sed 's/$(SRC_DIR)/$(OBJ_DIR)/g')
DEPS := $(OBJS:.o=.d)
TARGET ?= exec

all: $(TARGET)

$(TARGET): $(OBJS)	
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLU)

clean:
	rm -rf $(OBJ_DIR)

mrproper: clean
	rm -f $(TARGET)


-include $(DEPS)