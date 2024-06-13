# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Define the source directory, source files, and the corresponding object files
SRC_DIR = src
SRCS = $(SRC_DIR)/commands.c $(SRC_DIR)/errors.c $(SRC_DIR)/main.c $(SRC_DIR)/prints.c \
       $(SRC_DIR)/sorts.c $(SRC_DIR)/conv_date_time.c $(SRC_DIR)/hashtable.c \
       $(SRC_DIR)/memory_control.c $(SRC_DIR)/read_input.c
OBJS = $(SRCS:.c=.o)

# Define the header files
HEADERS = $(SRC_DIR)/commands.h $(SRC_DIR)/errors.h $(SRC_DIR)/header.h $(SRC_DIR)/prints.h \
          $(SRC_DIR)/sorts.h $(SRC_DIR)/conv_date_time.h $(SRC_DIR)/hashtable.h \
          $(SRC_DIR)/memory_control.h $(SRC_DIR)/read_input.h

# Define the target executable
TARGET = run

# Define the test script
TEST_SCRIPT = tests/test.sh

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the build files
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to clean result files
clean-results:
	find tests -type f -name "*.result" -delete
