/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 00:21:40 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/18 20:25:22 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_PARSER_H
# define ASM_PARSER_H

# include "s_asmdata.h"

/*
** s_label:
** name:		name in code
** name_len:	length of name (because stored in file)
** op_ref:		index of the operation in the ops array
**				to which the label refers
** line:		line where the label was found (for debugging)
*/

typedef struct		s_label
{
	const char		*name;
	size_t			name_len;
	int				op_ref;
	int				line;
}					t_label;

void				asm_parser(t_asmdata *adat);
int					label_cmp(void *l1, void *l2);
void				add_label(t_asmdata *adat, t_token *cur,
						int line, int op_ref);
void				parse_instruction(t_asmdata *adat, t_list *tokens,
						int line, int op_ref);

#endif
