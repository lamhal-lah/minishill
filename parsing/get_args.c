/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 22:37:27 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/26 18:24:38 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_arg(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp && tmp->type != Pipe)
	{
		if (tmp->type > 0 && tmp->type < 5)
		{
			tmp = tmp->next->next;
		}
		else
		{
			i++;
			tmp && (tmp = tmp->next);
		}
	}
	return (i);
}

char	*get_av(char *str, t_pars *pars)
{
	char	*str1;

	if (!str)
		str1 = NULL;
	else
	{
		str1 = ft_strdup(str);
		if (!str1)
			ft_free_exit(pars, "failed malloc");
	}
	return (str1);
}


char	**get_args(t_list **lst, t_pars *pars)
{
	char	**args;
	t_list	*tmp;
	int		i;
	int		count;

	tmp = *lst;
	count = count_arg(*lst);
	if (count == 0)
	{
		while (tmp && tmp->type != Pipe)
			tmp = tmp->next;
		return ((*lst = tmp), NULL);
	}
	i = 0;
	args = malloc((count + 1) * sizeof(char **));
	if (!args)
		ft_free_exit(pars, "failed malloc");
	while (tmp && tmp->type != Pipe)
	{
		if (tmp->type > 0 && tmp->type < 5)
			tmp = tmp->next->next;
		else
		{
			args[i++] = get_av(tmp->content, pars);
			tmp = tmp->next;
		}
	}
	*lst = tmp;
	args[i] = NULL;
	return (args);
}
