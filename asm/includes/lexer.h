/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:35:16 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/14 15:12:25 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

enum						e_token_type {T_WORD, T_STRING, T_SEPARATOR, T_NONE};

# define TOKEN_TYPE_COUNT	4

enum						e_token_word_id {I_COMMAND, I_LABEL,
	I_INSTRUCTION, I_REGISTER, I_DIRECT, I_INDIRECT, I_DIRECT_LABEL,
	I_INDIRECT_LABEL, I_NONE};

# define TOKEN_ID_COUNT		10

typedef struct				s_token
{
	enum e_token_type		type;
	enum e_token_word_id	id;
	int						op_code;
	char					*str;
	int						len;
}							t_token;

t_list						**lexer(t_list *file);
enum e_token_word_id		get_word_id(t_token *cur, int line_id);
void						error_unknown_token(int len, const char *str,
								int line_id);

#endif
