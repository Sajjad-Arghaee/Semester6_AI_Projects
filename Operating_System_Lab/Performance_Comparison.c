#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void * ThreadFunction(void *arguments)
{
  printf("Thread Running\n");
  for(int i=0; i<100000000; i++){
    // do nothing
  }
  return NULL;
}

void my_function(){
  printf("Function Running\n");
  for(int i=0; i<100000000; i++){
    // do nothing
  }
}

int main() {
  pthread_t thread1, thread2;
  printf("Calling Thread\n");
  clock_t seconds_thread_start, seconds_thread_end;
  double cpu_time_used_thread;
  seconds_thread_start = clock();

  pthread_create(&thread1, NULL, ThreadFunction, NULL);
  pthread_create(&thread2, NULL, ThreadFunction, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  
  seconds_thread_end = clock();
  cpu_time_used_thread = ((double) (seconds_thread_end - seconds_thread_start)) / CLOCKS_PER_SEC;
  printf("Time elapsed with threads = %f seconds\n", cpu_time_used_thread);
  
  int pid1, pid2;
  printf("Calling Process\n");
  clock_t seconds_process_start, seconds_process_end;
  double cpu_time_used_process;
  seconds_process_start = clock();
  
  pid1 = vfork();
  if (pid1 == 0) {
    printf("Process Running\n");
    for(int i=0; i<100000000; i++){
      // do nothing
    }
    exit(0);
  }
  pid2 = vfork();
  if (pid2 == 0) {
    printf("Process Running\n");
    for(int i=0; i<100000000; i++){
      // do nothing
    }
    exit(0);
  }
  
  seconds_process_end = clock();
  cpu_time_used_process = ((double) (seconds_process_end - seconds_process_start)) / CLOCKS_PER_SEC;
  printf("Time elapsed with processes = %f seconds\n", cpu_time_used_process);  
  
  printf("Calling Function\n");
  clock_t seconds_function_start, seconds_function_end;
  double cpu_time_used_function;
  seconds_function_start = clock();

  my_function();
  my_function();
  
  seconds_function_end = clock();
  cpu_time_used_function = ((double) (seconds_function_end - seconds_function_start)) / CLOCKS_PER_SEC;
  printf("Time elapsed with function = %f seconds\n", cpu_time_used_function);
  
  return 0;
}
