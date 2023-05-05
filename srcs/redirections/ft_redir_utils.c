/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:08:04 by suchua            #+#    #+#             */
/*   Updated: 2023/05/06 01:59:55 by suchua           ###   ########.fr       */
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