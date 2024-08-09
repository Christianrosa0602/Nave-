#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

void gotoxy(int x, int y) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;    //Variable para almacenar coordernadas
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);  //Mueve el cursor de la consola a la posición especificada por dwPos
}

void OcultarCursor() {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon, &cci);
}

void pintar_limites() {
    for (int i = 2; i < 119; i++) {
        gotoxy(i, 3); printf("%c", 205);
        gotoxy(i, 28); printf("%c", 205);
    }

    for (int i = 3; i < 28; i++) {
        gotoxy(2, i); printf("%c", 186);
        gotoxy(119, i); printf("%c", 186);
    }
    gotoxy(2, 3);    printf("%c", 201);
    gotoxy(2, 28);   printf("%c", 200);
    gotoxy(119, 3);  printf("%c", 187);
    gotoxy(119, 28); printf("%c", 188);
}

class NAVE {
    int x, y;
    int corazones;
    int vidas;
public:
    NAVE(int _x, int _y, int _corazones, int _vidas) : x(_x), y(_y), corazones(_corazones), vidas(_vidas) {};
    int X() { return x; }
    int Y() { return y; }
    void COR() { corazones--; }
    void pintar();
    void borrar();
    void mover();
    void pintar_corazones();
    void morir();
};

void NAVE::pintar() {
    gotoxy(x, y); printf("  %c", 94);
    gotoxy(x, y + 1); printf(" %c%c%c", 174, 207, 175);
    gotoxy(x, y + 2); printf("%C%C %C%C", 94, 190, 190, 94);
}

void NAVE::borrar() {
    gotoxy(x, y);     printf("       ");
    gotoxy(x, y + 1); printf("       ");
    gotoxy(x, y + 2); printf("       ");
}

void NAVE::mover() {
    if (_kbhit()) {
        char tecla = _getch();
        borrar();
        //Indica donde moverse
        if (tecla == IZQUIERDA && x>3) x--;
        if (tecla == DERECHA && x+6<116) x++;
        if (tecla == ARRIBA && y > 4) y--;
        if (tecla == ABAJO && y+2 < 27) y++;
        if (tecla == 'e') corazones--;
        pintar();
        pintar_corazones();
    }
} 

void NAVE::pintar_corazones(){

    gotoxy(65, 2); printf("Vidas %d", vidas);
    gotoxy(93,2); printf("Salud");
    gotoxy(100, 2); printf("                 ");
    for (int i = 0; i < corazones; i++) {
        gotoxy(100 + i * 3, 2); printf("<3");
    }
}

void NAVE::morir() {
    if (corazones == 0) {
        borrar();
        gotoxy(x, y);   printf("  *  ");
        gotoxy(x, y+1); printf(" *** ");
        gotoxy(x, y+2); printf("*****");
        Sleep(200);

        borrar();
        gotoxy(x, y);     printf("* * *");
        gotoxy(x, y + 1); printf(" ***");
        gotoxy(x, y + 2); printf("* * *");
        Sleep(200);
        borrar();

        vidas--;
        corazones = 3;
        pintar_corazones();
        pintar();
    }
}

class AST {
    int x, y;

    public:
        AST(int _x, int _y):x(_x),y(_y){}
        void pintar();
        void mover();
        void choque(struct NAVE &N);
};

void AST::pintar() {
    gotoxy(x, y); printf("%c", 184);
}

void AST::mover() {
    gotoxy(x, y); printf(" ");
    y++;
    if (y > 27) {
        x = rand() % 113 + 4;
        y = 4;
    }
    pintar();
}

void AST::choque(struct NAVE &N) {
    if (x >= N.X() && x < N.X()+5 && y >= N.Y() && y <= N.Y()+2) {
        N.COR();
        N.borrar();
        N.pintar();
        N.pintar_corazones();
        x = rand() % 113 + 4;
        y = 4;
    }
}

int main() {
    OcultarCursor();
    pintar_limites();
    NAVE N(7, 7, 3, 3);
    N.pintar();
    N.pintar_corazones();

    AST ast1(10, 4), ast2(4,8), ast3(15,10);

    bool game_over = false;
    while (!game_over) {
        ast1.mover(); ast1.choque(N);
        ast2.mover(); ast2.choque(N);
        ast3.mover(); ast3.choque(N);

        N.morir();
        N.mover();
        Sleep(30);
    }

    return 0;
}
