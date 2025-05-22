/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:19:01 by hakader           #+#    #+#             */
/*   Updated: 2025/05/19 21:12:05 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	io_error(t_shell *shell)
{
	ft_putstr_fd("No such file or directory\n", 2);
	shell->exit_status = EXIT_INVALID_ARGS;
	return (EXIT_FAILURE);
}
