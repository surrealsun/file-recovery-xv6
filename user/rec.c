#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
	int result = 1;

	if (argc == 1)
		printf("No parameter provided on the command line.\n");
	else if (argc == 2)
		result = rec(argv[1]);
	else
		printf("Usage: rec <path>\n");

	switch (result)
	{
	case 0:
		printf("Recovery successful.\n");
		break;

	case -1:
		printf("The parent directory of the specified file is not valid.\n");
		break;

	case -2:
		printf("There is no deleted file with the specified name.\n");
		break;

	case -3:
		printf("The inode of the file has been reused for something else.\n");
		break;

	case -4:
		printf("Some block of the file has been reused for something else.\n");
		break;

	default:
		break;
	}

	exit();
}
