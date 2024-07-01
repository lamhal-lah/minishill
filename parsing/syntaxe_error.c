/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:36:37 by lamhal            #+#    #+#             */
/*   Updated: 2024/07/01 15:23:26 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	check_couts(char *line)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == 34)
			j++;
		else if (line[i] == 39)
			k++;
		i++;
	}
	if (j % 2 == 1)
		return (ft_putstr_fd("syntaxe error missing dqout\n", 2), 1);
	if (k % 2 == 1)
		return (ft_putstr_fd("syntaxe error missing qout\n", 2), 1);
	return (0);
}

int	check_syntaxe_error(t_list *lst)
{
	t_list	*tmp;

	if (lst == NULL)
		return (1);
	tmp = lst;
	if(tmp->type == 0)
		return(ft_putstr_fd("syntaxe error near | \n", 2), 1);
	while (tmp->next)
	{
		if (tmp->type == 0 && tmp->next->type == 0)
			return(ft_putstr_fd("syntaxe error near | \n", 2), 1);
		else if ((tmp->type > 0  && tmp->type < 5) && ( tmp->next->type >= 0
				&& tmp->next->type < 5) )
			return(ft_putstr_fd("syntaxe error near ", 2),
				ft_putstr_fd(tmp->next->content, 2), ft_putstr_fd("\n",2), 1);
		tmp = tmp->next;
	}
	if (tmp->type >= 0 && tmp->type < 5)
		return(ft_putstr_fd("syntaxe error near newline\n", 2), 1);
	return (0);
}