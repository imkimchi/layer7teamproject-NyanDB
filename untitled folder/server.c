#include "cJSON.h"
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
    char recv_query[300];
    char *parsedJson;
    char *temp;
    char *jsonP;
    char *queryP;
    char *command[30]; // command[0] = 디비 네임, command[1] = 명령어
    int i = 0;


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
        read(client, recv_query, 300);
        n = strlen(recv_query);

        parsedJson = strchr(recv_query, '{');
        jsonP = strchr(parsedJson, ')');
        *jsonP = '\0';
        queryP = strchr(recv_query, '(');
        *queryP = '\0';

        // dbname과 command 구분
        temp = strtok(recv_query, ".");
        while (temp != NULL){
            command[i] = temp;
            temp = strtok(NULL, ".");
            i++;
        }

        printf("dbName : %s\n", command[0]);
        printf("command : %s\n", command[1]);
        //json 파싱
        cJSON *json = cJSON_Parse((const char *)parsedJson);
    cJSON *data = cJSON_GetObjectItem(json, "user");
    printf("%d", json->type);
    printf("%s", json->child->string);
/*
    while(1){
        if(json->type == 5){
            first = json->child->string;
            CJSON *data = cJSON_GetObjectItem(json, first);
            int dataLength = cJSON_GetArraySize(data);

            for(int i=0; i<dataLength; i++){
                cJSON * dataAD = cJSON_GetArrayItem(data, i);
                cJSON * first = json->child->child->string;
                cJSON * twice = json->child->child->next;
        }
    }
    */
    // Event의 데이터만 파싱하여 저장.
    int dataLength = cJSON_GetArraySize(data);

    /*
    // 데이터의 갯 수를 구함.
    for (int i = 0; i < dataLength; i++) {
        cJSON * dataAD = cJSON_GetArrayItem(data, i);
        cJSON * eventName = cJSON_GetObjectItem(dataAD, "Name");
        printf("Name : %s\n", cJSON_Print(eventName));

        cJSON * eventLv = cJSON_GetObjectItem(dataAD, "Lv");
        printf("Lv : %s\n", cJSON_Print(eventLv));

        cJSON * eventZone = cJSON_GetObjectItem(dataAD, "Location");
        printf("Zone : %s\n", cJSON_Print(eventZone));

        cJSON * eventImgSrc = cJSON_GetObjectItem(dataAD, "ImgSrc");
        printf("ImgSrc : %s\n", cJSON_Print(eventImgSrc));
    }
    */
        write(client, recv_query, n+1);
    }
    close(client);
    return 0;
}
