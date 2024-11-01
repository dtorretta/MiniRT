/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtorrett <dtorrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:17:54 by dtorrett          #+#    #+#             */
/*   Updated: 2024/05/13 21:10:48 by dtorrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtorrett <dtorrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:37:31 by dtorrett          #+#    #+#             */
/*   Updated: 2024/05/13 17:11:52 by dtorrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_isdigit(int c)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	else
// 		return (0);
// }
static double	double_number(char *nptr, int i, double result)
{
	double	factor;

	factor = 1.0;
	while (ft_isdigit(nptr[i]))
	{
		factor *= 0.1;
		result = result + ((nptr[i] - '0') * factor);
		i++;
	}
	return (result);
}

double	ft_atof(char *nptr)
{
	long	i;
	int		sign;
	double	result;

	sign = 1;
	result = 0.0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) && nptr[i])
	{
		result = (result * 10) + nptr[i] - '0';
		i++;
	}
	if (nptr[i] == '.')
		result = double_number(nptr, ++i, result);
	return (result * sign);
}

// int	main(void)
// {
// 	char a[] = "1.0";

// 	printf("%f\n", ft_atof(a));
// 	return (0);
// }