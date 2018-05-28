#include "my_header.h"

int add_account(char *account){
	int sock;							// socket
	struct sockaddr_in echoServAddr;	// Echo server address
	struct sockaddr_in fromAddr;		// Source address of echo
	unsigned short echoServPort;		// Echo server port
	unsigned int fromSize;				// In-out of address size for recvfrom()
	char *servIP;						// IP address of server
	char echoBuffer[ECHOMAX+1];			// Buffer for receiving echoed string
	int echoStringLen;					// Length of string to echo
	int respStringLen;					// Length of received response

	servIP = "155.230.17.40";

	if((echoStringLen = strlen(account)) > ECHOMAX)
		kill("Echo word too long");

	echoServPort = 3000;

	if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		kill("socket() failed");

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(echoServPort);

	if(sendto(sock, account, echoStringLen, 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr)) != echoStringLen)
		kill("sendto() sent a different number of bytes than expected");

	fromSize = sizeof(fromAddr);
	if((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr*)&fromAddr, &fromSize)) != echoStringLen)
		kill("recvfrom() failed");

	if(echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
	{
		fprintf(stderr,"Error: received a packet from unknown source.\n");
		exit(1);
	}

	echoBuffer[respStringLen] = '\0';
//	printf("Received: %s\n", echoBuffer);

	close(sock);
	return 1;
}

int login_server(char *account){
	int sock;							// socket
	struct sockaddr_in echoServAddr;	// Echo server address
	struct sockaddr_in fromAddr;		// Source address of echo
	unsigned short echoServPort;		// Echo server port
	unsigned int fromSize;				// In-out of address size for recvfrom()
	char *servIP;						// IP address of server
	char echoBuffer[ECHOMAX+1];			// Buffer for receiving echoed string
	int echoStringLen;					// Length of string to echo
	int respStringLen;					// Length of received response

	servIP = "155.230.17.40";

	if((echoStringLen = strlen(account)) > ECHOMAX)
		kill("Echo word too long");

	echoServPort = 3000;

	if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		kill("socket() failed");

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(echoServPort);

	if(sendto(sock, account, echoStringLen, 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr)) != echoStringLen)
		kill("sendto() sent a different number of bytes than expected");

	fromSize = sizeof(fromAddr);
	if((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr*)&fromAddr, &fromSize)) != echoStringLen)
		kill("recvfrom() failed");

	if(echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
	{
		fprintf(stderr,"Error: received a packet from unknown source.\n");
		exit(1);
	}

	echoBuffer[respStringLen] = '\0';
//	printf("Received: %s\n", echoBuffer);

	close(sock);
	return 1;
}

int filename_send(char *account){
	int sock;							// socket
	struct sockaddr_in echoServAddr;	// Echo server address
	struct sockaddr_in fromAddr;		// Source address of echo
	unsigned short echoServPort;		// Echo server port
	unsigned int fromSize;				// In-out of address size for recvfrom()
	char *servIP;						// IP address of server
	char echoBuffer[ECHOMAX+1];			// Buffer for receiving echoed string
	int echoStringLen;					// Length of string to echo
	int respStringLen;					// Length of received response

	servIP = "155.230.17.40";

	if((echoStringLen = strlen(account)) > ECHOMAX)
		kill("Echo word too long");

	echoServPort = 3000;

	if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		kill("socket() failed");

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(echoServPort);

	if(sendto(sock, account, echoStringLen, 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr)) != echoStringLen)
		kill("sendto() sent a different number of bytes than expected");

	fromSize = sizeof(fromAddr);
	if((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr*)&fromAddr, &fromSize)) != echoStringLen)
		kill("recvfrom() failed");

	if(echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
	{
		fprintf(stderr,"Error: received a packet from unknown source.\n");
		exit(1);
	}

	echoBuffer[respStringLen] = '\0';
//	printf("Received: %s\n", echoBuffer);

	close(sock);
	return 1;
}