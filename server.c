#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    int client, server, n;
    struct sockaddr_in c_addr, s_addr;
    socklen_t len;
    char recv_query[30];

    if(argc < 2){
      puts("Usage: ./server -p port");
      exit(1);
    }

    server = socket(PF_INET, SOCK_STREAM, 0);
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(atoi(argv[2]));

    if(bind(server, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1){
        puts("bind() error");
        exit(1);
    }

    if(listen(server, 5) == -1){
        puts("listen() error");
        exit(1);
    }

    len = sizeof(c_addr);
    client = accept(server, (struct sockaddr*)&c_addr, &len);
    if(client == -1){
      puts("Client connection failed");
      exit(1);
    }

    while(1){
        read(client, recv_query, 30);
        n = strlen(recv_query);
        write(client, recv_query, n+1);
        puts(recv_query);
    }
    close(client);
    return 0;
}
