/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:05:53 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/19 22:49:56 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "g_op_tab.h"
#include "errors.h"

static void		reset_token(t_token *cur)
{
	cur->type = T_NONE;
	cur->id = I_NONE;
	cur->op_code = -1;
	cur->str = NULL;
	cur->len = 0;
}

static void		init_token(t_token *cur, const char *line)
{
	if (*line == ',')
		cur->type = T_SEPARATOR;
	else if (*line == '"')
		cur->type = T_STRING;
	else
		cur->type = T_WORD;
	cur->str = (char *)line;
}

static void		delimit_token(t_token *cur, t_list **tokens,
	const char *line, int line_id)
{
	if (cur->type == T_NONE)
		return ;
	cur->len = line - cur->str;
	if (cur->type == T_SEPARATOR)
		cur->len += 1;
	else if (cur->type == T_STRING
		&& (size_t)cur->len + 1 <= ft_strlen(cur->str)
		&& cur->str[cur->len] == '"')
		cur->len += 1;
	else if (cur->type == T_STRING)
		cur->type = T_START_STRING;
	cur->id = cur->type == T_WORD ? get_word_id(cur, line_id) : I_NONE;
	ft_lst_push_back(tokens, cur, sizeof(t_token));
	reset_token(cur);
}

t_list			*tokenize(const char *line, int line_id, int *multiline_string)
{
	t_token	cur;
	t_list	*tokens;

	tokens = NULL;
	reset_token(&cur);
	while (*line && (cur.type == T_STRING || (*line != '#' && *line != ';')))
	{
		if (cur.type == T_WORD && ft_strchr(" \t,\"%", *line))
			delimit_token(&cur, &tokens, line, line_id);
		else if (cur.type == T_STRING && *line == '"')
			delimit_token(&cur, &tokens, line++, line_id);
		else
		{
			if (cur.type == T_NONE && !ft_strchr(" \t", *line))
				init_token(&cur, line);
			if (cur.type == T_SEPARATOR)
				delimit_token(&cur, &tokens, line, line_id);
			++line;
		}
	}
	delimit_token(&cur, &tokens, line, line_id);
	if (tokens
		&& ((t_token *)ft_lst_last(tokens)->content)->type == T_START_STRING)
		*multiline_string = 1;
	return (tokens);
}

t_list			**lexer(t_list *file, size_t file_len)
{
	int		multiline_string;
	int		fuse_multi;
	t_list	**tokens;
	int		i;

	tokens = (t_list **)ft_memalloc(file_len * sizeof(t_list *));
	i = 0;
	multiline_string = 0;
	fuse_multi = 0;
	while (file)
	{
		if (multiline_string)
		{
			tokens[i] = handle_multiline_string(file->content, i,
				&multiline_string);
			fuse_multi = 1;
		}
		else
			tokens[i] = tokenize(file->content, i, &multiline_string);
		file = file->next;
		++i;
	}
	if (fuse_multi)
		fuse_multiline_strings(tokens, file_len);
	return (tokens);
}
