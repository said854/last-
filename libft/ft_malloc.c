/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:53:14 by hakader           #+#    #+#             */
/*   Updated: 2025/05/17 16:36:44 by sjoukni          ###   ########.fr       */
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

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		node = ft_lstlast(*lst);
		if (node)
			node->next = new;
	}
}


void	*ft_malloc(size_t size, t_list **alloc_list)
{
	void	*ptr;
	t_list	*new_node;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("malloc");
		return (NULL);
	}
	if (!alloc_list)
		return (ptr); 
	new_node = ft_lstnew(ptr);
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(alloc_list, new_node);
	return (ptr);
}


void	free_all(t_list **alloc_list)
{
	t_list	*current_node;
	t_list	*next_node;

	if (!alloc_list)
		return ;
	current_node = *alloc_list;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	*alloc_list = NULL;
}

