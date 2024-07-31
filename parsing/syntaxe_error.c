/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:36:37 by lamhal            #+#    #+#             */
/*   Updated: 2024/07/30 10:55:39 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// int	check_syntaxe_error(t_list *lst)
// {
// t_list*tmp;

// if (lst == NULL)
// return (1);
// tmp = lst;
// if(tmp->type == 0)
// return(ft_putstr_fd("syntaxe error near | \n", 2), 1);
// while (tmp->next)
// {
// if (tmp->type == 0 && tmp->next->type == 0)
// return(ft_putstr_fd("syntaxe error near | \n", 2), 1);
// else if ((tmp->type > 0  && tmp->type < 5) && ( tmp->next->type >= 0
// && tmp->next->type < 5) )
// return(ft_putstr_fd("syntaxe error near ", 2),
// ft_putstr_fd(tmp->next->content, 2), ft_putstr_fd("\n",2), 1);
// tmp = tmp->next;
// }
// if (tmp->type >= 0 && tmp->type < 5)
// return(ft_putstr_fd("syntaxe error near newline\n", 2), 1);
// return (0);
// }

int	check_syntaxe_error(t_list *lst)
{
	t_list	*tmp;
	t_list  *tmp1;

	if (lst == NULL)
		return (1);
	tmp = lst;
	if(tmp->type == 0)
		return(ft_putstr_fd("syntaxe error near | \n", 2), 1);
	while (tmp->next)
	{
		tmp1 = tmp->next;
		if (tmp->type == Pipe && (tmp1->type == Pipe ||
			(tmp1->type == space && tmp1->next == Pipe)))
			return(ft_putstr_fd("syntaxe error near | \n", 2), 1);
		else if ((tmp->type > 0  && tmp->type < 5) && ( tmp->next->type >= 0
				&& tmp->next->type < 5) )
			return(ft_putstr_fd("syntaxe error near ", 2),
				ft_putstr_fd(tmp->next->content, 2), ft_putstr_fd("\n",2), 1);
		if ((tmp->type > 0  && tmp->type < 5) && (tmp1->type == 8) &&
			( tmp1->next->type >= 0 && tmp1->next->type < 5) )
			return(ft_putstr_fd("syntaxe error near ", 2),
				ft_putstr_fd(tmp1->next->content, 2), ft_putstr_fd("\n",2), 1);
		tmp = tmp->next;
	}
	if (tmp->type == dquot && tmp->content[ft_strlen(tmp->content) - 1] != '\"')
		return (ft_putstr_fd("syntaxe error missing dqout\n", 2),  1);
	else if (tmp->type == squot && tmp->content[ft_strlen(tmp->content) - 1] != '\'')
		return (ft_putstr_fd("syntaxe error missing sqout\n", 2),  1);
	else if (tmp->type >= 0 && tmp->type < 5)
		return(ft_putstr_fd("syntaxe error near newline\n", 2), 1);
	return (0);
}
