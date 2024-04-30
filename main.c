#include <stdlib.h>
#include <time.h>

#include "raylib.h"

int DIVIDER = 20;
Font font;

#include "headers/const.h"
#include "headers/structf.h"

int main(){
    //menu choice
    int choice = -1;

    //these could have been global variables too but I decided to make them normal ones
    int SCREEN_WIDTH = 1920;
    int SCREEN_HEIGHT = 1080;
    bool playing = true;

    //topbar with buttons already declared here couse its going to be the same for every one of them
    button topBar[MAXTOP];
    //algorithm with sorting statistics
    algorithm algorithm;

    //set srand seed and init raylib window
    srand(time(NULL));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "cSort");
    ToggleFullscreen();

    //set the fps as the standard fps and set the standard topbar
    SetTargetFPS(STDFPS);
    setTopBar(topBar);

    font = LoadFont("fonts/JetBrainsMono-Bold.ttf");

    //SE
    while(!WindowShouldClose() && choice != 8){

        //see menu function
        choice = menu(&SCREEN_WIDTH, &SCREEN_HEIGHT);

        //set standard algorithm values
        algorithm.comparison = 0;
        algorithm.forCicles = 0;
        algorithm.swaps = 0;
        algorithm.writesMain = 0;
        algorithm.writesSecond = 0;

        //switch on the menu choice
        switch (choice) {
            case 1:
                selectionSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
            case 2:
                shakerSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
            case 3:
                bubbleSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
            case 4:
                gnomeSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
            case 5:
                insertionSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
            case 6:
                oddEvenSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
            case 7:
                badSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
            //8 = quit
            case 9:
                countingSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
            case 10:
                shellSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
            case 11:
                combSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
            case 12:
                settings();
            break;
        }

        //if the user changed the fps during the simulation this resets it to its standard value
        SetTargetFPS(STDFPS);
    }

    UnloadFont(font);

    return 0;
}

//

void setArray(element array[], int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //this function just randomizes the array and sets its color
    int i;
    for (i = 0; i < dim; i++){
        array[i].value = 6+(rand()%((int)(SCREEN_HEIGHT/DIVIDER) * 4/5));
        array[i].color = WHITE;
    
        if (array[i].value < 1)
            array[i].value = 6;   
    }
}

void drawArray(element array[], int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int i;

    for (i = 0; i < dim; i++){
        array[i].Rect = (Rectangle){(float)i*DIVIDER, (float)(SCREEN_HEIGHT-(array[i].value*DIVIDER))+(DIVIDER*2), (float)DIVIDER, (float)array[i].value*DIVIDER};

        //draw the array
        DrawRectangleRec(array[i].Rect, array[i].color);
        DrawRectangle(0, SCREEN_HEIGHT-(DIVIDER*3), SCREEN_WIDTH, DIVIDER*3, BLACK);
    }

    for (i = 0; i < dim; i++){
        array[i].bottomRect = (Rectangle){(float)DIVIDER*i, (float)(SCREEN_HEIGHT-(DIVIDER*3)), (float)DIVIDER, (float)DIVIDER};

        //draw the bottom part of the array
        DrawRectangleRec(array[i].bottomRect, PINK);
        DrawText(TextFormat("%d",array[i].value-5), array[i].bottomRect.x, array[i].bottomRect.y+array[i].bottomRect.width/3, array[i].bottomRect.height/3, BLACK);
    }
}

void swap(int* n1, int* n2){
    //swap 2 numbers using pointers
    int num;

    num = *n1;
    *n1 = *n2;
    *n2 = num;
}

