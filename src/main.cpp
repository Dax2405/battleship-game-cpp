#include <iostream>
#include <unistd.h> //Library to use sleep function in loops
#include <random>
#ifdef _WIN32
#include <conio.h>
int readchar() {
    return _getch();  // Get a character input on Windows
}
#else
#include <ncurses.h>
int readchar() {
    initscr();            // Start ncurses mode
    noecho();             // Don't echo input characters
    cbreak();             // Disable line buffering

    int ch = getch();     // Get a character input
    endwin();
    return ch;
}
#endif


using namespace std;

/*
    * 0 -> Player 1
    * 1 -> Player 2
    * 0[index] -> Player 1's screen
    * 2[index] -> Player 2's screen
    * ship[0] -> Player 1's ships
    * ship[1] -> Player 2's ships
    * ship[0][0] -> Player 1's first ship
    * ship[1][0] -> Player 2's second ship
    * 0 -> horizontal
    * 1 -> vertical
    * 0 -> x
    * 1 -> y
 */




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

const int WIDTH = 30;
const int HEIGHT = 10;
const int HALF_WIDTH = WIDTH / 2;
const int HALF_HEIGHT = HEIGHT / 2;
const int SHIP_SIZE = 5;
const int SHIP_QUANTITY = 3;
const string EMPTY = " ";
const string HORIZONTAL = "-";
const string VERTICAL = "|";
const string CORNER = "+";
const string ATTACK = "X";


const string SHIP_L_H = GREEN + "\\" + RESET;
const string SHIP_M_H = GREEN + "_" + RESET;
const string SHIP_R_H = GREEN + "/" + RESET;
const string SHIP_M_V = GREEN + "|" + RESET;
const string SHIP_L_H_R = RED + "\\" + RESET;
const string SHIP_M_H_R = RED + "_" + RESET;
const string SHIP_R_H_R = RED + "/" + RESET;
const string SHIP_M_V_R = RED + "|" + RESET;



// Main array
string screens[4][HEIGHT][WIDTH];
//Ships array
int ships[2][SHIP_QUANTITY][SHIP_SIZE][2];
// PLayer Structure
struct Player {
    string name;
    int score = 0;
};

int randomNumber(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

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
            if(screens[screen][height][width] == VERTICAL ||
                screens[screen][height][width] == HORIZONTAL ||
                screens[screen][height][width] == CORNER){
                cout << RED << screens[screen][height][width] << RESET;// << "["<< screen<< "]" << "[" << height << "]" << "[" << width <<"] --> for debugging
            } else {
                cout << screens[screen][height][width];
            }
        }

        cout << endl;
    }
}

bool verifyAviavility(int x, int y, int player) {
    for (int i = 0; i < SHIP_QUANTITY; i++) {
        for (int j = 0; j < SHIP_SIZE; j++) {
            if (ships[player][i][j][0] == x && ships[player][i][j][1] == y) {
                return false;
            }
        }
    }
    return true;
}
void addShipCoordinates(int x, int y, int player, int ship, int orientation) {
    if (orientation == 0) {
        for (int i = 0; i < SHIP_SIZE; i++) {
            ships[player][ship][i][0] = x + i;
            ships[player][ship][i][1] = y;
        }
    } else {
        for (int i = 0; i < SHIP_SIZE; i++) {
            ships[player][ship][i][0] = x;
            ships[player][ship][i][1] = y + i;
        }
    }

}


void addShipToScreen(int x, int y, int orientation, int player) {
    int screen;
    if (player == 0 ) {
        screen = 0;
    } else {
        screen = 2;
    }

    if (orientation == 0) {

        screens[screen][y][x] = SHIP_L_H;
        screens[screen][y][x + 1] = SHIP_M_H;
        screens[screen][y][x + 2] = SHIP_M_H;
        screens[screen][y][x + 3] = SHIP_M_H;
        screens[screen][y][x + 4] = SHIP_R_H;
    } else {
        screens[screen][y][x] = SHIP_L_H;
        screens[screen][y + 1][x] = SHIP_M_V;
        screens[screen][y + 2][x] = SHIP_M_V;
        screens[screen][y + 3][x] = SHIP_M_V;
        screens[screen][y + 4][x] = SHIP_R_H;
    }
}

