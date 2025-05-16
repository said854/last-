/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:36:31 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/16 22:55:55 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

t_token *create_token(char *str, t_token_type type, t_list *alloc_list)
{
    t_token *new_token = ft_malloc(sizeof(t_token), &alloc_list);
    if (!new_token)
        return NULL;
    new_token->value = ft_strdup(str, alloc_list);
    new_token->type = type;
    new_token->next = NULL;
    return new_token;
}

void append_token(t_token **head, t_token *new)
{
    if (!*head)
    {
        *head = new;
        return;
    }
    t_token *temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
}

int get_token_length(char *line, int i)
{
    int start;
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (line[i] && ft_isspace(line[i]))
        i++;
    start = i;

    if (line[i] == ';')
    {
        if (line[i + 1] == ';')
            return -2;
        return 1;
    }
    if (is_operator(line[i]))
    {
        if (is_operator(line[i + 1]) && line[i] == line[i + 1] && line[i] != '|')
            return 2;
        return 1;
    }

    while (line[i])
    {
        if (line[i] == '`')
            return -4;
        if (line[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote, i++;
        else if (line[i] == '"' && !in_single_quote)
            in_double_quote = !in_double_quote, i++;
        else if (line[i] == '\\')
        {
            if (!line[i + 1])
                return -3;
            i += 2;
        }
        else
        {
            if (!in_single_quote && !in_double_quote &&
                (line[i] == ';' || ft_isspace(line[i]) || is_operator(line[i])))
                break;
            i++;
        }
    }
    if (in_single_quote || in_double_quote)
        return -1;
    return i - start;
}

t_token_type get_token_type(char *str)
{
    if (!strcmp(str, "|")) return PIPE;
    if (!strcmp(str, ">")) return REDIR_OUT;
    if (!strcmp(str, ">>")) return APPEND;
    if (!strcmp(str, "<")) return REDIR_IN;
    if (!strcmp(str, "<<")) return HEREDOC;
    if (!strcmp(str, ";")) return SEMICOLON;
    return WORD;
}

t_token *return_syntax(t_shell *shell, int len)
{
    if (len == -1)
    {
        print_error("unclosed quote");
        shell->exit_status = 258;
    }
    else if (len == -2)
    {
        print_error("near `;;'");
        shell->exit_status = 2;
    }
    else if (len == -3)
    {
        print_error("near `\\'");
        shell->exit_status = 258;
    }
    else if (len == -4)
    {
        print_error("near ``'");
        shell->exit_status = 258;
    }
    return (NULL);
}
int check_single(char *str)
{
    int i = 0;
    int single = 0;

    while (str[i] && str[i] != '$')
    {
        if(str[i] == '\'')
            single ++;
        i++;
    }
    if(single % 2 == 0)
        return 0;
    return 1;
    
}


t_token *tokenize_line(t_shell *shell, char *line, t_list *alloc_list)
{
    int i = 0, len;
    t_token *head = NULL;
    char *token_str;
    t_token_type type;
    int is_quete = 0;
    while (line[i])
    {
        while (ft_isspace(line[i]))
            i++;
        if (!line[i])
            break;

        len = get_token_length(line, i);
        if (len < 0)
            return (return_syntax(shell, len));
        token_str = strndup(line + i, len);
        type = get_token_type(token_str);
        if (type == WORD && ft_strchr(token_str, '$') && (!check_single(token_str)))
        {
            char *expanded = expand_token_value(token_str, shell, alloc_list);
            append_token(&head, create_token(expanded, type, alloc_list));
        }
        else
            append_token(&head, create_token(token_str, type, alloc_list));
        free(token_str);
        i += len;
    }
    return (head);
}