void setMenuRects(menuRect rects[], int SCREEN_WIDTH, menuImages *images){
    //SE
    int i;

    for (i = 0; i < 7; i++){
        rects[i].Rect.x = 100;
        rects[i].Rect.y = (i+1)*100;
        rects[i].Rect.height = 50;
        rects[i].Rect.width = 400;
        rects[i].num = i;
        rects[i].color = DARKGRAY;
    }

    //quit button
    rects[7].Rect.height = 50;
    rects[7].Rect.width = 400;
    rects[7].Rect.x = SCREEN_WIDTH-100-400;
    rects[7].Rect.y = 8*100;
    rects[7].num = 7;
    rects[7].color = DARKGRAY;

    for (i = 8; i < 11; i++){
        rects[i].Rect.height = 50;
        rects[i].Rect.width = 400;
        rects[i].Rect.x = ((float)SCREEN_WIDTH/2)-(rects[i].Rect.width/2);
        rects[i].Rect.y = (i-8+1)*100;
        rects[i].num = i;
        rects[i].color = DARKGRAY;
    }

    rects[11].Rect.height = 50;
    rects[11].Rect.width = 400;
    rects[11].Rect.x = SCREEN_WIDTH-100-400;
    rects[11].Rect.y = 7*100;
    rects[11].num = 7;
    rects[11].color = DARKGRAY;

    for (i = 0; i < ALGS; i++){
        rects[i].texture = images->normalTexture;
    }

    //set text position

    /**/

    rects[0].TextPosition = (Vector2) { rects[0].Rect.x + 30 + 20, rects[0].Rect.y + 2};
    rects[1].TextPosition = (Vector2) { rects[1].Rect.x + 70 + 20, rects[1].Rect.y + 2};
    rects[2].TextPosition = (Vector2) { rects[2].Rect.x + 70 + 20, rects[2].Rect.y + 2};
    rects[3].TextPosition = (Vector2) { rects[3].Rect.x + 80 + 20, rects[3].Rect.y + 2};
    rects[4].TextPosition = (Vector2) { rects[4].Rect.x + 35 + 20, rects[4].Rect.y + 2};
    rects[5].TextPosition = (Vector2) { rects[5].Rect.x + 55 + 20, rects[5].Rect.y + 2};
    rects[6].TextPosition = (Vector2) { rects[6].Rect.x + 100 + 20, rects[6].Rect.y + 2};
    rects[7].TextPosition = (Vector2) { rects[7].Rect.x + 130 + 20, rects[7].Rect.y + 2};
    rects[8].TextPosition = (Vector2) { rects[8].Rect.x + 50 + 20, rects[8].Rect.y + 2};
    rects[9].TextPosition = (Vector2) { rects[9].Rect.x + 80 + 20, rects[9].Rect.y + 2};
    rects[10].TextPosition = (Vector2) { rects[10].Rect.x + 95 + 20, rects[10].Rect.y + 2};
    rects[11].TextPosition = (Vector2) { rects[11].Rect.x + 95 + 20, rects[11].Rect.y + 2};

    /**/
}

int menu(int* SCREEN_WIDTH, int* SCREEN_HEIGHT){
    int choice = -1, i; //choice has by default an impossible value
    menuRect menuRects[ALGS];
    Rectangle mouse;
    menuImages images;

    /**/

    images.clickedImage = LoadImage("images/clickedButton.png");
    images.clickedTexture = LoadTextureFromImage(images.clickedImage);
    UnloadImage(images.clickedImage);

    images.normalImage = LoadImage("images/button.png");
    images.normalTexture = LoadTextureFromImage(images.normalImage);
    UnloadImage(images.normalImage);

    /**/

    setMenuRects(menuRects, *SCREEN_WIDTH, &images);

    mouse.height = 5;
    mouse.width = 5;

    //choice == -1 mean "if you still have not choosen"
    while (!WindowShouldClose() && choice == -1){
        mouse.x = GetMouseX()-2.5;
        mouse.y = GetMouseY()-2.5;

        menuCollisions(menuRects, mouse, &choice, &images);
        catchFullScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

        //draw menu
        BeginDrawing();
            ClearBackground(LIGHTGRAY);

            for (i = 0; i < ALGS; i++)
                DrawTexture(menuRects[i].texture, menuRects[i].Rect.x, menuRects[i].Rect.y, WHITE);
            
            
            DrawTextEx(font,"selectionSort", menuRects[0].TextPosition,menuRects[0].Rect.height-5, 3, menuRects[0].color);
            DrawTextEx(font,"shakerSort", menuRects[1].TextPosition,menuRects[1].Rect.height-5, 3, menuRects[1].color);
            DrawTextEx(font,"bubbleSort", menuRects[2].TextPosition,menuRects[2].Rect.height-5, 3, menuRects[2].color);
            DrawTextEx(font,"gnomeSort", menuRects[3].TextPosition,menuRects[3].Rect.height-5, 3, menuRects[3].color);
            DrawTextEx(font,"insertionSort", menuRects[4].TextPosition,menuRects[4].Rect.height-5, 3, menuRects[4].color);
            DrawTextEx(font,"oddEvenSort", menuRects[5].TextPosition,menuRects[5].Rect.height-5, 3, menuRects[5].color);
            DrawTextEx(font,"BadSort", menuRects[6].TextPosition,menuRects[6].Rect.height-5, 3, menuRects[6].color);
            DrawTextEx(font,"Quit", menuRects[7].TextPosition,menuRects[7].Rect.height-5, 3, menuRects[7].color);
            DrawTextEx(font,"countingSort", menuRects[8].TextPosition,menuRects[8].Rect.height-5, 3, menuRects[8].color);
            DrawTextEx(font,"shellSort", menuRects[9].TextPosition,menuRects[9].Rect.height-5, 3, menuRects[9].color);
            DrawTextEx(font,"combSort", menuRects[10].TextPosition,menuRects[10].Rect.height-5, 3, menuRects[10].color);
            DrawTextEx(font,"Settings", menuRects[11].TextPosition,menuRects[11].Rect.height-5, 3, menuRects[11].color);

        EndDrawing();
    }

    unloadmenu(menuRects, &images);
    return choice;
}

