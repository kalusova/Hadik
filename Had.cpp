// C program to build the complete
// snake game
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

//std::cout << RED << "hello world" << RESET << std::endl;

// Function to generate the fruit
// within the boundary
class Had{
private:
    int height = 20, width = 20;
    int x, y, fruitx, fruity, flag;
public:
    int gameover, score;
    Had();
    void start();
    void setup();
    void draw();
    void input();
    void logic();
};

Had::Had(){
}

void Had::start(){
    int m, n;

    // Generate boundary
    setup();

    // Until the game is over
    while (!gameover) {

        // Function Call
        draw();
        input();
        logic();
    }
}

void Had::setup()
{
    gameover = 0;

    // Stores height and width
    x = height / 2;
    y = width / 2;
    label1:
    fruitx = rand() % 20;
    if (fruitx == 0)
        goto label1;
    label2:
    fruity = rand() % 20;
    if (fruity == 0)
        goto label2;
    score = 0;
}

// Function to draw the boundaries
void Had::draw()
{
    int i, j;
    system("clear");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == width - 1
                || j == 0
                || j == height - 1) {
                printf("#");
            }
            else {
                if (i == x && j == y)
                    printf("0");
                else if (i == fruitx
                         && j == fruity)
                    printf("*");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }

    // Print the score after the
    // game ends
    printf("score = %d", score);
    printf("\n");
    printf("press X to quit the game\n");
}

// Function to take the input
void Had::input()
{
    if (1) { //??????????????????????????????????????
        switch (getchar()) {
            case 'a':
                flag = 1;
                break;
            case 's':
                flag = 2;
                break;
            case 'd':
                flag = 3;
                break;
            case 'w':
                flag = 4;
                break;
            case 'x':
                gameover = 1;
                break;
        }
    }
}

// Function for the logic behind
// each movement
void Had::logic()
{
    sleep(0.01);
    switch (flag) {
        case 1:
            y--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y++;
            break;
        case 4:
            x--;
            break;
        default:
            break;
    }

    // If the game is over
    if (x < 0 || x > height
        || y < 0 || y > width)
        gameover = 1;

    // If snake reaches the fruit
    // then update the score
    if (x == fruitx && y == fruity) {
        label3:
        fruitx = rand() % 20;
        if (fruitx == 0)
            goto label3;

        // After eating the above fruit
        // generate new fruit
        label4:
        fruity = rand() % 20;
        if (fruity == 0)
            goto label4;
        score += 10;
    }
}