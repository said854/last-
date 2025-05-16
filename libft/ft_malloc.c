/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:53:14 by hakader           #+#    #+#             */
/*   Updated: 2025/05/03 17:32:29 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (lst == NULL)
		return ;
	node = ft_lstlast(*lst);
	if (*lst)
		node->next = new;
	else
		*lst = new;
}

void *ft_malloc(size_t size, t_list **alloc_list)
{
    void *ptr = malloc(size);
    if (!ptr) {
        perror("malloc");
        return NULL;
    }
    t_list *new_node = ft_lstnew(ptr);
    if (!new_node) {
        free(ptr);  // Ensure we free the malloc-ed pointer if ft_lstnew fails
        return NULL;
    }
    ft_lstadd_back(alloc_list, new_node);
    return ptr;
}



void free_all(t_list *alloc_list)
{
    t_list *current_node;
    t_list *next_node;

    current_node = alloc_list;
    while (current_node)
    {
        next_node = current_node->next;
        free(current_node->content);  // Free the content of the node
        free(current_node);           // Free the node itself
        current_node = next_node;
    }
}
