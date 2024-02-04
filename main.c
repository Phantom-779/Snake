#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<windows.h>
#include <conio.h>
#include <time.h>


#define mapHight 20
#define mapWidth 40

//карта
char map[mapHight][mapWidth + 1];
//статус игры
bool game = true;

/*      ЗМЕЙКА     */
//инициализация змейки
char snakeHeadUp = '^';
char snakeHeadDown = 'V';
char snakeHeadLeft = '<';
char snakeHeadRight = '>';
char snakeHeadStart = '@';
char snakeBodyElement = '#';
int snakeBody[50][2];
int snakePositionX = 25;
int snakePositionY = 5;
int snakePositionXOld;
int snakePositionYOld;
int snakePartPositionXOld;
int snakePartPositionYOld;
char napravlenie;
char napravlenieOld;
int check = 0;
int score = 0;

//инициализация яблока
char apple = '*';
int applePositionX = 30;
int applePositionY = 7;

//отрисовка яблока
void appleDraw(){
    applePositionX = rand() * 1.0 / RAND_MAX * 38 + 1;
    applePositionY = rand() * 1.0 / RAND_MAX * 18 + 1;
    map[applePositionY][applePositionX] = apple;
}

//змейка кушает
void snakeEat(){
    if ((applePositionY == snakePositionY) && (applePositionX == snakePositionX)){
        score++;
        snakeBody[score][0] = applePositionY;
        snakeBody[score][1] = applePositionX;
        appleDraw();
    }
}

//отображение змейки
void drawSnake(){

    if (game != false){
       map[snakePositionY][snakePositionX] = snakeHeadStart;
    }

    int i = 0;
    while(snakeBody[i][0] != 0){
        map[snakeBody[i][0]][snakeBody[i][1]] = snakeBodyElement;
        i++;
    }
}
//перемещение тела змейки
void snakePartMove(){
/////////////////////////////////////
}

//перемещение змейки
void snakeMove(){
    if (kbhit()){
        napravlenieOld = napravlenie;
        napravlenie = getch();
        check = 1;
    }
    snakePositionYOld = snakePositionY;
    snakePositionXOld = snakePositionX;

    if (napravlenie == 'w' && snakeHeadStart != snakeHeadDown) {snakePositionY--; snakeHeadStart = snakeHeadUp;}
    if (napravlenie == 'w' && snakeHeadStart == snakeHeadDown) {snakePositionY++;}

    if (napravlenie == 's' && snakeHeadStart != snakeHeadUp) {snakePositionY++; snakeHeadStart = snakeHeadDown;}
    if (napravlenie == 's' && snakeHeadStart == snakeHeadUp) {snakePositionY--;}

    if (napravlenie == 'a' && snakeHeadStart != snakeHeadRight) {snakePositionX--; snakeHeadStart = snakeHeadLeft;}
    if (napravlenie == 'a' && snakeHeadStart == snakeHeadRight) {snakePositionX++;}

    if (napravlenie == 'd' && snakeHeadStart != snakeHeadLeft) {snakePositionX++; snakeHeadStart = snakeHeadRight;}
    if (napravlenie == 'd' && snakeHeadStart == snakeHeadLeft) {snakePositionX--;}
    if (napravlenie == 'q') {game = false;}
    if (map[snakePositionY][snakePositionX] == '#') {
            game = false;
            map[9][16] = 'G';
            map[9][17] = 'A';
            map[9][18] = 'M';
            map[9][19] = 'E';
            map[9][20] = ' ';
            map[9][21] = 'O';
            map[9][22] = 'V';
            map[9][23] = 'E';
            map[9][24] = 'R';
            map[9][25] = '!';
    }

    map[snakePositionYOld][snakePositionXOld] = ' ';

    int i = 0;
    if (check == 1){
        while(snakeBody[i][0] != 0){
            int a = snakeBody[i][0];
            int b = snakeBody[i][1];
            snakeBody[i][0] = snakePositionYOld;
            snakeBody[i][1] = snakePositionXOld;
            snakePositionYOld = a;
            snakePositionXOld = b;
            map[snakeBody[i][0]][snakeBody[i][1]] = snakeBodyElement;
            map[a][b] = ' ';
            i++;
        }
    }


}

//заполняем карту
void fillMap(){
    sprintf(map[0],"########################################");
    sprintf(map[mapHight - 1],"########################################");
    for (int i = 1; i < mapHight -1; i++)
        sprintf(map[i], "#                                      #");
}

//отрисовываем карту
void drawMap(){
    printf("");
    printf("\t\t\t\t\tW A S D - only");
    printf("\t\t\tScore - %d", score);
    printf("\n\t\t\t\t\teglish klava !");
    printf("\n\n");
    for (int i = 0; i < mapHight; i++)
        printf("\t\t\t\t\t%s\n", map[i]);
}

//обновление карты
void move(){
    appleDraw();
    do{
            Sleep(200);
            system("cls");
            snakeMove();
            drawSnake();
            drawMap();
            snakeEat();
    }
    while(game == true);

}

int main()
{
    srand(time(NULL));
    snakeBody[0][0] = 6;
    snakeBody[0][1] = 25;
    fillMap();
    move();
    appleDraw();
    getch();


}
