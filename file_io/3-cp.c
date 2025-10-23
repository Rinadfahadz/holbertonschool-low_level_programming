#include "main.h"

/**
 * check_write_error - check write errors
 * @w: write return value
 * @r: read return value
 * @filename: destination file
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 */
void check_write_error(ssize_t w, ssize_t r, char *filename,
		       int fd_from, int fd_to)
{
	if (w == -1 || w != r)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", filename);
		if (close(fd_from) == -1)
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
		if (close(fd_to) == -1)
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
		exit(99);
	}
}

/**
 * check_close_error - check close errors
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
 * open_files - open source and destination files
 * @file_from: source file
 * @file_to: destination file
 * @fd_from: pointer to source fd
 * @fd_to: pointer to destination fd
 */
void open_files(char *file_from, char *file_to, int *fd_from, int *fd_to)
{
	*fd_from = open(file_from, O_RDONLY);
	if (*fd_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		exit(98);
	}

	*fd_to = open(file_to, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (*fd_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
		check_close_error(*fd_from);
		exit(99);
	}
}

/**
 * copy_data - copy content from fd_from to fd_to
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @file_from: source filename
 * @file_to: destination filename
 */
void copy_data(int fd_from, int fd_to, char *file_from, char *file_to)
{
	ssize_t r, w;
	char buffer[1024];

	while ((r = read(fd_from, buffer, 1024)) > 0)
	{
		w = write(fd_to, buffer, r);
		check_write_error(w, r, file_to, fd_from, fd_to);
	}

	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		check_close_error(fd_from);
		check_close_error(fd_to);
		exit(98);
	}
}

/**
 * main - copies content of a file to another file
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	open_files(argv[1], argv[2], &fd_from, &fd_to);
	copy_data(fd_from, fd_to, argv[1], argv[2]);
	check_close_error(fd_from);
	check_close_error(fd_to);

	return (0);
}

