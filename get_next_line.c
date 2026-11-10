/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlebaill <rlebaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:57:45 by rlebaill          #+#    #+#             */
/*   Updated: 2026/11/10 10:04:10 by rlebaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *buff)
{
	char	*tmp;
	char	*line;
	char	*new_line;
	ssize_t	bytes_read;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	line = ft_strdup(buff);
	if (!line)
		return (free(tmp), NULL);
	while (!ft_strchr(line, '\n'))
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(tmp), free(line), NULL);
		if (bytes_read == 0)
			return (free(tmp), line);
		tmp[bytes_read] = '\0';
		new_line = ft_strjoin(line, tmp);
		if (!new_line)
			return (free(line), free(tmp), NULL);
		(free(line), line = new_line);
	}
	return (free(tmp), line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = {0};
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_file(fd, buf);
	if (!line)
		return (buf[0] = '\0', NULL);
	if (!line[0])
		return (free(line), NULL);
	if (!ft_strchr(line, '\n'))
		return (buf[0] = '\0', line);
	ft_strcpy(buf, ft_strchr(line, '\n') + 1);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n' && line[i + 1])
		line[i + 1] = '\0';
	return (line);
}

// #include <string.h>
// #include <errno.h>

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	if (argc != 2)
// 		return (printf("get_next_line: Wrong number of arguments\n"), 1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (dprintf(2, "get_next_line: %s\n", strerror(errno)), errno);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
