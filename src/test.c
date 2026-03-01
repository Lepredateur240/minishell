/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:23:10 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/26 15:40:27 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// print de l'init de la liste chainee
void test_print_env(t_list *env)
{
	t_env	*current;
	
	while (1)
	{
		current = (t_env *)env->content;
		printf("KEY == %s\nVALUE == %s \nexported? == %i\n\n", current->key, current->value, current->exported);

		if (!env->next)
			break ;
		env = env->next;
	}
}


/// test de la recherche de la VALUE dans l'env
// void test_print_env_value(t_list *env, char *key)
// {
// 	char *value;

// 	value = get_env_value(env, key);
// 	printf("Key: %s Value: %s\n", key, value);
// }

/// test du tableau des paths des exec
void	test_print_exec_path_tab(char **exec_path_tab)
{
	int	i;

	i = 0;
	while (exec_path_tab[i])
	{
		printf("%s\n", exec_path_tab[i]);
		i++;
	}
}


// /// print de la liste chainee de token
void	test_print_list_token(t_list *token_list)
{
	t_token	*token;

	printf("\n\033[0;31mtest_print_list_token:\033[0m\n");
	while (1)
	{
		token = (t_token *)token_list->content;
		printf("\033[0;36m%s\033[0m", token->token);
		if (token->type == 0)
			printf("(WORD) ");
		if (token->type == 1)
			printf("(PIPE) ");
		if (token->type == 2)
			printf("(R_INPUT) ");
		if (token->type == 3)
			printf("(R_OUTPUT) ");
		if (token->type == 4)
			printf("(R_OUTPUT_APPEND) ");
		if (token->type == 5)
			printf("(HEREDOC) ");
		if (!token_list->next)
			break ;
		token_list = token_list->next;
	}
	printf("\n\n");
}

void test_print_minish_cmds(t_minishell *minishell)
{
	t_cmd	*cmd;
	t_list	*current;
	int		i;
	int		y;

	current = minishell->cmds; 
	y = 0;
	printf("\033[0;31mtest_print_minish_cmds:\033[0m\n");
	while (current)
	{
		cmd = (t_cmd *)current->content;
		printf("%i:\n", y);
		if (cmd->args && cmd->args[0])
			printf("CMD: %s\n", cmd->args[0]);
		if (cmd->args && cmd->args[1])
		{
			printf("ARGS: ");
			i = 1;
			while (cmd->args[i])
			{
				printf("%s ", cmd->args[i]);
				i++;
			}
			printf("\n");
		}
		printf("path: %s\n", cmd->cmd_path);
		printf("fd_in: %i\n", cmd->fd_in);
		printf("fd_out: %i\n", cmd->fd_out);
		printf("\n");
		current = current->next;
		y++;
	}
}