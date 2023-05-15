#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() {
    int pid1, pid2, pid3;
    pid1 = vfork();
    char command1[100];
    char results1[10][1024];
    if (pid1 == 0) {
        for(int i=1;i<30;i++){
            snprintf(command1, sizeof(command1), "strings pictures/cat1/pic%d.png | grep ubuntu > output1.txt", i);
	    system(command1);
   	    FILE* fp1 = fopen("output1.txt", "r");
   	    char buffer1[1024];
   	    fgets(buffer1, sizeof(buffer1), fp1);
   	  //  strcpy(results1[i], buffer1);
   	    printf("%s\n", buffer1);
   	    fclose(fp1);
            remove("output1.txt");
	}
      exit(0);
    }
    pid2 = vfork();
    if (pid2 == 0) {
      exit(0);
    }
    pid3 = vfork();
    if (pid3 == 0) {
      exit(0);
    }
    else{
      return 0;
    }
}