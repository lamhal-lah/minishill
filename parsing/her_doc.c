/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:36:27 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/26 22:06:32 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	line = readline(">");
	while (line && ft_strncmp(line, str, ft_strlen(str) + 1) != 0)
	{
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
	fd = open("/tmp/tmp.txt", O_RDONLY);
	unlink("/tmp/tmp.txt");
	return (fd);
}
