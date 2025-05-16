/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:21:24 by hakader           #+#    #+#             */
/*   Updated: 2025/05/16 16:21:31 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd *create_cmd(t_list *alloc_list)
{
	t_cmd *new_cmd = ft_malloc(sizeof(t_cmd), &alloc_list);
	if (!new_cmd)
		return (NULL);
	ft_bzero(new_cmd, sizeof(t_cmd));
	return (new_cmd);
}

static int calculate_args(t_cmd *cmd)
{
	int i = 0;
	if (!cmd->args)
		return 0;
	while (cmd->args[i])
		i++;
	return i;
}

char *remove_quotes(const char *str, t_list *alloc_list)
{
	int i = 0, j = 0;
	int in_single = 0, in_double = 0;
	char *result = ft_malloc(ft_strlen(str) + 1, &alloc_list);

	while (str[i])
	{
		if (str[i] == '"' && !in_single)
			in_double = !in_double, i++;
		else if (str[i] == '\'' && !in_double)
			in_single = !in_single, i++;
		else if (str[i] == '\\' && str[i + 1])
			result[j++] = str[++i], i++;
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int is_cmd_empty(t_cmd *cmd)
{
	return (!cmd->args && !cmd->infiles && !cmd->outfiles && !cmd->heredoc_delim);
}

static void add_arg_to_cmd(t_cmd *cmd, char *arg, t_list *alloc_list)
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

char **append_str_array(char **arr, char *new_str, t_list *alloc_list)
{
	int (i), (j);
	i = 0;
	while (arr && arr[i])
		i++;
	char **new_arr = ft_malloc(sizeof(char *) * (i + 2), &alloc_list);
	if (!new_arr)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_arr[j] = arr[j];
		j++;
	}
	new_arr[i] = new_str;
	new_arr[i + 1] = NULL;
	return (new_arr);
}
int get_int_array_length(int *arr)
{
	int	i;

	i = 0;
	while (arr && (arr[i] == 0 || arr[i] == 1))
		i++;
	return (i);
}


int *append_int_array(int *arr, int value, t_list *alloc_list)
{
	int	*new_arr;
	
	int (i), (j);
	i = get_int_array_length(arr);
	new_arr = ft_malloc(sizeof(int) * (i + 2), &alloc_list);
	if (!new_arr)
		return NULL;
	j = 0;
	while (j < i)
	{
		new_arr[j] = arr[j];
		j++;
	}
	new_arr[i] = value;
	new_arr[i + 1] = -1;
	return (new_arr);
}



void add_cmd_to_list(t_cmd **head, t_cmd *new_cmd)
{
	if (!*head)
		*head = new_cmd;
	else
	{
		t_cmd *temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
	}
}

t_heredoc_tmp	*realloc_array_heredocs(t_heredoc_tmp *old, int new_count, t_list *alloc_list)
{
	t_heredoc_tmp *new_array = ft_malloc(sizeof(t_heredoc_tmp) * new_count, &alloc_list);
	if (!old)
		return new_array;
	for (int i = 0; i < new_count - 1; ++i)
		new_array[i] = old[i];
	return new_array;
}

int handle_token_redirection_or_arg(t_token **current, t_cmd *cmd, t_list *alloc_list)
{
	t_token *token = *current;

	if (token->type == WORD)
		add_arg_to_cmd(cmd, token->value, alloc_list);
	else if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == APPEND || token->type == HEREDOC)
	{
		if (!token->next || token->next->type != WORD)
			return (print_error("near unexpected token"));
		char *target = ft_strdup(token->next->value, alloc_list);
		if (token->type == REDIR_IN)
			cmd->infiles = append_str_array(cmd->infiles, target, alloc_list);
		else if (token->type == REDIR_OUT || token->type == APPEND)
		{
			if (token->type == APPEND)
			{
				cmd->outfiles = append_str_array(cmd->outfiles, target, alloc_list);
				cmd->append_flags = append_int_array(cmd->append_flags, 1, alloc_list);
			}
			else
			{
				cmd->outfiles = append_str_array(cmd->outfiles, target, alloc_list);
				cmd->append_flags = append_int_array(cmd->append_flags, 0, alloc_list);
			}
		}

		else if (token->type == HEREDOC)
		{
			// printf("terget is%s\n", target);
			char *delim = remove_quotes(target, alloc_list);
			int expand = !is_quote(*token->next->value);
			cmd->heredocs = realloc_array_heredocs(cmd->heredocs, cmd->heredoc_count + 1, alloc_list);
			cmd->heredocs[cmd->heredoc_count].delim = delim;
			cmd->heredocs[cmd->heredoc_count].expand = expand;
			cmd->heredoc_count++;
		}
		*current = token->next;
	}
	return 1;
}

t_cmd *build_cmd_list(t_token *tokens, t_list *alloc_list)
{
	t_cmd *cmd_list = NULL;
	t_cmd *current_cmd = create_cmd(alloc_list);
	t_token *current = tokens;

	while (current)
	{
		if (current->type == PIPE)
		{
			current_cmd->has_pipe = 1;
			add_cmd_to_list(&cmd_list, current_cmd);
			current_cmd = create_cmd(alloc_list);
		}
		else if (current->type == SEMICOLON)
		{
			if (is_cmd_empty(current_cmd))
			{
				print_error ("near unexpected token `;'");
				return (NULL);
			}
			add_cmd_to_list(&cmd_list, current_cmd);
			current_cmd = create_cmd(alloc_list);
		}
		else
		{
			if (!handle_token_redirection_or_arg(&current, current_cmd, alloc_list))
				return NULL;
		}
		current = current->next;
	}
	if (!is_cmd_empty(current_cmd))
		add_cmd_to_list(&cmd_list, current_cmd);
	return (cmd_list);
}

