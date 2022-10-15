#include "kernel/types.h"
#include "user/user.h"

//int i = 0;
//int r = 0; int w = 0; int p1[2];
//int p2[2];
//
//void inc_fork_rwcw() {
//
//// invariance: at the start of function call, 
//// all four p[] of the 2 pipes remained open. 
//
//  i++;   //decide where to read and write based on the oddness of i
//
//  if(i%2 == 0) {
//
//    r = p2[0];
//    w = p1[1];
//  } else {
//
//    r = p1[0];
//    w = p2[1];
//  } 
//
//  // no need to fork, if the first byte we read is 35
//
//  int first = 0;
//  read(r, &first, 1); 
//  printf("prime %d\n", first);
//
//  if(first == 5) {
//    exit(0);
//  }else {
//
//// still need to create new child process 
//    
//    int pid = fork();
//  
//    if(pid == 0){
//      inc_fork_rwcw();
//  
//    }else {
//
//// close unuseful pipe ports;
//
//      if(i%2 == 0) {
//        close(p2[1]);
//        close(p1[0]);
//      } else {
//  
//        close(p2[0]);
//        close(p1[1]);
//      }
//
//         
// // read write 
//
//      int t = 0; 
//      while(read(r, &t, 1)!=0) {
//         if((t % first) != 0) {
//           printf("about to write %d \n, first is %d", t, first);
//           write(w, &t, 1);
//         }
//      }  
//      close(r); 
//      close(w); 
//      int child_exit = 0;
//      wait(&child_exit);
//      exit(0);
//    }
//// end of work of parent process.
//
//  } 
//
//
//}
//
//
//int main() {
//
//  
//  pipe(p1);
//  pipe(p2);
//  
//  int pid = fork();
//   
//  if(pid == 0) {
//    inc_fork_rwcw(); 
//  }else {
//    close(p1[0]); 
//    close(p2[0]);
//    close(p2[1]);
//    int t = 0; 
//    for(t = 2; t <= 5;t++) {
//      write(p1[1], &t, 1);
//    }
//    close(p1[1]);  
//  }
// 
//  int child_exit = 0;
//
//  wait(&child_exit);
//
//return 0;
//
//}

void read_process_write(int r_from_parent) {
// read from parent;
// if already 35, do not do what follows, just printf and exit. 

 int first = 0;
 read(r_from_parent, &first , 1);
 printf("prime %d\n", first);

 int second = 0;
 if(read(r_from_parent, &second, 1) == 0) {
 // then no more to process, no need to create child 
 // just exit();
printf("the last number, pid is %d \n", getpid());
  exit(0);

  }
// create pipe and fork;
  int p[2];
  pipe(p);
  int pid = fork();

// do similar studff in the child process

  if(pid == 0) {
    close(p[1]);
    read_process_write(p[0]);
  }else {
    
  close(p[0]); 

      if(second % first != 0) 
      write(p[1], &second, 1);

    int t = 0;
    while( read(r_from_parent, &t, 1) != 0 ) {
      if(t % first != 0)
      write(p[1], &t, 1);
    }
    close(r_from_parent);
    close(p[1]);
    wait(&t);
    exit(0);
  }

// in the parent process, write to the child and wait.
}

int main() {

  int p[2];
  pipe(p);

  int pid = fork();

  if(pid == 0) {// child process
   close(p[1]);
    read_process_write(p[0]); 

  }else {
    // after fork, we could close. 

    close(p[0]);
    int i = 2; 
    while(i <= 35) {

      write(p[1],&i, 1);
      i++;  
    }
    close(p[1]);
   wait(&i);
exit(0);
  }

return 0;

} 




