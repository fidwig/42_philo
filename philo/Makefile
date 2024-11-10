NAME := philo
CC := clang -g3
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -MMD -MP -I inc -pthread #-lpthread
RM := rm -rf
SRC_DIR := src
INC_DIR := inc
BUILD_DIR := .build
HEADER := philosophers.h
HEADER := $(HEADER:%=$(INC_DIR)/%)
SRCS := main.c philos.c routine.c safe_operations.c utils.c time.c monitoring.c \
		init_and_end.c errors.c
SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

all: $(NAME)

$(NAME): $(BUILD_DIR) $(OBJS) $(HEADER)
	@echo Compiling $(NAME)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)

# bonus: $(BUILD_DIR) $(BONUS_OBJS) $(BONUS_HEADER) $(HEADER)
#	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

-include $(DEPS) #$(BONUS_DEPS)

clean:
	$(RM) $(wildcard $(OBJS) $(DEPS) $(BONUS_OBJS) $(BONUS_DEPS) $(BUILD_DIR))

fclean: clean
	$(RM) $(wildcard $(NAME) $(BONUS_NAME) $(BUILD_DIR))

re: fclean all

.PHONY: all bonus clean fclean re
