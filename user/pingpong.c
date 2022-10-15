#include "kernel/types.h" 
#include "user/user.h"
int main() {

int p1[2];
int p2[2];
pipe(p1);
pipe(p2);

int pid = fork();

// read from p1[0] p2[0]
// write from p1[1] p2[1]

// in the child process
  if(pid == 0) {
    close(p1[1]);
    close(p2[0]);
// the child read from p10, write to p21;

    char ch_read; 

    if(read(p1[0], &ch_read, 1)!=0) {

      printf("%d: received ping\n", getpid());
      write(p2[1], &ch_read, 1); 
      exit(0);

    };  
  
  }else {

// in the parent process  
    close(p2[1]);
    close(p1[0]);

    char towrite = 'a';
    write(p1[1], &towrite, 1); 
    if(read(p2[0], &towrite, 1) != 0) {
      printf("%d: received pong\n", getpid());
    } 
  
  }



return 0;



}