void deleteShip(int x, int y, int orientation, int player) {
    int screen;
    if (player == 0) {
        screen = 0;
    } else {
        screen = 2;
    }
    if (orientation == 0) {
        screens[screen][y][x] = EMPTY;
        screens[screen][y][x + 1] = EMPTY;
        screens[screen][y][x + 2] = EMPTY;
        screens[screen][y][x + 3] = EMPTY;
        screens[screen][y][x + 4] = EMPTY;
    } else {
        screens[screen][y][x] = EMPTY;
        screens[screen][y + 1][x] = EMPTY;
        screens[screen][y + 2][x] = EMPTY;
        screens[screen][y + 3][x] = EMPTY;
        screens[screen][y + 4][x] = EMPTY;
    }
}
void moveShip(int x, int y, int prevOrientation,  int player, int op, int ship) {
    deleteShip(x, y, prevOrientation, player);
    if (op == 101) {
        if (prevOrientation == 0) {
            addShipToScreen(x, y, 1, player);
            addShipCoordinates(x, y, player, ship, 1);
        }else {
            addShipToScreen(x, y, 0, player);
            addShipCoordinates(x, y, player, ship, 0);
        }
    }else {
        if (op == 119) {
            addShipToScreen(x, y - 1, prevOrientation, player);
            addShipCoordinates(x, y-1, player, ship, prevOrientation);
        }else if (op == 115) {
            addShipToScreen(x, y + 1, prevOrientation, player);
            addShipCoordinates(x, y+1, player, ship, prevOrientation);
        }else if (op == 97) {
            addShipToScreen(x - 1, y, prevOrientation, player);
            addShipCoordinates(x-1, y, player, ship, prevOrientation);
        }else if (op == 100) {
            addShipToScreen(x + 1, y, prevOrientation, player);
            addShipCoordinates(x+1, y, player, ship, prevOrientation);
        }
    }
}


void addShips(int player, Player playing) {
    int screen;
    if (player == 0) {
        screen = 0;
    }else {
        screen = 2;
    }
    for (int i = 0; i < SHIP_QUANTITY; i++) {
        int x = randomNumber(1, WIDTH - 2);
        int y = randomNumber(1, HEIGHT - 2);
        int orientation = 0;
        if (verifyAviavility(x, y, player)) {
            int op;
            addShipToScreen(x, y, orientation, player);
            addShipCoordinates(x, y, player, i, orientation);
            drawScreen(screen);
            cout << MAGENTA << playing.name << RESET << " press enter to confirm the position of the ship"  << endl;
            do {
                op = readchar();
                switch (op) {
                    case 119:

                        moveShip(x, y, orientation, player, 119, i);
                        y--;
                        break;
                    case 115:
                        moveShip(x, y, orientation, player, 115, i);
                        y++;
                        break;
                    case 97:
                        moveShip(x, y, orientation, player, 97, i);
                        x--;
                        break;
                    case 100:
                        moveShip(x, y, orientation, player, 100, i);
                        x++;
                        break;
                    case 101:
                        moveShip(x, y, orientation, player, 101, i);
                        if (orientation == 0) {
                            orientation = 1;
                        }else {
                            orientation = 0;
                        }
                        break;
                    default:
                        system("exit");
                }
                drawScreen(screen);
                cout << MAGENTA << playing.name << RESET << " press enter to confirm the position of the ship"  << endl;
                sleep(0.5);
                system("clear");
                drawScreen(screen);
                cout << MAGENTA << playing.name << RESET << " press enter to confirm the position of the ship"  << endl;

            }while(op != 10);
        } else {
            i--;
        }
    }



}

