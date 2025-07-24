#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

int
main(int argc, char *argv[])
{
    int fileCount = -1;
    int entryIndex = 0, nameOffset = 0, charIndex = 0;
    char *deletedFileNames = malloc(64 * (sizeof(char) * (DIRSIZ + 1)));

    if (argc == 1)
        fileCount = lsdel(".", deletedFileNames);
    else if (argc == 2)
        fileCount = lsdel(argv[1], deletedFileNames);

    if (fileCount < 0) {
        printf("The specified path is not valid.\n");
    } else if (fileCount == 0) {
        printf("There are no deleted files in the specified directory.\n");
    } else {
        for (; entryIndex < fileCount; nameOffset = (++entryIndex) * (DIRSIZ + 1), charIndex = 0, printf("\n")) {
            while (deletedFileNames[nameOffset + charIndex] != 0) {
                printf("%c", deletedFileNames[nameOffset + charIndex]);
                charIndex++;
            }
        }
    }

    free(deletedFileNames);
    exit();
}
