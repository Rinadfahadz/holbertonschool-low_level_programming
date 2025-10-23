#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

/**
 * print_magic - prints the ELF magic numbers
 * @e_ident: ELF identification bytes
 */
void print_magic(unsigned char *e_ident)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%02x%c", e_ident[i], i == EI_NIDENT - 1 ? '\n' : ' ');
}

/**
 * print_class - prints the ELF class
 * @e_ident: ELF identification bytes
 */
void print_class(unsigned char *e_ident)
{
	printf("  Class:                             ");
	switch (e_ident[EI_CLASS])
	{
		case ELFCLASS32:
			printf("ELF32\n");
			break;
		case ELFCLASS64:
			printf("ELF64\n");
			break;
		default:
			printf("<unknown: %x>\n", e_ident[EI_CLASS]);
			break;
	}
}

/**
 * print_data - prints the ELF data encoding
 * @e_ident: ELF identification bytes
 */
void print_data(unsigned char *e_ident)
{
	printf("  Data:                              ");
	switch (e_ident[EI_DATA])
	{
		case ELFDATA2LSB:
			printf("2's complement, little endian\n");
			break;
		case ELFDATA2MSB:
			printf("2's complement, big endian\n");
			break;
		default:
			printf("<unknown: %x>\n", e_ident[EI_DATA]);
			break;
	}
}

/**
 * print_version - prints the ELF version
 * @e_ident: ELF identification bytes
 */
void print_version(unsigned char *e_ident)
{
	printf("  Version:                           %d", e_ident[EI_VERSION]);
	if (e_ident[EI_VERSION] == EV_CURRENT)
		printf(" (current)");
	printf("\n");
}

/**
 * print_osabi - prints the ELF OS/ABI
 * @e_ident: ELF identification bytes
 */
void print_osabi(unsigned char *e_ident)
{
	printf("  OS/ABI:                            ");
	switch (e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV:
			printf("UNIX - System V\n");
			break;
		case ELFOSABI_NETBSD:
			printf("UNIX - NetBSD\n");
			break;
		case ELFOSABI_SOLARIS:
			printf("UNIX - Solaris\n");
			break;
		default:
			printf("<unknown: %x>\n", e_ident[EI_OSABI]);
			break;
	}
}

/**
 * print_abiversion - prints the ELF ABI version
 * @e_ident: ELF identification bytes
 */
void print_abiversion(unsigned char *e_ident)
{
	printf("  ABI Version:                       %d\n", e_ident[EI_ABIVERSION]);
}

/**
 * print_type - prints the ELF type
 * @e_type: ELF type
 */
void print_type(Elf64_Half e_type)
{
	printf("  Type:                              ");
	switch (e_type)
	{
		case ET_NONE:
			printf("NONE (None)\n");
			break;
		case ET_REL:
			printf("REL (Relocatable file)\n");
			break;
		case ET_EXEC:
			printf("EXEC (Executable file)\n");
			break;
		case ET_DYN:
			printf("DYN (Shared object file)\n");
			break;
		case ET_CORE:
			printf("CORE (Core file)\n");
			break;
		default:
			printf("<unknown: %x>\n", e_type);
			break;
	}
}

/**
 * print_entry - prints the ELF entry point
 * @e_entry: entry address
 * @e_ident: ELF identification bytes
 */
void print_entry(unsigned long e_entry, unsigned char *e_ident)
{
	printf("  Entry point address:               ");
	if (e_ident[EI_CLASS] == ELFCLASS32)
		printf("0x%x\n", (unsigned int)e_entry);
	else
		printf("0x%lx\n", e_entry);
}

/**
 * read_elf32 - reads and prints ELF32 header info
 * @fd: file descriptor
 * @e_ident: ELF identification bytes
 */
void read_elf32(int fd, unsigned char *e_ident)
{
	Elf32_Ehdr hdr;
	size_t r;

	r = read(fd, &hdr, sizeof(Elf32_Ehdr));
	if (r != sizeof(Elf32_Ehdr))
	{
		dprintf(STDERR_FILENO, "Error: Can't read ELF header\n");
		close(fd);
		exit(98);
	}
	print_type(hdr.e_type);
	print_entry(hdr.e_entry, e_ident);
}

/**
 * read_elf64 - reads and prints ELF64 header info
 * @fd: file descriptor
 * @e_ident: ELF identification bytes
 */
void read_elf64(int fd, unsigned char *e_ident)
{
	Elf64_Ehdr hdr;
	size_t r;

	r = read(fd, &hdr, sizeof(Elf64_Ehdr));
	if (r != sizeof(Elf64_Ehdr))
	{
		dprintf(STDERR_FILENO, "Error: Can't read ELF header\n");
		close(fd);
		exit(98);
	}
	print_type(hdr.e_type);
	print_entry(hdr.e_entry, e_ident);
}

/**
 * main - displays ELF header info
 * @argc: number of args
 * @argv: args array
 * Return: 0 on success, 98 on error
 */
int main(int argc, char *argv[])
{
	int fd;
	unsigned char e_ident[EI_NIDENT];
	size_t r;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: %s elf_filename\n", argv[0]);
		exit(98);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}

	r = read(fd, e_ident, EI_NIDENT);
	if (r != EI_NIDENT)
	{
		dprintf(STDERR_FILENO, "Error: Not an ELF file %s\n", argv[1]);
		close(fd);
		exit(98);
	}

	if (e_ident[EI_MAG0] != ELFMAG0 || e_ident[EI_MAG1] != ELFMAG1 ||
	    e_ident[EI_MAG2] != ELFMAG2 || e_ident[EI_MAG3] != ELFMAG3)
	{
		dprintf(STDERR_FILENO, "Error: Not an ELF file %s\n", argv[1]);
		close(fd);
		exit(98);
	}

	printf("ELF Header:\n");
	print_magic(e_ident);
	print_class(e_ident);
	print_data(e_ident);
	print_version(e_ident);
	print_osabi(e_ident);
	print_abiversion(e_ident);

	lseek(fd, 0, SEEK_SET);
	if (e_ident[EI_CLASS] == ELFCLASS32)
		read_elf32(fd, e_ident);
	else
		read_elf64(fd, e_ident);

	close(fd);
	return (0);
}

