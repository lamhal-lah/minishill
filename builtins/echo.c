/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:12:27 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/18 17:54:28 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chekc_string(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	echo(char **av)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 0;
	k = 0;
	while (av && av[i] && ft_strncmp(av[i], "-n", 2) == 0)
	{
		if (chekc_string(&av[i][1], 'n') == 1)
		{
			k = 1;
			i++;
		}
		else
			break ;
	}
	while (av && av[i])
	{
		ft_putstr_fd(av[i], 1);
		(av[i + 1]) && (printf(" "));
		i++;
	}
	(k == 0) && (printf("\n"));
	return (0);
}
