#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc,char **argv[]){
mqd_t queue;//variable to carry the id of the queue
struct mq_attr attrs; //variable to attribute of the queue
char *msg_ptr; //message pointer
ssize_t recvd; //received message size
size_t i;

if(argc<2){
fprintf(stderr,"%s <queuename>",argv[0]);
return 1;
}

//opening the queue for receiving message 
//mq_open parameters=>queue name,flags,attributes
queue=mq_open(argv[1],O_RDONLY|O_CREAT,S_IRUSR|S_IWUSR,NULL); 

if(queue==(mqd_t)-1){
perror("mq_open");
return 1;
}

//get the default message attribute 
if(mq_getattr(queue,&attrs)==-1){
perror("mq_getattr");
mq_close(queue);
return 1;
}

//some other attribute 
//mq_maxmsg=>maximum number of messages that can be stored in the queue
//mq_curmsgs=>number of messages in the queue
//mq_msgsize=>maximum size of each message in the given queue


//creating a space for the buffer to hold the message
msg_ptr=calloc(1,attrs.mq_msgsize);
if(msg_ptr==NULL){
perror(stderr,"calloc for msg_ptr");
mq_close(queue);
return 1;
}

//receive the queue with mq_receive
//mq_receive parameters=> queue name,msg_ptr,message size,priority
recvd=mq_receive(queue,msg_ptr,attrs.mq_msgsize,NULL);
if(recvd==-1){
perror("mq_receive");
return 1;
}

printf("Message : ");
for(i=0;i<(size_t)recvd;i++){

//writing the receiving message to the screen by navigating through
//the pointer address	
putchar(msg_ptr[i]);
pritf("\n");
}
return 0;
}
