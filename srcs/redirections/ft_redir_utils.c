/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:08:04 by suchua            #+#    #+#             */
/*   Updated: 2023/05/05 20:12:25 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_within_quotes(char *cmd)
{
	int		i;
	int		quote;

	i = -1;
	quote = -1;
	while (cmd[++i])
	{
		if (quote == -1 && (cmd[i] == 34 || cmd[i] == 39))
			quote = cmd[i];
		else if (quote == cmd[i])
			quote = -1;
		if (quote == -1 && (cmd[i] == '<' || cmd[i] == '>'))
			return (0);
	}
	return (1);
}
