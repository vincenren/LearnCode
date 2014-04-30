#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

static int set_fl(int fd, int flags)
{
	int val;

	if ((val = fcntl(fd,F_GETFL,0)) < 0) {
	printf("fcntl F_GETFL error\n");
	return -1;
	}

	val |= flags;

	if (fcntl(fd,F_SETFL,val) < 0) {
	printf("fcntl F_SETFL error\n");
	return -1;
	}

	return 0;
}

void timeout()
{
	printf("time out\n");
	exit(0);
}

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	struct hostent *host;
	char *msg = strdup("GET / HTTP/1.1\r\nHOST: ");
	char rbuf[32], res_header[1024];
	char *host_ip, *ptr, *pos;
	int ntowrite, nwrite, nread, nread_res_header = 0, content_length, nread_content_length = 0;

	signal(SIGALRM, timeout);

	if (argc < 2) {
	printf("请输入域名参数\n");
	exit(0);
	} else if (argc > 2) {
	printf("输入的参数过多\n");
	exit(0);
	}

	msg = realloc(msg, strlen(msg) + strlen(argv[1]) + sizeof("\r\n\r\n"));
	sprintf(msg + strlen(msg), "%s\r\n\r\n", argv[1]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
	perror("socket");
	exit(0);
	}

host = gethostbyname(argv[1]);
if (host == NULL) {
printf("无法获取此域名IP\n");
goto END;
}

host_ip = inet_ntoa(*((struct in_addr *)host->h_addr));

bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(80);
inet_pton(AF_INET, host_ip, &servaddr.sin_addr);
if( connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
perror("connect");
exit(0);
}

if (set_fl(sockfd, O_NONBLOCK) < 0) {
printf("set nonblock error");
goto END;
}

ntowrite = strlen(msg);
ptr = msg;
alarm(10);
while (ntowrite > 0) {
nwrite = write(sockfd, ptr, ntowrite);
if (nwrite <= 0) {
perror("write:");
goto END;
}
ptr += nwrite;
ntowrite -= nwrite;
}
alarm(0);

/* read response header */
ptr = res_header;
alarm(10);
while (1) {
errno = 0;
nread = read(sockfd, ptr, sizeof(res_header) - nread_res_header);
if(nread < 0){
if(errno == EAGAIN){
continue;
}
perror("read");
goto END;
}
nread_res_header += nread;
ptr += nread;
if((pos = strstr(res_header, "\r\n\r\n")) != NULL || nread_res_header == sizeof(res_header)){
break;
}
}
alarm(0);

if (!(pos = strstr(res_header, "Content-Length:"))) {
printf("响应报文错误");
goto END;
} else {
pos += 16;
if (!(ptr = strstr(pos, "\r\n"))) {
printf("响应报文错误");
goto END;
}
char buf[10];
snprintf(buf, (ptr - pos) > 10 ? 10 : (ptr - pos) + 1, "%s", pos);
content_length = atoi(buf);
}

write(STDOUT_FILENO, res_header, nread_res_header);
if ((pos = strstr(ptr, "\r\n\r\n"))) {
pos += 4;
nread_content_length = nread_res_header - (pos - res_header);
} else {
/* 此处有bug, 如果响应头很长, 没有读到\r\n\r\n, 但是, 先这样吧 :D */
goto END;
}

alarm(10);
while (1) {
errno = 0;
memset(rbuf, 0, sizeof(rbuf));
nread = read(sockfd, rbuf, sizeof(rbuf));
if (nread < 0) {
if (errno == EAGAIN) {
continue;
}
perror("read");
goto END;
}
write(STDOUT_FILENO, rbuf, nread);
nread_content_length += nread;
if (nread_content_length >= content_length){
break;
}
}
alarm(0);

END:
close(sockfd);
free(msg);
return 0;
}
