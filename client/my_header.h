#ifndef MY_HEADER
#define MY_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h> /* memset */
#include <unistd.h> /* close */
#include <time.h>
#include <ncurses.h> // need to be add compile option -lncurses
#include <string.h>
#include <errno.h>

#define true 1
#define false 0

#define BUFSIZE 101
#define PACKET_SIZE 100

#define DEFAULT_PORT 3000
#define PORT 67

#define SOCKET_ERROR -1
#define SOCKET_READ_TIMEOUT_SEC 2
#define LIMITE 10

#define ECHOMAX 255

#define DEFAULT_FILE_NAME "new_file"

// udp-recv.c
int file_upload(char*, char*, char*);

// udp-send.c
int file_download(char*);

// error.c
void kill(const char *msg);

// client.c
void menu_open();
void menu_open_echo();
int select_menu(int menu_num);
void menu_close();

// client_tools.c
int add_account(char *);
int login_server(char *);
int filename_send(char *);

#endif
