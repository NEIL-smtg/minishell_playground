/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:07:08 by suchua            #+#    #+#             */
/*   Updated: 2023/04/19 02:19:37 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_curr_dir(char *cmd, int i)
{
	int	j;

	if (i == 0 || ft_isspace(cmd[i - 1]))
		return (1);
	j = i;
	while (cmd[j] && !ft_isspace(cmd[j]))
		--j;
	return (ft_strncmp("./*", &cmd[j], 3) == 0);
}

void	manage_wildcard(t_cmdlst **node)
{
	int			i;
	t_cmdlst	*tmp;

	i = 0;
	tmp = *node;
	while (tmp->cmd[i] && tmp->cmd[i] != '*')
		++i;
	
}

void	ft_parse_wildcard(t_shell *info)
{
	t_cmdlst	*node;

	node = info->cmdlst;
	while (node)
	{
		if (ft_strchr(node->cmd, '*'))
			manage_wildcard(&node);
		node = node->next;
	}
}
