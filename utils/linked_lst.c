/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:02:43 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/29 08:38:33 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node -> content = content;
	node -> fd = -1;
	node -> next = NULL;
	return (node);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp -> next;
	return (tmp);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	tmp = ft_lstlast(*lst);
	if (!tmp)
		*lst = new;
	else
		tmp->next = new;
}

void	ft_lstadd_midl(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	tmp = *lst;
	if (!tmp->next)
		ft_lstadd_back(lst, new);
	else
	{
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)-> next;
		(tmp->fd > -1) && close(tmp->fd);
		free(tmp->content);
		free(tmp);
	}
	lst = NULL;
}
