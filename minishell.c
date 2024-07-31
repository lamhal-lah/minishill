/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:55:22 by lamhal            #+#    #+#             */
/*   Updated: 2024/07/30 15:18:03 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_list	*lst;
	t_list	*tmp;
	t_env	*env_lst;
	char	*line;

	(void)ac;
	(void)av;
	lst = NULL;
	env_lst = ft_env(env);
	line = readline("minishell:  ");
	while (line && ft_strncmp(line, "exit", 5))
	{
		add_history(line);
		// system("leaks minishell");
		proccess_line(line, &lst, env_lst);
		tmp = lst;
		while (tmp)
		{
			printf("%s-- %d\n", tmp->content, tmp->type);
			tmp = tmp->next;
		}
		free(line);
		ft_lstclear(&lst);
		line = readline("minishell:  ");
	}
}
