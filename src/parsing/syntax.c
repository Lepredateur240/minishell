/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:33:05 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/25 15:29:49 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_token_list(t_token *token, t_token *next)
{
	if (token->type == PIPE && (!next || next->type == PIPE))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (token->type >= R_INPUT && token->type <= HEREDOC)
	{
		if (!next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		if (next->type != WORD)
		{
			printf("minishell: syntax error near \
				unexpected token `%s'\n", next->token);
			return (1);
		}
	}
	return (0);
}

int	verify_token_list(t_list *token_list)
{
	t_token	*token;
	t_token	*next_token;

	if (((t_token *)token_list->content)->type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	while (token_list)
	{
		token = (t_token *)token_list->content;
		next_token = NULL;
		if (token_list->next)
			next_token = (t_token *)token_list->next->content;
		if (syntax_token_list(token, next_token))
			return (1);
		token_list = token_list->next;
	}
	return (0);
}
