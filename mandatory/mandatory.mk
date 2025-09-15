NAME		= cub3d

DIR			= mandatory
SRC_DIR		= $(DIR)/srcs
INC_DIR		= $(DIR)/includes
MAP_DIR		= map
WINDOWS_DIR = windows

MAP_SRCS	= map_init.c map_parsing.c map_utils.c
MAP_SRCS	:= $(addprefix $(MAP_DIR)/, $(MAP_SRCS))

SRCS		= main.c player_movement.c mlx_utils.c
SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS) $(MAP_SRCS) $(WINDOWS_SRCS))


vpath %.c $(SRC_DIR) $(SRC_DIR)/$(MAP_DIR) $(SRC_DIR)/$(WINDOWS_DIR)
vpath %.h $(INC_DIR)