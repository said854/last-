/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:11:01 by hakader           #+#    #+#             */
/*   Updated: 2025/05/16 23:17:32 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_exit(t_shell *shell, t_list *alloc_list)
{
	long	status;

	status = (long)shell->exit_status;
	status = ft_atoi(shell->cmds->args[1], alloc_list);
	if (count_args(shell->cmds->args) > 2)
	{
		put_error("exit: too many arguments");
		status = 1;
	}
	free_all(&alloc_list);
	printf("exit\n");
	printf("%ld", status);
	exit (status);
}
