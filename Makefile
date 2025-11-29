#                           COLORS                          #
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
RED     = \033[1;31m
BLUE    = \033[1;34m
RESET   = \033[0m

#                           PATHS                           #
OBJ_DIR     =   .obj/
SRC_DIR     =   src/
INC_DIR     =   include/
MLX_DIR     =   minilibx/
LIBFT_DIR   =   libft/

#                           FILES                           #
SRC_FILES   =   main.c map_init.c parsing.c parsing_syntax.c parsing_utils.c clean.c mlx_config.c init_player.c
OBJ_FILES   =   $(SRC_FILES:.c=.o)

SRC         =   $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ         =   $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# FIX 1: Define the actual library files so the rules below work
LIBFT       =   $(LIBFT_DIR)libft.a
MLX         =   $(MLX_DIR)libmlx.a
# Note: If using Linux MLX, this might need to be $(MLX_DIR)libmlx_Linux.a

NAME        =   cub3D

#                           COMPILER                        #
CC          =   gcc
CFLAGS      =   -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -g

#                           LIBRARIES                       #
LIBFT_FLAGS =   -L$(LIBFT_DIR) -lft
MLX_FLAGS   =   -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

#                           RULES                           #

all: print_flags $(MLX) $(LIBFT) $(NAME)

print_flags:
	@echo "$(BLUE)Compiler: $(CC)$(RESET)"
	@echo "$(BLUE)Flags: $(CFLAGS)$(RESET)"

# FIX 2: Added $(LIBFT) and $(MLX) as dependencies. 
# This guarantees they are built before linking.
$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(OBJ) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Build successful -> $(NAME)$(RESET)"

# Object compilation
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)Compiling $@...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Rules to compile external libraries
$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	@echo "$(RED)Removing object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re print_flags