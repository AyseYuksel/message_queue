#include <fcntl.h>
#include <limits.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc,cha **argv){
	
mqd_t queue; //variable to carry the id of the queue
struct mq_attr attrs; //variable to attribute of queue
size_t msg_len; //variable to message length

//getting the message to be added to the queue from 
//the terminal with argv variable

//argv[0]=> name of file
//argv[1]=>name of queue
//argv[2]=>message

if(argc<3){
fprintf(stderr,"%s <queuename> <message",argv[0]);
return 1;
}


//opening the queue (parameters=>queue name,flags)
queue=mq_open(argv[1],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR,NULL);

if(queue==(mqdt)-1){
perror("mq_open");
return 1;
}

//adding default attribute to queue
if(mq_getattr(queue,&attrs)==-1){
perror("mq_getattr");
mq_close(queue);
return 1;
}

msg_len=strlen(argv[2]);
if(msg_len>LONG_MAX||(long)msg_len>attrs.mq_msgsize){
fprintf(stderr,"Your message is too long for the queue.");
mq_close(queue);
return 1;
}

//sending message queue 
//(mq_send parameters=>queue name,message,message size,priority) 
if(mq_send(queue,argv[2],strlen(argv[2]),0)==-1){
perror("mq_send");
mq_close(queue);
return 1;
}

return 0;
}
