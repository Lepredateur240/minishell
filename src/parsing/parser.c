/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:19:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/26 18:54:54 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_builder_part(t_minishell *minishell, t_list *token_list)
{
	if (format_cmds(minishell, token_list))
	{
		ft_lstclear(&token_list, free_token);
		printf("minishell: memory allocation fail\n");
		return (1);
	}
	ft_lstclear(&token_list, free_token);
	find_path(minishell);
	return (0);
}

static int	expands_part(t_minishell *minishell, t_list **token_list)
{
	if (handle_expands(minishell, *token_list))
		return (1);
	remake_token_list(token_list);
	return (0);
}

static int	validation_part(t_minishell *minishell, t_list *token_list)
{
	if (verify_token_list(token_list))
	{
		minishell->exit_status = 2;
		ft_lstclear(&token_list, free_token);
		return (1);
	}
	return (0);
}

static int	lexing_part(char *prompt, t_list **token_list)
{
	if (verify_unclosed_quotes(prompt))
		return (1);
	*token_list = list_token(prompt);
	if (!(*token_list))
		return (1);
	return (0);
}

void	parsing_prompt(t_minishell *minishell, char *prompt)
{
	t_list	*token_list;

	token_list = NULL;
	if (lexing_part(prompt, &token_list))
		return ;
		
	/////////////////////////////////////////////////////// TEST
	test_print_list_token(token_list);

	if (validation_part(minishell, token_list))
		return ;

	if (expands_part(minishell, &token_list))
		return ;

	/////////////////////////////////////////////////////// TEST
	test_print_list_token(token_list);
		
	if (command_builder_part(minishell, token_list))
		return ;
	/////////////////////////////////////////////////////// TEST
	test_print_minish_cmds(minishell);
}
