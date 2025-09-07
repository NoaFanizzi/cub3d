NAME		= cub3d

DIR			= mandatory
SRC_DIR		= $(DIR)/srcs
INC_DIR		= $(DIR)/includes
GNL_DIR		= GNL
MAP_DIR		= map
WINDOWS_DIR = windows

GNL_SRCS	= get_next_line.c get_next_line_utils.c
GNL_SRCS	:= $(addprefix $(GNL_DIR)/, $(GNL_SRCS))

MAP_SRCS	= map_init.c map_parsing.c map_utils.c
MAP_SRCS	:= $(addprefix $(MAP_DIR)/, $(MAP_SRCS))

WINDOWS_SRCS = windows_creation.c
WINDOWS_SRCS := $(addprefix $(WINDOWS_DIR)/, $(WINDOWS_SRCS))

SRCS		= main.c
SRCS		:= $(addprefix $(SRC_DIR)/, $(SRCS) $(MAP_SRCS) $(GNL_SRCS) $(WINDOWS_SRCS))


vpath %.c $(SRC_DIR) $(SRC_DIR)/$(GNL_DIR) $(SRC_DIR)/$(MAP_DIR) $(SRC_DIR)/$(WINDOWS_DIR)
vpath %.h $(INC_DIR)