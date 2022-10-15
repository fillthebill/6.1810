#include "kernel/types.h"

#include "user/user.h"




int main(int argc, char* argv[]) {

  if(argc != 2) {
    printf("num of input arguments error!! \n");
    exit(1);
  }

  int n = atoi(argv[1]);
//  printf("sleep for %d seconds\n", n); 
  sleep(n);

  exit(0);
}
