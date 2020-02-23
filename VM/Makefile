############################## COMPILE VAR #####################################

CC			=	gcc
#CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		=	-g -Wall -Wextra -Werror -fsanitize=address,undefined
HDIR		=	includes
SRCDIR		=	src
SUB1D		=	../libft
HFLAGS		=	-I $(HDIR) -I $(SUB1D)/$(HDIR)
V			=	-lncurses -lform
LIBS		=	$(SUB1D)/libft.a $(V)
NAME		=	corewar

############################## SOURCES #########################################

VISUDIR			=	visu

SRCC			=	aff_instruction.c\
					check_champs.c\
					check_len_file.c\
					exec_champs.c\
					fork_instructions.c\
					init_champs.c\
					introduce_champs.c\
					live_instruction.c\
					load_instructions.c\
					main.c\
					op.c\
					operations_instructions.c\
					parse_arguments.c\
					process_live_fct.c\
					rdm_utils.c\
					read_args.c\
					read_file_utils.c\
					read_write_map.c\
					store_instructions.c\
					usage.c\
					verbose_op_legacy.c\
					verbose_op_legacy_2.c\
					verbose_op_legacy_3.c\
					verbose_pc.c\
					zjmp_instruction.c\

VISUC			=	visu_corewar.c\
					visu_corewar_ascii.c\
					visu_corewar_init.c\
					visu_corewar_utils.c\

ODIR			=	obj
OBJ				=	$(patsubst %.c,%.o,$(VISUC))\
					$(patsubst %.c,%.o,$(SRCC))\

vpath			%.o	$(ODIR)
vpath			%.h	$(HDIR)
vpath			%.h	$(SUB1D)/$(HDIR)
vpath			%.c	$(SRCDIR)/$(VISUDIR)
vpath			%.c	$(SRCDIR)

############################## BUILD ###########################################

all: $(NAME)

$(NAME): $(SUB1D)/libft.a $(ODIR) $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(patsubst %.o,$(ODIR)/%.o,$(OBJ)) $(LIBS)

$(SUB1D)/libft.a:
	@make -C $(SUB1D)

aff_instruction.o: op.h libft.h
check_champs.o: op.h libft.h
check_len_file.o: op.h libft.h
exec_champs.o: op.h libft.h operations.h
fork_instructions.o: op.h libft.h
init_champs.o: operations.h op.h libft.h
introduce_champs.o: op.h libft.h
live_instruction.o: op.h libft.h
load_instructions.o: op.h libft.h
main.o: op.h libft.h
op.o: op.h libft.h
operations_instructions.o: op.h libft.h
parse_arguments.o: op.h libft.h
process_live_fct.o: op.h libft.h
rdm_utils.o: op.h libft.h
read_args.o: op.h libft.h
read_file_utils.o: op.h libft.h
read_write_map.o: op.h libft.h
store_instructions.o: op.h libft.h
verbose_op_legacy.o: op.h libft.h
verbose_op_legacy_2.o: op.h libft.h
verbose_op_legacy_3.o: op.h libft.h
verbose_pc.o: op.h libft.h
visu_corewar.o: op.h libft.h
visu_corewar_ascii.o: op.h libft.h
visu_corewar_init.o: op.h libft.h
visu_corewar_utils.o: op.h libft.h
zjmp_instruction.o: op.h libft.h
%.o: %.c
	@mkdir -p $(ODIR)
	@$(CC) -c $(CFLAGS) $< $(HFLAGS) -o $(ODIR)/$@

$(ODIR):
	mkdir -p $@

############################## CLEANUP #########################################

clean:
	@rm -rf $(ODIR)
	@make -C $(SUB1D) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
