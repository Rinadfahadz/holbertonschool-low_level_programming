#include "main.h"

/**
 * check_write_error - checks write errors
 * @w: write return value
 * @r: read return value
 * @filename: filename to write
 * @fd_from: source fd
 * @fd_to: dest fd
 */
void check_write_error(int w, int r, char *filename, int fd_from, int fd_to)
{
	if (w == -1 || w != r)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", filename);
		close(fd_from);
		close(fd_to);
		exit(99);
	}
}

/**
 * check_read_error - checks read errors
 * @r: read return value
 * @filename: filename to read
 * @fd_from: source fd
 * @fd_to: dest fd
 */
void check_read_error(int r, char *filename, int fd_from, int fd_to)
{
	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", filename);
		close(fd_from);
		close(fd_to);
		exit(98);
	}
}

/**
 * check_close_error - checks close errors
 * @fd: file descriptor
 */
void check_close_error(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - copies content of a file to another
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to, r, w;
	char buffer[1024];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}

	fd_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		check_close_error(fd_from);
		exit(99);
	}

	while ((r = read(fd_from, buffer, 1024)) > 0)
	{
		w = write(fd_to, buffer, r);
		check_write_error(w, r, argv[2], fd_from, fd_to);
	}

	check_read_error(r, argv[1], fd_from, fd_to);
	check_close_error(fd_from);
	check_close_error(fd_to);

	return (0);
}

