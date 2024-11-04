# Name
NAME	= minirt

# Compiler and Flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g

# Minilibx
ifeq ($(shell uname),Linux)
	MLX_DIR = minilibx/
	LIBS = -lXext -lX11 -lm
else
	MLX_DIR = minilibx/
	LIBS = -framework OpenGL -framework AppKit
endif
MLX_NAME	= libmlx.a
MLX			= $(MLX_DIR)$(MLX_NAME)

# Libft
LIBFT_DIR		= libft/
LIBFT_NAME		= libft.a
LIBFT			= $(LIBFT_DIR)$(LIBFT_NAME)

# Includes
INC	=	-I ./includes/\
		-I ./libft/\
		-I $(MLX_DIR)

# Source files
SRC_DIR	=	sources/
#SRC_SUBDIRS =	$(shell find $(SRC_DIR) -type d)
SRC		=	$(SRC_DIR)/error/error.c \
			$(SRC_DIR)/parser/ambient.c \
			$(SRC_DIR)/parser/camera.c \
			$(SRC_DIR)/parser/cylinder.c \
			$(SRC_DIR)/parser/light.c \
			$(SRC_DIR)/parser/parser.c \
			$(SRC_DIR)/parser/plane.c \
			$(SRC_DIR)/parser/sphere.c \
			$(SRC_DIR)/utils/utils.c \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/render.c

# Object files
OBJ_DIR	= obj/
OBJ		= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Build rules
all:			$(MLX) $(LIBFT) $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)

$(MLX):
				@echo "Making MLX..."
				@make -sC $(MLX_DIR)

$(LIBFT):
				@echo "Making Libft..."
				@make -sC $(LIBFT_DIR)


$(NAME):		$(OBJ)
				@echo "Compiling MiniRT..."
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBFT) $(INC) $(LIBS)
				@echo "MiniRT ready."

clean:
				@echo "Removing .o object files..."
				@rm -rf $(OBJ_DIR)
				@make -s clean -C $(MLX_DIR)
				@make -s clean -C $(LIBFT_DIR)

fclean:			clean
				@echo "Removing MiniRT..."
				@rm -f $(NAME)
				@rm -f $(LIBFT_DIR)$(LIBFT_NAME)

re:		fclean all

# Phony targets represent actions not files
.PHONY: all clean fclean re
