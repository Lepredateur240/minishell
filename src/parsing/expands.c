/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 09:16:51 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/26 16:58:15 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*integrate_expand(char *token, char *expand_start,
							char *expand_key, char *expand_value)
{
	char	*result;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(token, 0, expand_start - token);
	tmp2 = ft_strjoin(tmp1, expand_value);
	result = ft_strjoin(tmp2, expand_start + 1 + ft_strlen(expand_key));
	free(token);
	free(tmp1);
	free(tmp2);
	return (result);
}

static char	*extract_expand(char *word)
{
	int		i;
	char	*key;

	i = 1;
	if (word[i] == '?')
		return (ft_strdup("?"));
	while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
		i++;
	if (i == 1)
		return (NULL);
	key = ft_substr(word, 1, i - 1);
	return (key);
}

static char	*is_there_expands(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
		{
			if (get_quote_state(word, i) != 1)
				return (&word[i]);
		}
		i++;
	}
	return (NULL);
}

static int	token_expands(t_minishell *minishell, t_token *token)
{
	char	*start;
	char	*key;
	char	*value;

	start = is_there_expands(token->token);
	while (start)
	{
		key = extract_expand(start);
		if (!key)
			return (1);
		value = get_env_value(minishell, key);
		if (!value)
			value = ft_strdup("expand \"EXPAND | DQ\"");
		token->token = integrate_expand(token->token, start, key, value);
		free(key);
		free(value);
		if (!token->token)
			return (1);
		start = is_there_expands(token->token);
	}
	return (0);
}

int	handle_expands(t_minishell *minishell, t_list *token_list)
{
	t_token	*token;

	while (token_list)
	{
		token = (t_token *)token_list->content;
		// if (ft_strcmp(token->token, "export") == 0)
		// 	handle_export(minishell, &token_list);
		if (token_expands(minishell, token))
			return (1);
		token_list = token_list->next;
	}
	return (0);
}
