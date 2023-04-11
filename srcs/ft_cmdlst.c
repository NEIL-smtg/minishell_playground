/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:17:32 by suchua            #+#    #+#             */
/*   Updated: 2023/04/12 01:41:41 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_cmd_info(t_cmdlst **lst)
{
	t_cmdlst	*tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp->open_brac = 0;
		tmp->close_brac = 0;
		tmp->no_brac = 0;
		tmp->relation = NORMAL;
		if (ft_strchr(tmp->cmd, '('))
			tmp->open_brac = 1;
		else if (ft_strchr(tmp->cmd, ')'))
			tmp->close_brac = 1;
		else
			tmp->no_brac = 0;
		if (tmp->next && cmdlst_is_double(tmp->next->cmd, "||"))
			tmp->relation = DOUBLE_PIPE;
		else if (tmp->next && cmdlst_is_double(tmp->next->cmd, "&&"))
			tmp->relation = DOUBLE_N;
		else if (tmp->next && cmdlst_is_double(tmp->next->cmd, "|"))
			tmp->relation = PIPE;
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
	split = interesting_split(cmd, 0);
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
			memset(s, 0, ft_strlen(s));
		++i;
	}
	fill_cmd_info(lst);
	print_lst(*lst);
	ft_free_cmdlst(lst);
}
