/*
void	get_size(t_structure_main *w)
{
	w->s_map.buff = get_next_line(w->fd);
	w->s_map.j = 0;
	w->s_map.temp = 0;
	while (w->s_map.buff)
	{
		w->s_map.temp_list = ft_split(w->s_map.buff, ' ');
		w->s_map.i = 0;
		while (w->s_map.temp_list[w->s_map.i])
		{
			free(w->s_map.temp_list[w->s_map.i]);
			w->s_map.i++;
		}
		if (w->s_map.temp < w->s_map.i)
			w->s_map.temp = w->s_map.i;
		free(w->s_map.temp_list);
		free(w->s_map.buff);
		w->s_map.buff = get_next_line(w->fd);
		w->s_map.j++;
	}
	w->s_map.sizex = w->s_map.temp;
	w->s_map.sizey = w->s_map.j;
	free(w->s_map.buff);
}

void	split_map(t_structure_main *w)
{
	w->s_map.buff = get_next_line(w->fd);
	w->s_map.j = 0;
	w->s_map.map = (char **)malloc(w->s_map.sizey * sizeof(char *));
	while (w->s_map.buff)
	{
		w->s_map.map[w->s_map.j] = (char *)malloc(w->s_map.sizex * sizeof(char));
		w->s_map.temp_list = ft_split(w->s_map.buff, ' ');
		w->s_map.i = 0;
		while (w->s_map.temp_list[w->s_map.i])
		{
			w->s_map.map[w->s_map.j][w->s_map.i] = *w->s_map.temp_list[w->s_map.i];
			//printf("%s ",w->s_map.temp_list[w->s_map.i]);
			w->s_map.i++;
		}
		//if (w->s_map.i != w->s_map.sizex)
		//	;
		w->s_map.i = 0;
		while (w->s_map.temp_list[w->s_map.i] && w->s_map.i < w->s_map.sizex)
		{
			free(w->s_map.temp_list[w->s_map.i]);
			w->s_map.i++;
		}
		//	printf("%c", w->s_map.buff[w->s_map.i]);
			//w->s_map.map[w->s_map.i] = w->s_map.buff;
		free(w->s_map.temp_list[w->s_map.i]);
		free(w->s_map.temp_list);
		w->s_map.j++;
		free(w->s_map.buff);
		w->s_map.buff = get_next_line(w->fd);
	}
	free(w->s_map.buff);
}

void	print_map(t_structure_main *w)
{
	//(void)w;
	int i = -1;
	while (w->s_map.map[++i])
		printf("%s\n", w->s_map.map[i]);
}

*/