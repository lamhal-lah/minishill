/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:23:54 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/11 10:29:48 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_first_char(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i])
			|| str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

void	unset(char **args, t_env **env)
{
	int		i;
	t_env	*tmp;
	t_env	*prev;

	i = 0;
	while (args[++i])
	{
		(1) && (tmp = *env, prev = NULL);
		if (!ft_check_first_char(args[i]))
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
		while (tmp)
		{
			if (ft_strncmp(args[i], tmp->key, ft_strlen(args[i]) + 1) == 0)
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
}
