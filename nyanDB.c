#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  int client, len, n;
  struct sockaddr_in c_addr;
  char query[30];
  char recv[30];

  if(argc < 2){
    puts("Usage: ./nyanDB -p port");
    exit(1);
  }

  client = socket(PF_INET, SOCK_STREAM, 0);
  c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  c_addr.sin_family = AF_INET;
  c_addr.sin_port = htons(atoi(argv[2]));

  if(connect(client, (struct sockaddr *)&c_addr, sizeof(c_addr)) == -1){
      puts("connect error");
      exit(1);
  }

  printf("\n░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄░░░░░░░░░\n");
  printf("░░░░░░░░▄▀░░░░░░░░░░░░▄░░░░░░░▀▄░░░░░░░\n");
  printf("░░░░░░░░█░░▄░░░░▄░░░░░░░░░░░░░░█░░░░░░░\n");
  printf("░░░░░░░░█░░░░░░░░░░░░▄█▄▄░░▄░░░█░▄▄▄░░░\n");
  printf("░▄▄▄▄▄░░█░░░░░░▀░░░░▀█░░▀▄░░░░░█▀▀░██░░             Welcome to nyanDB !\n");
  printf("░██▄▀██▄█░░░▄░░░░░░░██░░░░▀▀▀▀▀░░░░██░░             nyan nyan > _ <\n");
  printf("░░░░▀████░▀░░░░▄░░░██░░░▄█░░░░▄░▄█░░██░\n");
  printf("░░░░░░░▀█░░░░▄░░░░░██░░░░▄░░░▄░░▄░░░██░\n");
  printf("░░░░░░░▄█▄░░░░░░░░░░░▀▄░░▀▀▀▀▀▀▀▀░░▄▀░░\n");
  printf("░░░░░░█▀▀█████████▀▀▀▀████████████▀░░░░\n");
  printf("░░░░░░████▀░░███▀░░░░░░▀███░░▀██▀░░░░░░\n");
  printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n\n");


  while(1){
    printf("nyandb> ");
    memset(query, 0, sizeof(query));
    scanf("%s", query);
    write(client, query, 30);

    if((n = read(client, recv, sizeof(recv))) < 0){
        exit(1);
    }
    printf("\nSent: %s \n\n", recv);
  }

  close(client);
  return 0;
}
