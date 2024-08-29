/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:23:54 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/29 14:51:21 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_first_char(char *str)
{
	int	i;

	i = 1;
	if (ft_strncmp(str, "_", 2) == 0)
		return (2);
	if (!ft_isalpha(str[0]))
		return (0);
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

static void	print_unset_error(char *str)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	unset(char **av, t_env **env, int i, int k)
{
	t_env	*tmp;
	t_env	*prev;

	while (av[++i] && ft_strncmp(av[i], "_", 2) != 0)
	{
		(1) && (tmp = *env, prev = NULL);
		if (!ft_check_first_char(av[i]))
			return (print_unset_error(av[i]), k = 1);
		while (tmp)
		{
			if (ft_strncmp(av[i], tmp->key, ft_strlen(av[i]) + 1) == 0)
			{
				if (prev == NULL)
					*env = tmp->next;
				else
					prev->next = tmp->next;
				(1) && (free(tmp->key), free(tmp->value),
					free(tmp), tmp = NULL);
				break ;
			}
			(1) && (prev = tmp, tmp = tmp->next);
		}
	}
	return (k);
}
