/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:49:37 by aboulakr          #+#    #+#             */
/*   Updated: 2024/09/05 11:59:33 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red_in_out(t_cmds *cmds, t_list *red)
{
	if (red->type == red_in)
	{
		(cmds->fdin != 0) && (close(cmds->fdin));
		cmds->fdin = open(red->content, O_RDONLY);
		if (cmds->fdin == -1)
			return (ft_putstr_fd("minihell: ", 2), ft_putstr_fd(red->content,
					2), ft_putstr_fd(": ", 2), ft_putstr_fd(strerror(errno), 2),
				ft_putstr_fd("\n", 2), -1);
	}
	else if (red->type == red_out)
	{
		(cmds->fdout != 1) && (close(cmds->fdout));
		cmds->fdout = open(red->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (cmds->fdout == -1)
			return (ft_putstr_fd("minihell: ", 2), ft_putstr_fd(red->content,
					2), ft_putstr_fd(": ", 2), ft_putstr_fd(strerror(errno), 2),
				ft_putstr_fd("\n", 2), -1);
	}
	return (0);
}

int	red_app_ambg(t_cmds *cmds, t_list *red)
{
	if (red->type == append)
	{
		(cmds->fdout != 1) && (close(cmds->fdout));
		cmds->fdout = open(red->content,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (cmds->fdout == -1)
			return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(red->content,
					2), ft_putstr_fd(": ", 2), ft_putstr_fd(strerror(errno), 2),
				ft_putstr_fd("\n", 2), -1);
	}
	else if (red->type == ambigus)
	{
		(cmds->fdin && cmds->fdout != 1) && (close(cmds->fdout),
			close(cmds->fdin));
		return (ft_putstr_fd("minishell: ambiguous redirect\n", 2), -1);
	}
	else if (red->type == herdoc)
	{
		(cmds->fdin > 0) && (close(cmds->fdin));
		cmds->fdin = red->fd;
	}
	return (0);
}

void	under_score(t_cmds *cmds, t_env **env)
{
	t_env	*tmp;
	char	*str;
	int		i;
	int		size;

	(1) && (i = 0, tmp = *env, size = ft_cmdsize(cmds));
	while (cmds->args && cmds->args[i])
		i++;
	while (tmp && size == 1)
	{
		if (!ft_strncmp(tmp->key, "_", 2) && i > 0)
		{
			str = ft_strdup(cmds->args[i - 1]);
			(1) && (free(tmp->value), tmp->value = ft_strdup(str));
			free(str);
			break ;
		}
		tmp = tmp->next;
	}
	if (size > 1)
	{
		(tmp->value) && (free(tmp->value), 0);
		tmp->value = NULL;
	}
}

void	kil(int *pid, int i, int **fd)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	perror("fork");
	while (fd && fd[j])
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	while (k <= i)
	{
		kill(pid[k], SIGKILL);
		k++;
	}
}

void	shlvl(t_env **env)
{
	t_env	*tmp;
	char	*str;
	int		i;

	(1) && (i = 0, tmp = *env);
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "SHLVL", 6))
		{
			i = ft_atoi(tmp->value);
			if (i > 1000)
				i = 1;
			else
				i++;
			str = ft_itoa(i);
			(1) && (free(tmp->value), tmp->value = ft_strdup(str));
			free(str);
			break ;
		}
		tmp = tmp->next;
	}
}
