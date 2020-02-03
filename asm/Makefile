############################## COMPILE VAR #####################################

CC			=	gcc
#CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		=	-g -Wall -Wextra -Werror -fsanitize=address,undefined
HDIR		=	includes
SRCDIR		=	src
SUB1D		=	../libft
HFLAGS		=	-I $(HDIR) -I $(SUB1D)/$(HDIR)
LIBS		=	$(SUB1D)/libft.a
NAME		=	asm

############################## SOURCES #########################################

SRCC			=	add_label.c\
					asm_parser.c\
					compile_labels.c\
					compiler.c\
					debug.c\
					errors.c\
					g_op_tab.c\
					get_word_id.c\
					handle_multiline_string.c\
					lexer.c\
					main.c\
					parse_instruction.c\
					utils.c\
					write_exec_file.c\

ODIR			=	obj
OBJ				=	$(patsubst %.c,%.o,$(SRCC))

vpath			%.o	$(ODIR)
vpath			%.h	$(HDIR)
vpath			%.h	$(SUB1D)/$(HDIR)
vpath			%.c	$(SRCDIR)

############################## BUILD ###########################################

all: $(NAME)

$(NAME): $(SUB1D)/libft.a $(ODIR) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(patsubst %.o,$(ODIR)/%.o,$(OBJ)) $(LIBS)

$(SUB1D)/libft.a:
	make -C $(SUB1D)

add_label.o: asm_parser.h s_asmdata.h lexer.h libft.h g_op_tab.h errors.h
asm_parser.o: asm_parser.h s_asmdata.h lexer.h libft.h g_op_tab.h errors.h
compile_labels.o: asm_parser.h s_asmdata.h lexer.h libft.h g_op_tab.h errors.h
compiler.o: compiler.h asm_parser.h s_asmdata.h lexer.h libft.h g_op_tab.h\
	errors.h utils.h
debug.o: asm_parser.h s_asmdata.h lexer.h libft.h g_op_tab.h
errors.o: libft.h errors.h
g_op_tab.o: g_op_tab.h
get_word_id.o: lexer.h libft.h g_op_tab.h errors.h
handle_multiline_string.o: lexer.h libft.h errors.h
lexer.o: lexer.h libft.h g_op_tab.h errors.h
main.o: errors.h compiler.h asm_parser.h s_asmdata.h lexer.h libft.h\
	g_op_tab.h
parse_instruction.o: s_asmdata.h lexer.h libft.h g_op_tab.h errors.h
write_exec_file.o: s_asmdata.h lexer.h libft.h g_op_tab.h errors.h
%.o: %.c
	@mkdir -p $(ODIR)
	$(CC) -c $(CFLAGS) $< $(HFLAGS) -o $(ODIR)/$@

$(ODIR):
	mkdir -p $@

############################## CLEANUP #########################################

clean:
	rm -rf $(ODIR)
	make -C $(SUB1D) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
