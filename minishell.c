/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:55:22 by lamhal            #+#    #+#             */
/*   Updated: 2024/06/13 00:43:38 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_list	*lst;

	(void)ac;
	(void)av;
	(void)env;
	lst = NULL;
	char	*line;
	char	*msg;

	msg = "minishell:  ";
	line = readline(msg);
	while (line)
	{
		proccess_line(line, &lst);
		while (lst)
		{
			printf("%s\n", lst->content);
			lst = lst->next;
		}
		free(line);
		line = readline(msg);
	}
}
