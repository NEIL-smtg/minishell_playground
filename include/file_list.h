/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:25:38 by suchua            #+#    #+#             */
/*   Updated: 2023/05/11 14:43:54 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_LIST_H
# define FILE_LIST_H

//	to store info of files to redirect
typedef struct s_redirlst
{
	int					fd;
	char				*filename;
	struct s_redirlst	*next;
}	t_redirlst;

//	wildcard linked list, store file that found in directory
typedef struct s_files
{
	char				*file;
	struct s_files		*next;
}	t_files;

//	retation	=	relation of prev cmd and nxt cmd
//	open_brac	=	indicates bracket starts
//	close_brac	=	indicates bracket closed
//	no brac		=	cmd isnt within bracket
typedef struct s_cmdlst
{
	char				*cmd;
	int					open_brac;
	int					closed_brac;
	int					within_brac;
	int					relation;
	struct s_cmdlst		*prev;
	struct s_cmdlst		*next;
}	t_cmdlst;

#endif
