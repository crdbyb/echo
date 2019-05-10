#ifndef _TASK_
#define _TASK_
 
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/wait.h>
 
char *path = "/home/neko/网络编程/2"; //path
const int BUFFER_SIZE = 4096;
 
class task{
private:
	int connfd;
 
public:
	task(){}
	task(int fd):connfd(fd){}
	~task(){}
 
	void response(char *message, int status){   // error response function, status is the response status code
		char buf[512];
		sprintf(buf, "HTTP/1.1 %d OK\r\nConnection: Close\r\n""content-length:%d\r\n\r\n", status, strlen(message)); //response headers
		sprintf(buf, "%s%s", buf, message);
		write(connfd, buf, strlen(buf));
 
	}
	void response_file(int size, int status){ // request static file response function, size is the file size
		char buf[128];
		sprintf(buf, "HTTP/1.1 %d OK\r\nConnection: Close\r\n""content-length:%d\r\n\r\n", status, size);
		write(connfd, buf, strlen(buf));
	}
 
	void response_get(char *filename); // the Get function
 
	void response_post(char *filename, char *argv); // the Post function
 
	void doit();
};
 
void task::doit(){
	char buffer[BUFFER_SIZE];
	int size;
read:	size = read(connfd, buffer, BUFFER_SIZE - 1); //Read the Http request message
	if(size > 0){
		char method[5];
		char filename[50];
		int i, j;
		i = j = 0;
		while(buffer[j] != ' ' && buffer[j] != '\0'){  //Get request method
			method[i++] = buffer[j++];
		}
		++j;
		method[i] = '\0';
		i = 0;
		while(buffer[j] != ' ' && buffer[j] != '\0'){  // get the request file
			filename[i++] = buffer[j++];
		}
		filename[i] = '\0';
 
		if(strcasecmp(method, "GET") == 0){   //get method
			response_get(filename);
		}
		else if(strcasecmp(method, "POST") == 0){  //post method
			char argvs[100];
			memset(argvs, 0, sizeof(argvs));
			int k = 0;
			char *ch = NULL;
			++j;
			while((ch = strstr(argvs, "Content-Length")) == NULL){  // find the content-length line in the request header
				k = 0;
				memset(argvs, 0, sizeof(argvs));
				while(buffer[j] != '\r' && buffer[j] != '\0'){
					argvs[k++] = buffer[j++];
				}
				++j;
			}
			int length;
			char *str = strchr(argvs, ':');  // get the length of the POST request data
			++str;
			sscanf(str, "%d", &length);
			j = strlen(buffer) - length;     // get the request data from the end of the request message
			k = 0;
			memset(argvs, 0, sizeof(argvs));
			while(buffer[j] != '\r' && buffer[j] != '\0')
				argvs[k++] = buffer[j++];
 
			argvs[k] = '\0';
			response_post(filename, argvs);   // POST method
		}
		else{    // unknown methods
			char message[512];
			sprintf(message, "<html><title>Error</title>");
			sprintf(message, "%s<body>\r\n", message);
			sprintf(message, "%s 501\r\n", message);
			sprintf(message, "%s <p>%s: Httpd does not implement this method", message, method);
			sprintf(message, "%s<hr><h3>Web Server<h3></body>", message);
			response(message, 501);
		}
 
 
	}
	else if(size < 0)   // read failed, re-read
		goto read;
 
	sleep(3);    //wait for client close, avoid TIME_WAIT
	close(connfd);
}
 
void task::response_get(char *filename){
	char file[100];
	strcpy(file, path);
 
	int i = 0;
	bool is_dynamic = false;
	char argv[20];
	while(filename[i] != '?' && filename[i] != '\0')
		    ++i;
	if(filename[i] == '?'){
		int j = i;
		++i;
		int k = 0;
		while(filename[i] != '\0')   // split parameter and filename
			argv[k++] = filename[i++];
		argv[k] = '\0';
		filename[j] = '\0';
		is_dynamic = true;
	}
 
	if(strcmp(filename, "/") == 0)
		strcat(file, "/index.html");
	else
		strcat(file, filename);
 
 
	struct stat filestat;
	int ret = stat(file, &filestat);
 
	if(ret < 0 || S_ISDIR(filestat.st_mode)){   //file doesn't exits
		char message[512];
		sprintf(message, "<html><title>Error</title>");
		sprintf(message, "%s<body>\r\n", message);
		sprintf(message, "%s 404\r\n", message);
		sprintf(message, "%s <p>GET: Can't find the file", message);
		sprintf(message, "%s<hr><h3>Web Server<h3></body>", message);
		response(message, 404);
		return;
	}
 
	if(is_dynamic){
		if(fork() == 0) { /*Create a child process execute the corresponding subroutine, multithreaded, create a child process,Only the current thread will be copied, and the other threads will "disappear", which is exactly what we want.And after fork, execute execl, and the program is reloaded by the process*/
			dup2(connfd, STDOUT_FILENO);  //Redirect the standard output to the sockfd and write the subroutine output to the client.
	    		execl(file, argv);  //Execution subroutine
		}
		wait(NULL);
	}
	else{
		int filefd = open(file, O_RDONLY);
		response_file(filestat.st_size, 200);   //Use "zero copy" to send files
		sendfile(connfd, filefd, 0, filestat.st_size);
	}
}
 
 
void task::response_post(char *filename, char *argvs){
	char file[100];
	strcpy(file, path);
 
	strcat(file, filename);
 
	struct stat filestat;
	int ret = stat(file, &filestat);
	printf("%s\n", file);
	if(ret < 0 || S_ISDIR(filestat.st_mode)){   //file doesn't exits
		char message[512];
		sprintf(message, "<html><title>Error</title>");
		sprintf(message, "%s<body>\r\n", message);
		sprintf(message, "%s 404\r\n", message);
		sprintf(message, "%s <p>GET: Can't find the file", message);
		sprintf(message, "%s<hr><h3>Web Server<h3></body>", message);
		response(message, 404);
		return;
	}
 
	char argv[20];
	int a, b;
	ret = sscanf(argvs, "a=%d&b=%d", &a, &b);   //Determine whether the parameters are correct
	if(ret < 0 || ret != 2){
		char message[512];
		sprintf(message, "<html><title>Error</title>");
		sprintf(message, "%s<body>\r\n", message);
		sprintf(message, "%s 404\r\n", message);
		sprintf(message, "%s <p>GET: Parameter error", message);
		sprintf(message, "%s<hr><h3>Web Server<h3></body>", message);
		response(message, 404);
		return;
	}
	sprintf(argv, "%d&%d", a, b);
	if(fork() == 0) {
		dup2(connfd, STDOUT_FILENO);  
		execl(file, argv); 
	}
	wait(NULL);
}
 
 
 
#endif