#include "my_header.h"

int file_receive(char *file_name){

    int sock, rv, on = 1;
    struct sockaddr_in my_address, other_address;
    char buf[BUFSIZE], ack_flag[1];
    char atual_ack = '0';
    socklen_t addr_len = sizeof(struct sockaddr_in);
    ssize_t received;
    bool enable_send = true, first_pack = true;
    FILE *fd;

    //Inicializa o socket
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock == -1){
        kill("Socket error!");
    }

    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

    //Limpa a memoria
    memset((char *)&my_address, 0, addr_len);
    memset(buf, 0, BUFSIZE);

    //Parametros de my_address
    my_address.sin_family = AF_INET;
    my_address.sin_port = htons(/*port num*/4000);
    my_address.sin_addr.s_addr = htonl(INADDR_ANY);

    
    if(bind(sock, (struct sockaddr*)&my_address, addr_len) == -1){
        kill("Bind error!");
    }


//    printf("Aguardando...\n");

    //Enquanto tamanho recebido == BUFSIZE, receba
    while(enable_send){

        //Salva a qtd de bytes recebidas/Fica bloqueado até algum dado chegar
        received = recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr*)&my_address, &addr_len);

        //Checa se o arquivo existe, caso contrario, cria
        if(first_pack){
            fd = fopen(file_name, "rb");
            if(fd == NULL)
                fd = fopen(file_name, "wb");
            else
                kill("File already exists! Aborting!");
//            printf("Iniciando transferencia!\n");
            first_pack = false;
        }

        if (received == SOCKET_ERROR)
            kill("Error receiving!");
        else{

            //Recebeu diferente de BUFSIZE, processa e encerra
            if(received != BUFSIZE)
            enable_send = false;

            //Determina os parametros da origem
            other_address.sin_family = AF_INET;
            other_address.sin_port = htons(ntohs(my_address.sin_port));
            other_address.sin_addr.s_addr = inet_addr(inet_ntoa(my_address.sin_addr));

            //Se ack estiver OK, escreve no arquivo os bytes recebidos
            if(buf[0] == atual_ack){
                atual_ack = ack(atual_ack);
                fwrite(buf + 1, received - 1, 1, fd);
            }

            //Seta o ACK a ser enviado de acordo com o pacote recebido
            ack_flag[0] = buf[0] + 2;

            //Envia o ACK (1 byte) para a origem, confirmando recebimento
            if(sendto(sock, ack_flag,(unsigned long) 1, 0, (struct sockaddr*)&other_address, addr_len) == -1){
                kill("Ack response failed!\n");
            }
        }
    }

    if(fclose(fd) != 0)
    kill("Error during file closing!");

    if(close(sock) != 0)
    kill("Error during socket closing!");

    return 1;
}
