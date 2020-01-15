/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_asmdata.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:23:02 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/15 16:02:23 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_ASMDATA_H
# define S_ASMDATA_H

# include "libft.h"
# include "op.h"

/*
**
** Main asm data structure:
**
** file_name:	name of the input file (for the output)
** file:		stores every line of the input file in a chained list
** tokens:		array of chained list of file_len size storing the tokens
** file_len:	number of lines in the input file
** ops:			chained list of every operation in a compilable format
** ops_len:		number of operations
** labels:		chained list of every labels and their op reference
** prog_name:	value of the ".name" command
** prog_size:	length of the prog code
** comment:		value of the ".comment" command
** prog:		executable code
**
*/

typedef struct		s_asmdata
{
	const char		*file_name;
	t_list			*file;
	t_list			**tokens;
	size_t			file_len;
	t_list			*ops;
	size_t			ops_len;
	t_list			*labels;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	unsigned char	prog[CHAMP_MAX_SIZE];
}					t_asmdata;

#endif
