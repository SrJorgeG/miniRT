NAME = miniRT
COMPILER = CC
FLAGS = -Wall -Wextra -Werror -Iincludes -g3
MLX_DIR = libs/MLX42
BUILD_DIR = $(MLX_DIR)/build
LIBFT_DIR = libs/libft
LIBFT_NAME = libft

WAYLAND_LIBS = -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon
#LIBS = -L$(BUILD_DIR) -l:libmlx42.a -Iinclude -ldl -lglfw $(WAYLAND_LIBS) -pthread -lm -L$(LIBFT_DIR) -l:libft.a
LIBS = -L$(BUILD_DIR) -l:libmlx42.a -Iinclude -ldl -lglfw -pthread -lm -L$(LIBFT_DIR) -l:libft.a

CFILES = src/main.c src/exit.c src/init.c src/free_functions.c src/free_helpers.c src/free_cone.c src/render.c \
src/parser/parser.c src/parser/parser_scene.c src/parser/parser_objects.c \
src/ray/ray.c src/ray/hits.c src/ray/hits_cone.c src/ray/lighting.c src/ray/raycasting.c src/ray/ray_utils.c \
src/utils/color.c src/utils/color_helpers.c src/utils/scene.c src/utils/textures.c src/utils/str.c \
src/vector/vector.c src/vector/vector_aux.c src/vector/vector_basic.c src/vector/vector_utils.c \
src/hooks/keyboard.c \
src/hooks/mouse.c \
src/objects/object.c \
src/objects/sphere.c \
src/objects/cylinder.c \
src/objects/cone.c \
src/objects/plane.c \
src/functions/objects.c src/functions/objects_helpers.c \
src/debug/debug_parser.c src/debug/debug_helpers.c src/debug/debug_object_helpers.c \
src/cache/cache.c
COBJ = $(CFILES:.c=.o)




# Regla por defecto: compila el ejecutable
all: mlx_setup $(LIBFT_NAME) $(NAME)

# Para compilar el ejecutable, dependemos de que se hayan generado libft
$(NAME): $(COBJ) $(LIBFT_LIB)
	$(CC) $(FLAGS) -o $(NAME) $(COBJ) $(LIBS)

# Regla para compilar la libft
$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_DIR)

mlx_setup:
	@if [ ! -d "$(MLX_DIR)" ]; then git clone "https://github.com/codam-coding-college/MLX42.git"; fi
	@cmake -S $(MLX_DIR) -B $(BUILD_DIR)
	@$(MAKE) -C $(BUILD_DIR) -j4 all

mlx_debug:
	@if [ ! -d "$(MLX_DIR)" ]; then git clone "https://github.com/codam-coding-college/MLX42.git"; fi
	@cmake -DDEBUG=1 -DGLFW_FETCH=0 -S $(MLX_DIR) -B $(BUILD_DIR)
	@$(MAKE) -C $(BUILD_DIR) -j4 all

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(COBJ)
	$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)/build

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -rf $(MLX_DIR)/build

re: fclean all

bonus:
	@echo "No se han definido reglas para bonus aún.

asan: fclean mlx_setup $(LIBFT_NAME) asan_build
	@echo "✅ Compiled with AddressSanitizer"

asan_build: $(COBJ)
	$(CC) $(FLAGS) -g -fsanitize=address -fsanitize=leak -o $(NAME) $(COBJ) $(LIBS)

debug: fclean mlx_debug $(LIBFT_NAME) $(NAME)
	@echo "Compiled in debug mode"

.PHONY: all clean fclean re bonus mlx asan asan_build
