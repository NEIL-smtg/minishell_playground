/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 22:43:50 by suchua            #+#    #+#             */
/*   Updated: 2023/04/24 22:47:40 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_new_index(char *cmd, int sq, int dq, int echo)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_strncmp("echo", cmd + i, 4))
			echo = 1;
		if (!echo && !sq && !dq && (instr_split(&cmd[i]) || ft_isspace(cmd[i])))
			break ;
		if (cmd[i] == 34)
			dq = !dq;
		if (cmd[i] == 39)
			sq = !sq;
		if (echo && instr_split(&cmd[i]) && !dq && !sq)
			break ;
	}
	return (i);
}

char	**interesting_split(char *cmd, int depth)
{
	char	**res;
	char	*sub;
	int		i;

	while (ft_isspace(*cmd))
		cmd++;
	i = get_new_index(cmd, 0, 0, 0);
	if (!i)
		i += instr_split(&cmd[i]);
	sub = ft_substr(cmd, 0, (size_t) i);
	if (!cmd[i])
		res = ft_calloc(depth + 2, sizeof(char *));
	else
		res = interesting_split(cmd + i, depth + 1);
	res[depth] = sub;
	return (res);
}
