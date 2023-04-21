/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:17:32 by suchua            #+#    #+#             */
/*   Updated: 2023/04/22 04:11:52 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_brac(t_cmdlst **node)
{
	t_cmdlst	*tmp;
	int			i;
	
	tmp = *node;
	i = -1;
	while (tmp->cmd[++i])
		if (tmp->cmd[i] == ')' || tmp->cmd[i] == '(')
			tmp->cmd[i] = 32;
}

void	fill_cmd_info(t_cmdlst **lst)
{
	t_cmdlst	*tmp;
	t_cmdlst	*prev;

	tmp = *lst;
	prev = NULL;
	while (tmp)
	{
		tmp->within_brac = 0;
		tmp->open_brac = 0;
		tmp->closed_brac = 0;
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
		remove_brac(&tmp);
		prev = tmp;
		tmp = tmp->next;
	}
}

//	char	cmd[100] = "(echo 'msg1' || cmd2) && cmd3 | cmd4";
//	char	cmd[100] = "(echo 'ms |   |   |  g1' | cmd2) && (cmd3 || cmd4) || (cmd5 && cmd6)";
void	interpret_cmd(char *cmd, t_cmdlst **lst)
{
	char		*s;
	char		**split;
	int			i;

	s = NULL;
	split = interesting_split(cmd, 0, 0, 0);
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
	fill_cmd_info(lst);
	ft_free2d(split);
	free(s);
	// print_lst(*lst);
	// ft_free_cmdlst(lst);
}
