/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 23:28:38 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/19 23:30:11 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "compiler.h"
#include <fcntl.h>
#include <stdio.h>

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

int				main(int argc, char **argv)
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
	adat.tokens = lexer(adat.file, adat.file_len);
	asm_parser(&adat);
	compiler(&adat);
	ft_heap_collector(NULL, FT_COLLEC_FREE);
	return (0);
}
