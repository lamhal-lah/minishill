/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:53:05 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/15 13:15:06 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_empty_node(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while(tmp && tmp->next)
	{
	
		if(tmp->next->content == NULL)
			ft_remove_node(&tmp->next);
		else
			tmp = tmp->next;
	}
	tmp = *lst;
	while(tmp && tmp->next)
	{
	
		if(tmp->type == space && tmp->next->type == space)
			ft_remove_node(&tmp->next);
		else
			tmp = tmp->next;
	}
}

// void	remove_empty_node(t_list **lst)
// {
// 	t_list	*tmp;

// 	tmp = *lst;
// 	while(tmp && tmp->next)
// 	{
// 		if (tmp->next->type == space && tmp->next->next->content == NULL)
// 		{
// 			ft_remove_node(&tmp->next);
// 			ft_remove_node(&tmp->next);
// 		}
// 		else if(tmp->next->content == NULL)
// 			ft_remove_node(&tmp->next);
// 		else
// 			tmp = tmp->next;
// 	}
// }