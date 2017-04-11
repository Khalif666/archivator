#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
  pid_t pid;

  int rv;
  char proc[100];
while(1) {
  printf("Please, enter the name of the process:\n");
  scanf("%s",proc);
  if (strcmp(proc,"break")==0)
      exit(0);
  switch(pid=fork()) {
  case -1:
          perror("fork"); /* произошла ошибка */
          exit(1); /*выход из родительского процесса*/
  case 0:
          printf(" CHILD: This is child process!\n");
          printf(" CHILD: My PID is-- %d\n", getpid());
          printf(" CHILD: My parent PID -- %d\n",
              getppid());
          printf(" CHILD: My process was changed\n");
          execlp(proc,proc,0);
          printf(" CHILD: Enter the return code:");
          scanf(" %d");
          printf(" CHILD: Exit!\n");
          exit(rv);
  default:
          printf("PARENT: This is parent process!\n");
          printf("PARENT: My PID -- %d\n", getpid());
          printf("PARENT: My child PID %d\n",pid);
          printf("PARENT: I'm waiting for the completion of the child process: exit()...\n");
          wait();
          printf("PARENT: WEXITSTATUS:%d\n",
                   WEXITSTATUS(rv));
          printf("PARENT: EXIT!\n");
  }
}
