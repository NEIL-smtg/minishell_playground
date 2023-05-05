/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:46:42 by suchua            #+#    #+#             */
/*   Updated: 2023/05/05 20:13:42 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	build_redirlst(char *filename, t_shell *info, int type)
{
	if (type == L1)
		redirlst_addback(&info->infile, filename,
			open(filename, O_RDONLY));
	else if (type == R2)
		redirlst_addback(&info->outfile, filename,
			open(filename, O_RDWR | O_APPEND | O_CREAT, 0000644));
	else if (type == R1)
		redirlst_addback(&info->outfile, filename,
			open(filename, O_RDWR | O_TRUNC | O_CREAT, 0000644));
	free(filename);
}

static void	trim_cmd(t_cmdlst **node)
{
	t_cmdlst	*tmp;
	int			flag;
	int			i;

	i = -1;
	tmp = *node;
	flag = 0;
	while (tmp->cmd[++i])
	{
		if (tmp->cmd[i] == '<' || tmp->cmd[i] == '>')
		{
			tmp->cmd[i] = 32;
			flag = 1;
			continue ;
		}
		while (flag && tmp->cmd[i] && ft_isspace(tmp->cmd[i]))
			++i;
		while (flag && tmp->cmd[i] && !ft_isspace(tmp->cmd[i]))
		{
			tmp->cmd[i] = 32;
			++i;
		}
		flag = 0;
	}
}

static int	redir_decider(t_shell *info, t_cmdlst **node)
{
	if (!info->infile && !info->outfile)
		return (0);
	trim_cmd(node);
	ft_redir_exec(info, *node);
	ft_free_infile_outfile(info);
	return (1);
}

static void scan_redir(t_shell *info, t_cmdlst **node)
{
	t_cmdlst	*tmp;
	int			i;

	i = -1;
	tmp = *node;
	while (tmp->cmd[++i])
	{
		if (!ft_strncmp("<<", &(tmp->cmd[i]), 2))
			heredoc(get_limiter(&tmp->cmd[i + 2]), info, tmp->next);
		else if (tmp->cmd[i] == '<')
			build_redirlst(get_limiter(&tmp->cmd[i + 1]), info, L1);
		else if (!ft_strncmp(">>", &(tmp->cmd[i]), 2))
			build_redirlst(get_limiter(&tmp->cmd[i + 2]), info, R2);
		else if (tmp->cmd[i] == '>')
			build_redirlst(get_limiter(&tmp->cmd[i + 1]), info, R1);
		if (!ft_strncmp("<<", &(tmp->cmd[i]), 2)
			|| !ft_strncmp(">>", &(tmp->cmd[i]), 2))
			++i;
	}
}

int	set_redir(t_shell *info, t_cmdlst **node)
{
	if (!ft_strchr((*node)->cmd, '>') && !ft_strchr((*node)->cmd, '<'))
		return (0);
	if (redir_within_quotes((*node)->cmd))
		return (0);
	info->infile = NULL;
	info->outfile = NULL;
	scan_redir(info, node);
	return (redir_decider(info, node));
}