void menuCollisions(menuRect rects[], Rectangle mouse, int *choice, menuImages *images){
    //checks if you clicked on one of the buttons

    int i;

    for (i = 0; i < ALGS; i++){
        if (CheckCollisionRecs(rects[i].Rect, mouse)){
            rects[i].color = BLACK;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                rects[i].texture = images->clickedTexture;

                rects[i].TextPosition.x += 4;
                rects[i].TextPosition.y += 4;
            }else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                *choice = i+1;
                rects[i].texture = images->normalTexture;

                rects[i].TextPosition.x -= 4;
                rects[i].TextPosition.y -= 4;
            }

        }else{
            rects[i].color = DARKGRAY;
        }
    }
}

void catchPlaying(bool *playing, int* fps, button array[]){
    /*
        checks if you pressed space, clicked on the pause button,
        pressed the left/right arrow key or arrow button
        if you did it changes the values
    */

    if (IsKeyPressed(KEY_SPACE)){
        if (*playing){
            *playing = false;
        }else
            *playing = true;
    }

    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)){
        if (IsKeyPressed(KEY_LEFT))
            if (*fps > 80-DIVIDER){*fps -= 80-DIVIDER;}
        if (IsKeyPressed(KEY_RIGHT))
            *fps += 80-DIVIDER;

        SetTargetFPS(*fps);
    }

    if (array[1].active || array[2].active){
        if (array[1].active) {
            if (*fps > 80-DIVIDER)
                *fps -= 80-DIVIDER;
            array[1].active = false;
        }
        if (array[2].active) {*fps += 80-DIVIDER; array[2].active = false;}

        SetTargetFPS(*fps);
    }
}


////* sorting algs (SE)


void selectionSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int i = 0, ii = 0, minIdx = 0, fps = STDFPS;
    bool exit = false;

    bottom bottom;
    side side;
    element array[dim];

    sortingInit(SCREEN_WIDTH, SCREEN_HEIGHT, array, 'S', &bottom, &side);

    for (i = 0; i < dim-1; i++){
        algorithm->forCicles++;
        minIdx = i;

        for (ii = i+1; ii < dim && !WindowShouldClose();){
            if (*playing){
                algorithm->forCicles++;
                if (array[ii].value < array[minIdx].value)
                    minIdx = ii;
                
                algorithm->comparison++;
            }

            betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, ii, bottom, &side, &fps, algorithm, "selectionSort");
            if (IsKeyDown(KEY_ENTER)){
                return;
            }

            if (*playing)
                ii++;
        }

        swap(&array[minIdx].value, &array[i].value);
        algorithm->swaps++;
    }
    
    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void badSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int ii = 0, a = dim, fps = STDFPS;
    bool isSorted = false;

    bottom bottom;
    side side;
    element array[dim];

    sortingInit(SCREEN_WIDTH, SCREEN_HEIGHT, array, 'B', &bottom, &side);

    while (!isSorted){
        algorithm->forCicles++;
        isSorted = true;

        for (ii = 0; ii < a-1 && !WindowShouldClose();){
            if (*playing){
                algorithm->forCicles++;
                if (array[ii].value > array[ii+1].value){
                    swap(&array[ii].value, &array[ii+1].value);
                    ii = 0;
                    isSorted = false;
                    algorithm->swaps++;
                }
                algorithm->comparison++;
                if (ii == 1)
                    if (array[ii].value < array[ii-1].value){
                        swap(&array[ii].value, &array[ii-1].value);
                        ii = 0;
                        isSorted = false;
                        algorithm->swaps++;
                    }

                algorithm->comparison += 2;
            }

            betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, ii, ii, bottom, &side, &fps, algorithm, "badSort");
            if (IsKeyDown(KEY_ENTER)){
                return;
            }

            if (*playing)
                ii++;
        }
    }

    
    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oddEvenSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    bool isSorted = false;
    int i = 0, fps = STDFPS;

    bottom bottom;
    side side;
    element array[dim];

    sortingInit(SCREEN_WIDTH, SCREEN_HEIGHT, array, 'O', &bottom, &side);

    while (!isSorted && !WindowShouldClose()){
        algorithm->forCicles++;

        isSorted = true;

        for (i = 0; i < dim-1 && !WindowShouldClose();){
            if (*playing){
                algorithm->forCicles++;
                if (array[i].value > array[i+1].value){
                    swap(&array[i].value, &array[i+1].value);
                    isSorted = false;
                    algorithm->swaps++;
                }
                algorithm->comparison++;
            }

            betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, i, bottom, &side, &fps, algorithm, "oddEvenSort");
            if (IsKeyDown(KEY_ENTER)){
                return;
            }

            if (*playing)
                i += 2;
        }

        for (i = 1; i < dim-2 && !WindowShouldClose();){
            if (*playing){
                algorithm->forCicles++;
                if (array[i].value > array[i+1].value){
                    swap(&array[i].value, &array[i+1].value);
                    isSorted = false;
                    algorithm->swaps++;
                }

                algorithm->comparison++;
            }

            betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, i, bottom, &side, &fps, algorithm, "oddEvenSort");
            if (IsKeyDown(KEY_ENTER)){
                return;
            }

            if (*playing)
                i += 2;
        }
    }
    
    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void shakerSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int n = dim, start = 0, i, fps = STDFPS, end = n-1;
    bool swapped = true;

    bottom bottom;
    side side;
    element array[dim];

    sortingInit(SCREEN_WIDTH, SCREEN_HEIGHT, array, 'H', &bottom, &side);

    while (swapped && !WindowShouldClose()){
        algorithm->forCicles++;
        swapped = false;

        for (i = start; i < end && !WindowShouldClose();){
            if (*playing){
                algorithm->forCicles++;
                if (array[i].value > array[i+1].value){
                    swap(&array[i].value, &array[i+1].value);
                    swapped = true;
                    algorithm->swaps++;
                }
                algorithm->comparison++;
            }

            betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, i, bottom, &side, &fps, algorithm, "cocktailShakerSort");
            if (IsKeyDown(KEY_ENTER)){
                return;
            }

            if (*playing)
                i++;
        }

        if (!swapped) {break;}
        algorithm->comparison++;

        swapped = false;

        for (i = end; i > start && !WindowShouldClose();){
            if (*playing){
                algorithm->forCicles++;
                if (array[i].value < array[i-1].value){
                    swap(&array[i].value, &array[i-1].value);
                    swapped = true;
                    algorithm->swaps++;
                }
                algorithm->comparison++;
            }

            betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, i, bottom, &side, &fps, algorithm, "cocktailShakerSort");
            if (IsKeyDown(KEY_ENTER)){
                return;
            }

            if (*playing)
                i--;
        }

        start += 1;
    }

    
    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void bubbleSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int ii = 0, a = dim, fps = STDFPS;
    bool isSorted = false;

    bottom bottom;
    side side;
    element array[dim];

    sortingInit(SCREEN_WIDTH, SCREEN_HEIGHT, array, 'B', &bottom, &side);

    while (!isSorted){
        algorithm->forCicles++;
        isSorted = true;

        for (ii = 0; ii < a-1 && !WindowShouldClose();){
            if (*playing){
                algorithm->forCicles++;
                if (array[ii].value > array[ii+1].value){
                    swap(&array[ii].value, &array[ii+1].value);
                    isSorted = false;
                    algorithm->swaps++;
                }
                algorithm->comparison++;
            }

            betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, ii, ii, bottom, &side, &fps, algorithm, "bubbleSort");
            if (IsKeyDown(KEY_ENTER)){
                return;
            }

            if (*playing)
                ii++;
        }

        a--;
    }

    
    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void gnomeSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int index = 1, fps = STDFPS;

    bottom bottom;
    side side;
    element array[dim];

    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, &bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    sortingInit(SCREEN_WIDTH, SCREEN_HEIGHT, array, 'G', &bottom, &side);

    while (!WindowShouldClose() && index < dim){
        if (*playing){
            while (index != 0 && array[index].value < array[index-1].value){
                algorithm->forCicles++;
                swap(&array[index].value, &array[index-1].value);
                index -= 1;
                algorithm->swaps++;
                algorithm->comparison++;
            }

            algorithm->forCicles++;
        }

        betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, index, index, bottom, &side, &fps, algorithm, "gnomeSort");
        if (IsKeyDown(KEY_ENTER)){
            return;
        }

        if (*playing)
            index++;
    }

    
    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void insertionSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int i = 0, ii, fps = STDFPS;
    
    bottom bottom;
    side side;
    element array[dim];

    sortingInit(SCREEN_WIDTH, SCREEN_HEIGHT, array, 'I', &bottom, &side);

    while (!WindowShouldClose() && i < dim) {
        algorithm->forCicles++;
        ii = i;

        while (ii > 0 && array[ii-1].value > array[ii].value && !WindowShouldClose()){
            if (*playing){
                algorithm->forCicles++;
                swap(&array[ii].value, &array[ii-1].value);
                algorithm->swaps++;

                ii--;
                algorithm->comparison++;
            }

            betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, ii, bottom, &side, &fps, algorithm, "insertionSort");
            if (IsKeyDown(KEY_ENTER)){
                return;
            }
        }
        i++;
    }
    
    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void countingSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int max = 0, fps = STDFPS, i;
    int count[dim];

    bottom bottom;
    side side;
    element array[dim], output[dim];

    sortingInit(SCREEN_WIDTH, SCREEN_HEIGHT, array, 'C', &bottom, &side);

    max = array[0].value;

    for (i = 1; i < dim && !WindowShouldClose();){
        if (*playing){
            algorithm->forCicles++;
            if (array[i].value > max)
                max = array[i].value;
            
            algorithm->comparison++;
        }

        betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, i, bottom, &side, &fps, algorithm, "countingSort");
        if (IsKeyDown(KEY_ENTER)){
            return;
        }

        if (*playing)
            i++;
    }

    for (i = 0; i < dim && !WindowShouldClose();){
        if (*playing){
            algorithm->forCicles++;
            count[i] = 0;
            
            algorithm->writesSecond++;
        }

        betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, i, bottom, &side, &fps, algorithm, "countingSort");
        if (IsKeyDown(KEY_ENTER)){
            return;
        }

        if (*playing)
            i++;
    }

    for (i = 0; i < dim && !WindowShouldClose();){
        if (*playing){
            algorithm->forCicles++;
            count[array[i].value]++;
            algorithm->writesSecond++;
        }

        betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, i, bottom, &side, &fps, algorithm, "countingSort");
        if (IsKeyDown(KEY_ENTER)){
            return;
        }

        if (*playing)
            i++;
    }

    for (i = 1; i <= max && !WindowShouldClose();) {
        if (*playing){
            algorithm->forCicles++;
            count[i] += count[i-1];
            algorithm->writesSecond++;
        }

        betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, i, bottom, &side, &fps, algorithm, "countingSort");
        if (IsKeyDown(KEY_ENTER)){
            return;
        }

        if (*playing)
            i++;
    }

    for (i = dim-1; i >= 0 && !WindowShouldClose();){
        if (*playing){
            algorithm->forCicles++;
            output[count[array[i].value] - 1].value = array[i].value;
            count[array[i].value]--;
            algorithm->writesSecond += 2;
        }

        betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, i, bottom, &side, &fps, algorithm, "countingSort");
        if (IsKeyDown(KEY_ENTER)){
            return;
        }

        if (*playing)
            i--;
    }

    for (i = 0; i < dim && !WindowShouldClose();){
        if (*playing){
            algorithm->forCicles++;
            array[i].value = output[i].value;
            algorithm->writesMain++;
        }

        betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, i, bottom, &side, &fps, algorithm, "countingSort");
        if (IsKeyDown(KEY_ENTER)){
            return;  
        }

        if (*playing)
            i++;
    }

    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void shellSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int n = dim, fps = STDFPS, interval, i, temp, ii;

    bottom bottom;
    side side;
    element array[dim];

    sortingInit(SCREEN_WIDTH, SCREEN_HEIGHT, array, 's', &bottom, &side);

    for (interval = n/2; interval > 0; interval /= 2){
        algorithm->forCicles++;
        for (i = interval; i < n; i += 1){
            algorithm->forCicles++;
            temp = array[i].value;

            for (ii = i; ii >= interval && array[ii - interval].value > temp && !WindowShouldClose();){
                if (*playing){
                    algorithm->forCicles++;
                    array[ii].value = array[ii - interval].value;
                    algorithm->writesMain++;
                }

                betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, ii, bottom, &side, &fps, algorithm, "shellSort");
                if (IsKeyDown(KEY_ENTER)){
                    return;  
                }

                if (*playing)
                    ii -= interval;
            }

            array[ii].value = temp;
            algorithm->writesMain++;
        }
    }

    
    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void combSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int fps = STDFPS, gap = dim, i;
    bool swapped = true;
    
    bottom bottom;
    side side;
    element array[dim];

    sortingInit(SCREEN_WIDTH, SCREEN_HEIGHT, array, 'c', &bottom, &side);

    while (gap != 1 || swapped){
        algorithm->forCicles++;
        gap = nextGap(gap);
        swapped = false;

        for (i = 0; i < dim-gap && !WindowShouldClose();){
            if (*playing){
                algorithm->forCicles++;
                if (array[i].value > array[i+gap].value){
                    swap(&array[i].value, &array[i+gap].value);
                    swapped = true;
                    algorithm->swaps++;
                }
                algorithm->comparison++;
            }

            betterSortingCode(array, topBar, playing, SCREEN_WIDTH, SCREEN_HEIGHT, i, i, bottom, &side, &fps, algorithm, "combSort");
            if (IsKeyDown(KEY_ENTER)){
                return;
            }

            if (*playing)
                i++;
        }
    }

    
    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}


