// Este programa cierra una ventana a partir de su titulo, solamente funciona en un sistema operativo windows.

#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    // Manipulador para el proceso.
    HWND handler;

    if(argc != 2){
        printf("Usage: %s <window_title>", argv[0]);
        return EXIT_FAILURE;
    }
  
    // Busca a la ventana por el titulo dado en los argumentos.
    handler = FindWindowA(NULL, argv[1]);

    if(!handler){
        puts("Window not found.");
        return EXIT_FAILURE;
    }

    // Cierra la ventana especificando el manipulador y el tipo de acción (WM_CLOSE).
    PostMessage(handler, WM_CLOSE, 0, 0);

    puts("Window closed.");

    return EXIT_SUCCESS;
}
