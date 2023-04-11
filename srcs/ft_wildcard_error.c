/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:15:02 by suchua            #+#    #+#             */
/*   Updated: 2023/03/20 20:21:48 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*wildcard_error(char *str, t_files **files)
{
	if (*files)
		ft_free_files_lst(files);
	ft_putstr_fd("minishell : No matches found ", 2);
	ft_putendl_fd(str, 2);
	return (NULL);
}
