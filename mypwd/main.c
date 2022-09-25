#include <stdio.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
    char *pathName = NULL;
    char name[200] = {0};
    pathName = getcwd(name,200);
    if (pathName)
    {
        printf("%s\n",pathName);
    }
    else
    {
        printf("error...\n");
    }
    return 0;
}
