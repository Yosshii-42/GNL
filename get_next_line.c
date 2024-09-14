#include "get_next_line.h"

char	*ft_strjoin(char *s1, char c, int len)
{
	char	*result;
	int	i;

	if (!s1 && !c)
		return (NULL);
	result = NULL;
	result = (char *)malloc(sizeof(char) * len);
	if (!result)
		return (free(s1), NULL);
	i = -1;
	while (++i < len - 2)
		result[i] = s1[i];
	result[i] = c;
	result[++i] = '\0';
	free(s1);
	return (result);
}

void	buf_zero(char *buf, char *ptr, int *read_byte)
{
	int	i;

	i = -1;
	while (++i < BUFFER_SIZE)
		buf[i] = 0;
	*ptr = 0;
	ptr = NULL;
	*read_byte = 0;
}

char	get_char(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*ptr;
	static int	read_byte;

	if (read_byte == 0)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte < 0)
			return (buf_zero(buf, ptr, &read_byte), FAIL);
		ptr = buf;
	}
	if (--read_byte >= 0)
		return ((char) * (ptr++));
	return (buf_zero(buf, ptr, &read_byte), EOF);
}

char	*get_next_line(int fd)
{
	char	*result;
	char	c;
	int	len;

	if (fd == -1)
		return (NULL);
	result = NULL;
	c = '\0';
	len = 2;
	while (1)
	{
		c = get_char(fd);
		if (c == FAIL)
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
/*
int	main(void)
{
	char	*result;

	while (1)
	{
		result = NULL;
		result = get_next_line(0);
		if (!result)
			break;
		printf("%s", result);
		free(result);
	}
}
*/
