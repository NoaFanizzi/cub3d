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

#                           SUBDIRECTORIES                  #
MAP_DIR     =   map_importation/
MLX_MGMT    =   mlx_management/
RAYCAST_DIR =   raycasting/
PARSE_DIR   =   parsing/
PLAYER_DIR  =   player/

#                           FILES                           #
INC_FILES   =   $(INC_DIR)cube.h \
                $(INC_DIR)map.h \
                $(INC_DIR)mlx_management.h \
                $(INC_DIR)parsing.h \
                $(INC_DIR)player.h \
                $(INC_DIR)raycasting.h

SRC_FILES   =   main.c \
                clean.c \
                $(MAP_DIR)map_init.c \
                $(MAP_DIR)map_colors.c \
                $(MAP_DIR)map_resizing.c \
                $(MAP_DIR)map_line_management.c \
                $(MAP_DIR)map_utils.c \
                $(PARSE_DIR)parsing_config.c \
                $(PARSE_DIR)parsing_map.c \
                $(PARSE_DIR)parsing_syntax.c \
                $(PARSE_DIR)parsing_texture.c \
                $(PARSE_DIR)parsing_utils.c \
                $(MLX_MGMT)mlx_config.c \
                $(MLX_MGMT)mlx_init.c \
                $(MLX_MGMT)mlx_cleaning.c \
                $(RAYCAST_DIR)raycasting.c \
                $(RAYCAST_DIR)raycasting_texture.c \
                $(PLAYER_DIR)init_player.c \
                $(PLAYER_DIR)game_loop.c \
                $(PLAYER_DIR)control_key.c \
                $(PLAYER_DIR)player_mouvement.c

OBJ_FILES   =   $(SRC_FILES:.c=.o)
SRC         =   $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ         =   $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT       =   $(LIBFT_DIR)libft.a
MLX         =   $(MLX_DIR)libmlx.a

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

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(OBJ) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Build successful -> $(NAME)$(RESET)"

# Object compilation with subdirectory creation
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_FILES)
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Rules to compile external libraries
$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

clean:
	@echo "$(RED)Removing object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re print_flags