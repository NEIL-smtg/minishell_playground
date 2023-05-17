/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dangling_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 19:59:48 by suchua            #+#    #+#             */
/*   Updated: 2023/05/17 15:23:16 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validation(char *str, int i)
{
	int		j;
	int		k;

	j = i - 1;
	while (j >= 0 && ft_isspace(str[j]))
		--j;
	if (j < 0)
		++j;
	k = i + 1;
	while (str[k] && ft_isspace(str[k]))
		++k;
	if (!str[k])
		--k;
	if ((str[j] == '<' || str[j] == '>') && str[j] != str[i])
		return (0);
	if ((str[k] == '<' || str[k] == '>') && str[k] != str[i])
		return (0);
	k = i + 1;
	while (str[k] && str[i] == str[k])
		++k;
	if (k - i + 1 > 3)
		return (0);
	return (1);
}

//returns 1 when error
int	dangling_redir(char *str, int dq, int sq)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
			dq = !dq;
		else if (str[i] == 39)
			sq = !sq;
		else if (!dq && !sq && (str[i] == '<' || str[i] == '>')
			&& !validation(str, i))
		{
			ft_putstr_fd("minishell: parse error near '", 2);
			ft_putchar_fd(str[i], 2);
			ft_putendl_fd("'", 2);
			return (1);
		}
		++i;
	}
	return (0);
}
