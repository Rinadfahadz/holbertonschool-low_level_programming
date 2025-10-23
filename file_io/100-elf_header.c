#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

void print_magic(unsigned char *e_ident)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%2.2x%c", e_ident[i], i == EI_NIDENT - 1 ? '\n' : ' ');
}

void print_class(unsigned char *e_ident)
{
	printf("  Class:                             ");
	switch (e_ident[EI_CLASS])
	{
		case ELFCLASS32: printf("ELF32\n"); break;
		case ELFCLASS64: printf("ELF64\n"); break;
		default: printf("<unknown: %x>\n", e_ident[EI_CLASS]); break;
	}
}

void print_data(unsigned char *e_ident)
{
	printf("  Data:                              ");
	switch (e_ident[EI_DATA])
	{
		case ELFDATA2LSB: printf("2's complement, little endian\n"); break;
		case ELFDATA2MSB: printf("2's complement, big endian\n"); break;
		default: printf("<unknown: %x>\n", e_ident[EI_DATA]); break;
	}
}

void print_version(unsigned char *e_ident)
{
	printf("  Version:                           %d", e_ident[EI_VERSION]);
	if (e_ident[EI_VERSION] == EV_CURRENT)
		printf(" (current)");
	printf("\n");
}

void print_osabi(unsigned char *e_ident)
{
	printf("  OS/ABI:                            ");
	switch (e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
		case ELFOSABI_HPUX: printf("UNIX - HP-UX\n"); break;
		case ELFOSABI_NETBSD: printf("UNIX - NetBSD\n"); break;
		case ELFOSABI_LINUX: printf("UNIX - Linux\n"); break;
		case ELFOSABI_SOLARIS: printf("UNIX - Solaris\n"); break;
		case ELFOSABI_IRIX: printf("UNIX - IRIX\n"); break;
		case ELFOSABI_FREEBSD: printf("UNIX - FreeBSD\n"); break;
		case ELFOSABI_TRU64: printf("UNIX - TRU64\n"); break;
		case ELFOSABI_ARM: printf("ARM\n"); break;
		case ELFOSABI_STANDALONE: printf("Standalone App\n"); break;
		default: printf("<unknown: %x>\n", e_ident[EI_OSABI]); break;
	}
}

void print_abiversion(unsigned char *e_ident)
{
	printf("  ABI Version:                       %d\n", e_ident[EI_ABIVERSION]);
}

void print_type(Elf64_Half e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
		e_type = (e_type >> 8) | (e_type << 8);

	printf("  Type:                              ");
	switch (e_type)
	{
		case ET_NONE: printf("NONE (None)\n"); break;
		case ET_REL: printf("REL (Relocatable file)\n"); break;
		case ET_EXEC: printf("EXEC (Executable file)\n"); break;
		case ET_DYN: printf("DYN (Shared object file)\n"); break;
		case ET_CORE: printf("CORE (Core file)\n"); break;
		default: printf("<unknown: %x>\n", e_type); break;
	}
}

void print_entry(unsigned long e_entry, unsigned char *e_ident)
{
	printf("  Entry point address:               ");
	if (e_ident[EI_CLASS] == ELFCLASS32)
	{
		if (e_ident[EI_DATA] == ELFDATA2MSB)
			e_entry = ((e_entry & 0xFF) << 24) |
			          ((e_entry & 0xFF00) << 8) |
			          ((e_entry & 0xFF0000) >> 8) |
			          ((e_entry & 0xFF000000) >> 24);
		printf("0x%x\n", (unsigned int)e_entry);
	}
	else
	{
		if (e_ident[EI_DATA] == ELFDATA2MSB)
			e_entry = __builtin_bswap64(e_entry);
		printf("0x%lx\n", e_entry);
	}
}

int main(int argc, char **argv)
{
	int fd;
	ssize_t r;
	Elf64_Ehdr ehdr;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: %s elf_filename\n", argv[0]);
		exit(98);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Cannot open file %s\n", argv[1]);
		exit(98);
	}

	r = read(fd, &ehdr, sizeof(ehdr));
	if (r < sizeof(Elf64_Ehdr))
	{
		dprintf(STDERR_FILENO, "Error: Cannot read ELF header from %s\n", argv[1]);
		close(fd);
		exit(98);
	}

	if (ehdr.e_ident[EI_MAG0] != ELFMAG0 ||
	    ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
	    ehdr.e_ident[EI_MAG2] != ELFMAG2 ||
	    ehdr.e_ident[EI_MAG3] != ELFMAG3)
	{
		dprintf(STDERR_FILENO, "Error: Not an ELF file %s\n", argv[1]);
		close(fd);
		exit(98);
	}

	printf("ELF Header:\n");
	print_magic(ehdr.e_ident);
	print_class(ehdr.e_ident);
	print_data(ehdr.e_ident);
	print_version(ehdr.e_ident);
	print_osabi(ehdr.e_ident);
	print_abiversion(ehdr.e_ident);
	print_type(ehdr.e_type, ehdr.e_ident);
	print_entry(ehdr.e_entry, ehdr.e_ident);

	close(fd);
	return (0);
}

