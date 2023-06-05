Parallel processing#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() {
    int pid1, pid2, pid3;
    char command1[100];
    char command2[100];
    char command3[100];
    char results1[10][1024];
    char results2[10][1024];
    char results3[10][1024];
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    pid1 = vfork();
    if (pid1 == 0) {
        char buffer1[1024];
        for(int i=1;i<1001;i++){
            snprintf(command1, sizeof(command1), "strings pictures/cat1/pic%d.png | grep ubuntu > output1.txt", i);
            system(command1);
            FILE* fp1 = fopen("output1.txt", "r");
            fgets(buffer1, sizeof(buffer1), fp1);
            fclose(fp1);
            remove("output1.txt");
            if (strlen(buffer1) > 5){
                if (buffer1[7] == 49){
                  strcpy(results1[counter1], buffer1);
                  counter1 += 1;
                }
                else if (buffer1[7] == 50){
                  strcpy(results2[counter2], buffer1);
                  counter2 += 1;
                }
                else{
                  strcpy(results3[counter3], buffer1);
                  counter3 += 1;
                }
                
                memset(&buffer1[0], 0, sizeof(buffer1));
            }
	}
        exit(0);
    }
    pid2 = vfork();
    if (pid2 == 0) {
        char buffer2[1024];
        for(int j=1;j<1001;j++){
            snprintf(command2, sizeof(command2), "strings pictures/cat2/pic%d.png | grep ubuntu > output2.txt", j);
            system(command2);
            FILE* fp2 = fopen("output2.txt", "r");
            fgets(buffer2, sizeof(buffer2), fp2);
            fclose(fp2);
            remove("output2.txt");
            if (strlen(buffer2) > 5){
                if (buffer2[7] == 49){
                  strcpy(results1[counter1], buffer2);
                  counter1 += 1;
                }
                else if (buffer2[7] == 50){
                  strcpy(results2[counter2], buffer2);
                  counter2 += 1;
                }
                else{
                  strcpy(results3[counter3], buffer2);
                  counter3 += 1;
                }
                
                memset(&buffer2[0], 0, sizeof(buffer2));
            }
	}
        exit(0);
    }
    pid3 = vfork();
    if (pid3 == 0) {
        char buffer3[1024];
        for(int k=1;k<1001;k++){
            snprintf(command3, sizeof(command3), "strings pictures/cat3/pic%d.png | grep ubuntu > output3.txt", k);
            system(command3);
            FILE* fp3 = fopen("output3.txt", "r");
            fgets(buffer3, sizeof(buffer3), fp3);
            fclose(fp3);
            remove("output3.txt");
            if (strlen(buffer3) > 5){
                if (buffer3[7] == 49){
                  strcpy(results1[counter1], buffer3);
                  counter1 += 1;
                }
                else if (buffer3[7] == 50){
                  strcpy(results2[counter2], buffer3);
                  counter2 += 1;
                }
                else{
                  strcpy(results3[counter3], buffer3);
                  counter3 += 1;
                }
                
                memset(&buffer3[0], 0, sizeof(buffer3));
            }
	}
        exit(0);
    }
    else{
        int i, j;
        char temp[1024];
        for(i=0;i<10;i++){
          for(j=i+1;j<10;j++){
              if(strcmp(results1[i],results1[j])>0){
                  strcpy(temp,results1[i]);
                  strcpy(results1[i],results1[j]);
                  strcpy(results1[j],temp);
              }
          }
        }
        
        for(i=0;i<10;i++){
          for(j=i+1;j<10;j++){
              if(strcmp(results2[i],results2[j])>0){
                  strcpy(temp,results2[i]);
                  strcpy(results2[i],results2[j]);
                  strcpy(results2[j],temp);
              }
          }
        }
        for (i = 0; i < counter1; i++)
          if (i != 1)
            printf("%s", results1[i]);
        printf("%s", results1[1]);
        for (i = 0; i < counter2; i++)
          if (i != 1)
            printf("%s", results2[i]);
        printf("%s", results2[1]);
        for (i = 0; i < counter3; i++)
          printf("%s", results3[i]);
        return 0;
    }
}
