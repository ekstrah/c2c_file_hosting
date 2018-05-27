#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
typedef struct pack
{
	char id[30];
	char msg[200];
}pack;
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf, pack* sending);

int main(int argc, char *argv[])
{
	int sock;
	char message[BUF_SIZE];
	int str_len;
	struct sockaddr_in serv_adr;
	pack sending;
	socklen_t clnt_adr_sz;
	pid_t pid;

	if(argc!=3)
	{
		printf("Usage : %s <IP> <port>\n",argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock==-1) error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error");
	else
		puts("Connected...");

	printf("Type your ID> ");
	scanf("%s ", sending.id);
	//fgets(sending.id, 30, stdin);

	pid = fork();
	if (pid == 0) write_routine(sock, message, &sending);
	else read_routine(sock, message);

	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}

void read_routine(int sock, char *buf)
{
	pack *receive;
	while (1)
	{
		int str_len = read(sock, buf, sizeof(pack));
		if (str_len == 0) return;
		buf[str_len] = 0;
		receive = (pack*)buf;
		printf("%s > %s", receive->id , receive->msg);
	}
}

void write_routine(int sock, char *buf, pack* sending)
{
	while (1)
	{
		fgets(sending->msg, 200, stdin);
		if (!strcmp(sending->msg, "q\n") || !strcmp(sending->msg, "Q\n"))
		{
			shutdown(sock, SHUT_WR);
			return;
		}
		write(sock, (char*)sending, sizeof(pack));
	}
}

