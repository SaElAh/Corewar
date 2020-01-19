/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:39:35 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/19 22:45:06 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
** size of each argument type in the executable (in bytes)
*/

# define IND_BYTE_SIZE			2
# define REG_BYTE_SIZE			1
# define DIR_BYTE_SIZE			4
# define OP_BYTE_SIZE_MAX		18

/*
** values to write in the arg_type byte to code each argument type
*/

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define OP_COUNT				16

/*
** type of argument accepted for each instruction (in s_op.arg_types)
*/

# define T_REG					1
# define T_DIR					2
# define T_IND					4

# define COREWAR_EXEC_MAGIC		0xea83f3
# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define NULL_SEP				4

/*
** s_op:
** name:			string id of the instruction
** argc:			number of arguments it takes
** arg_types:		accepted types for each argument
** arg_type_code:	boolean indicating if the instruction has an arg_type
** 					coding byte (only if multiple types are possible)
** mod_tdir_size:	boolean indicating if the size of a T_DIR argument
**					is the same as a T_IND (2) or the default (4)
*/

typedef struct		s_op
{
	const char		*name;
	unsigned int	argc;
	unsigned char	arg_types[MAX_ARGS_NUMBER];
	unsigned int	arg_type_code;
	unsigned int	mod_tdir_size;
}					t_op;

extern const t_op	g_op_tab[OP_COUNT + 1];

#endif
