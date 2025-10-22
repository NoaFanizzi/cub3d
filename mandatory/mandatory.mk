NAME		= cub3d

DIR			= mandatory
SRC_DIR		= $(DIR)/srcs
INC_DIR		= $(DIR)/includes
GAME_DIR	= game
UTILS_DIR	= utils
MAP_DIR		= map
DRAWING_DIR	= drawing
RAYCAST_DIR = raycast

MAP_SRCS	= map_init.c map_parsing.c map_resizing.c map_textures_management.c map_utils.c wall_management.c
MAP_SRCS	:= $(addprefix $(MAP_DIR)/, $(MAP_SRCS))

DRAWING_SRCS = draw.c
DRAWING_SRCS := $(addprefix $(DRAWING_DIR)/, $(DRAWING_SRCS))

RAYCAST_SRCS = dda.c raycast.c wall_management.c
RAYCAST_SRCS := $(addprefix $(RAYCAST_DIR)/, $(RAYCAST_SRCS))

GAME_SRCS	= player_movement.c game.c
GAME_SRCS	:= $(addprefix $(GAME_DIR)/, $(GAME_SRCS))

UTILS_SRCS	= clean.c mlx_utils.c
UTILS_SRCS	:= $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))

SRCS		= main.c
SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS) $(MAP_SRCS) $(DRAWING_SRCS) $(RAYCAST_SRCS) $(GAME_SRCS) $(UTILS_SRCS))

vpath %.c $(SRC_DIR) $(SRC_DIR)/$(GAME_DIR) $(SRC_DIR)/$(MAP_DIR) $(SRC_DIR)/$(DRAWING_DIR) $(SRC_DIR)/$(UTILS_DIR) $(SRC_DIR)/$(RAYCAST_DIR)
vpath %.h $(INC_DIR)