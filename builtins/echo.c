/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:12:27 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/11 10:29:48 by lamhal           ###   ########.fr       */
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

void	echo(char **args)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 0;
	k = 0;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		if (chekc_string(&args[i][1], 'n') == 1)
		{
			k = 1;
			i++;
		}
		else
			break ;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		(args[i + 1]) && (printf(" "));
		i++;
	}
	(k == 0) && (printf("\n"));
}
