#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;


#define cube 254
#define en 190
#define keyUP 72
#define keyDOWN 80
#define keyENTER 13
#define W 119
#define S 115
#define A 97
#define D 100
#define horizontal_wall 205
#define vertical_wall 186
#define top_left_corner 201
#define top_right_corner 187
#define down_left_corner 200
#define down_right_corner 188
#define OPTIONS 3

const int point = 46; //46
const int alto = 0;
const int basso = 1;
const int destra = 2;
const int sinistra = 3;
const int offset = 2;       //offset per stampare correttamente i personaggi e il punteggio

struct pos{
    int x, y;   //0 <= Y => 26____0 <= X => 48
    int direction;  //0(Alto), 1(Basso), 2(Destra), 3(Sinistra)
    int precDirection;
};

int lab[27][49];
int ball[27][49];  //in che posizione si trovano le palline
bool gameOver = false;

void init();

struct pos enMovement(struct pos nemico, struct pos player);

void gotoxy( int column, int line ){        //http://www.cplusplus.com/forum/beginner/4234/
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coord);
}

///TUTORIAL
void tutorial(){
    cout << "\n\t\tBENVENUTO SU CUBEMOVE!\n";
    cout << "\t--------------------------------------\n";
    cout << " Lo scopo del gioco e' semplice: prendi tutte le palline senza entrare in contatto con i nemici!\n";
    cout << "\n Giocatore: " << char(cube);
    cout << "\n Nemico: " << char(en);
    cout << "\n\n Per entrare in contatto con i nemici bastera' essere accanto a loro, in uno di questi modi:\n";
    cout << "1) " << char(cube) << char(en);
    cout << "\n\n2) " << char(cube);
    cout << "\n   " << char(en);
    cout << "\n\n Buona fortuna!\n\n";
    system("pause");
}


int main(){
    srand(time(NULL));
    struct pos player;
    struct pos enemy;
    struct pos enemy1;
    struct pos enemy2;
    struct pos enemy3;
    struct pos enemy4;
    struct pos enemy5;
    struct pos enemy6;
    struct pos enemy7;
    struct pos enemy8;

    int ascii = 0, score = 0, k = 0;
    bool termina = false, menu = false;
    system("color 0a");
    tutorial();
    do{
      ///Inizializzazione scenario e nemici
        init();

        gameOver = false;
        system("cls");
        for(k = 0; k < 27; k++)
            for(int i = 0; i < 49; i++)
                ball[k][i] = lab[k][i]; //in modo da tener traccia delle palline

        //assegno una posizione ai nemici
        player.x = 11;
        player.y = 2;

        enemy.x = 36;
        enemy.y = 1;
        enemy.direction = sinistra;
        enemy.precDirection = enemy.direction;

        enemy1.x = 46;
        enemy1.y = 8;
        enemy1.direction = basso;
        enemy1.precDirection = enemy1.direction;

        enemy2.x = 36;
        enemy2.y = 11;
        enemy2.direction = sinistra;
        enemy2.precDirection = enemy2.direction;

        enemy3.x = 8;
        enemy3.y = 12;
        enemy3.direction = alto;
        enemy3.precDirection = enemy3.direction;

        enemy4.x = 3;
        enemy4.y = 19;
        enemy4.direction = destra;
        enemy4.precDirection = enemy4.direction;

        enemy5.x = 30;
        enemy5.y = 19;
        enemy5.direction = alto;
        enemy5.precDirection = enemy5.direction;

        enemy6.x = 34;
        enemy6.y = 22;
        enemy6.direction = destra;
        enemy6.precDirection = enemy6.direction;

        enemy7.x = 12;
        enemy7.y = 24;
        enemy7.direction = basso;
        enemy7.precDirection = enemy7.direction;

        enemy8.x = 33;
        enemy8.y = 25;
        enemy8.direction = destra;
        enemy8.precDirection = enemy8.direction;


        //posizionamento nemici nel campo
        lab[player.y][player.x] = cube;
        lab[enemy.y][enemy.x] = en;
        lab[enemy1.y][enemy1.x] = en;
        lab[enemy2.y][enemy2.x] = en;
        lab[enemy3.y][enemy3.x] = en;
        lab[enemy4.y][enemy4.x] = en;
        lab[enemy5.y][enemy5.x] = en;
        lab[enemy6.y][enemy6.x] = en;
        lab[enemy7.y][enemy7.x] = en;
        lab[enemy8.y][enemy8.x] = en;
        score = 0;
        cout << "\t\tPUNTEGGIO: " << score << endl;
        for(k = 0; k < 27; k++){
                printf("\n");
                for(int i = 0; i < 49; i++) printf("%c", lab[k][i]);
        }


        do{ ///Ciclo gioco
            gotoxy(0, 0);
            cout << "\t\tPUNTEGGIO: " << score;
            //stampa punteggio


            //attesa input player
            ascii = getch();
            if(ascii < 97) ascii += 32;
            switch(ascii){
                case W:
                    if(lab[player.y - 1][player.x] == 32 || lab[player.y - 1][player.x] == point){
                        if(lab[player.y - 1][player.x] == point) score++;
                        gotoxy(player.x, player.y+offset);
                        cout << char(32);
                        lab[player.y][player.x] = 32;
                        player.y--;
                        gotoxy(player.x, player.y+offset);
                        //lab[player.y][player.x] = cube;
                        cout << char(cube);
                    }
                    break;

                case S:
                    if(lab[player.y + 1][player.x] == 32 || lab[player.y + 1][player.x] == point){
                        if(lab[player.y + 1][player.x] == point) score++;
                        gotoxy(player.x, player.y+offset);
                        cout << char(32);
                        lab[player.y][player.x] = 32;
                        player.y++;
                        gotoxy(player.x, player.y+offset);
                        //lab[player.y][player.x] = cube;
                        cout << char(cube);
                    }
                    break;

                case A:
                    if(lab[player.y][player.x - 1] == 32 || lab[player.y][player.x - 1] == point){
                        if(lab[player.y][player.x-1] == point) score++;
                        gotoxy(player.x, player.y+offset);
                        cout << char(32);
                        lab[player.y][player.x] = 32;
                        player.x--;
                        gotoxy(player.x, player.y+offset);
                        //lab[player.y][player.x] = cube;
                        cout << char(cube);
                    }
                    break;

                case D:
                    if(lab[player.y][player.x + 1] == 32 || lab[player.y][player.x + 1] == point){
                        if(lab[player.y][player.x+1] == point) score++;
                        gotoxy(player.x, player.y+offset);
                        cout << char(32);
                        lab[player.y][player.x] = 32;
                        player.x++;
                        gotoxy(player.x, player.y+offset);
                        //lab[player.y][player.x] = cube;
                        cout << char(cube);
                    }
                    break;
            }

            ball[player.y][player.x] = 32;      // in modo che quando passa il nemico non rigenera le palline
            ///-------------------------DIREZIONE NEMICI---------------------///
                enemy = enMovement(enemy, player);
                enemy1 = enMovement(enemy1, player);
                enemy2 = enMovement(enemy2, player);
                enemy3 = enMovement(enemy3, player);
                enemy4 = enMovement(enemy4, player);
                enemy5 = enMovement(enemy5, player);
                enemy6 = enMovement(enemy6, player);
                enemy7 = enMovement(enemy7, player);
                enemy8 = enMovement(enemy8, player);


            if(gameOver){
                gotoxy(48, 6);
                cout << "\t\tHAI PERSO! :(";
                termina = true;
                for(int i = 0; i < 3; i++){
                    system("color 0c");
                    Sleep(100);
                    system("color 0a");
                    Sleep(100);
                }
            }

            if(score == 186){   //185
                gotoxy(48, 6);
                cout << "\t\tHAI VINTO!";
                termina = true;
            }

       }while(!termina);
       gotoxy(48, 7);
       cout << "\t\tPREMERE UN TASTO PER COMINCIARE UNA NUOVA PARTITA";
       getch();
       system("cls");
       termina = false;


    }while(!menu);




}

