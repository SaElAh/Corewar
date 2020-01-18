/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 13:11:42 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/18 20:09:18 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPILER_H
# define COMPILER_H

# include "asm_parser.h"

void	compiler(t_asmdata *adat);
void	compile_labels(t_asmdata *adat);

#endif
