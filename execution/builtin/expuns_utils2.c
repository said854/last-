/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expuns_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:48:45 by hakader           #+#    #+#             */
/*   Updated: 2025/05/13 11:05:41 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	remove_env_var(t_env **envp, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *envp;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (prev)
				prev->next = current->next;
			else
				*envp = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	is_new_line(char *arg)
{
	int	j;

	j = 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (EXIT_SUCCESS);
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (EXIT_FAILURE);
}

void	env_path(t_env **env_list, t_cmd *cmd)
{
	if (!cmd->args[1])
		print_this(env_list, "HOME");
}

int	execute_exit(t_shell *shell, t_list *alloc_list)
{
	int	status;

	printf("Exit status: %d\n", shell->exit_status);
	status = shell->exit_status;
	if (count_args(shell->cmds->args) > 2)
	{
		put_error("exit: too many arguments");
		return (1);
	}
	if (count_args(shell->cmds->args) > 1)
	status = ft_atoi(shell->cmds->args[1], alloc_list);
	free_all(alloc_list);
	// printf("exit\n");
	exit (status);
}
