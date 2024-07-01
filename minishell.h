/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:43:52 by lamhal            #+#    #+#             */
/*   Updated: 2024/07/01 18:14:32 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <stdio.h>

typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}	t_env;

size_t	ft_strlen(const	char *str);
t_list	*ft_lstnew(char *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **l, t_list *new);
void	ft_lstclear(t_list **lst);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	proccess_line(char *line, t_list **lst);
int		check_syntaxe_error(t_list *lst);
int		check_couts(char *line);
t_env	*ft_lstnew_env(char *env);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_lstadd_front_env(t_env **l, t_env *new);
void	ft_lstclear_env(t_env **lst);
t_env	*ft_env(char **env);

#endif