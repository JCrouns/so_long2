/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:40:41 by jait-chd          #+#    #+#             */
/*   Updated: 2024/12/13 15:41:42 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_store(int fd, char *buf, char *backup)
{
	ssize_t	read_byte;
	char	*temp;

	read_byte = 1;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	while (read_byte != 0)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte == -1)
			return (0);
		else if (read_byte == 0)
			break ;
		buf[read_byte] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*extract_line(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (NULL);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	line = read_store(fd, buf, backup);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	backup = extract_line(line);
	return (line);
}

// #include <stdio.h>

// int main()
// {
//     int fd;
//     char *line;

//     fd = open("test.txt", O_RDONLY);

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }
//    // printf("last : %s",line);
//     close(fd);
//     return (0);
// }

/* int     main ()
{
		int     fd;
		char    *new;
		int     d;

		fd = open ("test.txt", O_RDONLY | O_CREAT);
		printf("fd = %d\n", fd);
		new = get_next_line(fd);
		printf("returned string is : %s", new);
	free(new);
		new = get_next_line(fd);
		printf("returned string is : %s", new);
		free(new);
	new = get_next_line(fd);
		printf("returned string is : %s", new);
	free(new);
			new = get_next_line(fd);
			printf("last one is : %s",new);
		free(new);
		close(fd);
		return (0);


	int fd;
	char *str;
	int i = 0;

	fd = open("text.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	str = get_next_line(fd);
	if (str)
	{
		putstr(str);
	}
	close(fd);



}*/
