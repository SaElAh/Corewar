/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:55:00 by yforeau           #+#    #+#             */
/*   Updated: 2020/01/18 13:27:32 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

enum	e_errors {E_WRONG_USAGE = 1, E_WRONG_FILE, E_OPEN_FILE, E_READ_FILE,
	E_EMPTY_FILE, E_UNKNOWN_TOKEN, E_UNEXPECTED_TOKEN,
	E_COMMAND_WITHOUT_ARGUMENT, E_LABEL_DECLARED_TWICE, E_MISSING_SEPARATOR,
	E_MISSING_ARGUMENTS, E_WRONG_ARGUMENT_TYPE, E_PROGRAM_TOO_BIG};

void	error_unknown_token(int len, const char *str, int line_id);
void	error_unexpected_token(int len, const char *str, int line_id);

#endif