void init(){
    int k = 0;
        //k = 0
        lab[k][0] = top_left_corner;
        for(int i = 1; i < 20; i++)lab[k][i] = horizontal_wall;
        lab[k][20] = top_right_corner;
        for(int i = 21; i < 30; i++) lab[k][i] = 32;
        lab[k][30] = top_left_corner;
        for(int i = 31; i < 48; i++)lab[k][i] = horizontal_wall;
        lab[k][48] = top_right_corner;

        k++;
    //k = 1
        lab[k][0] = vertical_wall;
        lab[k][1] = 32;
        lab[k][2] = 32;
        for(int i = 3; i <= 19; i += 2) lab[k][i] = point;
        for(int i = 4; i <= 18; i += 2) lab[k][i] = 32;
        lab[k][20] = vertical_wall;
        for(int i = 21; i < 30; i++) lab[k][i] = 32;
        lab[k][30] = vertical_wall;
        for(int i = 31; i <= 47; i += 2) lab[k][i] = point;
        for(int i = 32; i <= 46; i += 2) lab[k][i] = 32;
        lab[k][48] = vertical_wall;

        k++;
    //k = 2
        lab[k][0] = vertical_wall;
        lab[k][1] = point;
        lab[k][2] = 32;
        lab[k][3] = top_left_corner;
        for(int i = 4; i <= 9; i++) lab[k][i] = horizontal_wall;
        lab[k][10] = top_right_corner;
        lab[k][11] = 32;
        lab[k][12] = top_left_corner;
        for(int i = 13; i <= 17; i++) lab[k][i] = horizontal_wall;
        lab[k][18] = top_right_corner;
        lab[k][19] = 32;
        lab[k][20] = vertical_wall;
        for(int i = 21; i <= 29; i++) lab[k][i] = 32;
        lab[k][30] = vertical_wall;
        lab[k][31] = 32;
        lab[k][32] = top_left_corner;
        for(int i = 33; i <= 37; i++) lab[k][i] = horizontal_wall;
        lab[k][38] = top_right_corner;
        lab[k][39] = 32;
        lab[k][40] = 32;
        lab[k][41] = top_left_corner;
        for(int i = 42; i <= 45; i++) lab[k][i] = horizontal_wall;
        lab[k][46] = top_right_corner;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;
    ///k = 3  DA QUA
        lab[k][0] = vertical_wall;
        lab[k][1] = 32;
        lab[k][2] = 32;
        lab[k][3] = down_left_corner;
        for(int i = 4; i <= 9; i++) lab[k][i] = horizontal_wall;
        lab[k][10] = down_right_corner;
        lab[k][11] = 32;
        lab[k][12] = vertical_wall;
        for(int i = 13; i <= 17; i++) lab[k][i] = 32;
        lab[k][18] = vertical_wall;
        lab[k][19] = point;
        lab[k][20] = down_left_corner;
        for(int i = 21; i <= 29; i++) lab[k][i] = horizontal_wall;
        lab[k][30] = down_right_corner;
        lab[k][31] = 32;
        lab[k][32] = vertical_wall;
        for(int i = 33; i <= 37; i++) lab[k][i] = 32;
        lab[k][38] = vertical_wall;
        lab[k][39] = point;
        lab[k][40] = 32;
        lab[k][41] = vertical_wall;
        for(int i = 42; i <= 45; i++) lab[k][i] = 32;
        lab[k][46] = vertical_wall;
        lab[k][47] = point;
        lab[k][48] = vertical_wall;

        k++;
    //k = 4
        lab[k][0] = vertical_wall;
        for(int i = 1; i <= 11; i += 2) lab[k][i] = point;
        for(int i = 2; i <= 10; i += 2) lab[k][i] = 32;
        lab[k][12] = vertical_wall;
        for(int i = 13; i <= 17; i++) lab[k][i] = 32;
        lab[k][18] = vertical_wall;
        for(int i = 19; i <= 31; i += 2) lab[k][i] = point;
        for(int i = 20; i <= 30; i += 2) lab[k][i] = 32;
        lab[k][32] = vertical_wall;
        for(int i = 33; i <= 37; i++) lab[k][i] = 32;
        lab[k][38] = vertical_wall;
        lab[k][39] = 32;
        lab[k][40] = point;
        lab[k][41] = vertical_wall;
        for(int i = 42; i <= 45; i++) lab[k][i] = 32;
        lab[k][46] = vertical_wall;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;

    //k = 5
        lab[k][0] = vertical_wall;
        lab[k][1] = 32;
        lab[k][2] = 32;
        lab[k][3] = top_left_corner;
        for(int i = 4; i <= 8; i++) lab[k][i] = horizontal_wall;
        lab[k][9] = top_right_corner;
        lab[k][10] = 32;
        lab[k][11] = 32;
        lab[k][12] = down_left_corner;
        for(int i = 13; i <= 17; i++) lab[k][i] = horizontal_wall;
        lab[k][18] = down_right_corner;
        lab[k][19] = 32;
        lab[k][20] = top_left_corner;
        for(int i = 21; i <= 24; i++) lab[k][i] = horizontal_wall;
        lab[k][25] = top_right_corner;
        lab[k][26] = 32;
        lab[k][27] = 32;
        lab[k][28] = top_left_corner;
        for(int i = 29; i <= 31; i++) lab[k][i] = horizontal_wall;
        lab[k][32] = down_right_corner;
        for(int i = 33; i <= 37; i++) lab[k][i] = 32;
        lab[k][38] = vertical_wall;
        lab[k][39] = point;
        lab[k][40] = 32;
        lab[k][41] = vertical_wall;
        for(int i = 42; i <= 45; i++) lab[k][i] = 32;
        lab[k][46] = vertical_wall;
        lab[k][47] = point;
        lab[k][48] = vertical_wall;
        k++;
    //k = 6
        lab[k][0] = vertical_wall;
        lab[k][1] = point;
        lab[k][2] = 32;
        lab[k][3] = down_left_corner;
        lab[k][4] = horizontal_wall;
        lab[k][5] = top_right_corner;
        lab[k][6] = 32;
        lab[k][7] = top_left_corner;
        lab[k][8] = horizontal_wall;
        lab[k][9] = down_right_corner;
        for(int i = 10; i <= 18; i += 2) lab[k][i] = 32;
        for(int i = 11; i <= 19; i += 2) lab[k][i] = point;
        lab[k][20] = vertical_wall;
        for(int i = 21; i <= 24; i++) lab[k][i] = 32;
        lab[k][25] = vertical_wall;
        lab[k][26] = 32;
        lab[k][27] = 32;
        lab[k][28] = down_left_corner;
        for(int i = 29; i <= 37; i++) lab[k][i] = horizontal_wall;
        lab[k][38] = down_right_corner;
        lab[k][39] = 32;
        lab[k][40] = point;
        lab[k][41] = down_left_corner;
        for(int i = 42; i <= 45; i++) lab[k][i] = horizontal_wall;
        lab[k][46] = down_right_corner;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;
    //k = 7
        lab[k][0] = vertical_wall;
        lab[k][1] = 32;
        for(int i = 2; i <= 10; i += 2) lab[k][i] = 32;
        lab[k][3] = point;
        lab[k][5] = vertical_wall;
        lab[k][7] = vertical_wall;
        lab[k][9] = point;
        lab[k][11] = top_left_corner;
        lab[k][12] = horizontal_wall;
        lab[k][13] = horizontal_wall;
        lab[k][14] = top_right_corner;
        lab[k][15] = 32;
        lab[k][16] = top_left_corner;
        lab[k][17] = horizontal_wall;
        lab[k][18] = top_right_corner;
        lab[k][19] = 32;
        lab[k][20] = vertical_wall;
        for(int i = 21; i <= 24; i++) lab[k][i] = 32;
        lab[k][25] = vertical_wall;
        for(int i = 26; i <= 46; i += 2) lab[k][i] = 32;
        for(int i = 27; i <= 47; i += 2) lab[k][i] = point;
        lab[k][48] = vertical_wall;

        k++;
    //k = 8
        lab[k][0] = vertical_wall;
        lab[k][1] = point;
        lab[k][2] = 32;
        lab[k][3] = 32;
        lab[k][4] = 32;
        lab[k][5] = down_left_corner;
        lab[k][6] = horizontal_wall;
        lab[k][7] = down_right_corner;
        lab[k][8] = 32;
        lab[k][9] = top_left_corner;
        lab[k][10] = horizontal_wall;
        lab[k][11] = down_right_corner;
        lab[k][12] = 32;
        lab[k][13] = 32;
        for(int i = 14; i <= 18; i += 2) lab[k][i] = vertical_wall;
        lab[k][15] = point;
        lab[k][17] = 32;
        lab[k][19] = 32;
        lab[k][20] = down_left_corner;
        for(int i = 21; i <= 24; i++) lab[k][i] = horizontal_wall;
        lab[k][25] = down_right_corner;
        lab[k][26] = 32;
        lab[k][27] = 32;
        lab[k][28] = top_left_corner;
        for(int i = 29; i <= 32; i++) lab[k][i] = horizontal_wall;
        lab[k][33] = top_right_corner;
        lab[k][34] = 32;
        lab[k][35] = 32;
        lab[k][36] = top_left_corner;
        for(int i= 37; i <= 44; i++) lab[k][i] = horizontal_wall;
        lab[k][45] = top_right_corner;
        lab[k][46] = 32;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;
    //k = 9
        lab[k][0] = vertical_wall;
        for(int i = 1; i <= 7; i += 2) lab[k][i] = 32;
        for(int i = 2; i <= 8; i += 2) lab[k][i] = point;
        lab[k][9] = vertical_wall;
        for(int i = 10; i <= 13; i++) lab[k][i] = 32;
        for(int i = 14; i <= 18; i += 2) lab[k][i] = vertical_wall;
        lab[k][15] = 32;
        lab[k][17] = 32;
        for(int i = 19; i <= 27; i += 2) lab[k][i] = point;
        for(int i = 20; i <= 26; i += 2) lab[k][i] = 32;
        lab[k][28] = vertical_wall;
        for(int i = 29; i <= 32; i++) lab[k][i] = 32;
        lab[k][33] = vertical_wall;
        lab[k][34] = point;
        lab[k][35] = 32;
        lab[k][36] = vertical_wall;
        for(int i = 37; i <= 44; i++) lab[k][i] = 32;
        lab[k][45] = vertical_wall;
        lab[k][46] = point;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;
    //k = 10
        lab[k][0] = vertical_wall;
        lab[k][1] = point;
        lab[k][2] = top_left_corner;
        for(int i = 3; i <= 6; i++) lab[k][i] = horizontal_wall;
        lab[k][7] = down_right_corner;
        lab[k][8] = 32;
        lab[k][9] = vertical_wall;
        for(int i = 10; i <= 13; i++) lab[k][i] = 32;
        lab[k][14] = vertical_wall;
        lab[k][15] = point;
        lab[k][16] = down_left_corner;
        lab[k][17] = horizontal_wall;
        lab[k][18] = down_right_corner;
        lab[k][19] = 32;
        lab[k][20] = top_left_corner;
        lab[k][21] = horizontal_wall;
        lab[k][22] = top_right_corner;
        lab[k][23] = 32;
        lab[k][24] = 32;
        lab[k][25] = top_left_corner;
        lab[k][26] = horizontal_wall;
        lab[k][27] = horizontal_wall;
        lab[k][28] = down_right_corner;
        for(int i = 29; i <= 32; i++) lab[k][i] = 32;
        lab[k][33] = vertical_wall;
        lab[k][34] = 32;
        lab[k][35] = 32;
        lab[k][36] = down_left_corner;
        for(int i = 37; i <= 44; i++) lab[k][i] = horizontal_wall;
        lab[k][45] = down_right_corner;
        lab[k][46] = 32;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;
    //k = 11
        lab[k][0] = vertical_wall;
        for(int i = 1; i <= 7; i += 2) lab[k][i] = 32;
        for(int i = 2; i <= 8; i += 2) lab[k][i] = point;
        lab[k][9] = vertical_wall;
        for(int i = 10; i<= 13; i++) lab[k][i] = 32;
        lab[k][14] = vertical_wall;
        for(int i = 15; i <= 19; i += 2) lab[k][i] = 32;
        lab[k][16] = point;
        lab[k][18] = point;
        lab[k][20] = vertical_wall;
        lab[k][21] = 32;
        lab[k][22] = vertical_wall;
        lab[k][23] = 32;
        lab[k][24] = point;
        lab[k][25] = down_left_corner;
        lab[k][26] = horizontal_wall;
        lab[k][27] = horizontal_wall;
        lab[k][28] = top_right_corner;
        for(int i = 29; i <= 32; i++) lab[k][i] = 32;
        lab[k][33] = vertical_wall;
        for(int i = 34; i <= 46; i += 2) lab[k][i] = 32;
        for(int i = 35; i <= 47; i += 2) lab[k][i] = point;
        lab[k][48] = vertical_wall;

        k++;
    //k = 12
        lab[k][0] = down_left_corner;
        for(int i = 1; i <= 6; i++) lab[k][i] = horizontal_wall;
        lab[k][7] = top_right_corner;
        lab[k][8] = 32;
        lab[k][9] = vertical_wall;
        for(int i = 10; i <= 13; i++) lab[k][i] = 32;
        lab[k][14] = down_left_corner;
        for(int i = 15; i <= 19; i++) lab[k][i] = horizontal_wall;
        lab[k][20] = down_right_corner;
        for(int i = 21; i <= 27; i += 2) lab[k][i] = 32;
        lab[k][22] = vertical_wall;
        lab[k][24] = point;
        lab[k][26] = point;
        lab[k][28] = vertical_wall;
        for(int i = 29; i <= 32; i++) lab[k][i] = 32;
        lab[k][33] = vertical_wall;
        lab[k][34] = 32;
        lab[k][35] = top_left_corner;
        for(int i = 36; i <= 38; i++) lab[k][i] = horizontal_wall;
        lab[k][39] = top_right_corner;
        lab[k][40] = 32;
        lab[k][41] = top_left_corner;
        for(int i = 42; i <= 47; i++) lab[k][i] = horizontal_wall;
        lab[k][48] = down_right_corner;

        k++;
    //k = 13
        for(int i = 0; i <= 6; i++) lab[k][i] = 32;
        lab[k][7] = vertical_wall;
        lab[k][8] = point;
        lab[k][9] = vertical_wall;
        for(int i = 10; i <= 21; i++) lab[k][i] = 32;
        lab[k][22] = vertical_wall;
        lab[k][23] = 32;
        lab[k][24] = top_left_corner;
        lab[k][25] = horizontal_wall;
        lab[k][26] = top_right_corner;
        lab[k][27] = 32;
        lab[k][28] = down_left_corner;
        for(int i = 29; i <= 32; i++) lab[k][i] = horizontal_wall;
        lab[k][33] = down_right_corner;
        lab[k][34] = 32;
        lab[k][35] = vertical_wall;
        for(int i = 36; i <= 38; i++) lab[k][i] = 32;
        lab[k][39] = vertical_wall;
        lab[k][40] = 32;
        lab[k][41] = vertical_wall;
        for(int i = 42; i <= 48; i++) lab[k][i] = 32;

        k++;
    ///k = 14 A QUA
        lab[k][0] = top_left_corner;
        for(int i = 1; i <= 6; i++) lab[k][i] = horizontal_wall;
        lab[k][7] = down_right_corner;
        lab[k][8] = 32;
        lab[k][9] = down_left_corner;
        for(int i = 10; i <= 21; i++) lab[k][i] = horizontal_wall;
        lab[k][22] = down_right_corner;
        lab[k][23] = point;
        lab[k][24] = vertical_wall;
        lab[k][26] = vertical_wall;
        for(int i = 25; i  <= 33; i += 2) lab[k][i] = 32;
        for(int i = 28; i <= 34; i += 2) lab[k][i] = point;
        lab[k][35] = vertical_wall;
        for(int i = 36; i <= 38; i++) lab[k][i] = 32;
        lab[k][39] = vertical_wall;
        lab[k][40] = 32;
        lab[k][41] = down_left_corner;
        for(int i = 42; i <= 47; i++) lab[k][i] = horizontal_wall;
        lab[k][48] = top_right_corner;

        k++;
    //k = 15
        lab[k][0] = vertical_wall;
        for(int i = 1; i <= 25; i += 2) lab[k][i] = 32;
        for(int i = 2; i <= 22; i += 2) lab[k][i] = point;
        lab[k][24] = vertical_wall;
        lab[k][26] = vertical_wall;
        lab[k][27] = point;
        lab[k][28] = 32;
        lab[k][29] = top_left_corner;
        lab[k][30] = horizontal_wall;
        lab[k][31] = horizontal_wall;
        lab[k][32] = top_right_corner;
        lab[k][33] = 32;
        lab[k][34] = 32;
        lab[k][35] = down_left_corner;
        for(int i = 36; i <= 38; i++) lab[k][i] = horizontal_wall;
        lab[k][39] = down_right_corner;
        for(int i = 40; i <= 46; i += 2) lab[k][i] = point;
        for(int i = 41; i <= 47; i += 2) lab[k][i] = 32;
        lab[k][48] = vertical_wall;

        k++;
    //k = 16
        lab[k][0] = vertical_wall;
        lab[k][1] = 32;
        lab[k][2] = 32;
        lab[k][3] = top_left_corner;
        for(int i = 4; i <= 13; i++) lab[k][i] = horizontal_wall;
        lab[k][14] = top_right_corner;
        lab[k][15] = 32;
        lab[k][16] = top_left_corner;
        for(int i = 17; i <= 21; i++) lab[k][i] = horizontal_wall;
        lab[k][22] = top_right_corner;
        lab[k][23] = 32;
        lab[k][24] = down_left_corner;
        lab[k][25] = horizontal_wall;
        lab[k][26] = down_right_corner;
        lab[k][27] = 32;
        lab[k][28] = 32;
        lab[k][29] = vertical_wall;
        lab[k][30] = 32;
        lab[k][31] = 32;
        lab[k][32] = vertical_wall;
        for(int i = 33; i <= 43; i += 2) lab[k][i] = point;
        for(int i = 34; i <= 42; i += 2) lab[k][i] = 32;
        lab[k][44] = top_left_corner;
        lab[k][45] = top_right_corner;
        lab[k][46] = 32;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;
    //k = 17
        lab[k][0] = vertical_wall;
        lab[k][1] = point;
        lab[k][2] = 32;
        lab[k][3] = vertical_wall;
        for(int i = 4; i <= 13; i++) lab[k][i] = 32;
        lab[k][14] = vertical_wall;
        lab[k][15] = point;
        lab[k][16] = vertical_wall;
        for(int i = 17; i <= 21; i++) lab[k][i] = 32;
        lab[k][22] = vertical_wall;
        for(int i = 23; i <= 27; i += 2) lab[k][i] = 32;
        for(int i = 24; i <= 28; i += 2) lab[k][i] = point;
        lab[k][29] = down_left_corner;
        lab[k][30] = horizontal_wall;
        lab[k][31] = horizontal_wall;
        lab[k][32] = down_right_corner;
        lab[k][33] = 32;
        lab[k][34] = 32;
        lab[k][35] = top_left_corner;
        for(int i = 36; i <= 40; i++) lab[k][i] = horizontal_wall;
        lab[k][41] = top_right_corner;
        lab[k][42] = 32;
        lab[k][43] = 32;
        lab[k][44] = vertical_wall;
        lab[k][45] = vertical_wall;
        lab[k][46] = 32;
        lab[k][47] = point;
        lab[k][48] = vertical_wall;

        k++;
    // k = 18
        lab[k][0] = vertical_wall;
        lab[k][1] = 32;
        lab[k][2] = 32;
        lab[k][3] = down_left_corner;
        for(int i = 4; i <= 13; i++) lab[k][i] = horizontal_wall;
        lab[k][14] = down_right_corner;
        lab[k][15] = 32;
        lab[k][16] = vertical_wall;
        for(int i = 17; i <= 21; i++) lab[k][i] = 32;
        lab[k][22] = vertical_wall;
        lab[k][23] = 32;
        lab[k][24] = 32;
        lab[k][25] = top_left_corner;
        lab[k][26] = horizontal_wall;
        lab[k][27] = top_right_corner;
        for(int i = 28; i <= 34; i += 2) lab[k][i] = 32;
        for(int i = 29; i <= 33; i += 2) lab[k][i] = point;
        lab[k][35] = vertical_wall;
        for(int i = 36; i <= 40; i++) lab[k][i] = 32;
        lab[k][41] = vertical_wall;
        lab[k][42] = point;
        lab[k][43] = 32;
        lab[k][44] = vertical_wall;
        lab[k][45] = vertical_wall;
        lab[k][46] = point;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;
    //k = 19
        lab[k][0] = vertical_wall;
        for(int i = 1; i <= 15; i += 2) lab[k][i] = 32;
        for(int i = 2; i <= 14; i += 2) lab[k][i] = point;
        lab[k][16] = vertical_wall;
        for(int i = 17; i <= 21; i++) lab[k][i] = 32;
        lab[k][22] = vertical_wall;
        lab[k][23] = point;
        lab[k][24] = 32;
        lab[k][25] = vertical_wall;
        lab[k][26] = 32;
        lab[k][27] = vertical_wall;
        for(int i = 28; i <= 31; i++) lab[k][i] = 32;
        lab[k][32] = top_left_corner;
        lab[k][33] = horizontal_wall;
        lab[k][34] = horizontal_wall;
        lab[k][35] = down_right_corner;
        for(int i = 36; i <= 40; i++) lab[k][i] = 32;
        lab[k][41] = vertical_wall;
        lab[k][42] = 32;
        lab[k][43] = 32;
        lab[k][44] = vertical_wall;
        lab[k][45] = vertical_wall;
        lab[k][46] = 32;
        lab[k][47] = point;
        lab[k][48] = vertical_wall;

        k++;
    // k = 20
        lab[k][0] = vertical_wall;
        lab[k][1] = 32;
        lab[k][2] = 32;
        lab[k][3] = top_left_corner;
        for(int i = 4; i <= 7; i++) lab[k][i] = horizontal_wall;
        lab[k][8] = top_right_corner;
        lab[k][9] = 32;
        lab[k][10] = top_left_corner;
        lab[k][11] = horizontal_wall;
        lab[k][12] = horizontal_wall;
        lab[k][13] = top_right_corner;
        lab[k][14] = 32;
        lab[k][15] = 32;
        lab[k][16] = down_left_corner;
        for(int i = 17; i <= 21; i++) lab[k][i] = horizontal_wall;
        lab[k][22] = down_right_corner;
        lab[k][23] = 32;
        lab[k][24] = 32;
        lab[k][25] = vertical_wall;
        lab[k][26] = 32;
        lab[k][27] = vertical_wall;
        lab[k][28] = 32;
        lab[k][29] = point;
        lab[k][30] = 32;
        lab[k][31] = 32;
        lab[k][32] = vertical_wall;
        for(int i = 33; i <= 40; i++) lab[k][i] = 32;
        lab[k][41] = vertical_wall;
        lab[k][42] = 32;
        lab[k][43] = point;
        lab[k][44] = down_left_corner;
        lab[k][45] = down_right_corner;
        lab[k][46] = point;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;
    // k = 21
        lab[k][0] = vertical_wall;
        lab[k][1] = 32;
        lab[k][2] = point;
        lab[k][3] = vertical_wall;
        for(int i = 4; i <= 7; i++) lab[k][i] = 32;
        lab[k][8] = vertical_wall;
        lab[k][9] = point;
        lab[k][10] = vertical_wall;
        lab[k][11] = 32;
        lab[k][12] = 32;
        lab[k][13] = vertical_wall;
        for(int i = 14; i <= 24; i += 2) lab[k][i] = 32;
        for(int i = 15; i <= 23; i += 2) lab[k][i] = point;
        lab[k][25] = down_left_corner;
        lab[k][26] = horizontal_wall;
        lab[k][27] = down_right_corner;
        lab[k][28] = 32;
        lab[k][29] = 32;
        lab[k][30] = point;
        lab[k][31] = 32;
        lab[k][32] = down_left_corner;
        for(int i = 33; i <= 40; i++) lab[k][i] = horizontal_wall;
        lab[k][41] = down_right_corner;
        for(int i = 42; i <= 44; i++) lab[k][i] = 32;
        lab[k][45] = point;
        lab[k][46] = 32;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;
    // k = 22
        lab[k][0] = vertical_wall;
        lab[k][1] = 32;
        lab[k][2] = 32;
        lab[k][3] = vertical_wall;
        for(int i = 4; i <= 7; i++) lab[k][i] = 32;
        lab[k][8] = vertical_wall;
        lab[k][9] = 32;
        lab[k][10] = down_left_corner;
        lab[k][11] = horizontal_wall;
        lab[k][12] = horizontal_wall;
        lab[k][13] = down_right_corner;
        lab[k][14] = 32;
        lab[k][15] = top_left_corner;
        lab[k][16] = horizontal_wall;
        lab[k][17] = horizontal_wall;
        lab[k][18] = top_right_corner;
        lab[k][19] = 32;
        for(int i = 20; i <= 42; i += 2) lab[k][i] = 32;
        for(int i = 21; i <= 43; i += 2) lab[k][i] = point;
        lab[k][44] = top_left_corner;
        lab[k][45] = top_right_corner;
        lab[k][46] = point;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;
    // k = 23
        lab[k][0] = vertical_wall;
        lab[k][1] = point;
        lab[k][2] = 32;
        lab[k][3] = vertical_wall;
        for(int i = 4; i <= 7; i++) lab[k][i] = 32;
        lab[k][8] = vertical_wall;
        for(int i = 9; i <= 13; i += 2) lab[k][i] = point;
        for(int i = 10; i <= 14; i += 2) lab[k][i] = 32;
        lab[k][15] = vertical_wall;
        lab[k][16] = 32;
        lab[k][17] = 32;
        lab[k][18] = vertical_wall;
        lab[k][19] = point;
        lab[k][20] = top_left_corner;
        for(int i = 21; i <= 29; i++) lab[k][i] = horizontal_wall;
        lab[k][30] = top_right_corner;
        lab[k][31] = 32;
        lab[k][32] = 32;
        lab[k][33] = top_left_corner;
        for(int i = 34; i <= 37; i++) lab[k][i] = horizontal_wall;
        lab[k][38] = top_right_corner;
        lab[k][39] = 32;
        lab[k][40] = 32;
        lab[k][41] = top_left_corner;
        lab[k][42] = horizontal_wall;
        lab[k][43] = horizontal_wall;
        lab[k][44] = down_right_corner;
        lab[k][45] = vertical_wall;
        lab[k][46] = 32;
        lab[k][47] = point;
        lab[k][48] = vertical_wall;

        k++;
    // k = 24
        lab[k][0] = vertical_wall;
        lab[k][1] = 32;
        lab[k][2] = point;
        lab[k][3] = down_left_corner;
        for(int i = 4; i <= 7; i++) lab[k][i] = horizontal_wall;
        lab[k][8] = down_right_corner;
        for(int i = 9; i <= 14; i++) lab[k][i] = 32;
        lab[k][15] = down_left_corner;
        lab[k][16] = horizontal_wall;
        lab[k][17] = horizontal_wall;
        lab[k][18] = down_right_corner;
        lab[k][19] = 32;
        lab[k][20] = vertical_wall;
        for(int i = 21; i <= 29; i++) lab[k][i] = 32;
        lab[k][30] = vertical_wall;
        lab[k][31] = 32;
        lab[k][32] = 32;
        lab[k][33] = down_left_corner;
        for(int i = 34; i <= 37; i++) lab[k][i] = horizontal_wall;
        lab[k][38] = down_right_corner;
        lab[k][39] = 32;
        lab[k][40] = 32;
        lab[k][41] = down_left_corner;
        for(int i = 42; i <= 44; i++) lab[k][i] = horizontal_wall;
        lab[k][45] = down_right_corner;
        lab[k][46] = point;
        lab[k][47] = 32;
        lab[k][48] = vertical_wall;

        k++;
    // k = 25
        lab[k][0] = vertical_wall;
        lab[k][1] = 32;
        for(int i = 2; i <= 18; i += 2) lab[k][i] = 32;
        for(int i = 3; i <= 19; i += 2) lab[k][i] = point;
        lab[k][20] = vertical_wall;
        for(int i = 21; i<= 29; i++) lab[k][i] = 32;
        lab[k][30] = vertical_wall;
        for(int i = 31; i <= 47; i += 2) lab[k][i] = 32;
        for(int i = 32; i <= 46; i += 2) lab[k][i] = point;
        lab[k][48] = vertical_wall;

        k++;
    // k = 26
        lab[k][0] = down_left_corner;
        for(int i = 1; i <= 19; i++) lab[k][i] = horizontal_wall;
        lab[k][20] = down_right_corner;
        for(int i = 21; i<= 29; i++) lab[k][i] = 32;
        lab[k][30] = down_left_corner;
        for(int i = 31; i <= 47; i++) lab[k][i] = horizontal_wall;
        lab[k][48] = down_right_corner;
}


