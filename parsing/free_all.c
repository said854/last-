/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:06:52 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/03 17:26:44 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void free_array(char **arr)
// {
//     int i = 0;
//     while (arr[i])
//         free(arr[i++]);
//     free(arr);
// }
// void free_cmd(t_cmd *cmd)
// {
//     if (!cmd)
//         return;
//     if (cmd->args)
//         free_array(cmd->args);
//     if (cmd->infile)
//         free(cmd->infile);
//     if (cmd->outfile)
//         free(cmd->outfile);
//     if (cmd->heredoc_delim)
//         free(cmd->heredoc_delim);
//     free(cmd);
// }
// void //free_cmd_list(t_cmd *cmd_list)
// {
//     t_cmd *tmp;

//     while (cmd_list)
//     {
//         tmp = cmd_list->next;
//         free_cmd(cmd_list);
//         cmd_list = tmp;
//     }
// }
// void free_token_list(t_token *head)
// {
//     t_token *tmp;

//     while (head)
//     {
//         tmp = head->next;
//         if (head->value)
//             free(head->value);
//         free(head);
//         head = tmp;
//     }
// }
// void free_env_list(t_env *env)
// {
//     t_env *tmp;
//     while (env)
//     {
//         tmp = env->next;
//         free(env->key);
//         free(env->value);
//         free(env);
//         env = tmp;
//     }
// }

// void free_shell(t_shell *shell)
// {
// 	if (!shell)
// 		return;
// 	free_env_list(shell->env);
// 	free_token_list(shell->tokens);
// 	//free_cmd_list(shell->cmds);
// 	free(shell);
// }
