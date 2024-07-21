#include <iostream>
#include <unistd.h> //Library to use sleep function in loops
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
int main() {
    fillScreens();
    drawMargins();
    while (true) {
        drawScreen(1);
        sleep(1);
        system("clear");
    }
    return 0;
}
