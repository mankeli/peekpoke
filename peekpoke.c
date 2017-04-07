#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAP_SIZE 4096UL

extern const char *__progname;

int main(int argc, char *argv[])
{
	int func = 0;
	
	if (!strcmp(__progname, "peek"))
		func = 0;
	else if (!strcmp(__progname, "poke"))
		func = 1;
	else
	{
		printf("no function: %s\n", __progname);
		exit(1);
	}

	long address = strtoul(argv[1], NULL, 0);

	long pageaddr = address & ~(MAP_SIZE - 1);
	long offset = address & (MAP_SIZE - 1);

	int memfd = open("/dev/mem", O_RDWR | O_SYNC);
 	void* page = mmap(0, MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, memfd, pageaddr);

	void* value = page + offset;


	if (func == 0)
	{
		uint32_t arvo = *(uint32_t *)value;
	 	printf("PEEK 0x%lX = 0x%X\n", address, arvo);	
	}
	else if (func == 1)
	{
		uint32_t arvo = strtoul(argv[2], NULL, 0);
		*(uint32_t *)value = arvo;
	 	printf("POKE 0x%lX = 0x%X\n", address, arvo);	
	}

    }
