/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:05:58 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/01 17:14:05 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_env
{
	char	*key;
	char	*value;
	int		exported;		
}	t_env;

typedef struct	s_cmd
{
	char	**args;
	char	*cmd_path;
	int		fd_in;
	int		fd_out;
	char	*delim;
}	t_cmd;

typedef struct	s_minishell
{
	t_list	*env;
	char	**exec_path_tab;
	t_list	*cmds;
	int		exit_status;
	
	
}	t_minishell;

typedef enum e_type
{
	WORD,
	PIPE,
	R_INPUT,
	R_OUTPUT,
	R_OUTPUT_APPEND,
	HEREDOC,
	
}	t_type;

typedef struct s_token
{
	char	*token;
	t_type	type;
}	t_token;


/* env/ */
// env_init.c
t_list	*init_env(char **envp);

// env_utils.c
char	*get_env_value(t_minishell *minishell, char *key);

// env_path.c
char	**get_exec_path(t_minishell *minishell);


/* parsing/ */
// lexer.c
t_list	*list_token(char *prompt);

// parser.c
void	parsing_prompt(t_minishell *minishell, char *prompt);

// expands.c
int		handle_expands(t_minishell *minishell, t_list *token_list);

// cmds_builder.c
int		format_cmds(t_minishell *minishell, t_list *token_list);

// post_expands.c
void	remake_token_list(t_list **token_list);

// syntax.c
int		verify_token_list(t_list *token_list);

// utils.c
void	update_quote_state(char c, int *state);
int		get_quote_state(char *str, int index);
int		verify_unclosed_quotes(char *prompt);
int		count_args_list(t_list *token_list);

// token_type.c
int	handle_token_type(t_cmd *cmd, t_list **token_list);


/* utils/ */
// free.c
void	free_token(void *content);
void	free_env(void *content);
void	free_tab(char **tab);
void	free_all(t_minishell *minishell);

// ft_split_unquoted.c
char	**ft_split_unquoted(char const *s, char c);


/* exec/ */
// exec_path.c
void	find_path(t_minishell *minishell);

/* signal/ */
// signal.c
void	handle_signal(int sig);
/* tests/ */
// test.c
void	test_print_env(t_list *env);
void	test_print_exec_path_tab(char **exec_path_tab);
void	test_print_list_token(t_list *token_list);
void	test_print_minish_cmds(t_minishell *minishell);

extern volatile sig_atomic_t g_receive_message;

#endif