/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:47:57 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/17 22:19:49 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_quote(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if(str[i] == '"' || str[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
