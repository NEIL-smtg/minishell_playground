/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:07:09 by suchua            #+#    #+#             */
/*   Updated: 2023/03/20 20:26:58 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_dir(char *dir, int len)
{
	if (len == 0 || !ft_strncmp("./", dir, len))
		return (1);
	return (0);
}

int	is_local_dir(char *cmd, int i)
{
	int	j;

	j = i - 1;
	while (j >= 0 && cmd[j] != 32)
		--j;
	if (valid_dir(&cmd[j], i - j - 1))
		return (1);
	msg_cmd_not_found(ft_split(cmd, 32));
	return (0);
}

// 0 means wildcard not found, -1 means cmd error
int	wild_card_exists(char *cmd)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '*' && !is_local_dir(cmd, i))
			return (-1);
		else if (cmd[i] == '*')
			flag = 1;
	}
	return (flag);
}

void	add_file(t_files **lst, char *file)
{
	t_files	*new;
	t_files	*last;

	new = ft_calloc(1, sizeof(t_files));
	new->file = ft_strdup(file);
	new->next = NULL;
	if (!lst || !*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	get_the_files(t_files **lst, char *type)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		exit(EXIT_FAILURE);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (is_file_type(entry->d_name, type))
			add_file(lst, entry->d_name);
		entry = readdir(dir);
	}
	free(dir);
	if (type)
		free(type);
}
