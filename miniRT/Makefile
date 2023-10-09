
SRCS	= shade/shade_hit.c get_next_line/get_next_line.c libft_utils/utils.c libft_utils/atoif.c\
 shape/sphere.c \
  mlx/mlx.c  color/color.c shade/reflection.c   shade/shading.c camera/camera.c material/material.c   minirt.c\
   world/world.c parse/parsing.c intersection/intersection.c intersection/intersect_objt.c\
   matrix/matrix_init.c  matrix/matrix_rotation.c matrix/matrix_optn.c\
   matrix/matrix_transf.c matrix/matrix_inverse.c libft_utils/linked_list_utils.c libft_utils/split.c\
   tuples/init_tuples.c  tuples/tuples_compare.c tuples/tuples_opt.c     tuples/tuples_opt2.c ray/ray.c\
   world/init_world.c material/phong_model.c shape/plane.c shape/cylinder.c shape/cone.c shape/triangle.c parse/parsing_utils.c parse/parsing_triangle.c \
   parse/parsing_cylinder.c parse/parsing_plane.c parse/parsing_sphere.c parse/parsing_cone.c\
   camera/define_view.c clean_up.c parse/set_up_world_parse.c libft_utils/utils2.c matrix/matrix_rotations.c mlx/render.c color/color_ops.c libft_utils/strncmp.c\
   shape/cylinder_utils.c shape/cone_utils.c

OBJS	= ${SRCS:.c=.o}
NAME	= miniRT
HEAD	= includes
CC		= cc
CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address -g
RM 		= rm -f

all:	${NAME}


${NAME}:	${OBJS}
			$(CC) $(CFLAGS) $(SRCS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o ${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re
