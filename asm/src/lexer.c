/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 21:05:53 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/03 13:18:27 by yforeau          ###   ########.fr       */
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

static t_token	*delimit_token(t_token *cur, t_list **tokens,
								const char *line, int line_id)
{
	t_token	*ret;

	if (cur->type == T_NONE)
		return (NULL);
	cur->len = line - cur->str;
	if (cur->type == T_SEPARATOR)
		cur->len += 1;
	else if (cur->type == T_WORD && *line == ':' && !*tokens)
		cur->len += 1;
	else if (cur->type == T_STRING
		&& (size_t)cur->len + 1 <= ft_strlen(cur->str)
		&& cur->str[cur->len] == '"')
		cur->len += 1;
	else if (cur->type == T_STRING)
		cur->type = T_START_STRING;
	cur->id = cur->type == T_WORD ? get_word_id(cur, line_id) : I_NONE;
	ret = (t_token *)ft_lst_push_back(tokens, cur, sizeof(t_token))->content;
	reset_token(cur);
	return (ret);
}

//TODO: normify
t_list			*tokenize(const char *line, int line_id, int *multiline_string)
{
	t_token	cur;
	t_token	*last;
	t_list	*tokens;

	tokens = NULL;
	reset_token(&cur);
	while (*line && (cur.type == T_STRING || (*line != '#' && *line != ';')))
	{
		if (cur.type == T_WORD && ft_strchr(" \t,\"%", *line))
			delimit_token(&cur, &tokens, line, line_id);
		else if (cur.type == T_WORD && !tokens && *line == ':')
			delimit_token(&cur, &tokens, line++, line_id);
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
	last = delimit_token(&cur, &tokens, line, line_id);
	*multiline_string = last && last->type == T_START_STRING;
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
