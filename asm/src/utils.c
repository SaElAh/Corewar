/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:59:54 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/15 13:41:22 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static long int	ft_strtol(const char *nptr)
{
	unsigned long	acc;
	unsigned long	cutoff;
	int				neg;
	int				cutlim;

	acc = 0;
	neg = 0;
	while (*nptr == 32 || (*nptr > 8 && *nptr < 14))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		neg = *nptr++ == '-';
	cutoff = (unsigned long)LONG_MAX + neg;
	cutlim = (cutoff % 10) + 48;
	cutoff /= 10;
	while (*nptr > 47 && *nptr < 58
		&& (acc < cutoff || (acc == cutoff && *nptr <= cutlim)))
			acc = (acc * 10) + (*nptr++ - 48);
	if (*nptr > 47 && *nptr < 58) 
		acc = neg ? LONG_MIN : LONG_MAX;
	else if (neg)
		acc = -acc;
	return (acc);
}

int				ft_std_atoi(const char *str)
{
	return ((int)ft_strtol(str));
}
