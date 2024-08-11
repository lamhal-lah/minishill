/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:02:43 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/09 16:08:34 by lamhal           ###   ########.fr       */
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

void	ft_lstadd_front(t_list **l, t_list *new)
{
	if (!new || !l)
		return ;
	new -> next = *l;
	*l = new;
}

void	ft_remove_node(t_list **lst)
{
	t_list	*tmp;
	
	if (!lst)
		return ;
	
	tmp = *lst;
	//printf ("tmp:%s  %d\n", tmp->content, tmp->type);
	*lst = (*lst)->next; // [2], null , [4]
	//printf ("tmp:%d  %d\n", (*lst) == NULL, tmp == NULL);
	free(tmp->content);
	free(tmp);
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
		free(tmp->content);
        free(tmp);
	}
    lst = NULL;
}

// int	main()
// {
// 	t_list *lst;
// 	t_list *node;
// 	t_list *tmp;

// 	lst = NULL;
// 	node = ft_lstnew("a");
// 	ft_lstadd_back(&lst, node);
// 	node = ft_lstnew("b");
// 	ft_lstadd_back(&lst, node);
// 	node = ft_lstnew("c");
// 	ft_lstadd_back(&lst, node);
// 	node = ft_lstnew("5");
// 	ft_lstadd_midl(&lst->next, node);
// 	tmp = lst;
// 	tmp = tmp->next;
// 	ft_remove_node(&tmp);
// 	while(lst)
// 	{
// 		printf("%s\n", lst->content);
// 		lst = lst->next;
// 	}
// }