//---------------------------


void settings(){
    int i = 0;
    bool stop = false;

    slider DIVIDER_slider;
    Rectangle mouse;

    //at 1 am what do you do? code in C raylib
    //bruuh

    SetTargetFPS(STDFPS*2);

    setDeviderSlider(&DIVIDER_slider);

    mouse.x = GetMouseX()-2.5;
    mouse.y = GetMouseY()-2.5;
    mouse.height = 5;
    mouse.width = 5;
    DIVIDER_slider.slider.x = 10+(DIVIDER*11);

    while (!WindowShouldClose() && !stop){
        mouse.x = GetMouseX()-2.5;
        mouse.y = GetMouseY()-2.5;

        manageDeviderSlider(&DIVIDER_slider);

        if (CheckCollisionRecs(mouse, DIVIDER_slider.Rect))
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                if (! (DIVIDER_slider.slider.x < 10 || DIVIDER_slider.slider.x > 10+500+25))
                    DIVIDER_slider.slider.x = mouse.x-((float)25/2);


        if (IsKeyPressed(KEY_ENTER)) stop = true;

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            
            DrawTexture(DIVIDER_slider.texture, DIVIDER_slider.Rect.x, DIVIDER_slider.Rect.y, WHITE);
            DrawTextEx(font, TextFormat("DIVIDER (2 - 40): %d (ENTER to save and exit)",DIVIDER), (Vector2) {10+500+20, 10}, 25, 0, BLACK);
            DrawRectangle(DIVIDER_slider.slider.x, DIVIDER_slider.slider.y, DIVIDER_slider.slider.width, DIVIDER_slider.slider.height, BLACK);
        EndDrawing();
    }

}

