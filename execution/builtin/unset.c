/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:53:42 by hakader           #+#    #+#             */
/*   Updated: 2025/05/13 10:34:38 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_env_remove_if(t_env **env, void *data_ref,
			int (*cmp)(void *, void *), void (*del)(void *))
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (cmp(curr->key, data_ref) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			if (del)
			{
				del(curr->key);
				del(curr->value);
			}
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	cmp_key(void *a, void *b)
{
	return (strncmp((char *)a,
			(char *)b, ft_strlen((char *)b) + 1));
}

int	excute_unset(t_shell **shell, t_list *alloc_list)
{
	(void)shell;
	char	**check;
	int	i;

	i = 1;
	if ((*shell)->cmds->args)
	{
		check = ft_split((*shell)->cmds->args[i], '=', alloc_list);
		if (!check)
			return (1);
		else if (ft_strcmp(check[0], "USER") == 0)
		{
			(*shell)->exit_status = 1;
			return ((put_error("can't unset USER")), 1);
		}
	}
	while ((*shell)->cmds->args[i])
	{
		ft_env_remove_if(&((*shell)->env), (*shell)->cmds->args[i],
						cmp_key, free);
		i++;
	}
	(*shell)->exit_status = 0;
	return (EXIT_FAILURE);
}
