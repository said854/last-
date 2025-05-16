/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:58:34 by hakader           #+#    #+#             */
/*   Updated: 2025/05/16 18:37:47 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void	update_env(t_env **env, char *key, char *replace, t_list *alloc_list)
{
	t_env	*tmp;

	if (!key || !replace)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			tmp->value = ft_strdup(replace, alloc_list);
			free (replace);
			return ;
		}
		tmp = tmp->next;
	}
}

char	**get_paths(t_shell **shell, t_list *alloc_list)
{
	t_env	*tmp;

	tmp = (*shell)->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			return (ft_split(tmp->value, ':', alloc_list));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*check_cmd(char **paths, char *cmd, t_list *alloc_list)
{
	char	*command;
	int		i;

	if (!cmd || !paths || !paths[0])
		return (NULL);
	i = 0;
	while (paths[i])
	{
		command = ft_strjoin(paths[i], "/", alloc_list);
		command = ft_strjoin(command, cmd, alloc_list);
		if (access(command, X_OK) == 0)
			return (command);
		i++;
	}
	return (NULL);
}
