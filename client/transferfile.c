#include "my_header.h"

unsigned long packets_to_send;

unsigned long fsize(FILE **f){
	fseek(*f, 0, SEEK_END);
	unsigned long len = (unsigned long)ftell(*f);
	rewind(*f);
	return len;
}

int copy_size(unsigned long file_size, int send_qtd){
	if(file_size > PACKET_SIZE * send_qtd)
		return PACKET_SIZE;
	else
		return PACKET_SIZE + file_size - (PACKET_SIZE*send_qtd);
}

int hasContent(){
	if(packets_to_send == 0)
		return 0;
	packets_to_send--;
	return 1;
}

unsigned long packets_counter(unsigned long file_size){
	return (file_size/PACKET_SIZE) + 1;
}

char ack(char atual){
	if(atual == '1')
		return '0';
	return '1';
}

int file_transfer(char *file_name){

	int sock, rv, packs_to_expire = 0, on = 1;
	socklen_t addr_len = sizeof(struct sockaddr_in);
	unsigned long file_size, start = 0, size, packets_send = 0;
	char atual_ack = '0';
	struct sockaddr_in my_address, other_address;
	FILE *fd;
	char buffer[BUFSIZE];
	bool enable_send = true;
	ssize_t received;
	fd_set set;
	struct timeval timeout;

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sock == -1)
		kill("Socket error!");

	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
	
	memset((char*)&my_address, 0, addr_len);
	my_address.sin_family = AF_INET;
	my_address.sin_port = htons(DEFAULT_PORT);
	my_address.sin_addr.s_addr = htonl(INADDR_ANY);

	other_address.sin_family = AF_INET;
	other_address.sin_port = htons(/*port num*/4000);
	other_address.sin_addr.s_addr = inet_addr(/*server ip*/"155.230.17.40");

	if(bind(sock, (struct sockaddr*)&my_address, addr_len) == -1){
		kill("Bind error!");
	}

	fd = fopen(file_name, "rb");
	if(fd == NULL)
		kill("file not found!");

	file_size = fsize(&fd);
	packets_to_send = packets_counter(file_size);

	char *file = malloc((sizeof(char) * file_size) + 1);

	if(file == NULL)
		kill("Memory error!");
	if(fread(file, 1, file_size, fd) != file_size)
		kill("Copy error!");

	file[file_size] = '\0';

	FD_ZERO(&set);
	FD_SET(sock, &set);

	timeout.tv_sec = SOCKET_READ_TIMEOUT_SEC;
	timeout.tv_usec = 0;

	while(hasContent()){
		size = copy_size(file_size, packets_send + 1);

		buffer[0] = atual_ack;

		if(size > 0)
			strncpy(buffer + 1, file + start, size);

		start += size;

		while(enable_send && packs_to_expire != LIMITE){
			if(sendto(sock, buffer, (unsigned long)(size + 1), 0, (struct sockaddr*)&other_address, addr_len) == -1)
				kill("Send failed!");
			rv = select(sock + 1, &set, NULL, NULL, &timeout);

			if(rv == SOCKET_ERROR)
				kill("Socket error!");
			else if(rv == 0){
				packs_to_expire++;

				timeout.tv_usec = 0;
				timeout.tv_sec = SOCKET_READ_TIMEOUT_SEC;
				FD_ZERO(&set);
				FD_SET(sock, &set);

				printf("Timeout expired! %d try!\n", packs_to_expire);
			}
			else{
				if(recvfrom(sock, buffer, BUFSIZE, 0, (struct sockaddr*)&my_address, &addr_len) == SOCKET_ERROR)
					kill("Error receiving!");
				else{
					if(buffer[0] == (atual_ack + 2)){
						atual_ack = ack(atual_ack);
						enable_send = false;
//						printf("Ack %c successfully received!\n", buffer[0]);
					}
					else{
						packs_to_expire++;
						printf("Not an ack! Sending again %d try!\n", packs_to_expire);
					}
				}
			}
		}

		enable_send = true;

		if(packs_to_expire == LIMITE){
			kill("No response! Stopping");
		}

		memset(buffer, 0, BUFSIZE);

		packs_to_expire = 0;
		packets_send++;
		timeout.tv_usec = 0;
		timeout.tv_sec = SOCKET_READ_TIMEOUT_SEC;
	}
	if(fclose(fd) != 0)
		kill("Error during file closing!");

	if(close(sock) != 0)
		kill("Error during socket closing!");

	free(file);

	return 1;
}
