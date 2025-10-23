#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

/**
 * check_read_error - check if read failed
 * @fd_from: source file descriptor
 * @r: return value of read
 * @file_name: source file name
 */
void check_read_error(int fd_from, ssize_t r, char *file_name)
{
	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_name);
		if (close(fd_from) == -1)
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
		exit(98);
	}
}

/**
 * check_write_error - check if write failed
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @w: return value of write
 * @file_name: destination file name
 */
void check_write_error(int fd_from, int fd_to, ssize_t w, char *file_name)
{
	if (w == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_name);
		if (close(fd_from) == -1)
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
		if (close(fd_to) == -1)
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
		exit(99);
	}
}

/**
 * check_close_error - check if close failed
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
 * main - copies content of a file to another file
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;
	ssize_t r, w;
	char buffer[BUFFER_SIZE];

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

	while ((r = read(fd_from, buffer, BUFFER_SIZE)) > 0)
	{
		check_read_error(fd_from, r, argv[1]);
		w = write(fd_to, buffer, r);
		check_write_error(fd_from, fd_to, w, argv[2]);
	}

	check_read_error(fd_from, r, argv[1]);

	check_close_error(fd_from);
	check_close_error(fd_to);

	return (0);
}

