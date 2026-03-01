/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:56:22 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/25 15:30:17 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args_list(t_list *token_list)
{
	t_token	*token;
	int		args_count;

	args_count = 0;
	while (token_list)
	{
		token = (t_token *)token_list->content;
		if (token->type == PIPE)
			break ;
		else if (token->type >= R_INPUT && token->type <= HEREDOC)
		{
			if (token_list->next)
				token_list = token_list->next;
		}
		else if (token->type == WORD)
			args_count++;
		token_list = token_list->next;
	}
	return (args_count);
}
