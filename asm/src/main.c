/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:34:14 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/18 19:19:52 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "compiler.h"
#include <fcntl.h>
#include <stdio.h>

/*
static void		print_file(t_list *file) //TEMP
{
	int		lc;

	lc = 0;
	while (file)
	{
		ft_printf("%d: '%s'\n", ++lc, (char *)file->content);
		file = file->next;
	}
}
*/

const char		*g_token_type_str[TOKEN_TYPE_COUNT] = {
	"T_WORD", "T_STRING", "T_SEPARATOR", "T_NONE"
};

const char		*g_token_word_id[TOKEN_ID_COUNT] = {
	"I_COMMAND", "I_LABEL", "I_INSTRUCTION", "I_REGISTER", "I_DIRECT",
	"I_INDIRECT", "I_DIRECT_LABEL", "I_INDIRECT_LABEL", "I_NONE"
};

/*
static void		print_tokens(t_list **tokens, int len) //TEMP
{
	int		i;
	t_token	*cur;
	t_list	*line;

	i = -1;
	while (++i < len)
	{
		if ((line = tokens[i]))
			ft_printf("line %d:\n", i + 1);
		while (line)
		{
			cur = (t_token *)line->content;
			ft_printf("[ type = %s, id = %s, op_code = %d, str = %.*s ]\n",
				g_token_type_str[cur->type], g_token_word_id[cur->id],
				cur->op_code, cur->len, cur->str);
			line = line->next;
		}
	}
}
*/

void	print_ops(t_parsed_op *ops, size_t ops_len) //TEMP
{
	size_t			i;
	unsigned int	j;
	t_token			*cur;

	i = 0;
	while (i < ops_len)
	{
		ft_printf("ops[%zu]: %s, argc = %u\nargs:\n", i,
			g_op_tab[ops[i].op_code - 1].name, ops[i].argc);
		j = 0;
		while (j < ops[i].argc)
		{
			cur = ops[i].args[j++];
			ft_printf("[ type = %s, id = %s, op_code = %d, str = %.*s ]\n",
				g_token_type_str[cur->type], g_token_word_id[cur->id],
				cur->op_code, cur->len, cur->str);
		}
		++i;
	}
}

void	print_labels(t_list *labels) //TEMP
{
	t_label	*cur;

	while (labels)
	{
		cur = labels->content;
		ft_printf("label '%.*s': op_ref = %d, line = %d\n", cur->name_len,
			cur->name, cur->op_ref, cur->line);
		labels = labels->next;
	}
}

void	print_hex_prog(t_asmdata *adat) //TEMP
{
	unsigned int	address;
	unsigned int	i;

	address = 0;
	while (address < adat->prog_size)
	{
		ft_printf("%.8x:", address);
		i = 0;
		while (address + i < adat->prog_size && i < 16)
		{
			if (!(i % 2))
				ft_printf(" ");
			ft_printf("%.2x", adat->prog[address + i]);
			++i;
		}
		ft_printf("\n");
		address += 16;
	}
}

static t_list	*read_file(const char *file_name)
{
	int		fd;
	int		rd;
	char	*line;
	t_list	*file;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		perror("open");
		ft_exit(NULL, E_OPEN_FILE);
	}
	file = NULL;
	line = NULL;
	while ((rd = get_next_line(fd, &line)) > 0)
	{
		ft_lstadd(&file, ft_lstnew(NULL, 0));
		file->content = line;
	}
	if (rd == -1)
		ft_exit("get_next_line: error while reading file", E_READ_FILE);
	if (!file)
		ft_exit("read_file: empty file", E_EMPTY_FILE);
	ft_lst_reverse(&file);
	return (file);
}

int			main(int argc, char **argv)
{
	int				len;
	t_asmdata		adat;

	if (argc != 2)
	{
		ft_dprintf(2, "usage: %s asm.s\n", argv[0]);
		return (E_WRONG_USAGE);
	}
	else if ((len = ft_strlen(argv[1])) < 2
		|| ft_strcmp(argv[1] + len - 2, ".s"))
		ft_exit("error: wrong file type", E_WRONG_FILE);
	ft_bzero((void *)&adat, sizeof(t_asmdata));
	adat.file_name = argv[1];
	adat.file = read_file(argv[1]);
	adat.file_len = ft_lst_size(adat.file);
//	print_file(adat.file); //TEMP
	adat.tokens = lexer(adat.file, adat.file_len);
//	print_tokens(adat.tokens, adat.file_len); //TEMP
	asm_parser(&adat);
	print_ops(adat.ops, adat.ops_len); //TEMP
	print_labels(adat.labels); //TEMP
	compiler(&adat);
	print_hex_prog(&adat); //TEMP
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (0);
}
