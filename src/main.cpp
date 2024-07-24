#include <iostream>
#include <unistd.h> //Library to use sleep function in loops
#include <windows.h>
#include <thread>
using namespace std;

// ANSI escape codes for colors
const string RESET = "\033[0m";
const string BLACK = "\033[30m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

const int WIDTH = 70;
const int HEIGHT = 40;
const string EMPTY = " ";
const string HORIZONTAL = "-";
const string VERTICAL = "|";
const string CORNER = "+";
const int lengthB=80;

// Main array
string screens[4][HEIGHT][WIDTH];

// Function to fill the screens with empty spaces
void fillScreens() {
    for (int screen = 0; screen < 4; screen++) {
        for (int height = 1; height < HEIGHT - 1; height++) {
            for (int width = 1; width < WIDTH - 1; width++) {
                screens[screen][height][width] = EMPTY;
            }
        }
    }
}

// Function to draw the margins of the screens using const variables
void drawMargins() {
    for (int screen = 0; screen < 4; screen++) {
        screens[screen][0][0] = CORNER;
        screens[screen][0][WIDTH - 1] = CORNER;
        screens[screen][HEIGHT - 1][0] = CORNER;
        screens[screen][HEIGHT - 1][WIDTH - 1] = CORNER;
        for (int width = 1; width < WIDTH - 1; width++) {
            screens[screen][0][width] = HORIZONTAL;
            screens[screen][HEIGHT - 1][width] = HORIZONTAL;
        }
        for (int height = 1; height < HEIGHT - 1; height++) {
            screens[screen][height][0] = VERTICAL;
            screens[screen][height][WIDTH - 1] = VERTICAL;
        }
    }
}
// Function to draw the screen by printing the content of the screens array
void drawScreen(int screen) {
    for (int height = 0; height < HEIGHT; height++) {
        for (int width = 0; width < WIDTH; width++) {
            // Print the margins with colors and the rest of the screen with the content of the screens array
            if(screens[screen][height][width] == VERTICAL || screens[screen][height][width] == HORIZONTAL || screens[screen][height][width] == CORNER){
                cout << RED << screens[screen][height][width] << RESET;// << "["<< screen<< "]" << "[" << height << "]" << "[" << width <<"] --> for debugging
            } else {
                cout << screens[screen][height][width];
            }
        }

        cout << endl;
    }
}

void loadingBar() {
    char x=35;
    int contador=0;
    cout<<"CARGANDO"<<endl;
    do {
        for(int i=0; i<=contador; i++) {
            cout<<x;
        }
        Sleep(100);
        contador++;

        if(contador!=50) {
            system("cls");
        }

    }while(contador!=50);
cout<<endl;
}

void start() {
    string arr[15]={
        " ",
        " ",
        "             |>   |>   |> ",
        "             )_)  )_)  )_) ",
        "            )___))___))___) ",
        "            )____)____)_____) ",
        "         _____|____|____|____",
        "--------{_____________________/-------",
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
        "BBBB AAAA  TTTTTT TTTTTT  LL     EEEEEE SSSSS  HH  HH  IIIIII  PPPPPP",
        "B  B A  A    TT     TT    LL     EE     SS     HH  HH    II    PP   P",
        "BBBB AAAA    TT     TT    LL     EEEEE  SSSSS  HHHHHH    II    PPPPP",
        "B  B A  A    TT     TT    LL     EE        SS  HH  HH    II    PP",
        "BBB  A  A    TT     TT    LLLLLL EEEEEE SSSSS  HH  HH  IIIIII  PP",
    };
    for(int i = 0; i <20; i++) {
        for(int j = 0; j <90; j++) {
            if(i == 0 || i == 19 || j == 0 || j == 89) {
                cout << "*";
            } else {
                int posX = i - 4;
                int posY = j - 14;
                if(posX >= 0 && posX < 15 && posY >= 0 && posY < arr[posX].size()) {
                    cout << arr[posX][posY];
                } else {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}





void finish (){
    cout<<"GGGGGGG    AAAAAA  MM         MM  EEEEE         OOOOOOO V           V  EEEEE RRRRRR      "<<endl;
    cout<<"GG    GG AA    AA MM  M   M  MM  EE            OO   OO VV         VV  EE    RR   RR   "<<endl;
    cout<<"GG       AA    AA MM    M    MM  EE            OO   OO  VV       VV   EE    RR   RR "<<endl;
    cout<<"GG       AAAAAAAA MM         MM  EEEEE         OO   OO   VV     VV    EEEEE RRRRRRR    "<<endl;
    cout<<"GG   GGG AA    AA MM         MM  EE            OO   OO    VV   VV     EE    RR   RR    "<<endl;
    cout<<"GG    GG AA    AA MM         MM  EE            OO   OO     VV VV      EE    RR    RR "<<endl;
    cout<<"GGGGGG   AA    AA MM         MM  EEEEE         OOOOOOO      VVV       EEEEE RR     RR   "<<endl;
}

string Title(){


}

int main() {
    fillScreens();
    drawMargins();
    start();
    loadingBar();
    finish();
    while (true) {
        drawScreen(1);
        sleep(1);
        system("clear");
    }


    return 0;
}
