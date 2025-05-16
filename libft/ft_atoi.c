/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:12:11 by hakader           #+#    #+#             */
/*   Updated: 2025/05/16 23:17:10 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	exit_error(const char *str, t_list *alloc_list)
{
	put_error("exit");
	write(2, "exit: ", ft_strlen("exit: "));
	write(2, str, ft_strlen(str));
	put_error(": numeric argument required");
	free_all(&alloc_list);
	exit(EXIT_INVALID_ARGS);
}

long	ft_atoi(const char *str, t_list *alloc_list)
{
	long long	result;

	int (i), (sign);
	i = 0;
	sign = 1;
	result = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > ((LONG_MAX - (str[i] - '0')) / 10))
			exit_error(str, alloc_list);
		result = result * 10 + (str[i] - 48);
		i++;
	}
	result = (long)result;
	if (str[i])
		exit_error(str, alloc_list);
	return (sign * result);
}
