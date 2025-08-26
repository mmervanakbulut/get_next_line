/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musakbul <musakbul@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:24:54 by musakbul          #+#    #+#             */
/*   Updated: 2025/08/01 14:06:10 by musakbul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_append(int fd, char *buffer)
{
	char	*temp_buffer;
	char	*new_buffer;
	int		bytes_read;

	temp_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n')) // => buffer \n içeriyor mu? okunan byte 0'dan büyük mü?
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		new_buffer = ft_strjoin(buffer, temp_buffer); // burada temp_buffer ile önceki buffer birleştiriliyor ve new_buffer'a atanıyor
		free(buffer);
		buffer = new_buffer; // buffer güncelleniyor ve değişmiyor
	}
	free(temp_buffer);
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n') // EOF ve \n bulana kadar i artırılıyor
		i++;
	if (buffer[i] == '\n') // \n ise i bir kere daha arttırılıyor
		i++;
	line = ft_calloc(i + 1, sizeof(char)); // calloc ile \n + 1 kadar yer ayrılıyor ?????? \0 için tabii
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n') // EOF ve \n bulana kadar buffer line'a eşitleiniyor
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i]) // buffer update işlemini yaparken eğer EOF geldiysek NULL burada dönüyor
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!new_buffer)
		return (NULL);
	i++; // asıl başlangıç yerine geldik
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++]; // buffer update işlemi
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(1, 1);
	buffer = read_and_append(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
