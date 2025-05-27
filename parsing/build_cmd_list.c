/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:49:25 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/26 16:40:46 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*create_cmd(t_list *alloc_list)
{
	t_cmd	*new_cmd;

	new_cmd = ft_malloc(sizeof(t_cmd), &alloc_list);
	if (!new_cmd)
		return (NULL);
	ft_bzero(new_cmd, sizeof(t_cmd));
	return (new_cmd);
}

static int	calculate_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->args)
		return (0);
	while (cmd->args[i])
		i++;
	return (i);
}

void	add_arg_to_cmd(t_cmd *cmd, char *arg, t_list *alloc_list)
{
	char	*clean;
	char	**args;

	int (old_len), (i);
	clean = remove_quotes(arg, alloc_list);
	old_len = calculate_args(cmd);
	args = ft_malloc(sizeof(char *) * (old_len + 2), &alloc_list);
	if (!args)
		return ;
	i = 0;
	while (i < old_len)
	{
		args[i] = cmd->args[i];
		i++;
	}
	args[old_len] = clean;
	args[old_len + 1] = NULL;
	cmd->args = args;
}

void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*temp;

	if (!*head)
		*head = new_cmd;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
	}
}
