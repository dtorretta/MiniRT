# Name
NAME = minirt

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Minilibx
MLX_DIR = minilibx/
LIBS = -lXext -lX11 -lm -L $(MLX_DIR) -lmlx

MLX_NAME = libmlx.a
MLX = $(MLX_DIR)$(MLX_NAME)

# Libft
LIBFT_DIR = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)

# Includes
INC = -I ./includes/ \
      -I ./libft/ \
      -I $(MLX_DIR)

# Source files
SRC_DIR = sources/
SRC = $(SRC_DIR)/error/error.c \
      $(SRC_DIR)/parser/ambient.c \
      $(SRC_DIR)/parser/camera.c \
      $(SRC_DIR)/parser/cylinder.c \
      $(SRC_DIR)/parser/light.c \
      $(SRC_DIR)/parser/parser.c \
      $(SRC_DIR)/parser/parser_utils.c \
      $(SRC_DIR)/parser/plane.c \
      $(SRC_DIR)/parser/sphere.c \
      $(SRC_DIR)/render/color.c \
      $(SRC_DIR)/render/color_utils.c \
      $(SRC_DIR)/render/events.c \
      $(SRC_DIR)/render/render_camera.c \
      $(SRC_DIR)/render/render_cylinder.c \
      $(SRC_DIR)/render/render_cylinder_utils.c \
      $(SRC_DIR)/render/render_plane.c \
      $(SRC_DIR)/render/render_sphere.c \
      $(SRC_DIR)/render/render.c \
      $(SRC_DIR)/utils/vector_utils.c \
      $(SRC_DIR)/utils/vector_utils_2.c \
      $(SRC_DIR)/utils/utils.c \
      $(SRC_DIR)/main.c \

# Object files
OBJ_DIR = obj/
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Build rules
all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(MLX):
	@echo "Making MLX..."
	@make -C $(MLX_DIR)

$(LIBFT):
	@echo "Making Libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@echo "Compiling MiniRT..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX) $(LIBFT) $(INC) $(LIBS)
	@echo "MiniRT ready."

clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_DIR)
	@make -s clean -C $(MLX_DIR)
	@make -s clean -C $(LIBFT_DIR)
	@echo "\n------------------------------------------\n"
	@echo "💧 Clean done \n"
	@echo "------------------------------------------\n"


fclean:			clean
	@echo "Removing MiniRT..."
	@rm -f $(NAME)
	@rm -f $(LIBFT_DIR)$(LIBFT_NAME)
	@echo "\n------------------------------------------\n"
	@echo "🧼 Fclean done \n"
	@echo "------------------------------------------\n"

re:		fclean all

# Phony targets represent actions not files
.PHONY: all clean fclean re