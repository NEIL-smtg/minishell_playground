/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 03:20:58 by suchua            #+#    #+#             */
/*   Updated: 2023/03/20 20:20:23 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_file_type(char *file, char *type)
{
	int	i;

	if (!ft_strncmp("..", file, 2) || !ft_strncmp(".", file, 1))
		return (0);
	if (type == NULL)
		return (1);
	i = 0;
	while (file[i] && file[i] != *type)
		++i;
	if (!file[i] || ft_strncmp(&file[i], type, ft_strlen(type)))
		return (0);
	return (1);
}

int	get_wildcard_strlen(char *cmd, t_files *files)
{
	int	len;
	int	j;

	len = 0;
	while (files)
	{
		len += ft_strlen(files->file);
		files = files->next;
		++len;
	}
	j = -1;
	while (cmd[++j])
	{
		if (cmd[j] == '*')
			while (cmd[j] && cmd[j] != 32)
				++j;
		if (!cmd[j])
			break ;
		++len;
	}
	return (len + 1);
}

static void	store_to_str(char *new, char *cmd, t_files *tmp)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (cmd[j] != '*')
		new[i++] = cmd[j++];
	while (tmp)
	{
		k = -1;
		while (tmp->file[++k])
			new[i++] = tmp->file[k];
		new[i++] = 32;
		tmp = tmp->next;
	}
	while (cmd[j])
	{
		if (cmd[j] == '*')
			while (cmd[j] && cmd[j] != 32)
				++j;
		if (!cmd[j])
			break ;
		new[i++] = cmd[j++];
	}
}

char	*write_files_to_str(char *cmd, t_files **files)
{
	char	*new;

	if (!files || !*files)
		return (wildcard_error(cmd, files));
	new = ft_calloc(get_wildcard_strlen(cmd, *files), sizeof(char));
	store_to_str(new, cmd, *files);
	ft_free_files_lst(files);
	return (new);
}
