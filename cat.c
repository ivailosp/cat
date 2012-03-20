#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE 256

int cat_read(int fd)
{
	char tmp_buff[BUFF_SIZE];
	ssize_t readed;
	while((readed = read(fd, tmp_buff, sizeof(tmp_buff))) > 0){
		write(STDOUT_FILENO, tmp_buff, readed);
	}
    return readed?1:0;
}

int cat_params_read(int argc, char* argv[])
{
    int i;
	int file_fd;    
    int ret = 0;

	for(i = 1; i < argc; i++){
		if(strcmp(argv[i], "-")==0){
			file_fd = dup(STDIN_FILENO);
		}else{
		    file_fd = open(argv[i], O_RDONLY);
        }
	    if(file_fd < 0){
		    fprintf(stderr, "%s: %s: %s\n", argv[0], argv[i], strerror(errno));
            ret = 1;
		    continue;
	    }
        cat_read(file_fd);
		close(file_fd);
	}

    return ret;
}

int main(int argc, char* argv[])
{
	if(argc > 1){
		return cat_params_read(argc, argv);
	}else{
		return cat_read(STDIN_FILENO);
	}
}

