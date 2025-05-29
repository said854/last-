/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:59:09 by hakader           #+#    #+#             */
/*   Updated: 2025/05/26 17:53:39 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	cmp_key(void *a, void *b)
{
	return (ft_strncmp((const char *)a,
			(const char *)b, ft_strlen((char *)b) + 1));
}

void	ft_env_remove_if(t_env **env, void *data_ref,
			int (*cmp)(void *, void *))
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
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	excute_unset(t_shell **shell, t_list *alloc_list)
{
	char	**check;
	int		i;

	i = 1;
	if (check_options((*shell)->cmds, "unset"))
	{
		(*shell)->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if ((*shell)->cmds->args)
	{
		check = ft_split((*shell)->cmds->args[i], '=', alloc_list);
		if (!check)
			return (1);
	}
	while ((*shell)->cmds->args[i])
	{
		ft_env_remove_if(&((*shell)->env), (*shell)->cmds->args[i],
			cmp_key);
		i++;
	}
	(*shell)->exit_status = 0;
	return (EXIT_FAILURE);
}
