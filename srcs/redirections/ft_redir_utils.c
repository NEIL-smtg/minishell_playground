/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:08:04 by suchua            #+#    #+#             */
/*   Updated: 2023/05/11 15:10:38 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(char c)
{
	return (c == '<' || c == '>');
}

int	redir_within_quotes(char *cmd)
{
	int		i;
	int		sq;
	int		dq;

	i = -1;
	dq = 0;
	sq = 0;
	while (cmd[++i])
	{
		if (cmd[i] == 34)
			dq = !dq;
		if (cmd[i] == 39)
			sq = !sq;
		if (is_redir(cmd[i]) && !dq && !sq)
			return (0);
	}
	return (1);
}

int	ft_parse_redir(t_cmdlst **node)
{
	int		i;
	char	*check;

	i = 0;
	check = ft_strrchr((*node)->cmd, '>');
	if (!check)
		return (1);
	while (check[i++])
	{
		if (check[i] == 34)
			return (1);
		if (check[i] == 39)
			return (1);
	}
	return (0);
}
