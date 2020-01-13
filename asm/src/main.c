/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:34:14 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/14 00:10:57 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "errors.h"
#include "lexer.h"
#include <fcntl.h>
#include <stdio.h>

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
	t_list			*file;
	t_list			**tokens;
//	t_parsed_data	pdat;

	if (argc != 2)
	{
		ft_dprintf(2, "usage: %s asm.s\n", argv[0]);
		return (E_WRONG_USAGE);
	}
	else if ((len = ft_strlen(argv[1])) < 2
		|| ft_strcmp(argv[1] + len - 2, ".s"))
		ft_exit("error: wrong file type", E_WRONG_FILE);
	file = read_file(argv[1]);
	print_file(file); //TEMP
	tokens = lexer(file);
//	ft_bzero((void *)&pdat, sizeof(t_parsed_data));
//	pdat = parser(&pdat, file, tokens);
//	compile(tokens);
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (0);
}
