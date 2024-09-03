/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:49:37 by aboulakr          #+#    #+#             */
/*   Updated: 2024/09/01 01:17:06 by aboulakr         ###   ########.fr       */
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
