/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:25:32 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/11 10:29:48 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	check_first_char(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i])
			|| str[i] == '_' || str[i] == '+')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_check_key(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		if (str[i] == c && str[i +1] != '\0')
			j = 2;
		i++;
	}
	return (j);
}

int	help_export(t_env **env, t_env **new, char *args)
{
	*new = ft_lstnew_env(args);
	if (!new)
		return (1);
	ft_lstadd_back_env(env, *new);
	return (0);
}
