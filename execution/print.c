/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:40:15 by hakader           #+#    #+#             */
/*   Updated: 2025/05/28 15:05:11 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_list_env(t_env **head, t_list *alloc_list)
{
	t_env	*sorted = copy_env(*head, alloc_list);
	t_env	*i = sorted;
	t_env	*j;

	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0)
				swap_env(i, j);
			j = j->next;
		}
		i = i->next;
	}
	while (sorted)
	{
		if (sorted->value)
			printf("declare -x %s=\"%s\"\n", sorted->key, sorted->value);
		else
			printf("declare -x %s\n", sorted->key);
		sorted = sorted->next;
	}
}

void print_cmd_list(t_cmd *cmd_list)
{
    int i;
    int cmd_num = 1;

    while (cmd_list)
    {
        printf("🔹 CMD %d:\n", cmd_num++);

        // Args
        printf("  args    = ");
        if (cmd_list->args)
        {
            i = 0;
            while (cmd_list->args[i])
                printf("\"%s\" ", cmd_list->args[i++]);
        }
        else
            printf("(none)");
        printf("\n");

        // Infiles
        printf("  infiles  = ");
        if (cmd_list->infiles)
        {
            i = 0;
            while (cmd_list->infiles[i])
                printf("\"%s\" ", cmd_list->infiles[i++]);
        }
        else
            printf("(none)");
        printf("\n");

        // Outfiles
        printf("  outfiles = ");
        if (cmd_list->outfiles)
        {
            i = 0;
            while (cmd_list->outfiles[i])
                printf("\"%s\" ", cmd_list->outfiles[i++]);
        }
        else
            printf("(none)");
        printf("\n");

        // Append flags
        printf("  append flags = ");
        int *flags = cmd_list->append_flags;
        for (int i = 0; flags && flags[i] != -1; i++)
            printf("%d ", flags[i]);
        printf("\n");

        // Pipe flag
        printf("  pipe    = %s\n", cmd_list->has_pipe ? "true" : "false");
          printf("  redirection  = ");
        if (cmd_list->rediriction)
        {
            i = 0;
            while (cmd_list->rediriction[i])
                printf("\"%s\" ", cmd_list->rediriction[i++]);
        }
        else
            printf("(none)");
        printf("\n");
        // Heredoc list (if you stored them in heredocs array)
        if (cmd_list->heredoc_count > 0)
        {
            printf("  heredocs =\n");
            for (i = 0; i < cmd_list->heredoc_count; i++)
            {
                printf("    [%d] delim=\"%s\" expand=%d\n",
                    i,
                    cmd_list->heredocs[i].delim ? cmd_list->heredocs[i].delim : "(null)",
                    cmd_list->heredocs[i].expand
                );
            }
        }
        else
            printf("  heredocs = (none)\n");

        // Final heredoc used
        printf("  heredoc used = %s\n", cmd_list->heredoc_delim ? cmd_list->heredoc_delim : "(null)");
        printf("  heredoc expand = %d\n", cmd_list->heredoc_expand);
        printf("  heredoc fd = %d\n", cmd_list->heredoc_fd);
        printf("\n");

        cmd_list = cmd_list->next;
    }
}



void print_list(t_token *head)
{
	t_token *tmp = head;

	while (tmp)
	{
		printf("value: %s || type: %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}
