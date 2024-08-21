/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambgus.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:20:38 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/21 18:46:20 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ambigus_one(t_list *lst, t_env *env, t_list *lst1)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp->type == var)
	{
		while (tmp && tmp->type == var)
		{
			if (count_lenght(tmp, env, lst1) == 0)
				tmp = tmp->next;
			else
				break ;
		}
		if (!tmp || (tmp && (tmp->type <= 4 || tmp->type == space)))
			return (1);
	}
	tmp = lst;
	while (tmp && tmp->type != space && tmp->type > 4)
	{
		if (tmp->type == var && count_lenght(tmp, env, lst1) > 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_ambigus_var(t_list *lst, t_env *env, t_list *lst1)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp && tmp->type != space && tmp->type > 4)
	{
		if (tmp->type == var && count_lenght(tmp, env, lst1) == 1
			&& space_at_end(tmp->content, env, lst1))
		{
			tmp = tmp->next;
			while (tmp && tmp->type != space && tmp->type > 4)
			{
				if (tmp && count_lenght(tmp, env, lst1))
					return (1);
				tmp && (tmp = tmp->next);
			}
		}
		tmp && (tmp->type != space && tmp->type > 4) && (tmp = tmp->next);
	}
	return (0);
}

int	check_ambigus_word(t_list *lst, t_env *env, t_list *lst1)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp && tmp->type != space && tmp->type > 4)
	{
		if (count_lenght(tmp, env, lst1) == 1)
		{
			tmp = tmp->next;
			while (tmp && tmp->type != space && tmp->type > 4)
			{
				if (tmp->type == var)
				{
					if (count_lenght(tmp, env, lst1) == 1
						&& space_at_bgn(tmp->content, env, lst1))
						return (1);
				}
				tmp = tmp->next;
			}
		}
		tmp && (tmp->type != space && tmp->type > 4) && (tmp = tmp->next);
	}
	return (0);
}

int	check_ambigus(t_list *lst, t_env *env, t_list *lst1)
{
	if (check_ambigus_one(lst, env, lst1))
		return (1);
	if (check_ambigus_var(lst, env, lst1))
		return (1);
	if (check_ambigus_word(lst, env, lst1))
		return (1);
	return (0);
}

void	flag_ambigus(t_list *lst, t_env *env)
{
	t_list	*tmp;
	int		ambg;

	tmp = lst;
	while (tmp)
	{
		ambg = 0;
		if (tmp->type == red_out || tmp->type == red_in || tmp->type == append)
		{
			tmp = tmp->next;
			if (tmp->type == space)
				tmp = tmp->next;
			ambg = check_ambigus(tmp, env, lst);
			while (tmp && tmp->type != space && tmp->type > 4)
			{
				if (ambg)
					tmp->type = ambigus;
				tmp = tmp->next;
			}
		}
		tmp && (tmp->type != red_out) && tmp->type != red_in
		&& tmp->type != append && (tmp = tmp->next);
	}
}