void deleteShip(int player, int ship) {
    int screen;
    if (player == 0) {
        screen = 0;
    }else {
        screen = 2;
    }
    for (int i = 0; i < SHIP_SIZE; i++) {
        screens[screen][ships[player][ship][i][1]][ships[player][ship][i][0]] = EMPTY;
    }
    for (int i = 0; i < SHIP_SIZE; i++) {
        ships[player][ship][i][0] = 0;
        ships[player][ship][i][1] = 0;
    }
}
bool attack(int player, Player playing) {
    int screen;
    if (player == 0) {
        screen = 1;
    }else {
        screen = 3;
    }
    int x = WIDTH/2, y = HEIGHT/2;
    int op;
    screens[screen][y][x] = ATTACK;
    drawScreen(screen);
    do {
        op = readchar();
        switch (op) {
            case 119:
                screens[screen][y][x] = EMPTY;
                y--;
                screens[screen][y][x] = ATTACK;
                break;
            case 115:
                screens[screen][y][x] = EMPTY;
                y++;
                screens[screen][y][x] = ATTACK;
                break;
            case 97:
                screens[screen][y][x] = EMPTY;
                x--;
                screens[screen][y][x] = ATTACK;
                break;
            case 100:
                screens[screen][y][x] = EMPTY;
                x++;
                screens[screen][y][x] = ATTACK;
                break;
            default:
                system("exit");
        }
        drawScreen(screen);
        cout << MAGENTA << playing.name << RESET << " press enter to confirm the position of the ship"  << endl;
        sleep(0.5);
        system("clear");
        drawScreen(screen);
        cout << MAGENTA << playing.name << RESET << " press enter to confirm the position of the ship"  << endl;

    }while(op != 10);
    screens[screen][y][x] = EMPTY;
    if (player == 0) {
        for (int i = 0; i < SHIP_QUANTITY; i++) {
            for (int j = 0; j < SHIP_SIZE; j++) {
                if (ships[1][i][j][0] == x && ships[1][i][j][1] == y) {
                    deleteShip(player, i);
                    return true;
                }
            }
        }
    }else {
        for (int i = 0; i < SHIP_QUANTITY; i++) {
            for (int j = 0; j < SHIP_SIZE; j++) {
                if (ships[0][i][j][0] == x && ships[0][i][j][1] == y) {
                    deleteShip(player, i);
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    fillScreens();
    drawMargins();
    Player player1;
    Player player2;
    cout << "Welcome to Battleship" << endl;
    cout << "Press any key to start" << endl;
    sleep(2);
    readchar();
    system("clear");
    cout << CYAN << "Ingresa el nombre del jugador 1: " << RESET;
    cin >> player1.name;
    system("clear");
    cout << MAGENTA << "Ingresa el nombre del jugador 2: " << RESET;
    cin >> player2.name;
    system("clear");
    cout << CYAN <<"Player 1, place your ships" << RESET <<endl;
    addShips(0, player1);
    system("clear");
    cout << MAGENTA << "Player 2, place your ships" << RESET <<endl;
    addShips(1, player2);
    int player = 0;
    system("clear");
    do {
        cout << player1.name << " = " << player1.score <<"     " << player2.name << " = " << player2.score << endl;
        if(player == 0) {
            cout << CYAN << player1.name << " turn" << RESET << endl;
            if (attack(player, player1)) {
                player1.score++;
            }
            drawScreen(2);
            player = 1;
        }else {
            cout << MAGENTA << player2.name << " turn" << RESET << endl;
            if (attack(player, player2)) {
                player2.score++;
            }
            player = 0;
        }
        cout << player1.name << " = " << player1.score <<"     " << player2.name << " = " << player2.score << endl;


    }while(player1.score < SHIP_QUANTITY || player2.score < SHIP_QUANTITY);
    if (player1.score == SHIP_QUANTITY) {
        cout << CYAN << player1.name << " wins" << RESET << endl;
    }else {
        cout << MAGENTA << player2.name << " wins" << RESET << endl;
    }

    return 0;
}