void setDeviderSlider(slider *slider){
    //SE

    slider->image = LoadImage("images/slider.png");
    slider->texture = LoadTextureFromImage(slider->image);
    UnloadImage(slider->image);
    slider->Rect.height = 25;
    slider->Rect.width = 500;
    slider->Rect.x = 10;
    slider->Rect.y = 10;

    slider->slider.x = slider->Rect.x+10;
    slider->slider.y = slider->Rect.y;
    slider->slider.height = 25;
    slider->slider.width = 25;

    //V x v = true
}

void manageDeviderSlider(slider *slider){
    //sets DIVIDER value using the X position of the slider as reference
    DIVIDER = (int)((slider->slider.x - slider->Rect.x)/11);

    //if the DIVIDER is bigger then its maximum or smaller then its minimum
    //it manages the exception
    if (DIVIDER <= 1) DIVIDER = 2;
    else if (DIVIDER > 40) DIVIDER = 40;

    if (slider->slider.x < 10) slider->slider.x = 10;
    else if (slider->slider.x > 10+500+25) slider->slider.x = 10+500+25; 
}

void catchFullScreen(int *SCREEN_WIDTH, int *SCREEN_HEIGHT){
    //Still in early demo (does not work at all lol)
    bool isFullScreen;

    if (*SCREEN_WIDTH == GetMonitorWidth(GetCurrentMonitor()))
        isFullScreen = true;
    else
        isFullScreen = false;

    if (IsKeyPressed(KEY_F11)){
        if (!isFullScreen){
            *SCREEN_WIDTH = GetMonitorWidth(GetCurrentMonitor());
            *SCREEN_HEIGHT = GetMonitorWidth(GetCurrentMonitor());

            SetWindowSize(*SCREEN_WIDTH, *SCREEN_HEIGHT);
            ToggleFullscreen();
        }else{
            *SCREEN_WIDTH = 1800;
            *SCREEN_HEIGHT = 980;

            SetWindowSize(*SCREEN_WIDTH, *SCREEN_HEIGHT);
        }
    }

}

//---------------------------

void through(element array[], bool* playing, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int i;
    *playing = true;

    SetTargetFPS(STDFPS);

    for (i = 0; i < dim; i++)
        array[i].color = WHITE;

    for (i = 0; i < dim-1 && !WindowShouldClose(); i++){
        array[i].color = BLUE;

        BeginDrawing();
            ClearBackground(BLACK);
            drawArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
        EndDrawing();

        if (array[i+1].value >= array[i].value){
            array[i].color = GREEN;
        }else{
            array[i].color = RED;
        }
    }
}

// TOPBAR

void drawTopBar(button array[], int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //SE
    int i;

    DrawRectangle(0, 0, SCREEN_WIDTH, 5+5+40, LIGHTGRAY);

    for (i = 0; i < MAXTOP; i++)
        DrawTexture(array[i].texture, array[i].Rect.x, array[i].Rect.y, WHITE);
}

void topBarInteraction(button array[], bool *playing){
    //checks if you pressed a button in the topbar and if you did it makes the .active
    //bool value true

    Rectangle mouse;
    int i;

    mouse.x = GetMouseX()-2.5;
    mouse.y = GetMouseY()-2.5;
    mouse.height = 5;
    mouse.width = 5;

    for (i = 0; i < MAXTOP; i++){
        if (CheckCollisionRecs(mouse, array[i].Rect)){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                array[i].texture = array[i].clickedTexture;
            }else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                array[i].texture = array[i].normalTexture;

                if (array[i].active) 
                    array[i].active = false;
                else
                    array[i].active = true;

                if (i == 0) {
                    if (!*playing)
                        *playing = true;
                    else
                        *playing = false;
                }
            }
        }
    }
}

