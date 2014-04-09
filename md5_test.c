#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>
#include <openssl/md5.h>

int main(int argc, char* argv[])
{
	MD5_CTX hash_ctx;
	char buf[16];
	int i=0;

	if ( 3 != argc )
	{
		fprintf(stdout,"this tool must be used like this: \n");
		fprintf(stdout,"%s [fs]  yourfile(yourstring)\n", argv[0]);
		exit(-1);
		
	}

	if (argv[1][1] == 'f')
	{
		int fd = open(argv[2],O_RDONLY);
		if (-1 == fd)
		{
			perror("can't open file");
			exit(-1);
		}

		struct stat s_stat;
		if( -1 == fstat(fd, &s_stat) )
		{
			perror("can't get file size");
			exit(-1);
		}
		void *filebuf = malloc(s_stat.st_size);
		read(fd, filebuf, s_stat.st_size);

		MD5_Init(&hash_ctx);
		MD5_Update(&hash_ctx, filebuf, s_stat.st_size);
		MD5_Final(buf, &hash_ctx);

		free(filebuf);
		filebuf = NULL;
	}
	else if (argv[1][1] == 's')
	{
		MD5_Init(&hash_ctx);
		MD5_Update(&hash_ctx, argv[2], strlen(argv[2]));
		MD5_Final(buf, &hash_ctx);
	}
	else
	{
		fprintf(stdout,"this tool must be used like this: \n");
		fprintf(stdout,"%s [fs] yourfile(yourstring)\n", argv[0]);
		exit(-1);
	}

	fprintf(stdout,"The MD5 result is:\n");
	for(i=0;i<16;i++)
	{
		fprintf(stdout, "%01x", (buf[i]&0xf0)>>4 );
		fprintf(stdout, "%01x", (buf[i]&0x0f) );
	}
	fprintf(stdout, "\n");

	exit(0);
}
