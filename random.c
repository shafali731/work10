#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int randomizer(){
	int *arr = malloc(8);
  int fd = open("/dev/random", O_RDONLY);
	if(fd<0){
		printf("There was an error printing random number: %s\n", strerror(errno));
	}
	read(fd, arr, 8);
	close(fd);
	return *arr;
}

int main() {
  printf("Filling array with random numbers:\n");
  int *ran_arr = calloc(10,sizeof(int));
  int *check_arr = calloc(10,sizeof(int));

  for (int i = 0; i < 10; i++) {
    ran_arr[i] = randomizer();
    printf("random %d: %d\n", i, ran_arr[i]);
  }
  printf("========================================");

  printf("\nWriting numbers from array to file\n");
  int o = open("foo.txt", O_WRONLY | O_CREAT, S_IRWXU); //gives file owner access
  if(o < 0){
    printf("error in open: %s\n",strerror(errno));
  }
  else {
   printf("Writing numbers to file \n\n");
   write(o, ran_arr, 10 * sizeof(int));
   close(o);
 }

 printf("========================================");

  printf("\nReading numbers from file into array \n\n");
  int fd_check = open("foo.txt", O_RDONLY);
  if(fd_check < 0){
    printf("error in open: %s\n",strerror(errno));
  }
  else {
    printf("Reading numbers from file\n");
  	read(fd_check, check_arr, 10 * sizeof(int));
    close(fd_check);
  }
  printf("Checking random arr\n");
  for(int i = 0; i<10;i++){
    printf("random %d: %d \n",i,check_arr[i]);
  }
  return 0;
}
