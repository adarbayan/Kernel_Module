#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#define READ_END 0
#define WRITE_END 1




int main(void) {
	struct timeval current_time;
	time_t t;
	
	pid_t pid;
	pid_t pid_2;
	int fd[2];
    pipe(fd);
	int fd_2[2];
	pipe(fd_2);
	int fd_3[2];
	pipe(fd_3);
	int fd_4[2];
	pipe(fd_4);
	int val = 0;
    pid_t child;
    pid_t grandchild;
    char write_msg[64];
    char read_msg[64];
    pid = fork();
	
    if(pid < 0){
        fprintf(stderr, "Fork Failed!");
        return 1;
    }
    if(pid > 0) {
        close(fd[READ_END]);
        gettimeofday(&current_time, NULL);
		val = current_time.tv_sec;
        write(fd[WRITE_END], &val, sizeof(val));
        close(fd[WRITE_END]);
        close(fd_2[WRITE_END]);
        read(fd_2[READ_END], &val, sizeof(val));
        printf("B -> A: %d(in miliseconds)\n", val);
        close(fd_2[READ_END]);
        kill(pid, SIGKILL);
    } else {
        close(fd[WRITE_END]);
        gettimeofday(&current_time, NULL);
		val = current_time.tv_sec;
        read(fd[READ_END], &val, sizeof(val));
        printf("A -> B: %d(in miliseconds)\n", val);
        close(fd[READ_END]);
        sleep(3);
        pid_2 = fork();
        if(pid_2 < 0){
            fprintf(stderr, "Fork Failed!");
            return 1;
        }
        if(pid_2 > 0) {
            close(fd_3[READ_END]);
            gettimeofday(&current_time, NULL);
			val = current_time.tv_sec;
            write(fd_3[WRITE_END], &val, sizeof(val));
            close(fd_3[WRITE_END]);
            close(fd_4[WRITE_END]);
            read(fd_4[READ_END], &val, sizeof(val));
            printf("C -> B: %d(in miliseconds)\n", val);
            close(fd_4[READ_END]);
            sleep(3);      
            close(fd_2[READ_END]);
            gettimeofday(&current_time, NULL);
			val = current_time.tv_sec;
            write(fd_2[WRITE_END], &val, sizeof(val));
            close(fd_2[WRITE_END]);          
            kill(pid_2, SIGKILL);
        } else {
        
            close(fd_3[WRITE_END]);
            read(fd_3[READ_END], &val, sizeof(val));
            printf("B -> C: %d(in miliseconds)\n", val);
            close(fd_3[READ_END]);    
            sleep(3);
            close(fd_4[READ_END]);
            write(fd_4[WRITE_END], &val, sizeof(val));
            close(fd_4[WRITE_END]);
        }      
        exit(0);
    }
    return 0;
}
