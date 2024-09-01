/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:43:52 by lamhal            #+#    #+#             */
/*   Updated: 2024/09/01 00:56:21 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>

int	g_i;

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
	ambigus,
	nofile
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

typedef struct s_line
{
	char			*line;
	t_env			*env_lst;
	struct termios	original_term;
	struct termios	current_term;
}	t_line;

typedef struct s_execute
{
	int		fake_in;
	int		fake_out;
	int		status;
}	t_execute;

typedef struct s_pars
{
	t_list	*lst;
	t_env	*env;
	t_cmds	*cmds;
	char	*line;
	int		status;
}	t_pars;

//----------------------------------builtin-----------------------------------//

int		ft_exit(char **av);
int		check_if_builtin(t_cmds *cmds);
int		ft_is_builtin(t_cmds *cmds, t_env **env);
int		pwd(t_env *env);
int		ft_print_env(t_env *env);
t_env	*ft_env(char **env);
int		cd(char **av, t_env *env);
int		echo(char **av);
int		unset(char **av, t_env **env, int i, int k);
int		export(char **av, t_env **env, int i, t_export *exp);
void	ft_print_export(char **av, t_env *env);

//-----------------------------utils-builtin----------------------------------//

int		chekc_string(char *str, char c);
int		check_first_char(char *str);
int		ft_check_key(char *str, char c);
int		ft_fill(char **key, char **value, char *str);
int		help_export(t_env **env, t_env **new, char *av);

//----------------------------execution---------------------------------------//

void	ctrl_c(int signo);
void	sig_handler2(int signo);
void	sig_handler(int signo);
int		red_app_ambg(t_cmds *cmds, t_list *red);
int		red_in_out(t_cmds *cmds, t_list *red);
int		handle_one_cmd(t_cmds *cmd, t_env **env);
int		open_rediractions_parent(t_cmds *cmds);
int		handle_rediractions(t_cmds *cmds);
void	ft_check_redirections(t_cmds *cmd, int **fd, int i);
void	ft_check_redirections_parent(t_cmds *cmd);
char	**environement(t_env *env);
int		execute(t_cmds *cmd, t_env **env, int i, t_execute *exec);
void	middle_commands(t_cmds *cmd, t_env *env, int **fd, int i);

//----------------------------------utils-execution---------------------------//

int		fill_pipes(t_cmds *cmd, int ***fd, int i, int **pid);
char	**free_split_execution(char **split, size_t size);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_getenv(char *name, t_env *env);
t_env	*ft_lstnew_env(char *env);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	**free_split(char **split, size_t size);
t_cmds	*ft_lstlast_cmd(t_cmds *lst);
char	**ft_split_execution(char *str, char c);
int		ft_lstsize(t_env *lst);
char	*find_path(char *cmd, t_env *env);
int		ft_cmdsize(t_cmds *cmd);

//----------------------------------Erorr-execution---------------------------//

void	error_management(t_cmds *cmds, t_env *env);
void	slash_condition(t_cmds *cmds, t_env *env);
void	ft_handle_dot(t_cmds *cmds, t_env *env);
void	handle(t_cmds *cmds, t_env *env);
void	print_error_and_exit(t_cmds *cmds, char *error_msg, int exit_code);
void	handle_other_error(t_cmds *cmds, t_env *env);
void	handle_execve_error(t_cmds *cmds, t_env *env);

//---------------------------------utils--------------------------------------//

void	handle_fds(t_cmds *cmd);
int		prepare(t_execute *exec);
size_t	ft_strlen(const	char *str);
size_t	ft_split_size(char **split);
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
t_list	*lstnew_red(t_list *lst_node, t_pars *pars);
void	ft_lstadd_back_cmd(t_cmds **lst, t_cmds *new);
void	ft_lstclear_cmd(t_cmds **lst);
t_cmds	*list_cmds(t_list *lst, t_pars *pars);
int		count_words(char *str);
int		open_rediractions(t_cmds *cmd);
void	ft_free_exit(t_pars *parsg, char *str);//
char	*ft_itoa(int n);

//----------------------------------parsing-----------------------------------//

int		find_type(char *str);
void	flag_limitter(t_list *lst);
int		check_ambigus_word2(t_list *tmp, t_env *env, t_pars *parsg);
void	lst_jion(t_list *tmp, t_pars *pars);
void	mark_spaces(t_list *lst);
void	expand_join_infile(t_env *env, t_list **lst, t_pars *pars);
void	expand(t_list *lst, t_env *env, t_pars *parsg);
char	**ft_split(char *str);
void	ft_lst_join(t_list **lst, t_pars *pars);
t_cmds	*proccess_line(char *line, int *status, t_env *env);
int		check_syntaxe_error(t_list *lst);
//t_env	*ft_env(char **env);
void	remove_quotes(t_list *list, t_pars *parsg);
//char	*ft_getenv(char *key, t_env *env);
void	*get_token(char *line, int *i);
void	flag_ambigus(t_list *lst, t_env *env, t_pars *parsg);
char	*expand_dquot(char *str, t_env *env, t_pars *parsg);
void	remove_empty_node(t_list **lst);
int		process_herdoc(char *str, int type, t_env *env, t_pars *pars);
void	ft_free(char **str, int n);
int		count_lenght(t_list *node, t_env *env, t_pars *parsg);
int		space_at_bgn(char *str, t_env *env, t_pars *parsg);
int		space_at_end(char *str, t_env *env, t_pars *parsg);
void	expand_var(char *var, t_env *env, t_list **node, t_pars *pars);
void	remove_spaces(t_list **lst);
char	**get_args(t_list **lst, t_pars *pars);

#endif
