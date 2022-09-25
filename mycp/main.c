#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define BUFFER_SIZE 200
int main(int argc,char *argv[])
{
	if(argc == 1)
	{
		printf("mycp: missing file operand\n");
		printf("Try 'mycp --help' for more information.\n\n");
	}
	else if(argc == 2)
	{
		if(strcmp(argv[1],"--help") == 0)
		{
			printf("usage:  mycp... SOURCE... DEST\n");
			printf("Copy SOURCE to DEST.\n\n");
		}
		else
		{
			printf("mycp: missing destination file operand after '%s'\n",argv[1]);
			printf("Try 'mycp --help' for more information.\n\n");
		}
	}
	else if (argc > 3)
	{
		printf("mycp: too many arguments\n");
		printf("Try 'mycp --help' for more information.\n\n");
	}
	else
	{
		if(strcmp(argv[1],argv[2]) == 0)
		{
			printf("cp: '%s' and '%s' are the same file\n",argv[1],argv[2]);
		}
		else
		{
			int source = open(argv[1], O_RDONLY);
			if(source == -1)
			{
				printf("mycp: cannot stat '%s': No such file or directory\n",argv[1]);
			}
			else
			{
				int dest = open(argv[2], O_WRONLY|O_CREAT, 0644);
				if(dest == -1)
				{
					printf("cp: cannot create regular file '%s': No such file or directory\n",argv[2]);
				}
				else
				{
					char buffer[BUFFER_SIZE]={0};
					unsigned int count = 0;
					while ((count = read(source,buffer,BUFFER_SIZE)) != 0)
					{
						if (count == -1)
						{
							printf("unable to read from '%s'\n",argv[1]);
						}
						else
						{
							if(write(dest,buffer,count) == -1)
							{
								printf("unable to write to '%s'\n",argv[2]);
							}
						}
					}
					close(dest);
					close(source);
				}
			}
		}
	}
	return 0;
}
