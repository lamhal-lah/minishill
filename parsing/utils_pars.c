/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 04:49:02 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/29 13:39:53 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_type(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (0);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (3);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (4);
	else if (str[0] == '\"')
		return (5);
	else if (str[0] == '\'')
		return (6);
	else if (str[0] == '$' && str[1] != '\0')
		return (7);
	else if (str[0] == ' ')
		return (8);
	return (9);
}

int	find_type_limter(t_list *lst)
{
	t_list	*tmp;
	int		type;

	tmp = lst;
	type = limtr;
	while (tmp && tmp->type != space && tmp->type > 4)
	{
		if (tmp->type == dquot || tmp->type == squot)
			type = limtr_qt;
		tmp = tmp->next;
	}
	return (type);
}

void	flag_limitter(t_list *lst)
{
	t_list	*tmp;
	int		type;

	tmp = lst;
	while (tmp && tmp->next)
	{
		if (tmp->type == herdoc)
		{
			tmp && (tmp = tmp->next);
			if (tmp->type == space && tmp->next)
				tmp = tmp->next;
			type = find_type_limter(tmp);
			while (tmp && tmp->type != space && tmp->type > 4)
			{
				tmp->type = type;
				tmp = tmp->next;
			}
		}
		tmp && (tmp->type != herdoc) && (tmp = tmp->next);
	}
}

void	mark_spaces(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, " ", 2))
			tmp->type = space;
		tmp = tmp->next;
	}
}
