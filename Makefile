# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 12:35:23 by ckrasniq          #+#    #+#              #
#    Updated: 2025/12/20 20:52:43 by msalangi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cube3D

CC := cc

CFLAGS := -Wextra -Wall -Werror -Wunreachable-code -O3 -ffast-math -D_GNU_SOURCE
LIBMLX := ./MLX42
LIBFT_REPO := https://github.com/ckrasniqi/libft.git
MLX_REPO := https://github.com/codam-coding-college/MLX42.git

HEADERS := -I $(LIBMLX)/include -I include -I include/libft -I include/get_next_line -I .

EXTRA_LIBS := -lX11 -lGL -lXrandr -lXi -lXxf86vm

LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(EXTRA_LIBS) $(LIBFT_A)

LIBFT_DIR := include/libft

OBJDIR := build/obj
LIBDIR := build/lib

LIBFT_A := $(LIBDIR)/libft.a

SRC_CORE	=	src/core/main.c \
				src/core/init.c \
				src/core/free.c \
				src/core/error.c \
				src/core/utils.c

SRC_PARSE	=	src/parse/load.c \
				src/parse/validate.c \
				src/parse/map.c \
				src/parse/headers.c \
				src/parse/io.c \
				src/parse/map_utils.c \
				src/parse/parse_utils.c \
				src/parse/path_bonus.c

SRC_RENDER	=	src/render/raycast.c \
				src/render/rc_math.c \
				src/render/minimap.c \
				src/render/view.c \
				src/render/mask.c \
				src/render/hand.c \
				src/render/raycast_utils.c \
				src/render/light.c

SRC_INPUT	=	src/input/hooks.c \
				src/input/move.c \
				src/input/collision.c

SRCS		= $(SRC_CORE) $(SRC_PARSE) $(SRC_RENDER) $(SRC_INPUT)
OBJS := $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))



all: libmlx libft $(NAME)

libmlx:
	@echo Cloning MLX42 into $(LIBMLX)
	@rm -rf $(LIBMLX)
	@git clone $(MLX_REPO) $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build >/dev/null || true
	@$(MAKE) -C $(LIBMLX)/build -j4

libft: $(LIBFT_A)

$(LIBFT_A):
	@echo "Ensure libft is available"
	@mkdir -p $(LIBDIR)
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning libft into $(LIBFT_DIR) (shallow)"; \
		git clone --depth=1 $(LIBFT_REPO) $(LIBFT_DIR); \
	else \
		echo "libft already present; attempting to update"; \
		cd $(LIBFT_DIR) && git pull --ff-only || true; \
	fi
	@echo Building libft
	@if [ -f "$(LIBFT_DIR)/Makefile" ]; then \
		$(MAKE) -C $(LIBFT_DIR) >/dev/null || true; \
		cp -f $(LIBFT_DIR)/libft.a $(LIBFT_A) 2>/dev/null || true; \
	else \
		echo "Error: No Makefile in $(LIBFT_DIR). Please ensure libft is present with a Makefile."; exit 1; \
	fi




$(OBJDIR)/%.o: src/%.c libmlx libft
	@echo Compiling: $(notdir $<)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

%.o: %.c
	@echo Compiling: $(notdir $<)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)


$(NAME): $(OBJS) $(LIBFT_A) libmlx
	@echo Linking: $(NAME)
	@$(CC) $(OBJS) -Wl,--start-group $(LIBFT_A) $(LIBMLX)/build/libmlx42.a -Wl,--end-group -ldl -lglfw -pthread -lm $(EXTRA_LIBS) -o $(NAME)

clean:
	@echo Cleaning object files
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBDIR)

fclean: clean
	@echo Removing binary
	@rm -rf $(NAME)
	@echo Removing vendored libs and MLX
	@rm -rf $(LIBMLX)
	@rm -rf $(LIBFT_DIR)
	@rm -rf $(GNL_DIR)

re: fclean all

.PHONY: all clean fclean re libmlx
