/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:45:24 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/26 15:15:01 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_type(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (0);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (3);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (4);
	else if (str[0] == '\"')
		return (5);
	else if (str[0] == '\'')
		return (6);
	else if (str[0] == '$' && str[1] != '\0')
		return (7);
	else if (str[0] == ' ')
		return (8);
	return (9);
}

int	find_type_limter(t_list *lst)
{
	t_list	*tmp;
	int		type;

	tmp = lst;
	type = limtr;
	while (tmp && tmp->type != space && tmp->type > 4)
	{
		if (tmp->type == dquot || tmp->type == squot)
			type = limtr_qt;
		tmp = tmp->next;
	}
	return (type);
}

void	flag_limitter(t_list *lst)
{
	t_list	*tmp;
	int		type;

	tmp = lst;
	while (tmp && tmp->next)
	{
		if (tmp->type == herdoc)
		{
			tmp && (tmp = tmp->next);
			if (tmp->type == space && tmp->next)
				tmp = tmp->next;
			type = find_type_limter(tmp);
			while (tmp && tmp->type != space && tmp->type > 4)
			{
				tmp->type = type;
				tmp = tmp->next;
			}
		}
		tmp && (tmp->type != herdoc) && (tmp = tmp->next);
	}
}

void	add_to_list(t_list **lst, char *token, t_pars *parsg)
{
	t_list	*node;

	if (token && ft_strncmp(token, "$?", 3) == 0)
	{
		free(token);
		token = ft_itoa(parsg->status);
	}
	if(!token)
		ft_free_exit(parsg, "failled malloc\n");
	node = ft_lstnew(token);
	if (!node)
	{
		free(token);
		ft_free_exit(parsg, "failled malloc\n");
	}
	node->type = find_type(token);
	ft_lstadd_back(lst, node);
}

void	tokonisation(t_list **lst, char *line, t_pars *parsg)
{
	char	*token;
	int		i;

	i = 0;
	token = NULL;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line && line[i])
	{
		token = get_token(line, &i);
		add_to_list(lst, token, parsg);
		if (line[i] && (line[i] == ' ' || line [i] == '\t'))
		{
			while (line[i] == ' ' || line [i] == '\t')
				i++;
			if (line[i] != '\0')
			{
				token = ft_strdup(" ");
				add_to_list(lst, token, parsg);
			}
		}
	}
}

t_pars	*alloc_intaillese(char **line, t_list **lst, t_env **env, int status)
{
	t_pars	*parsg;

	parsg = malloc(sizeof(t_pars));
	if (!parsg)
		(free(line), ft_lstclear(lst), ft_lstclear_env(env),
			ft_putstr_fd("failled malloc\2", 2), exit(1));
	parsg->line = *line;
	parsg->lst = *lst;
	parsg->env = *env;
	parsg->cmds = NULL;
	parsg->status = status;
	return (parsg);
}

t_cmds	*proccess_line(char *line, int status, t_env *env)
{
	t_list	*lst;
	t_list	*node;
	t_cmds	*cmds;

	t_pars	*parsg;
	parsg = alloc_intaillese(&line, &lst, &env, status);
	lst = NULL;
	node = NULL;
	tokonisation(&lst, line, parsg);
	printf("**********************************************\n");
	t_list *tmp;
	tmp = lst;
	while (tmp)
	{
		printf("%s %d\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
	printf("**********************************************\n");
	if (check_syntaxe_error(lst))
	{
		ft_lstclear(&lst);
		return (NULL);
	}
	remove_quotes(lst, parsg);
	flag_limitter(lst);
	flag_ambigus(lst, env, parsg);
	expand(lst, env, parsg);
	tmp = lst;
	while (tmp)
	{
		printf("%s %d\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
	printf("**********************************************\n");
	ft_lst_join(&lst, parsg);//
	tmp = lst;
	while (tmp)
	{
		printf("%s %d\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
	cmds = list_cmds(lst, parsg);//
	int	i;
	t_cmds	*tmp1;
	t_list	*tmp2;
	tmp1 = cmds;
	while (tmp1)
	{
		i = 0;
		if (!tmp1->args)
			printf("args = NULL\n");
      	while(tmp1 && tmp1->args && tmp1->args[i])
		{
			printf("args[%d] = %s\n", i, tmp1->args[i]);
			i++;
		}
		tmp2 = tmp1->red;
		if (!tmp2)
			printf("red = NULL\n");
		while (tmp2)
		{
			printf("%s-- %d\n", tmp2->content, tmp2->type);
			tmp2 = tmp2->next;
		}
		printf("------------------\n");
		tmp1 = tmp1->next;
	}
	ft_lstclear(&lst);//
	return (cmds);
}
