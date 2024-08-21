/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:36:27 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/21 19:53:24 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_herdoc(char	*str, int type, t_env *env, t_list *lst)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open("/tmp/tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	line = readline(">");
	while (line && ft_strncmp(line, str, ft_strlen(str) + 1) != 0)
	{
		if (type == limtr)
		{
			tmp = line;
			line = expand_dquot(line, env, lst);
			free(tmp);
		}
		tmp = line;
		line = ft_strjoin(line, "\n");
		free(tmp);
		ft_putstr_fd(line, fd);
		free(line);
		line = readline(">");
	}
	close(fd);
	fd = open("/tmp/tmp.txt", O_RDONLY);
	unlink("/tmp/tmp.txt");
	return (fd);
}
