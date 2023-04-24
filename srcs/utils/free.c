/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:54:31 by suchua            #+#    #+#             */
/*   Updated: 2023/04/24 22:41:03 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_files_lst(t_files **lst)
{
	t_files	*tmp;

	while ((*lst))
	{
		tmp = (*lst)->next;
		free((*lst)->file);
		free((*lst));
		(*lst) = tmp;
	}
}

void	ft_free_infile_outfile(t_shell *info)
{
	t_redirlst	*tmp;

	while (info->infile)
	{
		tmp = info->infile->next;
		free(info->infile->filename);
		free(info->infile);
		info->infile = tmp;
	}
	while (info->outfile)
	{
		tmp = info->outfile->next;
		free(info->outfile->filename);
		free(info->outfile);
		info->outfile = tmp;
	}
}

void	free_everything(t_shell *info)
{
	free(info->input_line);
	ft_free2d(info->ms_env);
	free(info->ms_prompt);
}

void	ft_free_cmdlst(t_cmdlst **lst)
{
	t_cmdlst	*tmp;

	while ((*lst))
	{
		tmp = (*lst)->next;
		free((*lst)->cmd);
		free((*lst));
		(*lst) = tmp;
	}
}
