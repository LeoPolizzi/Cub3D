BLUE  	:= \033[1;34m
GREEN 	:= \033[1;32m
RED   	:= \033[1;31m
PURPLE 	:= \033[1;35m
CYAN  	:= \033[1;36m
YELLOW	:= \033[1;33m
RESET 	:= \033[0m

NAME    := cub3d
CFLAGS  := -Wall -Wextra -Werror -Ofast -g3 -D_REENTRANT
LIBMLX  := MLX42
LIBFT   := libft

HEADERS := -I./includes -I $(LIBMLX)/include
LIBS    := $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS    := srcs/main.c srcs/init.c
OBJS    := $(SRCS:.c=.o)

CC      := cc

all: libft libmlx $(NAME)

libft:
	@if [ ! -d "$(LIBFT)" ]; then \
		echo "$(CYAN)Cloning libft...$(RESET)"; \
		git clone https://github.com/LeoFalkins/Libft.git $(LIBFT) > /dev/null; \
		echo "$(GREEN)Libft cloned successfully!$(RESET)"; \
	fi
	@echo "$(CYAN)Building libft...$(RESET)"
	@make -C $(LIBFT) -j4 > /dev/null
	@echo "$(GREEN)Libft built successfully!$(RESET)"

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "$(CYAN)Cloning MLX42...$(RESET)"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX) /dev/null; \
		echo "$(GREEN)MLX42 cloned successfully!$(RESET)"; \
	fi
	@echo "$(CYAN)Building MLX42...$(RESET)"
	@cmake $(LIBMLX) -B $(LIBMLX)/build > /dev/null && make -C $(LIBMLX)/build -j4 > /dev/null
	@echo "$(GREEN)MLX42 built successfully!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "$(YELLOW)Compiling: $(PURPLE)$(notdir $<)\n$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

dev: fclean libft libmlx $(OBJS)
	@echo "$(CYAN)Compiling $(NAME) with sanitizers...$(RESET)"
	@$(CC) $(OBJS) $(LIBS) -fsanitize=address,leak,undefined -g3 $(HEADERS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"
	@echo "$(RED)Development mode enabled!$(RESET)"

clean:
	@echo "$(CYAN)Cleaning object files...$(RESET)"
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@echo "$(GREEN)Object files cleaned successfully!$(RESET)"

fclean: clean
	@echo "$(CYAN)Cleaning libft...$(RESET)"
	@make -C $(LIBFT) fclean > /dev/null
	@echo "$(GREEN)Libft cleaned successfully!$(RESET)"
	@echo "$(CYAN)Cleaning MLX42...$(RESET)"
	@rm -rf $(LIBMLX)/build
	@echo "$(GREEN)MLX42 cleaned successfully!$(RESET)"
	@echo "$(CYAN)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(NAME) cleaned successfully!$(RESET)"

re: fclean all

help:
	@echo "$(CYAN)Available commands:$(RESET)"
	@echo "$(YELLOW)make$(RESET) - compiles the project"
	@echo "$(YELLOW)make dev$(RESET) - compiles the project with sanitizers"
	@echo "$(YELLOW)make clean$(RESET) - removes object files"
	@echo "$(YELLOW)make fclean$(RESET) - removes object files, libraries and the executable"
	@echo "$(YELLOW)make re$(RESET) - removes object files, libraries and the executable, then recompiles the project"
	@echo "$(YELLOW)make help$(RESET) - displays this message"

.PHONY: all clean fclean re libft libmlx