void setTopBar(button array[]){
    //SE

    array[0].Rect = (Rectangle){400, 5, 40, 40};

    array[0].clickedImage = LoadImage("images/clickedPlay.png");
    array[0].clickedTexture = LoadTextureFromImage(array[0].clickedImage);
    UnloadImage(array[0].clickedImage);

    array[0].normalImage = LoadImage("images/play.png");
    array[0].normalTexture = LoadTextureFromImage(array[0].normalImage);
    UnloadImage(array[0].normalImage);

    array[0].texture = array[0].normalTexture;

    /*---*/

    array[1].Rect = (Rectangle){480, 0, 40, 40};

    array[1].clickedImage = LoadImage("images/clickedBefore.png");
    array[1].clickedTexture = LoadTextureFromImage(array[1].clickedImage);
    UnloadImage(array[1].clickedImage);

    array[1].normalImage = LoadImage("images/before.png");
    array[1].normalTexture = LoadTextureFromImage(array[1].normalImage);
    UnloadImage(array[1].normalImage);

    array[1].texture = array[1].normalTexture;

    /*---*/

    array[2].Rect = (Rectangle){560, 0, 40, 40};

    array[2].clickedImage = LoadImage("images/clickedNext.png");
    array[2].clickedTexture = LoadTextureFromImage(array[2].clickedImage);
    UnloadImage(array[2].clickedImage);

    array[2].normalImage = LoadImage("images/next.png");
    array[2].normalTexture = LoadTextureFromImage(array[2].normalImage);
    UnloadImage(array[2].normalImage);

    array[2].texture = array[2].normalTexture;

    /*---*/

    array[3].Rect = (Rectangle){800, 5, 40, 40};

    array[3].clickedImage = LoadImage("images/clickedMenu.png");
    array[3].clickedTexture = LoadTextureFromImage(array[3].clickedImage);
    UnloadImage(array[3].clickedImage);

    array[3].normalImage = LoadImage("images/menu.png");
    array[3].normalTexture = LoadTextureFromImage(array[3].normalImage);
    UnloadImage(array[3].normalImage);

    array[3].texture = array[3].normalTexture;
}

//*/

bool checkSorted(element array[], int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //checks if the current element is sorted compared to its next element
    int i;
    bool ret = true;

    for (i = 0; i < dim; i++){
        if (array[i].value > array[i+1].value)
            ret = false;
    }

    return ret;
}

void drawAll(element array[], button topBar[], char sort[], int i, int ii, bottom *bottom, side side, algorithm algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //draws everything
    int c;
    int fntSize = DIVIDER;

    for (c = 0; c < dim; c++){
        array[c].color = WHITE;
    }

    array[ii].color = BLUE;

    BeginDrawing();
        ClearBackground(BLACK);
        drawArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
        drawTopBar(topBar, SCREEN_WIDTH, SCREEN_HEIGHT);
        drawBox(algorithm);
        drawUpdateBottom(array, i, ii, bottom);
        drawSide(side);

        DrawTextEx(font, sort, (Vector2){5, 5}, 40, 3, DARKGRAY);
    EndDrawing();

    array[ii].color = WHITE;
}

void setBottom(element array[], bottom *bottom, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //draws the bottom part in the sorting screen

    bottom->image = LoadImage("images/arrow.png");
    bottom->texture = LoadTextureFromImage(bottom->image);

    bottom->rect.x = array[0].bottomRect.x;
    bottom->rect.y = SCREEN_HEIGHT-(DIVIDER*2);
    bottom->rect.height = DIVIDER;
    bottom->rect.width = DIVIDER;

    UnloadImage(bottom->image);
}

void drawUpdateBottom(element array[], int i, int ii, bottom *bottom){
    bottom->rect.x = array[ii].bottomRect.x;

    if (bottom->rect.x != 0)
        DrawTexture(bottom->texture, bottom->rect.x, bottom->rect.y, WHITE);
}

void setSideAnimation(side *side, char type, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //sets the side screen

    side->blackRect.x = SCREEN_WIDTH;
    side->blackRect.y = 0;
    side->blackRect.height = SCREEN_HEIGHT;
    side->blackRect.width = (float)SCREEN_WIDTH/2;

    side->mouse.x = GetMouseX()-2.5;
    side->mouse.y = GetMouseY()-2.5;
    side->mouse.height = 5;
    side->mouse.width = 5;

    switch (type) {
        case 'S':
            side->image = LoadImage("images/sort/selectionSort.png");
            side->imgX = 200;
            side->imgY = 100;
        break;
        case 'B':
            side->image = LoadImage("images/sort/bubbleSort.png");
            side->imgX = 155;
            side->imgY = 65;
        break;
        case 'b':
            side->image = LoadImage("images/sort/badSort.png");
            side->imgX = 145;
            side->imgY = 55;
        break;
        case 'O':
            side->image = LoadImage("images/sort/oddEvenSort.png");
            side->imgX = 170;
            side->imgY = 20;
        break;
        case 'H':
            side->image = LoadImage("images/sort/shakerSort.png");
            side->imgX = 225;
            side->imgY = 10;
        break;
        case 'G':
            side->image = LoadImage("images/sort/gnomeSort.png");
            side->imgX = 160;
            side->imgY = 75;
        break;
        case 'I':
            side->image = LoadImage("images/sort/insertionSort.png");
            side->imgX = 140;
            side->imgY = 60;
        break;
        case 'C':
            side->image = LoadImage("images/sort/countSort.png");
            side->imgX = 90;
            side->imgY = 50;
        break;
        case 's':
            side->image = LoadImage("images/sort/shellSort.png");
            side->imgX = 50;
            side->imgY = 220;
        break;
        case 'c':
            side->image = LoadImage("images/sort/combSort.png");
            side->imgX = 200;
            side->imgY = 50;
        break;
    }

    side->texture = LoadTextureFromImage(side->image);
    UnloadImage(side->image);
}

