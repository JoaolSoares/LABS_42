NAME_ENCODER =	Encoder
NAME_DECODER =	Decoder

FLAGS =			-Werror -Wall -Wextra

CC =			cc

GREEN =			\033[1;32m
NOCOLOR =		\033[0m

LIBFTPATH =		./lib
LIBFT =			./lib/libft.a

SRCS_ENCODER =	encoder/src/main.c				\
				encoder/src/process_infos.c		\
				encoder/src/files_utils.c		\
				encoder/src/frequency_list.c	\
				encoder/src/huffman_tree.c		\
				encoder/src/dictionary.c		\
				encoder/src/shared_memory.c		\
				encoder/src/free.c				\

SRCS_DECODER =	decoder/src/main.c				\
				decoder/src/shared_memory.c		\
				decoder/src/treat_mensage.c		\
				decoder/src/decode.c			\

OBJS_ENCODER =	${SRCS_ENCODER:.c=.o}
OBJS_DECODER =	${SRCS_DECODER:.c=.o}

all: ${NAME_ENCODER} ${NAME_DECODER}

${NAME_ENCODER}: ${OBJS_ENCODER}
	@ make -C ${LIBFTPATH}
	@ $(CC) $(FLAGS) $(OBJS_ENCODER) $(LIBFT) -o $(NAME_ENCODER)
	@ echo "${GREEN}-=- ENCODER SUCCESSFUL COMPILED -=-${NOCOLOR}"

${NAME_DECODER}: ${OBJS_DECODER}
	@ make -C ${LIBFTPATH}
	@ $(CC) $(FLAGS) $(OBJS_DECODER) $(LIBFT) -o $(NAME_DECODER)
	@ echo "${GREEN}-=- DECODER SUCCESSFUL COMPILED -=-${NOCOLOR}"
	
clean:
	@ rm -f $(OBJS_ENCODER)
	@ rm -f $(OBJS_DECODER)
	@ make fclean -C ${LIBFTPATH}

rmv:
	@ rm -f $(NAME_ENCODER)
	@ rm -f $(NAME_DECODER)

fclean: rmv clean

re: fclean all

refast: rmv all clean

.PHONY: all clean rmv fclean re refast