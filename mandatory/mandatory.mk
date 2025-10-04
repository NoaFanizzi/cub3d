NAME		= cub3d

DIR			= mandatory
SRC_DIR		= $(DIR)/srcs
INC_DIR		= $(DIR)/includes
MAP_DIR		= map
CLEAN_DIR	= clean
WINDOWS_DIR = windows
DRAWING_DIR	= drawing

MAP_SRCS	= map_init.c map_parsing.c map_resizing.c map_textures_management.c map_utils.c
MAP_SRCS	:= $(addprefix $(MAP_DIR)/, $(MAP_SRCS))

CLEAN_SRCS	= clean.c
CLEAN_SRCS	:= $(addprefix $(CLEAN_DIR)/, $(CLEAN_SRCS))

DRAWING_SRCS = draw.c
DRAWING_SRCS := $(addprefix $(DRAWING_DIR)/, $(DRAWING_SRCS))

SRCS		= main.c player_movement.c mlx_utils.c
SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS) $(MAP_SRCS) $(WINDOWS_SRCS) $(CLEAN_SRCS) $(DRAWING_SRCS))

vpath %.c $(SRC_DIR) $(SRC_DIR)/$(MAP_DIR) $(SRC_DIR)/$(WINDOWS_DIR) $(SRC_DIR)/$(CLEAN_DIR) $(SRC_DIR)/$(DRAWING_DIR)
vpath %.h $(INC_DIR)