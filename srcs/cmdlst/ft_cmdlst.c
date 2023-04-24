/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:17:32 by suchua            #+#    #+#             */
/*   Updated: 2023/04/24 22:47:30 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_brac(t_cmdlst **node, int dq, int sq, int echo)
{
	t_cmdlst	*tmp;
	int			i;

	tmp = *node;
	i = -1;
	while (tmp->cmd[++i])
	{
		if (!ft_strncmp("echo", &tmp->cmd[i], 4))
			echo = 1;
		if (tmp->cmd[i] == 34)
			dq = !dq;
		if (tmp->cmd[i] == 39)
			sq = !sq;
		if (!echo && !dq && !sq && (tmp->cmd[i] == ')' || tmp->cmd[i] == '('))
			tmp->cmd[i] = 32;
	}
}

void	fill_cmd_info(t_cmdlst **lst)
{
	t_cmdlst	*tmp;
	t_cmdlst	*prev;

	tmp = *lst;
	prev = NULL;
	while (tmp)
	{
		if (ft_strchr(tmp->cmd, '('))
		{
			tmp->open_brac = 1;
			tmp->within_brac = 1;
		}
		if (ft_strchr(tmp->cmd, ')'))
		{
			tmp->closed_brac = 1;
			tmp->within_brac = 1;
		}
		if (prev && prev->within_brac && !prev->closed_brac)
			tmp->within_brac = 1;
		remove_brac(&tmp, 0, 0, 0);
		prev = tmp;
		tmp = tmp->next;
	}
}

static void	fill_cmdlst(char **split, t_cmdlst **lst)
{
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	while (split[i])
	{
		while (split[i] && !to_split(split[i]))
		{
			s = gnl_strjoin(s, split[i]);
			s = gnl_strjoin(s, " ");
			++i;
		}
		ft_cmdlst_addback(lst, s);
		if (!split[i])
			break ;
		ft_cmdlst_addback(lst, split[i]);
		if (s)
			ft_memset(s, 0, ft_strlen(s));
		++i;
	}
	free(s);
}

void	interpret_cmd(char *cmd, t_cmdlst **lst)
{
	char		**split;

	split = interesting_split(cmd, 0);
	fill_cmdlst(split, lst);
	fill_cmd_info(lst);
	ft_free2d(split);
}
