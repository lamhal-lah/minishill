/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:59:22 by aboulakr          #+#    #+#             */
/*   Updated: 2024/08/26 03:10:45 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long			res;

	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= 48 && str[i] <= 57)
		res = res * 10 + str[i++] - '0';
	return (res * sign);
}

int	check_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **av)
{
	int		exit_code;
	int		i;

	(1) && (i = 0, exit_code = 0);
	while (av[i])
		i++;
	if (av[1] && av[1][0] != '#')
	{
		if (check_digit(av[1]))
			(1) && (ft_putstr_fd("minishell: exit: ", 2), ft_putstr_fd(av[1],
			2), ft_putstr_fd(": numeric argument required\n", 2), exit(255), 0);
		else if (i > 2)
			return (ft_putstr_fd
				("minishell: exit: too many arguments\n", 2), 1);
		else if (i == 2 && !check_digit(av[1]))
		{
			printf("exit\n");
			exit_code = (unsigned char)ft_atoi(av[1]);
			exit(exit_code);
		}
	}
	return (exit_code);
}
