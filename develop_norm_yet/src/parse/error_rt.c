#include "parse.h"

/*
** 씬파일 이상 유무 확인하는 함수,
** 보너스파트까지  고려했을  때   어떻게 할지 고민,
** 한줄 씩 읽어서,
1. 해당  라인의 식별자가  정의되어있는지 확인
2. 해당 식별자의 작성 규칙에  맞는지 확인
3.
*/

void	parse_error_identifier(char *line)
{
	perror("Error\n");
	ft_printf("** SCENE FILE ERROR **\n");
	ft_printf("** Scene file(intput '.rt' file) has wrong identifier line **\n");
	ft_printf("** this line: \"%s\" **", line);
	exit(EXIT_SUCCESS);
}

void	parse_error_data_count(char **data, int n, char *line)
{
	int		i;

	i = 0;
	while (data[i] != NULL)
		i++;
	if (i != n)
	{
		perror("Error\n");
		ft_printf("** SCENE FILE ERROR **\n");
		ft_printf("** Wrong number of data\n");
		ft_printf("** this line: \"%s\" **", line);
		exit(EXIT_SUCCESS);
	}
}

void	parse_error_img_filepath(void *img, char *line)
{
	if (img == NULL)
	{
		perror("Error\n");
		ft_printf("** SCENE FILE ERROR **\n");
		ft_printf("** Wrong img path \n");
		ft_printf("** this line: \"%s\" **", line);
		exit(EXIT_SUCCESS);
	}
}

// +,-부호는 맨 앞에, . 은 아무대나 오직 한개만, 나머지는 다 digit
void	data_is_double(char *str, char *line)
{
	char *start_point;

	start_point = str;
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
		++str;
	if (*str == '.')
		++str;
	while (ft_isdigit(*str))
		++str;
	if (*str == 0)
		return ;
	perror("Error\n");
	ft_printf("** SCENE FILE ERROR **\n");
	ft_printf("** Wrong type of data : IS NOT DOUBLE\n");
	ft_printf("** this line: \"%s\" **\n", line);
	ft_printf("** this data: \"%s\" **\n", start_point);
	exit(EXIT_SUCCESS);
}

void	data_is_integer(char *str, char *line)
{
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
		++str;
	if (*str == 0)
		return ;
	perror("Error\n");
	ft_printf("** SCENE FILE ERROR **\n");
	ft_printf("** Wrong type of data : IS NOT INTEGER\n");
	ft_printf("** this line: \"%s\" **\n", line);
	ft_printf("** this data: \"%s\" **\n", str);
	exit(EXIT_SUCCESS);
}
void	parse_data_set_double(char **data, int n, char *line)
{
	int		i;

	parse_error_data_count(data, n, line);
	i = -1;
	while (++i < n)
		data_is_double(data[i], line);
}

// is num 이고 0~ 1 사이여야함.
void	data_is_zero_to_one(char *str, char *line)
{
	data_is_double(str, line);
	if (atod(str) >= -1 && atod(str) <= 1)
		return ;
	perror("Error\n");
	ft_printf("** SCENE FILE ERROR **\n");
	ft_printf("** Wrong type of data : IS NOT FEET IN [0, 1]\n");
	ft_printf("** this line: \"%s\" **\n", line);
	ft_printf("** this data: \"%s\" **\n", str);
	exit(EXIT_SUCCESS);
}

void	parse_data_set_zero_to_one(char **data, int n, char *line)
{
	int			i;

	parse_error_data_count(data, n, line);
	i = -1;
	while (++i < n)
		data_is_zero_to_one(data[i], line);
}

void	data_is_in_rgb_range(char *str, char *line)
{
	data_is_integer(str, line);
	if (ft_atoi(str) >= 0 && ft_atoi(str) <= 255)
		return ;
	perror("Error\n");
	ft_printf("** SCENE FILE ERROR **\n");
	ft_printf("** Wrong type of data : IS NOT FEET IN RGB RANGE[0, 255] **\n");
	ft_printf("** this line: \"%s\" **\n", line);
	ft_printf("** this data: \"%s\" **\n", str);
	exit(EXIT_SUCCESS);
}

void	data_is_in_degree_range(char *str, char *line)
{
	data_is_double(str, line);
	if (atod(str) >= 0 && atod(str) <= 180)
		return ;
	perror("Error\n");
	ft_printf("** SCENE FILE ERROR **\n");
	ft_printf("** Wrong type of data : IS NOT FEET IN DEGREE RANGE[0, 180] **\n");
	ft_printf("** this line: \"%s\" **\n", line);
	ft_printf("** this data: \"%s\" **\n", str);
	exit(EXIT_SUCCESS);
}
void	parse_data_set_rgb(char **data, int n, char *line)
{
	int			i;

	parse_error_data_count(data, n, line);
	i = -1;
	while (++i < n)
		data_is_in_rgb_range(data[i], line);
}

void	error_malloc(void)
{
	perror("Malloc Failed in somewhere");
	exit(0);
}
