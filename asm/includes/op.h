/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:39:35 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/18 19:35:16 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE


# define IND_BYTE_SIZE			2
# define REG_BYTE_SIZE			1
# define DIR_BYTE_SIZE			REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define OP_COUNT				16

/*
**
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

/*
**
*/

# define COREWAR_EXEC_MAGIC		0xea83f3
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define NULL_SEP				4

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
