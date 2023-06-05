#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char *readCSVCell(int rowIndex, int columnIndex, char *path)
{
    FILE *fp;
    char line[10000];
    char *token;

    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Failed to open file\n");
        return NULL;
    }

    for (int i = 1; i <= rowIndex; i++)
        fgets(line, 10000, fp);

    token = strtok(line, ",");
    for (int i = 1; i < columnIndex; i++)
        token = strtok(NULL, ",");

    fclose(fp);

    return token;
}

int main()
{

    // initializing parameters
    char *path1 = "Ds1_New.csv";
    char *path2 = "Ds2_New.csv";
    char *path3 = "Ds3_New.csv";
    int fd_12[2];
    int fd_23[2];
    int fd_31[2];
    pipe(fd_12);
    pipe(fd_23);
    pipe(fd_31);
    int rowNumber = 1;
    int state_1 = 0;
    int state_2 = 0;
    int state_3 = 0;
    FILE *fptr1;
    fptr1 = fopen("file1.txt", "w");  
    FILE *fptr2;
    fptr2 = fopen("file2.txt", "w"); 
    FILE *fptr3;
    fptr3 = fopen("file3.txt", "w"); 
    char readbuffer1_2[80];
    char readbuffer1_3[80];
    char readbuffer2_1[80];
    char readbuffer2_3[80];
    char readbuffer3_1[80];
    char readbuffer3_3[80];

    pid_t pid1, pid2, pid3;

    // Create the first child process
    pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid1 == 0) {
        // First child process
        // Perform operations specific to the first child process
        while(rowNumber < 10){
            state_1 = 0;
            char *token1 = readCSVCell(rowNumber, 3, path1);
            char *token1_1 = readCSVCell(rowNumber, 1, path1);
            char *token1_2 = readCSVCell(rowNumber, 2, path1);
            strcat(token1_1, token1_2);
            if (strcmp(token1, "Physics")){
                fputs(token1_1, fptr1);
            } else if(strcmp(token1, "Biology")){
                close(fd_12[0]);
                write(fd_12[1], token1_1, (strlen(token1_1)+1));
            } else if(strcmp(token1, "Chemistry")){
                close(fd_31[0]);
                write(fd_31[1], token1_1, (strlen(token1_1)+1));
            }
            sleep(0.1);
            // handle pipeline 1-2
            close(fd_12[1]);
            read(fd_12[0], readbuffer1_2, sizeof(readbuffer1_2));
            if (strlen(readbuffer1_2) > 5){
                fputs(readbuffer1_2, fptr1);
            }
            // handle pipeline 1-3
            close(fd_31[1]);
            read(fd_31[0], readbuffer1_3, sizeof(readbuffer1_3));
            if (strlen(readbuffer1_3) > 5){
                fputs(readbuffer1_3, fptr1);
            }
            while (state_1 == 0){ //  || state_2 == 0 || state_3 == 0
                // waiting for all processes to finish
                // printf("%d\n", state_1);
            }

        rowNumber ++;
        state_1 = 1;
        sleep(0.1);
        // state_2 = 0;
        // state_3 = 0;
        }
        return 0;
    }

    // Create the second child process
    pid2 = fork();

    if (pid2 < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid2 == 0) {
        // Second child process
        // Perform operations specific to the second child process
        return 0;
    }

    // Create the third child process
    pid3 = fork();

    if (pid3 < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid3 == 0) {
        // Third child process
        // Perform operations specific to the third child process
        return 0;
    }

    // Parent process
    printf("Parent process (PID: %d)\n", getpid());
    // Perform operations specific to the parent process

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);
    return 0;
}
