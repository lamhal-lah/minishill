/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:36:27 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/27 20:45:03 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sighandl()
{
	printf("hi from sighandl\n");
	if (g_i == 1)
	{
		close(0);
		g_i = 3;
	}
}

int	process_herdoc(char	*str, int type, t_env *env, t_pars *pars)
{
	int		fd;
	int		fd_stdin;
	char	*line;
	char	*tmp;

	fd_stdin = dup(0);
	unlink("/tmp/tmp.txt");
	fd = open("/tmp/tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	g_i = 1;
	if (g_i == 1)
		signal(SIGINT, sighandl);
	line = readline(">");
	while (1)
	{
		if (!line)
			break ;
		if (line && ft_strncmp(line, str, ft_strlen(str)) == 0)
			break ;
		printf("line = '%s'\n", line);
		signal(SIGINT, sighandl);
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
	dup2(fd_stdin, 0);
	close(fd_stdin);
	free(line);
	close(fd);
	(g_i == 1) && (g_i = 0);
	fd = open("/tmp/tmp.txt", O_RDONLY);
	unlink("/tmp/tmp.txt");
	return (fd);
}

