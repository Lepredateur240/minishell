/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:14:26 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/25 14:53:54 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remake_token_list(t_list **token_list)
{
	t_token	*token;
	t_list	*current;
	t_list	*prev;
	t_list	*tmp;
	char	**tokens;
	int		i;
	t_list	*sub_current;
	t_token	*sub_token;
	
	current = *token_list;
	prev = NULL;
	tmp = NULL;

	sub_token = NULL;

	
	while (current)
	{
		token = (t_token *)current->content;
		if (!token->token || token->token[0] == '\0')
		{
			if (prev)
				prev->next = current->next;
			else
				*token_list = current->next;
			tmp = current;
			current = current->next;
			free_token(tmp->content);
			free(tmp);
			continue ;
		}
		if (ft_strchr(token->token, ' '))
		{
			tokens = ft_split_unquoted(token->token, ' ');

			if (tokens && tokens[0])
			{
				free(token->token);
				token->token = ft_strdup(tokens[0]);
				if (!token->token)
					return ;
			}
			
			i = 1;
			while (tokens[i])
			{
				sub_token = malloc(sizeof(t_token));
				if (!sub_token)
					return ; //////////////////////////////////////////////
				sub_token->token = ft_strdup(tokens[i]);
				if (!sub_token->token)
					break ; ///////////////////////
				sub_token->type = WORD;
				sub_current = ft_lstnew(sub_token);
				if (!sub_current)
					return ;/////////////////////////////////////////

				sub_current->next = current->next;
				current->next = sub_current;

				prev = current;
				current = sub_current;
				
				i++;
			}
			free_tab(tokens);
		}
		prev = current;
		current = current->next;
	}
}