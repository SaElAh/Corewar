/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:55:00 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/31 18:37:08 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

enum	e_errors {E_WRONG_USAGE = 1, E_WRONG_FILE, E_OPEN_FILE, E_READ_FILE,
	E_EMPTY_FILE, E_UNKNOWN_TOKEN, E_UNEXPECTED_TOKEN,
	E_COMMAND_WITHOUT_ARGUMENT, E_MISSING_SEPARATOR, E_MISSING_ARGUMENTS,
	E_WRONG_ARGUMENT_TYPE, E_NO_LABEL_MATCH, E_WRITE_ERROR,
	E_UNFINISHED_STRING, E_NO_NAME, E_NO_COMMENT};

void	error_unknown_token(int len, const char *str, int line_id);
void	error_unexpected_token(int len, const char *str, int line_id);
void	error_command_without_argument(int len, const char *str, int line_id);

#endif
