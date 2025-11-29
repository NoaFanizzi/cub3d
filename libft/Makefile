SRCS_FILE :=	$(addprefix ft_, \
		absl \
		abs \
		atoi \
		atol_base \
		atol \
		atoll \
		bzero \
		calloc \
		close_all \
		count_words \
		free_split \
		free \
		gnl \
		isalnum \
		isalpha \
		isascii \
		isdigit \
		islower \
		isprint \
		isspace \
		isupper \
		itoa \
		llitoa \
		lstadd_back \
		lstadd_front \
		lstlast \
		lstnew \
		lstsize \
		lstswap \
		lstdelone \
		lstdup \
		lstfirst \
		lstget_index \
		lstindex \
		lstclear \
		lstiter \
		lstmap \
		memchr \
		memcmp \
		memcpy \
		memmove \
		memset \
		putchar_fd \
		putendl_fd \
		putnbr_base_fd \
		putnbr_fd \
		putstr_fd \
		read_file \
		split \
		strcat \
		strchr \
		strcmp \
		strcpy \
		strcrop \
		strdup \
		striteri \
		strjoin_all \
		strjoin \
		strjoinfree \
		strlcat \
		strlcpy \
		strlen \
		strmapi \
		strncat \
		strncmp \
		strnstr \
		strrchr \
		strrev \
		strtrim \
		substr \
		tolower \
		toupper \
		printf \
		printf_hexa \
		printf_pnt \
		)

SRCS := $(addsufix .c, $(SRCS_FILE))
OBJ_DIR := .objs/
OBJS :=	$(addsuffix .o, $(addprefix $(OBJ_DIR), $(SRCS_FILE)))
INC_FILE := libft.h
AR :=	ar -rcs
CC :=	cc
CFLAGS :=	-Wall -Wextra -Werror -fPIC
NAME :=	libft.a

GREEN := \033[0;32m
YELLOW :=\033[0;33m
RED := \033[0;31m
BLUE := \033[0;34m
END := \033[0m

GREENB := \033[1;32m
BLUEB := \033[1;34m
YELLOWB :=\033[1;33m
REDB := \033[1;31m


all: $(OBJ_DIR) $(NAME)

$(OBJS): Makefile

${NAME}: ${OBJS}
	@echo "$(YELLOWB)🗃️  $@$(END)"
	@$(AR) $(NAME) ${OBJS}

$(OBJ_DIR)%.o: %.c $(INC_FILE)
	@echo -n "$(BLUEB)🔨 $<"
	@echo " ->$(END) $@" | cut -b 1-8,15-
	@${CC} ${CFLAGS} -c $< -o $@

$(OBJ_DIR):
	@echo "$(GREENB)mkdir $(GREEN)$(OBJ_DIR)$(END)"
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(REDB)🗑️  $(OBJ_DIR)$(END)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(REDB)🗑️  $(NAME)$(END)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
