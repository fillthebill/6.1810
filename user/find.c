#include "kernel/types.h" 
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find_impl(char *path, char *file_name) {

  int fd;
// dirent,   directory entry....
  struct dirent de;
  struct stat st, tmp_st;
  char buf[512], *p; 

  if( (fd = open(path, 0)) < 0){
     printf("invalid path name! \n");  
     exit(1); 
  }

  if(fstat(fd, &st) < 0) {

     printf("cannot read stat... \n");
     close(fd);
     exit(1);
  } 
//printf("correct path\n");
  switch(st.type) {

    case T_DEVICE: 
       printf("invalid path name, should not be a device \n"); 
       exit(1);
       break;
  
    case T_FILE: 
       printf("invalid path name, should not be a file name \n");
       exit(1); 
       break; 

    case T_DIR:
       strcpy(buf, path);
       p = buf + strlen(buf);
       *p++ = '/';
   
       while( read(fd, &de, sizeof(de)) == sizeof(de) ) {

         if(de.inum == 0)
           continue;
	 if(strcmp(de.name, ".") == 0) 
           continue;
	 if(strcmp(de.name, "..") == 0) 
           continue;
// make up the path name to file_name 
         if(strcmp(de.name, file_name) == 0 ) {
           memmove(p, de.name, DIRSIZ);
           p[DIRSIZ] = 0;
           if(stat(buf, &tmp_st) < 0) {
             printf("find : cannot stat %s, \n", buf);
	     continue;
           }
           //printf("%s %d %d %d \n", buf, tmp_st.type, tmp_st.ino, tmp_st.size);
           printf("%s\n", buf);
           if(tmp_st.type == T_DIR) 
             find_impl(buf, file_name);
         } else {
           memmove(p, de.name, DIRSIZ);
           p[DIRSIZ] = 0;
           if( stat(buf, &tmp_st) < 0) {
             printf("find : cannot stat %s, \n", buf); 
	    continue;
           } 
	//	printf("after stat call...\n ");          
           if(tmp_st.type == T_DIR) {
             find_impl(buf, file_name);
           }


         }
        
        

       }
  }

  close(fd);
}

int main(int args, char* argv[]) {

// argv1, the directory path to start search.
// argv2, the file name to search for.

  if(args < 3) {
    printf("find need at least two arguments \n");
    exit(1);
  }

// get all meta data for the directory argv1, 
// search the file recursively. 
find_impl(argv[1], argv[2]);
return 0;

}


















