#include "shell.h"
#include <fcntl.h>
/**
 * main - entry point
 * @argc: number of arguments
 * @argv: array of arguments
 */
int main(int argc, char **argv)
{
	info_t info = INFO_INIT;
	int fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			switch (errno)
			{
				case EACCES:
					exit(126);
				case ENOENT:
					_eputs(argv[0]);
					_eputs(": 0: Can't Open ");
					_eputs(argv[1]);
					_eputchar('\n');
					_eputchar(BUF_FLUSH);
					exit(127);
				default:
					return(EXIT_FAILURE);
			}
		}
		info.fd = fd;
	}
	populate_env_list(&info);
	read_history(&info);

	while (1)
	{
		ssize_t input_result = get_input(&info);

		if (input_result == -1)
		{
			break;
		}
		hsh(&info, argv);
		
	}

	return (EXIT_SUCCESS);
}
