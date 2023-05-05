/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:30:39 by suchua            #+#    #+#             */
/*   Updated: 2023/05/06 02:39:33 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_doubles(char *s)
{
	return (ft_strncmp(s, "||", 3) == 0
		|| ft_strncmp(s, "&&", 3) == 0);
}

void	wait_child_process(t_shell *info)
{
	while (waitpid(-1, &info->ms_status, 0) > 0)
		continue ;
}

static int skip(t_cmdlst *node)
{
	return ((node->next->within_brac || !is_doubles(node->next->cmd)));
}

void	skip_cmd_decider(t_cmdlst **node)
{
	while ((*node)->next && skip(*node))
		(*node) = (*node)->next;
}
