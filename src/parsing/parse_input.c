/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:34:49 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/13 18:41:21 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	name_check(const char *filename)
{
	const char	*ext = ft_strrchr(filename, '.');

	if (!ext || ft_strcmp(ext, ".cub") != 0)
		ft_error("Error: Invalid file extension. Expected .cub\n");
}

void	validate_sides(const char *filename, t_map_data **map_data)
{
	(void)filename;
	(void)map_data;
}

void	validate_floor_ceiling(const char *filename, t_map_data **map_data)
{
	(void)filename;
	(void)map_data;
}

void	validate_map_structure(const char *filename, t_map_data **map_data)
{
	(void)filename;
	(void)map_data;
}

void	free_lines(char **lines, int line_count, char *last_line)
{
	for (int i = 0; i < line_count; i++)
		free(lines[i]);
	free(lines);
	free(last_line);
	ft_error("Error: Memory allocation failed while reading lines.\n");
}

void	floor_ceiling_parser(const char *line, t_map_data **map_data)
{
	if (!((*map_data)->floor_color) && ft_strncmp(line, "F ", 2) == 0)
	{
		printf("%s\n", line);
	}
	else if (!((*map_data)->ceiling_color) && ft_strncmp(line, "C ", 2) == 0)
	{
		printf("%s\n", line);
	}
}

void	parse_line(const char *line, t_map_data **map_data)
{
	if (line == NULL || map_data == NULL)
		return;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (!((*map_data)->no_path = ft_strdup(line + 3)))
			ft_error("Error: Memory allocation failed for NO path.\n");
		printf("%s\n", line);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (!((*map_data)->so_path = ft_strdup(line + 3)))
			ft_error("Error: Memory allocation failed for SO path.\n");
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (!((*map_data)->we_path = ft_strdup(line + 3)))
			ft_error("Error: Memory allocation failed for WE path.\n");
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (!((*map_data)->ea_path = ft_strdup(line + 3)))
			ft_error("Error: Memory allocation failed for EA path.\n");
	}
	else
		floor_ceiling_parser(line, map_data);
}

void	save_map_data(const char *filename, t_map_data **map_data)
{
	int		fd;
	char	*line;
	char	**lines;
	int		line_count;
	// int i = 0;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Error: Unable to open file.\n");
	line_count = 0;
	lines = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_count++;
		lines = realloc(lines, sizeof(char *) * (line_count + 1));
		if (!lines)
			free_lines(lines, line_count - 1, line);
		lines[line_count - 1] = line;
		lines[line_count] = NULL;
		parse_line(line, map_data);
		// i++;
		// printf("%d: %s",i,  line);
	}
	close(fd);
	(void)map_data;




}

void	parse_map(const char *filename, t_map_data *map_data)
{
	ft_memset(map_data, 0, sizeof(t_map_data));
	if (ft_strlen(filename) < 4)
	{
		fprintf(stderr, "Error: Filename too short to be valid.\n");
		exit(EXIT_FAILURE);
	}
	name_check(filename);
	save_map_data(filename, &map_data);
	validate_sides(filename, &map_data);
	validate_floor_ceiling(filename, &map_data);
	printf("Parsing map from file: %s\n", filename);
}
