/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:49:31 by suchua            #+#    #+#             */
/*   Updated: 2022/10/13 13:09:53 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	write (fd, s, ft_strlen(s));
}

// #include <string.h>
// #include <stdlib.h>
// #include <fcntl.h>

// int main (int argc, char *argv[])
// {
//     int fd1;
//     char buf[128];
//     fd1 = open(argv[1], O_WRONLY);
//     // if (fd1 == -1) {
//     //     perror(argv[1]);
//     //     return EXIT_FAILURE;
//     // }

//     /* Enter the data to be written into the file */
//     scanf("%127s", buf);

// 	printf("%d\n",fd1);

//     close(fd1);

//     return 0;
// }
