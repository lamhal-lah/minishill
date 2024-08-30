/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:36:27 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/30 18:28:28 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handel_herdoc(char *str, int type, t_env *env, t_pars *pars)
{
	char	*line;
	int		fd;
	char	*tmp;

	fd = open("/tmp/tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline(">");
	while (1)
	{
		if (!line || ft_strncmp(line, str, ft_strlen(str) + 1) == 0)
			break ;
		if (type == limtr)
		{
			tmp = line;
			line = expand_dquot(line, env, pars);
			free(tmp);
		}
		tmp = line;
		line = ft_strjoin(line, "\n");
		free(tmp);
		ft_putstr_fd(line, fd);
		free(line);
		line = readline(">");
	}
	return (rl_catch_signals = 0, free(line), fd);
}

int	process_herdoc(char	*str, int type, t_env *env, t_pars *pars)
{
	int		fd;
	int		fd_stdin;

	fd_stdin = dup(0);
	unlink("/tmp/tmp.txt");
	g_i = 1;
	fd = handel_herdoc(str, type, env, pars);
	dup2(fd_stdin, 0);
	close(fd_stdin);
	close(fd);
	(g_i == 1) && (g_i = 0);
	fd = open("/tmp/tmp.txt", O_RDONLY);
	unlink("/tmp/tmp.txt");
	return (fd);
}
