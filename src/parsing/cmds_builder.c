/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:40:53 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/26 15:22:35 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_cmd_struct(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd_path = NULL;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->delim = NULL;
	return (cmd);
}

static int	words_to_args(t_cmd *cmd, t_token *token, int *i)
{
	cmd->args[*i] = ft_strdup(token->token);
	if (!cmd->args[*i])
	{
		free_tab(cmd->args);
		return (1);
	}
	(*i)++;
	return (0);
}

static int	fill_cmd_args(t_cmd *cmd, t_list **token_list)
{
	t_token	*token;
	int		i;

	i = 0;
	while (*token_list)
	{
		token = (t_token *)(*token_list)->content;
		if (token->type == PIPE)
		{
			*token_list = (*token_list)->next;
			break ;
		}
		if (token->type >= R_INPUT && token->type <= HEREDOC)
		{
			if (handle_token_type(cmd, token_list))
				return (1);
		}
		else if (token->type == WORD)
		{
			if (words_to_args(cmd, token, &i))
				return (1);
		}
		*token_list = (*token_list)->next;
	}
	cmd->args[i] = NULL;
	return (0);
}

static t_cmd	*build_cmd(t_list **token_list)
{
	t_cmd	*cmd;
	int		args_count;

	cmd = init_cmd_struct();
	if (!cmd)
		return (NULL);
	args_count = count_args_list(*token_list);
	cmd->args = malloc(sizeof(char *) * (args_count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	if (fill_cmd_args(cmd, token_list) == 1)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

int	format_cmds(t_minishell *minishell, t_list *token_list)
{
	t_cmd	*cmd;
	t_list	*new_node;

	minishell->cmds = NULL;
	while (token_list)
	{
		cmd = build_cmd(&token_list);
		if (!cmd)
			return (1);
		new_node = ft_lstnew(cmd);
		if (!new_node)
		{
			free_tab(cmd->args);
			free(cmd);
			return (1);
		}
		ft_lstadd_back(&minishell->cmds, new_node);
	}
	return (0);
}
