
SRCS	= shade_hit.c get_next_line/get_next_line.c libft_utils/utils.c libft_utils/atoif.c\
 sphere.c  matrix_transformations.c \
  mlx.c  color.c reflection.c   shading.c camera.c material.c   minirt.c\
   world.c parsing.c intersection/intersection.c intersection/intersect_objt.c\
   matrix/matrix_init.c  matrix/matrix_rotation.c matrix/matrix_optn.c\
   matrix/matrix_transf.c matrix/matrix_inverse.c libft_utils/linked_list_utils.c libft_utils/split.c\
   tuples/init_tuples.c  tuples/tuples_compare.c tuples/tuples_opt.c     tuples/tuples_opt2.c ray/ray.c\
   world/world.c material/phong_model.c plane.c cylinder.c

OBJS	= ${SRCS:.c=.o}
NAME	= minirt
HEAD	= includes
CC		= cc 
CFLAGS	= 
RM 		= rm -f

all:	${NAME}

${NAME}:	${OBJS}
			$(CC) $(SRCS) -Lmlx -lmlx -framework OpenGL -framework AppKit  -o  ${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all clean fclean re
