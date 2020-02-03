/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multiline_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 20:15:02 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/03 17:07:43 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "errors.h"

static void		fuse_tokens(t_list **tokens, size_t start, size_t i, size_t len)
{
	t_token	*start_token;
	t_token	*cur;
	char	*str;

	start_token = ft_lst_last(tokens[start])->content;
	start_token->type = T_STRING;
	start_token->len = len;
	str = ft_strncat(ft_strncpy(ft_strnew(len),
		start_token->str, start_token->len), "\n", 1);
	while (++start < i)
	{
		cur = tokens[start]->content;
		ft_strncat(str, cur->str, cur->len);
		if (start < i - 1)
			ft_strncat(str, "\n", 1);
		ft_memdel(&tokens[start]->content);
		ft_memdel((void **)&tokens[start]);
	}
	start_token->str = str;
}

static size_t	fetch_and_fuse(t_list **tokens, size_t i,
					t_list *line, size_t file_len)
{
	t_token	*token;
	size_t	start;
	size_t	len;

	start = i;
	len = 0;
	while (line)
	{
		token = line->content;
		len += token->len + (token->type != T_END_STRING);
		if (line->next && (token = line->next->content))
			error_unexpected_token(token->len, token->str, i);
		line = ++i < file_len && token->type != T_END_STRING ? tokens[i] : NULL;
	}
	if (token->type != T_END_STRING)
		ft_exit("lexer: unfinished string", E_UNFINISHED_STRING);
	fuse_tokens(tokens, start, i, len);
	return (i - 1);
}

void			fuse_multiline_strings(t_list **tokens, size_t file_len)
{
	size_t	i;
	t_list	*line;
	t_token	*token;

	i = 0;
	while (i < file_len)
	{
		if (tokens[i])
		{
			line = tokens[i];
			while (line)
			{
				token = line->content;
				if (token->type == T_START_STRING)
				{
					i = fetch_and_fuse(tokens, i, line, file_len);
					break ;
				}
				line = line->next;
			}
		}
		++i;
	}
}

//TODO: test if this function works if a second multilinestring is on the line
//TODO: it should
t_list			*handle_multiline_string(const char *line, int i,
					int *multiline_string)
{
	t_token	cur;
	t_list	*tokens;

	cur.type = T_PART_STRING;
	cur.id = I_NONE;
	cur.op_code = -1;
	cur.str = (char *)line;
	cur.len = 0;
	while (*line && *line != '"')
		++line;
	if (*line == '"')
	{
		cur.len = line - cur.str + 1;
		cur.type = T_END_STRING;
		*multiline_string = 0;
	}
	else
		cur.len = line - cur.str;
	tokens = ft_lstnew((void *)&cur, sizeof(t_token));
	if (cur.type == T_END_STRING)
		tokens->next = tokenize(++line, i, multiline_string);
	return (tokens);
}