/*cout << "          10   15   20   25   30   35   40      48" << endl;
cout << "   0123456789012345678901234567890123456789012345678 --> 48" << endl;
cout << "   ╔═══════════════════╗         ╔═════════════════╗ 0   " << endl;
cout << "   ║  • • • • • • • • •║         ║• • •¥• • • • • •║ 1" << endl;
cout << "   ║• ╔══════╗■╔═════╗ ║         ║ ╔═════╗  ╔════╗ ║ 2" << endl;
cout << "   ║  ╚══════╝ ║     ║•╚═════════╝ ║     ║• ║    ║•║ 3" << endl;
cout << "   ║• • • • • •║     ║• • • • • • •║     ║ •║    ║ ║ 4" << endl;
cout << "   ║  ╔═════╗  ╚═════╝ ╔════╗  ╔═══╝     ║• ║    ║•║ 5" << endl;
cout << "   ║• ╚═╗ ╔═╝ • • • • •║    ║  ╚═════════╝ •╚════╝ ║ 6" << endl;
cout << "   ║  • ║ ║ • ╔══╗ ╔═╗ ║    ║ • • • • • • • • • • •║ 7" << endl;         //205 ═
cout << "   ║•   ╚═╝ ╔═╝  ║•║ ║ ╚════╝  ╔════╗  ╔════════╗¥ ║ 8" << endl;         //186 ║
cout << "   ║ • • • •║    ║ ║ ║• • • • •║    ║• ║        ║• ║ 9" << endl;         //201 ╔
cout << "   ║•╔════╝ ║    ║•╚═╝ ╔═╗  ╔══╝    ║  ╚════════╝  ║ 10" << endl;         //187 ╗
cout << "   ║ • • • •║    ║ • • ║ ║ •╚══╗    ║ •¥• • • • • •║ 11" << endl;          //200 ╚
cout << "   ╚══════╗¥║    ╚═════╝ ║ • • ║    ║ ╔═══╗ ╔══════╝ 12" << endl;           //188 ╝
cout << "          ║•║            ║ ╔═╗ ╚════╝ ║   ║ ║        13" << endl;
cout << "   ╔══════╝ ╚════════════╝•║ ║ • • • •║   ║ ╚══════╗ 14" << endl;
cout << "   ║ • • • • • • • • • • • ║ ║• ╔══╗  ╚═══╝• • • • ║ 15" << endl;
cout << "   ║  ╔══════════╗ ╔═════╗ ╚═╝  ║  ║• • • • • •╔╗  ║ 16" << endl;
cout << "   ║• ║          ║•║     ║ • • •╚══╝  ╔═════╗  ║║ •║ 17" << endl;
cout << "   ║  ╚══════════╝ ║     ║  ╔═╗ • • • ║     ║• ║║• ║ 18" << endl;
cout << "   ║ •¥• • • • • • ║     ║• ║ ║  ¥ ╔══╝     ║  ║║ •║ 19" << endl;
cout << "   ║  ╔════╗ ╔══╗  ╚═════╝  ║ ║ •  ║        ║ •╚╝• ║ 20" << endl;
cout << "   ║ •║    ║•║  ║ • • • • • ╚═╝  • ╚════════╝   •  ║ 21" << endl;
cout << "   ║  ║    ║ ╚══╝ ╔══╗  • • • • • • •¥• • • • •╔╗• ║ 22" << endl;
cout << "   ║• ║    ║• • • ║  ║•╔═════════╗  ╔════╗  ╔══╝║ •║ 23" << endl;
cout << "   ║ •╚════╝   ¥  ╚══╝ ║         ║  ╚════╝  ╚═══╝• ║ 24" << endl;
cout << "   ║  • • • • • • • • •║         ║ •¥• • • • • • • ║ 25" << endl;
cout << "   ╚═══════════════════╝         ╚═════════════════╝ 26"<<endl;
cout << "   0123456789012345678901234567890123456789012345678 --> 48" << endl;
cout << "            10        20        30        40      48"<<endl;*/

