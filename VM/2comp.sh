#!/bin/bash

FILES="op.c main.c read_file_utils.c check_len_file.c rdm_utils.c "
FILES+="exec_champs.c read_args.c read_write_map.c verbose_pc.c "
FILES+="init_champs.c introduce_champs.c parse_arguments.c "
FILES+="aff_instruction.c live_instruction.c load_instructions.c operations_instructions.c store_instructions.c zjmp_instruction.c fork_instructions.c "
FILES+="verbose_op_legacy.c verbose_op_legacy_2.c verbose_op_legacy_3.c "
FILES+="process_live_fct.c check_champs.c usage.c "
FILES+="ncurses/visu_corewar_init.c ncurses/visu_corewar.c ncurses/get_next_line.c ncurses/libft/libft.a "
FILES+="ncurses/visu_corewar_ascii.c ncurses/visu_corewar_utils.c "

V=" -lncurses -lform"
W=" -Wall -Wextra -Werror"
FS=" -fsanitize=address,undefined"
COMP="gcc -g"

if [ $# -eq 0 ];
	then rm -rf a.out.dSYM a.out
else
	while [ "$1" != "" ]; do
		echo $1
		if [ "$1" == "W" ];
			then COMP+=$W
		fi
		if [ "$1" == "FS" ];
			then COMP+=$FS
		fi
		if [ "$1" == "v" ];
			then COMP+=$V
		fi
		shift
	done
	echo $COMP
	$COMP $FILES
fi

