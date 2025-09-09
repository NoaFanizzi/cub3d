# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 13:45:35 by nofanizz          #+#    #+#              #
#    Updated: 2025/09/09 10:31:37 by lmarcucc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BINARIES    = cub3d

ifeq ($(filter bonus clean fclean,$(MAKECMDGOALS)),)
    include mandatory/mandatory.mk
endif

OBJ_DIR = .obj
DEP_DIR = .dep
LIBFT_DIR = libft
MLX_DIR = minilibx-linux
# ou MLX_DIR = mlx si tu utilises la version macOS

LIBFT       = $(LIBFT_DIR)/libft.a
MLX_LIB     = $(MLX_DIR)/libmlx.a

# Détection de l'OS pour les flags appropriés
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX_FLAGS = -lmlx -lXext -lX11 -lm
    MLX_COMPILE = $(MAKE) -C $(MLX_DIR)
endif
ifeq ($(UNAME_S),Darwin)
    MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
    MLX_COMPILE = $(MAKE) -C $(MLX_DIR)
endif

CC      = cc
C_FLAGS = -Wall -Wextra -Werror
D_FLAGS = -MMD -MP -MF $(DEP_DIR)/$*.d
I_FLAGS = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
L_FLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) $(MLX_FLAGS)
CF      = $(CC) $(C_FLAGS) $(I_FLAGS)

vpath %.c $(LIBFT_DIR)
vpath %.h $(LIBFT_DIR)
vpath %.o $(OBJ_DIR)
vpath %.d $(DEP_DIR)

OBJS    = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
DEPS    = $(addprefix $(DEP_DIR)/, $(notdir $(SRCS:.c=.d)))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@echo "Creating $(NAME)\n"
	@$(CF) $^ $(L_FLAGS) -o $@
	@echo "Program Created \n"

bonus: $(NAME)

$(LIBFT): FORCE
	@echo "Building libft \n"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX_LIB): FORCE
	@echo "Building minilibx \n"
	@$(MLX_COMPILE)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR) $(DEP_DIR)
	@echo "Compilation $< $@ "
	@$(CF) $(D_FLAGS) -c $< -o $@

$(OBJ_DIR) $(DEP_DIR):
	@echo "Creating obj directory"
	@mkdir -p $@

clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "Deleting obj files"
	@rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean:
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "Deleting obj files"
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@echo "Removing binaries"
	@rm -f $(BINARIES)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re debug help
FORCE:
