// Este programa sobreescribe memoria dentro del juego Minecraft
// Donde el direccionamiento de memoria se dará en un bloque para generar stacks mayores a 64 (max del juego).

#include "windows.h"

int main(int argc, char const *argv[])
{
    DWORD Proceso;
    DWORD BloqueMinecraft = 0x9C36B18C; // Especifica el tipo de bloque y su código, puede ser cualquier bloque u objeto.
    unsigned short int bloque = 100000; // El valor del bloque donde se le establece su cantidad

    HWND ventanaMinecraft = FindWindowA(NULL, "Minecraft 1.17.1"); // Busca la ventana del juego
    GetWindowThreadProcessId(ventanaMinecraft, &Proceso);

    HANDLE m = OpenProcess(PROCESS_ALL_ACCESS, NULL, Proceso);
    WriteProcessMemory(m, (LPVOID)BloqueMinecraft, &bloque, sizeof(bloque), 0);

    return 0;
}

