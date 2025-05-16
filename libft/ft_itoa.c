/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:00:08 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/03 16:42:16 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n, t_list *alloc_list)
{
	int		len;
	char	*ptr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648", alloc_list));
	len = ft_len(n);
	ptr = (char *)ft_malloc((len + 1), &alloc_list);
	if (ptr == NULL)
		return (NULL);
	ptr[len] = '\0';
	if (n < 0)
	{
		n = -n;
		ptr[0] = '-';
	}
	if (n == 0)
		ptr[0] = '0';
	len--;
	while (n > 0)
	{
		ptr[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (ptr);
}