struct pos enMovement(struct pos nemico, struct pos player){


    switch(nemico.direction){
                ///-----------------------Alto---------------------------///
                    case alto:
                        if(lab[nemico.y-1][nemico.x] == 32 || lab[nemico.y-1][nemico.x] == point || lab[nemico.y-1][nemico.x] == cube || lab[nemico.y-1][nemico.x] == en){

                            gotoxy(nemico.x, nemico.y+offset);
                            cout << char(ball[nemico.y][nemico.x]);
                            lab[nemico.y][nemico.x] = ball[nemico.y][nemico.x];
                            nemico.y--;
                            gotoxy(nemico.x, nemico.y+offset);
                            //lab[nemico.y][nemico.x] = en;
                            cout << char(en);


                        }else{
                               nemico.direction = rand()%2;
                               if(nemico.direction == 0){
                                    if(lab[nemico.y][nemico.x+1] == 32 || lab[nemico.y][nemico.x+1] == point || lab[nemico.y][nemico.x+1] == cube || lab[nemico.y][nemico.x+1] == en){
                                        nemico.direction = destra;
                                    }else{
                                        nemico.direction = sinistra;
                                    }
                               }else if(nemico.direction == 1){
                                    if(lab[nemico.y][nemico.x-1] == 32 || lab[nemico.y][nemico.x-1] == point || lab[nemico.y][nemico.x-1] == cube || lab[nemico.y][nemico.x-1] == en){
                                        nemico.direction = sinistra;
                                    }else{
                                        nemico.direction = destra;
                                    }
                               }
                        }
                        break;

                ///------------------------------Basso-----------------------///
                    case basso:
                        if(lab[nemico.y+1][nemico.x] == 32 || lab[nemico.y+1][nemico.x] == point || lab[nemico.y+1][nemico.x] == cube || lab[nemico.y+1][nemico.x] == en){

                            gotoxy(nemico.x, nemico.y+offset);
                            cout << char(ball[nemico.y][nemico.x]);
                            lab[nemico.y][nemico.x] = ball[nemico.y][nemico.x];
                            nemico.y++;
                            gotoxy(nemico.x, nemico.y+offset);
                            //lab[nemico.y][nemico.x] = en;
                            cout << char(en);

                        }else{
                               nemico.direction = rand()%2;
                               if(nemico.direction == 0){
                                    if(lab[nemico.y][nemico.x+1] == 32 || lab[nemico.y][nemico.x+1] == point || lab[nemico.y][nemico.x+1] == cube || lab[nemico.y][nemico.x+1] == en){
                                        nemico.direction = destra;
                                    }else{
                                        nemico.direction = sinistra;
                                    }
                               }else if(nemico.direction == 1){
                                    if(lab[nemico.y][nemico.x-1] == 32 || lab[nemico.y][nemico.x-1] == point || lab[nemico.y][nemico.x-1] == cube || lab[nemico.y][nemico.x-1] == en){
                                        nemico.direction = sinistra;
                                    }else{
                                        nemico.direction = destra;
                                    }
                               }
                        }
                        break;

                ///-------------------------Destra------------------------///
                    case destra:
                        if(lab[nemico.y][nemico.x+1] == 32 || lab[nemico.y][nemico.x+1] == point || lab[nemico.y][nemico.x+1] == cube || lab[nemico.y-1][nemico.x] == en){

                            gotoxy(nemico.x, nemico.y+offset);
                            cout << char(ball[nemico.y][nemico.x]);
                            lab[nemico.y][nemico.x] = ball[nemico.y][nemico.x];
                            nemico.x++;
                            gotoxy(nemico.x, nemico.y+offset);
                            //lab[nemico.y][nemico.x] = en;
                            cout << char(en);

                        }else{
                               nemico.direction = rand()%2;
                               if(nemico.direction == 0){
                                    if(lab[nemico.y-1][nemico.x] == 32 || lab[nemico.y-1][nemico.x] == point || lab[nemico.y-1][nemico.x] == cube || lab[nemico.y-1][nemico.x] == en){
                                        nemico.direction = alto;
                                    }else{
                                        nemico.direction = basso;
                                    }
                               }else if(nemico.direction == 1){
                                    if(lab[nemico.y+1][nemico.x] == 32 || lab[nemico.y+1][nemico.x] == point || lab[nemico.y+1][nemico.x] == cube || lab[nemico.y+1][nemico.x] == en){
                                        nemico.direction = basso;
                                    }else{
                                        nemico.direction = alto;
                                    }
                               }
                        }
                        break;
                ///-----------------------------Sinistra----------------------///
                    case sinistra:
                        if(lab[nemico.y][nemico.x-1] == 32 || lab[nemico.y][nemico.x-1] == point || lab[nemico.y][nemico.x-1] == cube || lab[nemico.y][nemico.x-1] == en){

                            gotoxy(nemico.x, nemico.y+offset);
                            cout << char(ball[nemico.y][nemico.x]);
                            lab[nemico.y][nemico.x] = ball[nemico.y][nemico.x];
                            nemico.x--;
                            gotoxy(nemico.x, nemico.y+offset);
                            //lab[nemico.y][nemico.x] = en;
                            cout << char(en);

                        }else {

                            //do{
                               nemico.direction = rand()%2;
                               if(nemico.direction == 0){
                                    if(lab[nemico.y-1][nemico.x] == 32 || lab[nemico.y-1][nemico.x] == point || lab[nemico.y-1][nemico.x] == cube || lab[nemico.y-1][nemico.x] == en){
                                        nemico.direction = alto;
                                    }else{
                                        nemico.direction = basso;
                                    }
                               }else if(nemico.direction == 1){
                                    if(lab[nemico.y+1][nemico.x] == 32 || lab[nemico.y+1][nemico.x] == point || lab[nemico.y+1][nemico.x] == cube || lab[nemico.y+1][nemico.x] == en){
                                        nemico.direction = basso;
                                    }else{
                                        nemico.direction = alto;
                                    }
                               }

                        }
                        break;
                }   // FINE SWITCH

                if((nemico.x - player.x == 1 || nemico.x - player.x == -1) && nemico.y - player.y == 0){
                    gameOver = true;
                }
                if((nemico.y - player.y == 1 || nemico.y - player.y == -1) && nemico.x - player.x == 0){
                    gameOver = true;
                }
                return nemico;
}
