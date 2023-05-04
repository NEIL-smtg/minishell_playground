/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:07:08 by suchua            #+#    #+#             */
/*   Updated: 2023/05/05 02:07:11 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	store_files(char *target, t_files **files, int cmd_type)
{
	struct dirent	*entry;
	DIR				*dir;

	dir = opendir(".");
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (target_found(entry->d_name, target))
			files_addback(files, entry->d_name, cmd_type);
		entry = readdir(dir);
	}
	free(dir);
	if (target)
		free(target);
	return (1);
}

void	overwrite_cmd(t_cmdlst **node, t_files *files, int *i, int j)
{
	char	*front;
	char	*back;
	char	*middle;

	if (!files)
		return ;
	middle = NULL;
	front = ft_substr((*node)->cmd, 0, (size_t)(*i));
	while ((*node)->cmd[j] && !ft_isspace((*node)->cmd[j]))
		++j;
	back = ft_substr((*node)->cmd, j, ft_strlen((*node)->cmd) - j - 1);
	while (files)
	{
		middle = gnl_strjoin(middle, files->file);
		middle = gnl_strjoin(middle, " ");
		files = files->next;
	}
	front = gnl_strjoin(front, middle);
	front = gnl_strjoin(front, back);
	free(back);
	free((*node)->cmd);
	(*node)->cmd = front;
	*i += (int) ft_strlen(middle) - 1;
	free(middle);
}

int	manage_wildcard(t_cmdlst **node)
{
	int		i;
	t_files	*files;
	int		ret;

	i = -1;
	files = NULL;
	while ((*node)->cmd[++i])
	{
		if ((*node)->cmd[i] == '*')
		{
			ret = is_curr_dir((*node)->cmd, i);
			if (!ret || !store_files(get_target((*node)->cmd, i + 1),
					&files, ret))
				return (0);
			overwrite_cmd(node, files, &i, i);
			ft_free_files_lst(&files);
		}
	}
	return (1);
}

void	ft_parse_wildcard(t_shell *info)
{
	t_cmdlst	*node;

	node = info->cmdlst;
	while (node)
	{
		if (ft_strchr(node->cmd, '*') && !manage_wildcard(&node))
			return ;
		node = node->next;
	}
}
