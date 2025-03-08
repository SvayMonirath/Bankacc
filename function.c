#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void ClearSystem() {
    #ifdef _WIN32
        system("cls");  // Windows clear screen command
    #else
        system("clear"); // Linux/macOS clear screen command
    #endif
}

void PauseSystem() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}
