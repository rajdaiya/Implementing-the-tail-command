#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buffer[512];

void tail(int fd, char *name, int x)
{
int i, n, c, start, count,dummyptr;
c=0;
n=0;
count=0;
dummyptr = open ("dummyfile", O_CREATE | O_RDWR);
while((n = read(fd, buffer, sizeof(buffer))) > 0)              //while will run until n is negative
{

write (dummyptr, buffer, sizeof(buffer));                 //creating a copy of the file
   for(i=0;i<=n;i++)
        {
                if(buffer[i]=='\n')
                c++;                        //counting the number of lines
        }
}
start=c-x-1;
close (dummyptr);
dummyptr = open ("dummyfile", 0);                   //opening a new copy of the file to reset n

while((n = read(dummyptr, buffer, sizeof(buffer))) > 0)
{
    for (i = 0; i<n; i++)
    {
      if (count >= start && count<c)
        printf(1,"%c",buffer[i]);
      if(buffer[i] == '\n')
        count++;


      }
}

close (dummyptr);
unlink("dummyfile");
exit();
}


int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    tail(0, "",9);
    exit();
  }
// int len=sizeof(argv[1]);


//when no: of lines is not defined
else if(argc==2)
{

  for(i = 1; i < argc; i++)
    {
      if((fd = open(argv[i], 0)) < 0){
        printf(1, "tail: cannot open %s\n", argv[i]);
        exit();
      }

      tail(fd, argv[i],9);
      close(fd);
    }
}

//when no of lines is defined
else if(argc==3)
{
char c[512];
strcpy(c,argv[1]);
char *num_str = c;
num_str=num_str+1;
int x= atoi(num_str);

  for(i = 2; i < argc; i++)
  {
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "tail: cannot open %s\n", argv[i]);
      exit();
    }
    tail(fd, argv[i],x-1);
    close(fd);
  }
}


else if(argc>3 && argv[1][0]=='-')
{char c[512];
for(i=1;i<strlen(argv[1]);i++)
{
c[i-1]=argv[1][i];
}
int x=atoi(c);

for(i = 3; i < argc; i++)
  {
    if((fd = open(argv[i], 0)) < 0)
        {
      printf(1, "tail: cannot open %s\n", argv[i]);
      exit();
    }
        tail(fd, argv[i],x-1);
    close(fd);
}
}

else
{
  printf(1,"tail: syntax error");
}
  exit();


}
