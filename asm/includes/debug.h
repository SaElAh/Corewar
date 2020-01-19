/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 23:19:21 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/19 23:21:20 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "s_asmdata.h"

void	print_file(t_list *file);
void	print_tokens(t_list **tokens, int len);
void	print_ops(t_parsed_op *ops, size_t ops_len);
void	print_labels(t_list *labels);
void	print_hex_prog(t_asmdata *adat);

#endif
