/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2020/02/23 16:39:36 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include <stdint.h>

/*
** For the visu
*/
# include <libc.h>
# include <time.h>
# include <ncurses.h>
# include "libft.h"

# define MEMORY 4096
# define LINE_LENGTH 192
# define LINES_NB 64
# define OFFSET_COLS (((COLS / 4) * 3) - 192) / 2
# define OFFSET_LINES (LINES - 64 + 15) / 2
# define WRITING_LEN 4

/*
** COLORS
*/
# define J1 1
# define J2 2
# define J3 3
# define J4 4
# define EMPTY 5
# define ASCII 6
# define WHITE 7


/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

/*
** Mon commentaire:
** Les macros ci-dessous permettent de determiner l'OCP
*/

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				4096
# define IDX_MOD				(4096 / 8)
# define CHAMP_MAX_SIZE			(4096 / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define SIZE_TAB_PRO			1024

/*
** Mon commentaire:
** Ecrit sur les 4 premiers octets du binaire .cor juste avant le name
** indique dans le .s
*/
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
** Mon commentaire:
** prog_size correspond a la taille en octets prise
** par les instructions dans le .cor
*/

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_op
{
	char			*ope;
	int				nb_args;
	t_arg_type		type_args[MAX_ARGS_NUMBER];
	int				op_code;
	int				nb_cycles;
	char			*description;
	int				ocp;
	int				dir_size;
	int				modif_carry;
}					t_op;

typedef struct		s_arguments
{
	int				type;
	int				size;
	int32_t			value;
}					t_args;

typedef struct		s_pro
{
	uint32_t		reg[REG_NUMBER];
	struct s_pro	*next;
	struct s_pro	*prev;
	int64_t			curr_add;
	uint32_t		carry;
	uint32_t		nb_lives;
	uint32_t		cur_cycles;
	uint32_t		last_cycle_live;
	int32_t			index_champ;
	uint32_t		index_pro;
	uint8_t			curr_char;
}					t_pro;

typedef struct		s_champion
{
	uint8_t			prog[CHAMP_MAX_SIZE];
	t_header		header;
	int64_t			curr_add;
	uint64_t		id_champ;
	uint32_t		index_champ;
	uint32_t		nb_lives;
	uint32_t		last_cycle_live;
}					t_champ;

typedef struct s_corewar	t_cor;

extern	t_op		g_op_tab[17];

typedef	int			(*t_fnc[16])	(t_cor *cor, t_pro *pro);

typedef void		(*t_pf_verbose[15])(t_cor*, t_args[MAX_ARGS_NUMBER],
						t_pro *, int[2]);

typedef struct		s_owner
{
	uint8_t			owner;
	unsigned char	map_value;
}					t_owner;

typedef struct timespec		t_time;
typedef struct s_corewar	t_cor;

typedef struct		s_visu
{
	WINDOW		*vm;
	WINDOW		*dash;
	t_cor		*cor;
	t_owner		owner[MEMORY];
	t_time		time1;
	t_time		time2;
}					t_visu;

struct				s_corewar
{
	t_pro			*tab_process[SIZE_TAB_PRO];
	t_champ			champ[MAX_PLAYERS];
	t_fnc			dispatcher;
	uint8_t			owner[MEM_SIZE];
	uint8_t			map[MEM_SIZE];
	uint32_t		biggest_ind_pro;
	uint32_t		curr_ind_process;
	uint32_t		nb_champs;
	uint32_t		nb_checks;
	uint32_t		sum_lives;
	int32_t			cycles_to_die_ref;
	int32_t			cycles_to_die;
	uint32_t		nb_cycles;
	int64_t			nb_cycles_dump;
	uint32_t		dump_opt;
	uint32_t		show_opt;
	uint32_t		verbose;
	uint32_t		graphic;
};

/*
** levels of verbose (can be cumulated)
** (VERBOSE_DEATH and VERBOSE_PC are not implemented yet)
** Also VERBOSE_OPERATIONS differs from the original (this
** could be corrected or a legacy option could be added to
** mimic the original behavior for testing purposes)
*/

# define VERBOSE_LIVES		1
# define VERBOSE_CYCLES		2
# define VERBOSE_OP_LEGACY	4
# define VERBOSE_DEATH		8
# define VERBOSE_PC			16
# define VERBOSE_OPERATIONS	32

/*
**	Options + champions parsing functions
*/
int					read_binary(char *av, t_champ *champ);
int					read_magic(int file, t_champ *champ);
int					read_prog_name(int file, t_champ *champ);
int					read_prog_size(int file, t_champ *champ);
int					read_comment(int file, t_champ *champ);
int					read_prog(int file, t_champ *champ);
int					check_len_file(int file, char *av);
int					check_dump(int *nb_args, char ***av, t_cor *cor);
int					check_nb_opt(int *nb_args, char ***av,
									uint64_t *id_champ);

/*
**	VM Initialisation
*/
int					init_corewar(t_cor *cor, int nb_args, char **av);
int					parse_arguments(int argc, char **argv, t_cor *cor);
void				usage(char *name);
int					check_champs(t_cor *cor, char *name);

/*
**	Exec champions functions
*/
void				ft_exec_champs(t_cor *cor, t_visu *visu);
void				free_champs_process(t_cor *cor);
int					read_args(t_args args[MAX_ARGS_NUMBER],
						t_cor *cor, t_pro *pro);
void				adjust_curr_add(int64_t *address);
int					read_map(uint8_t map[MEM_SIZE], int64_t address);
uint32_t			sum_lives(t_cor *cor, int ind);
void				re_init_lives_champs(t_cor *cor);
void				refresh_process_posi(t_cor *cor, t_pro *pro,
											int curr, int dest);
void				get_curr_char(t_pro *pro, t_cor *cor);
void				write_map(t_cor *cor, int64_t addr, int value, int index_champ);

/*
** Utils for debug
*/
void				print_args(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
						int nb_args, int carry);
void				print_map(t_cor *cor);
int					champ_nb(uint32_t owner);

/*
** Printing functions
*/
void				introduce_champs(t_cor *cor);
void				verbose_pc(t_pro *tmp, t_cor *cor, int64_t tmp_add);
void				print_op(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
								t_pro *pro, int utils[2]);
void				verbose_sti(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
								t_pro *pro, int utils[2]);
void				verbose_ldi(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
								t_pro *pro, int utils[2]);
void				verbose_lld(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
								t_pro *pro, int utils[2]);
void				verbose_lldi(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
								t_pro *pro, int utils[2]);
void				verbose_add_sub(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
								t_pro *pro, int utils[2]);
void				verbose_and_or_xor(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
								t_pro *pro, int utils[2]);
void				verbose_forks(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
								t_pro *pro, int utils[2]);
void				verbose_live_zjmp(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
								t_pro *pro, int utils[2]);
void				verbose_ld(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
								t_pro *pro, int utils[2]);
void				verbose_st(t_cor *cor, t_args args[MAX_ARGS_NUMBER],
								t_pro *pro, int utils[2]);

/*
** FONCTIONS NCURSES_COREWAR
*/
void	get_info(t_visu *visu, t_cor *cor);
void	init_colors();
int		ft_visu(t_cor *cor, t_visu *visu);
int8_t	call_open(char *path);
void	windows_mgmt(t_visu *visu, int8_t fd_1, int8_t fd_2);
int		read_corewar(int fd, WINDOW *win, int8_t offset);
void	nprint_map(t_visu *visu, size_t len);
void	print_champ_area(t_visu *visu, int64_t curr_add);
void	call_map_check_process	(t_visu *visu);

#endif













