#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"


void
writerr(char *name, int n)
{
	char buf[512];
	int fd; // file descriptor 
	struct stat st;
	
	// The second argument indicates the mode (read, write, read and write, or create);
// the path can also be a directory, and in that case, for reading we'll use the dirent structure (de)
	if((fd = open(name, 0x200)) < 0){	// we create it (0x200)

		printf("writer: cannot create\n");
		return;
	}
	if((fd = open(name, 0x002)) < 0){ 	// we open it for reading and writing (0x002);
		printf("writer: cannot open\n");
		return;
	}

	if(fstat(fd, &st) < 0){			// fstat reads the inode from the file descriptor and stores the attributes in st (reads everything except the addr array)
		printf("writer: cannot stat\n");
		close(fd);
		return;
	}
	char c='a';
	int i,k=0;
	for(i=0 ; i<n ; ++i,++k){
		if(k==512){ 			// WE WRITE ONE BLOCK TO THE FILE; EVERY BYTE IN THE BLOCK IS THE SAME
			if(write(fd,buf,k) != k)
				printf("writer: write");
			k = 0;
			if(c=='z') c='a';
			else ++c;
		}		
		buf[k]=c;
	}
	
	if(k>0 && (write(fd,buf,k) != k))
		printf("writer: write");
	
	close(fd);
}

int
main(int argc, char *argv[])
{	
	int i;
	if(argc == 3){
		i = atoi(argv[2]);
		writerr(argv[1],i); // LIMIT THE SIZE OF THE SECOND ARGUMENT
	}
	
	exit();
}
