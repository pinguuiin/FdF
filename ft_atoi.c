/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 03:41:01 by piyu              #+#    #+#             */
/*   Updated: 2024/11/09 22:35:40 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi(const char *nptr)
{
	int			sign;
	long long	num;

	sign = 0;
	num = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if ((*nptr == 43 || *nptr == 45) && sign == 0)
	{
		sign = 44 - *nptr;
		nptr++;
	}
	if ((*nptr == 43 || *nptr == 45) && sign != 0)
		return (0);
	while (*nptr >= 48 && *nptr <= 57)
	{
		num = (num * 10) + (*nptr - 48);
		if (num < 0)
			return (0);
		nptr++;
	}
	if (sign == -1)
		num *= -1;
	return (num);
}
