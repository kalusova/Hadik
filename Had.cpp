// C program to build the complete
// snake game


//std::cout << RED << "hello world" << RESET << std::endl;



#include "Had.h"

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

// Function to generate the fruit
// within the boundary
void Had::setup(){
    gameover = 0;
    x = height / 2;
    y = width / 2;

    fruitx = rand() % (width-2)+1;
    fruity = rand() % (height-2)+1;
    score = 0;
}

// Function to draw the boundaries
std::string Had::draw(){
    naplneniePola();

    std::string plocha = "";
    for (int k = 0; k < height; ++k) {
        for (int l = 0; l < width; ++l) {
            plocha += hraciaPlocha[l][k];
        }
        plocha += "\n";
    }
    plocha += "Skore je: ";
    plocha += std::to_string(score);
    plocha += "\n";
    plocha += "press X to quit the game\n";
    return plocha + "\n";
}

void Had::naplneniePola(){
    int i, j;
    system("clear");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == width - 1
                || j == 0
                || j == height - 1) {
                hraciaPlocha[i][j] = "#";
            } else {
                if (i == x && j == y)
                    hraciaPlocha[i][j] = "0"; // PREROBIT NA SIPKU
                else if (i == fruitx
                         && j == fruity)
                    hraciaPlocha[i][j] = "?";
                else
                    hraciaPlocha[i][j] = " ";
            }
        }
    }
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