void manageAnimation(side *side, element *array, button button, bool *playing, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //manages the side screen during sorting

    int i;

    side->mouse.x = GetMouseX()-2.5;
    side->mouse.y = GetMouseY()-2.5;

    if (CheckCollisionRecs(side->mouse, button.Rect) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        if (side->blackRect.x > (float)SCREEN_WIDTH/2)
            side->blackRect.x -= 2500*GetFrameTime();

    }else if (side->blackRect.x < SCREEN_WIDTH)
        side->blackRect.x += 2500*GetFrameTime();

    if (side->blackRect.x+side->blackRect.width < SCREEN_WIDTH)
        side->blackRect.x = SCREEN_WIDTH-side->blackRect.width;

    for (i = 0; i < dim; i++){
        if (CheckCollisionRecs(side->mouse, array[i].Rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            clickAnimation(array[i], playing, side->mouse, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    }
}

//--

void drawSide(side side){
    DrawRectangleRec(side.blackRect, DARKGRAY);
    DrawTexture(side.texture, side.blackRect.x+side.imgX, side.imgY, WHITE);
}

int getMax(element array[], int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int max = array[0].value, i;

    for (i = 1; i < dim; i++)
        if (array[i].value > max)
            max = array[i].value;
    
    return max;
}

int nextGap(int gap){
    gap = (gap*10)/13;

    if (gap < 1)
        return 1;
    return gap;
}

void drawBox(algorithm algorithm){
    int increase = 20;

    DrawText(TextFormat("comparisons: %d",algorithm.comparison), 20/2, 30*2, 20, LIGHTGRAY);
    DrawText(TextFormat("switches: %d",algorithm.swaps), 20/2, 30*2 + increase, 20, LIGHTGRAY);
    DrawText(TextFormat("writes to secondary: %d",algorithm.writesSecond), 20/2, 30*2 + increase*2, 20, LIGHTGRAY);
    DrawText(TextFormat("iterations: %d",algorithm.forCicles), 20/2, 30*2 + increase*3, 20, LIGHTGRAY);
}


//--


void betterSortingCode(element array[], button* topBar, bool* playing, int SCREEN_WIDTH, int SCREEN_HEIGHT, int i, int ii, bottom bottom, side* side, int* fps, algorithm *algorithm, char string[]){

    topBarInteraction(topBar, playing);
    catchPlaying(playing, fps, topBar);
    manageAnimation(side, array, topBar[3], playing, SCREEN_WIDTH, SCREEN_HEIGHT);

    drawAll(array, topBar, string, ii, ii, &bottom, *side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void sortingInit(int SCREEN_WIDTH, int SCREEN_HEIGHT, element array[], char type, bottom *bottom, side *side){
    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSideAnimation(side, type, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void unloadmenu(menuRect rects[], menuImages *images){
    int i;

    for (i = 0; i < ALGS; i++){
        UnloadTexture(rects[i].texture);
    }

    UnloadTexture(images->clickedTexture);
    UnloadTexture(images->normalTexture);
}

void clickAnimation(element clicked, bool *playing, Rectangle mouse, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    bool was;
    bool animation = true;

    int pos = SCREEN_HEIGHT;
    Image img;
    Texture txt;

    img = LoadImage("images/big.png");
    txt = LoadTextureFromImage(img);
    UnloadImage(img);

    if (*playing)
        was = true;
    else
        was = false;

    *playing = false;

    while (!WindowShouldClose()){

        BeginDrawing();
            ClearBackground(LIGHTGRAY);

            DrawTexture(txt, (SCREEN_WIDTH/2)-(250), pos, WHITE);
            DrawTextEx(font, TextFormat("value: %d (ESC to exit)", clicked.value-5), (Vector2){((float)SCREEN_WIDTH/2)-220, (float)(pos+250-20)}, 40, 1, BLACK);
        EndDrawing();

        if (pos > ((SCREEN_HEIGHT/2)-250) && animation){
            pos -= (40 * GetFrameTime() * 50);
        }
    }

    if (was)
        *playing = true;

    UnloadTexture(txt);
}