############################## COMPILE VAR #####################################

SUB1D		=	libft
SUB2D		=	asm
SUB3D		=	VM

############################## BUILD ###########################################

all: libft asm corewar

libft:
	make -C $(SUB1D)

asm:
	make -C $(SUB2D)

corewar:
	make -C $(SUB3D)

############################## CLEANUP #########################################

clean:
	make -C $(SUB1D) fclean
	make -C $(SUB2D) fclean
	make -C $(SUB3D) fclean

fclean: clean

re: fclean all

.PHONY: all clean fclean re libft asm corewar
