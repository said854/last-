/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:00:53 by hakader           #+#    #+#             */
/*   Updated: 2025/05/13 10:39:24 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_this(t_env **env_list, char *sch)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, sch) == 0)
			printf("key = %s, value = %s", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("%s", arr[i]);
		if (arr[i + 1])
			printf(" ");
		i++;
	}
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	if (!args || !args[i])
		return (EXIT_SUCCESS);
	while (args[i])
		i++;
	return (i);
}

void	mini_display(void)
{
	printf(GREEN"\n  ____  ____  _          _ _\n"
		" | ___|/ ___|| |__   ___| | |\n"
		" | |_  \\___ \\| '_ \\ / _ \\ | |\n"
		" |  _|  ___) | | | |  __/ | |\n"
		" |_|   |____/|_| |_|\\___|_|_|\n\n"RESET);
}
