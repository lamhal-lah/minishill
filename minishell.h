/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulakr <aboulakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:43:52 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/13 17:07:05 by aboulakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>

typedef enum e_type
{
	Pipe,
	red_out,
	red_in,
	herdoc,
	append,
	dquot,
	squot,
	var,
	space,
	word,
	limtr,
	limtr_qt,
	ambigus
}	t_type;

typedef struct s_list
{
	int				fd;
	char			*content;
	t_type			type;
	struct s_list	*next;
}	t_list;

typedef struct s_cmds
{
	t_list			*red;
	char			**args;
	int				fdin;
	int				fdout;
	struct s_cmds	*next;	
}	t_cmds;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				printed;
}	t_env;

typedef struct s_export
{
	t_env	*tmp;
	t_env	*new;
	char	*new_key;
	char	*new_value;
}	t_export;

//-----------------execution---------------//
void	directory_or_file(char *cmd, t_cmds *cmds);
int		handle_rediractions(t_cmds *cmds);
int		ft_is_builtin(t_cmds *cmds, t_env *env);
void	pwd(void);
char	*ft_strndup(const char *s1, size_t n);
void	ft_print_env(t_env *env);
char	*ft_getenv(char *name, t_env *env);
t_env	*ft_env(char **env);
t_env	*ft_lstnew_env(char *env);
void	cd(char **av, t_env *env);
int		chekc_string(char *str, char c);
void	echo(char **av);
void	unset(char **av, t_env **env);
void	export(char **av, t_env **env, int i, t_export *exp);
int		ft_check_key(char *str, char c);
int		check_first_char(char *str);
int		ft_isalpha(int c);
void	ft_print_export(char **av, t_env *env);
int		ft_fill(char **key, char **value, char *str);
int		ft_isdigit(int c);
int		help_export(t_env **env, t_env **new, char *av);
char	**free_split(char **split, size_t size);
t_cmds	*ft_lstlast_cmd(t_cmds *lst);
//char	*ft_strjoin_free(char *str1, char *str2);

//-----------------execution2---------------//
void	ft_check_redirections(t_cmds *cmd, int **fd, int i);
char	**ft_split_execution(char *str, char c);
int		ft_lstsize(t_env *lst);
char	*find_path(char *cmd, t_env *env);
char	**environement(t_env *env);
int		execute(t_cmds *cmd, t_env *env, int i);
// void	ft_first_command(t_cmds *cmd, char **env, char *path, int *fd);
void	middle_commands(t_cmds *cmd, char **env, char *path, int **fd, int i);
// int		last_command(t_cmds *cmd, char **env, char *path, int *fd, int *i);
int		ft_cmdsize(t_cmds *cmd);

//----------utils-----------

size_t	ft_strlen(const	char *str);
t_list	*ft_lstnew(char *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **l, t_list *new);
void	ft_remove_node(t_list **lst);
void	ft_lstclear(t_list **lst);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
//t_env	*ft_lstnew_env(char *env);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_lstadd_midl(t_list **lst, t_list *new);
void	ft_lstadd_front_env(t_env **l, t_env *new);
void	ft_lstclear_env(t_env **lst);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *str1, char *str2);
char	*ft_strchr(const char *s, int c);
t_cmds	*ft_lstnew_cmd(t_list **lst);
void	ft_lstadd_back_cmd(t_cmds **lst, t_cmds *new);
void	ft_lstclear_cmd(t_cmds **lst);
t_cmds	*list_cmds(t_list *lst);
int		count_words(char *str);
int		open_rediractions(t_cmds *cmd);
//------------parsing-----------

void	expand(t_list *lst, t_env *env);
char	**ft_split(char *str);
void	ft_lst_join(t_list **lst);
t_cmds	*proccess_line(char *line, t_list **lst, t_env *env);
int		check_syntaxe_error(t_list *lst);
//t_env	*ft_env(char **env);
void	remove_quotes(t_list *list);
//char   *ft_getenv(char *key, t_env *env);

#endif