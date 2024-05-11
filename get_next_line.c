/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:46:06 by yotsurud          #+#    #+#             */
/*   Updated: 2024/05/11 11:38:56 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char c, int len)
{
	char	*string;
	int		i;

	i = 0;
	if (!s1 && !c)
		return (NULL);
	string = NULL;
	string = (char *)malloc(sizeof(char) * len);
	if (!string)
		return (free(s1), NULL);
	i = -1;
	while (++i < len - 2)
		string[i] = s1[i];
	string[i] = c;
	string[++i] = '\0';
	free(s1);
	return (string);
}

static char	ft_getchar(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*ptr;
	static int	read_byte;

	if (read_byte == 0)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte < 0)
			return (FALSE);
		ptr = buf;
	}
	if (--read_byte >= 0)
		return ((char)*(ptr++));
	else
		return (EOF);
}

char	*get_next_line(int fd)
{
	char	*result;
	char	c;
	int		len;

	if (fd == -1)
		return (NULL);
	result = NULL;
	c = '\0';
	len = 2;
	while (1)
	{
		c = ft_getchar(fd);
		if (c == FALSE)
			return (free(result), NULL);
		if (c == EOF)
			break ;
		result = ft_strjoin(result, c, len);
		len++;
		if (c == '\n')
			break ;
	}
	return (result);
}

// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q a.out");
// }

//  int	main()
// {
//  	int		fd;
//  	char	*result;

//  	fd = open("test.txt", O_RDONLY);
//  	while(1)
//  	{
//  		result = get_next_line(fd);
//  		if (!result)
//  			break ;
//  		printf("%s", result);
//  		free(result);
//  	}
//  	close(fd);
// }
