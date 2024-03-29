//SE = self explanatory

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "raylib.h"

#include "headers/const.h"
#include "headers/structf.h"

//global variable (its needed in the whole code)
int DEVIDER = 2;

int main(){
    //menu choice
    int choice;

    //these could have been global variables too but I decided to make them normal ones
    int SCREEN_WIDTH = 1800;
    int SCREEN_HEIGHT = 980;
    bool playing = true;

    //topbar with buttons already declared here couse its going to be the same for every one of them
    button topBar[MAXTOP];
    //algorithm with sorting statistics
    algorithm algorithm;

    //set srand seed and init raylib window
    srand(time(NULL));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "sorting");

    //set the fps as the standard fps and set the standard topbar
    SetTargetFPS(STDFPS);
    setTopBar(topBar);

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
                selectionSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT, (int)(SCREEN_WIDTH/DEVIDER));
            break;
            case 2:
                shakerSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT, (int)(SCREEN_WIDTH/DEVIDER));
            break;
            case 3:
                bubbleSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT, (int)(SCREEN_WIDTH/DEVIDER));
            break;
            case 4:
                gnomeSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT, (int)(SCREEN_WIDTH/DEVIDER));
            break;
            case 5:
                insertionSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT, (int)(SCREEN_WIDTH/DEVIDER));
            break;
            case 6:
                oddEvenSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT, (int)(SCREEN_WIDTH/DEVIDER));
            break;
            case 7:
                badSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT, (int)(SCREEN_WIDTH/DEVIDER));
            break;
            //8 = quit
            case 9:
                countingSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT, (int)(SCREEN_WIDTH/DEVIDER));
            break;
            case 10:
                shellSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT, (int)(SCREEN_WIDTH/DEVIDER));
            break;
            case 11:
                combSort(&playing, topBar, &algorithm, SCREEN_WIDTH, SCREEN_HEIGHT, (int)(SCREEN_WIDTH/DEVIDER));
            break;
            case 12:
                settings();
            break;
        }

        //if the user changed the fps during the simulation this resets it to its standard value
        SetTargetFPS(STDFPS);
    }

    return 0;

}

//

void setArray(element array[], int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //this function just randomizes the array and sets its color
    int i;
    for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER); i++){
        array[i].value = 5+(rand()%((int)(SCREEN_HEIGHT/DEVIDER) * 4/5));
        array[i].value += 1;
        array[i].color = WHITE;
    }
}

void drawArray(element array[], Rectangle iiRect, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int i;

    for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER); i++){
        array[i].Rect.x = i*(DEVIDER);
        array[i].Rect.y = (SCREEN_HEIGHT-(array[i].value*(DEVIDER)))+(DEVIDER*2);
        array[i].Rect.width = DEVIDER;
        array[i].Rect.height = array[i].value*DEVIDER;

        //draw the array
        DrawRectangleRec(iiRect, BLUE);
        DrawRectangleRec(array[i].Rect, array[i].color);
        DrawRectangle(0, SCREEN_HEIGHT-(DEVIDER*3), SCREEN_WIDTH, DEVIDER*3, BLACK);
    }

    for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER); i++){
        array[i].bottomRect.x = DEVIDER*i;
        array[i].bottomRect.y = SCREEN_HEIGHT-(DEVIDER*3);
        array[i].bottomRect.height = DEVIDER;
        array[i].bottomRect.width = DEVIDER;

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

void setMenuRects(menuRect rects[], int SCREEN_WIDTH, int SCREEN_HEIGHT){
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
        rects[i].Image = LoadImage("images/button.png");
        rects[i].Texture = LoadTextureFromImage(rects[i].Image);
        UnloadImage(rects[i].Image);
    }
}

int menu(int* SCREEN_WIDTH, int* SCREEN_HEIGHT){
    int choice = -1, i; //choice has by default an impossible value
    menuRect menuRects[ALGS];
    Rectangle mouse;

    //load menu font
    Font font = LoadFont("fonts/CaskaydiaCoveNerdFontMono-Bold.ttf");

    setMenuRects(menuRects, *SCREEN_WIDTH, *SCREEN_HEIGHT);

    mouse.height = 5;
    mouse.width = 5;

    //choice == -1 mean "if you still have not choosen"
    while (!WindowShouldClose() && choice == -1){
        mouse.x = GetMouseX()-2.5;
        mouse.y = GetMouseY()-2.5;

        menuCollisions(menuRects, mouse, &choice);
        catchFullScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

        //draw menu
        BeginDrawing();
            for (i = 0; i < ALGS; i++)
                DrawTexture(menuRects[i].Texture, menuRects[i].Rect.x, menuRects[i].Rect.y, WHITE);
            
            
            DrawTextEx(font,"selectionSort", (Vector2) { menuRects[0].Rect.x + 30 + 20, menuRects[0].Rect.y + 2.}, menuRects[0].Rect.height-5, 0, menuRects[0].color);
            DrawTextEx(font,"shakerSort", (Vector2) { menuRects[1].Rect.x + 70 + 20, menuRects[1].Rect.y + 2.}, menuRects[1].Rect.height-5, 0, menuRects[1].color);
            DrawTextEx(font,"bubbleSort", (Vector2) { menuRects[2].Rect.x + 70 + 20, menuRects[2].Rect.y + 2.}, menuRects[2].Rect.height-5, 0, menuRects[2].color);
            DrawTextEx(font,"gnomeSort", (Vector2) { menuRects[3].Rect.x + 80 + 20, menuRects[3].Rect.y + 2.}, menuRects[3].Rect.height-5, 0, menuRects[3].color);
            DrawTextEx(font,"insertionSort", (Vector2) { menuRects[4].Rect.x + 35 + 20, menuRects[4].Rect.y + 2.}, menuRects[4].Rect.height-5, 0, menuRects[4].color);
            DrawTextEx(font,"oddEvenSort", (Vector2) { menuRects[5].Rect.x + 55 + 20, menuRects[5].Rect.y + 2.}, menuRects[5].Rect.height-5, 0, menuRects[5].color);
            DrawTextEx(font,"BadSort", (Vector2) { menuRects[6].Rect.x + 100 + 20, menuRects[6].Rect.y + 2.}, menuRects[6].Rect.height-5, 0, menuRects[6].color);
            DrawTextEx(font,"Quit", (Vector2) { menuRects[7].Rect.x + 130 + 20, menuRects[7].Rect.y + 2.}, menuRects[7].Rect.height-5, 0, menuRects[7].color);
            DrawTextEx(font,"countingSort", (Vector2) { menuRects[8].Rect.x + 50 + 20, menuRects[8].Rect.y + 2.}, menuRects[8].Rect.height-5, 0, menuRects[8].color);
            DrawTextEx(font,"shellSort", (Vector2) { menuRects[9].Rect.x + 80 + 20, menuRects[9].Rect.y + 2.}, menuRects[9].Rect.height-5, 0, menuRects[9].color);
            DrawTextEx(font,"combSort", (Vector2) { menuRects[10].Rect.x + 95 + 20, menuRects[10].Rect.y + 2.}, menuRects[10].Rect.height-5, 0, menuRects[10].color);
            DrawTextEx(font,"Settings", (Vector2) { menuRects[11].Rect.x + 95 + 20, menuRects[11].Rect.y + 2.}, menuRects[11].Rect.height-5, 0, menuRects[11].color);

            ClearBackground(BLACK);
        EndDrawing();
    }

    return choice;
}

void menuCollisions(menuRect rects[], Rectangle mouse, int *choice){
    //checks if you clicked on one of the buttons

    int i;

    for (i = 0; i < ALGS; i++){
        if (CheckCollisionRecs(rects[i].Rect, mouse)){
            rects[i].color = BLUE;

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                *choice = i+1;
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
            if (*fps > 80-DEVIDER){*fps -= 80-DEVIDER;}
        if (IsKeyPressed(KEY_RIGHT))
            *fps += 80-DEVIDER;

        SetTargetFPS(*fps);
    }

    if (array[1].active || array[2].active){
        if (array[1].active) {
            if (*fps > 80-DEVIDER)
                *fps -= 80-DEVIDER;
            array[1].active = false;
        }
        if (array[2].active) {*fps += 80-DEVIDER; array[2].active = false;}

        SetTargetFPS(*fps);
    }
}


////* sorting algs (SE)


void selectionSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int DIM){
    int i = 0, ii = 0, minIdx = 0, fps = STDFPS;

    bottom bottom;
    side side;
    element array[DIM]; //uses a constant declared at the start of the stack (no heap used)

    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, &bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSideAnimation(&side, 'S', SCREEN_WIDTH, SCREEN_HEIGHT);

    for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER)-1; i++){
        algorithm->forCicles++;
        minIdx = i;

        for (ii = i+1; ii < (int)(SCREEN_WIDTH/DEVIDER) && !WindowShouldClose();){

            if (*playing){
                algorithm->forCicles++;
                if (array[ii].value < array[minIdx].value)
                    minIdx = ii;
                
                algorithm->comparison++;
                ii++;
            }
            
            if (IsKeyDown(KEY_ENTER)) return;

            topBarInteraction(topBar, playing);
            catchPlaying(playing, &fps, topBar);
            manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

            drawAll(array, topBar, "selectionSort", ii, ii, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        swap(&array[minIdx].value, &array[i].value);
        algorithm->swaps++;
    }

    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void badSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int DIM){
    int ii = 0, a = (int)(SCREEN_WIDTH/DEVIDER), fps = STDFPS;
    bool isSorted = false;

    bottom bottom;
    side side;
    element array[DIM];

    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, &bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSideAnimation(&side, 'B', SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!isSorted){
        algorithm->forCicles++;
        isSorted = true;

        for (ii = 0; ii < a-1 && !WindowShouldClose(); ii = ii){
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
                
                ii++;
            }

            topBarInteraction(topBar, playing);
            catchPlaying(playing, &fps, topBar);
            manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (IsKeyPressed(KEY_ENTER)){
                return;
            }

            drawAll(array, topBar, "badSort", ii, ii, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    }

    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void oddEvenSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int DIM){
    bool isSorted = false;
    int i = 0, fps = STDFPS;

    bottom bottom;
    side side;
    element array[DIM];

    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, &bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSideAnimation(&side, 'O', SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!isSorted && !WindowShouldClose()){
        algorithm->forCicles++;

        isSorted = true;

        for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER)-1 && !WindowShouldClose(); i = i){
            if (*playing){
                algorithm->forCicles++;
                if (array[i].value > array[i+1].value){
                    swap(&array[i].value, &array[i+1].value);
                    isSorted = false;
                    algorithm->swaps++;
                }
                
                i += 2;

                algorithm->comparison++;
            }

            topBarInteraction(topBar, playing);
            catchPlaying(playing, &fps, topBar);
            manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (IsKeyPressed(KEY_ENTER)){
                return;
            }

            drawAll(array, topBar, "oddEvenSort", i, i, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        for (i = 1; i < (int)(SCREEN_WIDTH/DEVIDER) && !WindowShouldClose(); i = i){
            if (*playing){
                algorithm->forCicles++;
                if (array[i].value > array[i+1].value){
                    swap(&array[i].value, &array[i+1].value);
                    isSorted = false;
                    algorithm->swaps++;
                }

                algorithm->comparison++;
                                
                i += 2;
            }

            topBarInteraction(topBar, playing);
            catchPlaying(playing, &fps, topBar);
            manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (IsKeyPressed(KEY_ENTER)){
                return;
            }

            drawAll(array, topBar, "oddEvenSort", i, i, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    }

    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void shakerSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int DIM){
    int n = (int)(SCREEN_WIDTH/DEVIDER), start = 0, i, fps = STDFPS, end = n-1;
    bool swapped = true;

    bottom bottom;
    side side;
    element array[DIM];

    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, &bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSideAnimation(&side, 'H', SCREEN_WIDTH, SCREEN_HEIGHT);

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

                i += 1;
            }

            topBarInteraction(topBar, playing);
            catchPlaying(playing, &fps, topBar);
            manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (IsKeyPressed(KEY_ENTER)){
                return;
            }

            drawAll(array, topBar, "cocktailShakerSort", i, i, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        if (!swapped) {break;}
        algorithm->comparison++;

        swapped = false;
        end -= 1;

        for (i = end; i > start && !WindowShouldClose();){
            if (*playing){
                algorithm->forCicles++;
                if (array[i].value < array[i-1].value){
                    swap(&array[i].value, &array[i-1].value);
                    swapped = true;
                    algorithm->swaps++;
                }
                algorithm->comparison++;

                i -= 1;
            }

            topBarInteraction(topBar, playing);
            catchPlaying(playing, &fps, topBar);
            manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (IsKeyPressed(KEY_ENTER)){
                return;
            }

            drawAll(array, topBar, "cocktailShakerSort", i, i, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        start += 1;
    }

    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void bubbleSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int DIM){
    int ii = 0, a = (int)(SCREEN_WIDTH/DEVIDER), fps = STDFPS;
    bool isSorted = false;

    bottom bottom;
    side side;
    element array[DIM];

    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, &bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSideAnimation(&side, 'B', SCREEN_WIDTH, SCREEN_HEIGHT);

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

                ii++;
            }

            topBarInteraction(topBar, playing);
            catchPlaying(playing, &fps, topBar);
            manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (IsKeyPressed(KEY_ENTER)){
                return;
            }

            drawAll(array, topBar, "bubbleSort", ii, ii, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        a--;
    }

    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void gnomeSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int DIM){
    int index = 1, fps = STDFPS;

    bottom bottom;
    side side;
    element array[DIM];

    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, &bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSideAnimation(&side, 'G', SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!WindowShouldClose() && index < (int)(SCREEN_WIDTH/DEVIDER)){

        if (*playing){
            while (index != 0 && array[index].value < array[index-1].value){
                algorithm->forCicles++;
                swap(&array[index].value, &array[index-1].value);
                index -= 1;
                algorithm->swaps++;
                algorithm->comparison++;
            }

            algorithm->forCicles++;

            index += 1;
        }

        topBarInteraction(topBar, playing);
        catchPlaying(playing, &fps, topBar);
        manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (IsKeyPressed(KEY_ENTER)){
            return;
        }

        drawAll(array, topBar, "gnomeSort", index, index, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void insertionSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int DIM){
    int i = 0, ii, fps = STDFPS; 
    
    bottom bottom;
    side side;
    element array[DIM];

    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, &bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSideAnimation(&side, 'I', SCREEN_WIDTH, SCREEN_HEIGHT);

    while (!WindowShouldClose() && i < (int)(SCREEN_WIDTH/DEVIDER)) {
        algorithm->forCicles++;
        ii = i;

        while (ii > 0 && array[ii-1].value > array[ii].value && !WindowShouldClose()){
            if (*playing){
                algorithm->forCicles++;
                swap(&array[ii].value, &array[ii-1].value);
                ii -= 1;
                algorithm->swaps++;
                algorithm->comparison++;
            }

            topBarInteraction(topBar, playing);
            catchPlaying(playing, &fps, topBar);
            manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (IsKeyPressed(KEY_ENTER)){
                return;
            }

            drawAll(array, topBar, "insertionSort", i, ii, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        i += 1;
    }
    
    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void countingSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int DIM){
    int max = 0, fps = STDFPS, i;
    int count[DIM];

    bottom bottom;
    side side;
    element array[DIM], output[DIM];

    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, &bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSideAnimation(&side, 'C', SCREEN_WIDTH, SCREEN_HEIGHT);

    max = array[0].value;

    for (i = 1; i < (int)(SCREEN_WIDTH/DEVIDER) && !WindowShouldClose();){
        if (*playing){
            algorithm->forCicles++;
            if (array[i].value > max)
                max = array[i].value;
            i++;

            algorithm->comparison++;
        }

        topBarInteraction(topBar, playing);
        catchPlaying(playing, &fps, topBar);
        manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (IsKeyPressed(KEY_ENTER)) return;

        drawAll(array, topBar, "countSort", i, i, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER) && !WindowShouldClose();){
        if (*playing){
            algorithm->forCicles++;
            count[i] = 0;
            i++;
            algorithm->writesSecond++;
        }

        topBarInteraction(topBar, playing);
        catchPlaying(playing, &fps, topBar);
        manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (IsKeyPressed(KEY_ENTER)) return;

        drawAll(array, topBar, "countSort (memoryKiller)", i, i, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER) && !WindowShouldClose();){
        if (*playing){
            algorithm->forCicles++;
            count[array[i].value]++;
            i++;
            algorithm->writesSecond++;
        }

        topBarInteraction(topBar, playing);
        catchPlaying(playing, &fps, topBar);
        manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (IsKeyPressed(KEY_ENTER)) return;

        drawAll(array, topBar, "countSort (memoryKiller)", i, i, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    for (i = 1; i <= max && !WindowShouldClose();) {
        if (*playing){
            algorithm->forCicles++;
            count[i] += count[i-1];
            i++;
            algorithm->writesSecond++;
        }

        topBarInteraction(topBar, playing);
        catchPlaying(playing, &fps, topBar);
        manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (IsKeyPressed(KEY_ENTER)) return;

        drawAll(array, topBar, "countSort (memoryKiller)", i, i, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    for (i = (int)(SCREEN_WIDTH/DEVIDER)-1; i >= 0 && !WindowShouldClose();){
        if (*playing){
            algorithm->forCicles++;
            output[count[array[i].value] - 1].value = array[i].value;
            count[array[i].value]--;
            i--;
            algorithm->writesSecond += 2;
        }

        topBarInteraction(topBar, playing);
        catchPlaying(playing, &fps, topBar);
        manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (IsKeyPressed(KEY_ENTER)) return;

        drawAll(array, topBar, "countSort (memoryKiller)", i, i, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER) && !WindowShouldClose();){
        if (*playing){
            algorithm->forCicles++;
            array[i].value = output[i].value;
            i++;
            algorithm->writesMain++;
        }

        topBarInteraction(topBar, playing);
        catchPlaying(playing, &fps, topBar);
        manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (IsKeyPressed(KEY_ENTER)) return;

        drawAll(array, topBar, "countSort (memoryKiller)", i, i, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void shellSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int DIM){
    int n = DIM, fps = STDFPS, interval, i, temp, ii;

    bottom bottom;
    side side;
    element array[DIM];

    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, &bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSideAnimation(&side, 's', SCREEN_WIDTH, SCREEN_HEIGHT);

    for (interval = n/2; interval > 0; interval /= 2){
        algorithm->forCicles++;
        for (i = interval; i < n; i += 1){
            algorithm->forCicles++;
            temp = array[i].value;

            for (ii = i; ii >= interval && array[ii - interval].value > temp && !WindowShouldClose();){
                if (*playing){
                    algorithm->forCicles++;
                    array[ii].value = array[ii - interval].value;
                    ii -= interval;
                    algorithm->writesMain++;
                }

                topBarInteraction(topBar, playing);
                catchPlaying(playing, &fps, topBar);
                manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

                if (IsKeyPressed(KEY_ENTER)){
                    return;
                }

                drawAll(array, topBar, "shellSort", i, ii, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
            }

            array[ii].value = temp;
            algorithm->writesMain++;
        }
    }

    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void combSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int DIM){
    int fps = STDFPS, gap = DIM, i;
    bool swapped = true;

    bottom bottom;
    side side;
    element array[DIM];

    setArray(array, SCREEN_WIDTH, SCREEN_HEIGHT);
    setBottom(array, &bottom, SCREEN_WIDTH, SCREEN_HEIGHT);
    setSideAnimation(&side, 'c', SCREEN_WIDTH, SCREEN_HEIGHT);

    while (gap != 1 || swapped){
        algorithm->forCicles++;
        gap = nextGap(gap);
        swapped = false;

        for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER)-gap && !WindowShouldClose();){
            if (*playing){
                algorithm->forCicles++;
                if (array[i].value > array[i+gap].value){
                    swap(&array[i].value, &array[i+gap].value);
                    swapped = true;
                    algorithm->swaps++;
                }
                algorithm->comparison++;
                i++;
            }

            topBarInteraction(topBar, playing);
            catchPlaying(playing, &fps, topBar);
            manageAnimation(&side, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (IsKeyPressed(KEY_ENTER)) return;

            drawAll(array, topBar, "combSort", i, i, &bottom, side, *algorithm, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
    }

    through(array, playing, SCREEN_WIDTH, SCREEN_HEIGHT);
}


//---------------------------

void settings(){
    //the settings change the global variable DEVIDER using a slider

    int i = 0;
    bool stop = false;

    //load the font
    Font font = LoadFont("fonts/CaskaydiaCoveNerdFontMono-Bold.ttf");
    slider devider_slider;
    Rectangle mouse;

    //at 1 am what do you do? code in C raylib
    //bruuh

    SetTargetFPS(STDFPS*2);

    setDeviderSlider(&devider_slider);

    mouse.x = GetMouseX()-2.5;
    mouse.y = GetMouseY()-2.5;
    mouse.height = 5;
    mouse.width = 5;
    devider_slider.slider.x = 10+(DEVIDER*11);

    while (!WindowShouldClose() && !stop){
        mouse.x = GetMouseX()-2.5;
        mouse.y = GetMouseY()-2.5;

        manageDeviderSlider(&devider_slider);

        if (CheckCollisionRecs(mouse, devider_slider.Rect))
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                if (! (devider_slider.slider.x < 10 || devider_slider.slider.x > 10+500+25))
                    devider_slider.slider.x = mouse.x-((float)25/2);


        if (IsKeyPressed(KEY_ENTER)) stop = true;

        BeginDrawing();
            DrawTexture(devider_slider.Texture, devider_slider.Rect.x, devider_slider.Rect.y, WHITE);
            DrawTextEx(font, TextFormat("DEVIDER (2 - 40): %d",DEVIDER), (Vector2) {10+500+20, 10}, 25, 0, LIGHTGRAY);
            DrawRectangle(devider_slider.slider.x, devider_slider.slider.y, devider_slider.slider.width, devider_slider.slider.height, BLACK);
            ClearBackground(DARKGRAY);
        EndDrawing();
    }

}

void setDeviderSlider(slider *slider){
    //SE

    slider->Image = LoadImage("images/slider.png");
    slider->Texture = LoadTextureFromImage(slider->Image);
    UnloadImage(slider->Image);
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
    //sets DEVIDER value using the X position of the slider as reference
    DEVIDER = (int)((slider->slider.x - slider->Rect.x)/11);

    //if the DEVIDER is bigger then its maximum or smaller then its minimum
    //it manages the exception
    if (DEVIDER <= 1) DEVIDER = 2;
    else if (DEVIDER > 40) DEVIDER = 40;

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
    //if an array is sorted it goes through it with an index and it checks if it is sorted
    //SE

    int i;
    *playing = true;

    Rectangle iiRect;

    SetTargetFPS(STDFPS);

    for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER); i++)
        array[i].color = WHITE;

    for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER)-1 && !WindowShouldClose(); i = i){

        iiRect.x = array[i].Rect.x;
        iiRect.y = array[i].Rect.y;
        iiRect.height = array[i].Rect.height;
        iiRect.width = array[i].Rect.width;
        
        if (array[i+1].value >= array[i].value){
            array[i].color = GREEN;
        }else{
            array[i].color = RED;
        }
        i += 1;

        BeginDrawing();
            ClearBackground(BLACK);
            drawArray(array, iiRect, SCREEN_WIDTH, SCREEN_HEIGHT);
        EndDrawing();

    }
}

// TOPBAR

void drawTopBar(button array[], int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //SE
    int i;

    DrawRectangle(0, 0, SCREEN_WIDTH, 5+5+40, LIGHTGRAY);

    for (i = 0; i < MAXTOP; i++)
        DrawTexture(array[i].Texture, array[i].Rect.x, array[i].Rect.y, WHITE);
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
        if (CheckCollisionRecs(mouse, array[i].Rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (array[i].active) array[i].active = false;
            else array[i].active = true;

            if (i == 0) {
                if (!*playing)
                    *playing = true;
                else
                    *playing = false;
            }
        }
    }
}

void setTopBar(button array[]){
    //SE

    array[0].Rect.x = 40*10;
    array[0].Rect.y = 5;
    array[0].Rect.width = 40;
    array[0].Rect.height = 40;
    array[0].Image = LoadImage("images/play.png");
    array[0].Texture = LoadTextureFromImage(array[0].Image);

    array[1].Rect.x = (40*10)+(40*2);
    array[1].Rect.y = 0;
    array[1].Rect.width = 40;
    array[1].Rect.height = 40;
    array[1].Image = LoadImage("images/before.png");
    array[1].Texture = LoadTextureFromImage(array[1].Image);

    array[2].Rect.x = (40*10)+(40*4);
    array[2].Rect.y = 0;
    array[2].Rect.width = 40;
    array[2].Rect.height = 40;
    array[2].Image = LoadImage("images/next.png");
    array[2].Texture = LoadTextureFromImage(array[2].Image);
}

//*/

bool checkSorted(element array[], int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //checks if the current element is sorted compared to its next element
    int i;
    bool ret = true;

    for (i = 0; i < (int)(SCREEN_WIDTH/DEVIDER); i++){
        if (array[i].value > array[i+1].value)
            ret = false;
    }

    return ret;
}

void drawAll(element array[], button topBar[], char sort[], int i, int ii, bottom *bottom, side side, algorithm algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //draws everything
    int c;

    //index rectangle
    Rectangle iiRect;
    iiRect.x = array[ii].Rect.x;
    iiRect.y = array[ii].Rect.y;
    iiRect.height = array[ii].Rect.height;
    iiRect.width = array[ii].Rect.width;

    for (c = 0; c < (int)(SCREEN_WIDTH/DEVIDER); c++){
        array[c].color = WHITE;
    }

    BeginDrawing();
        ClearBackground(BLACK);
        drawArray(array, iiRect, SCREEN_WIDTH, SCREEN_HEIGHT);
        drawTopBar(topBar, SCREEN_WIDTH, SCREEN_HEIGHT);
        drawBox(algorithm);
        drawUpdateBottom(array, i, ii, bottom);
        drawSide(side);

        DrawText(sort, 5, 5, 30, BLUE);
    EndDrawing();
}

void setBottom(element array[], bottom *bottom, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //draws the bottom part in the sorting screen

    bottom->Image = LoadImage("images/arrow.png");
    bottom->Texture = LoadTextureFromImage(bottom->Image);

    bottom->Rect.x = array[0].bottomRect.x;
    bottom->Rect.y = SCREEN_HEIGHT-(DEVIDER*2);
    bottom->Rect.height = DEVIDER;
    bottom->Rect.width = DEVIDER;

    UnloadImage(bottom->Image);
}

void drawUpdateBottom(element array[], int i, int ii, bottom *bottom){
    bottom->Rect.x = array[ii].bottomRect.x;

    if (bottom->Rect.x != 0)
        DrawTexture(bottom->Texture, bottom->Rect.x, bottom->Rect.y, WHITE);
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
            side->Image = LoadImage("images/sort/selectionSort.png");
            side->imgX = 200;
            side->imgY = 100;
        break;
        case 'B':
            side->Image = LoadImage("images/sort/bubbleSort.png");
            side->imgX = 155;
            side->imgY = 65;
        break;
        case 'b':
            side->Image = LoadImage("images/sort/badSort.png");
            side->imgX = 145;
            side->imgY = 55;
        break;
        case 'O':
            side->Image = LoadImage("images/sort/oddEvenSort.png");
            side->imgX = 170;
            side->imgY = 20;
        break;
        case 'H':
            side->Image = LoadImage("images/sort/shakerSort.png");
            side->imgX = 225;
            side->imgY = 10;
        break;
        case 'G':
            side->Image = LoadImage("images/sort/gnomeSort.png");
            side->imgX = 160;
            side->imgY = 75;
        break;
        case 'I':
            side->Image = LoadImage("images/sort/insertionSort.png");
            side->imgX = 140;
            side->imgY = 60;
        break;
        case 'C':
            side->Image = LoadImage("images/sort/countSort.png");
            side->imgX = 90;
            side->imgY = 50;
        break;
        case 's':
            side->Image = LoadImage("images/sort/shellSort.png");
            side->imgX = 50;
            side->imgY = 220;
        break;
        case 'c':
            side->Image = LoadImage("images/sort/combSort.png");
            side->imgX = 200;
            side->imgY = 50;
        break;
    }

    side->Texture = LoadTextureFromImage(side->Image);
    UnloadImage(side->Image);
}

void manageAnimation(side *side, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //manages the side screen during sorting

    Rectangle hitBox;
    hitBox.x = SCREEN_WIDTH-((float)SCREEN_WIDTH/8);
    hitBox.y = 0;
    hitBox.height = SCREEN_HEIGHT;
    hitBox.width = (float)SCREEN_WIDTH/8;

    side->mouse.x = GetMouseX()-2.5;
    side->mouse.y = GetMouseY()-2.5;

    if (CheckCollisionRecs(side->mouse, hitBox) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        if (side->blackRect.x > (float)SCREEN_WIDTH/2) side->blackRect.x -= DEVIDER*2;
    }else if (side->blackRect.x < SCREEN_WIDTH) side->blackRect.x += DEVIDER*2;

    if (side->blackRect.x+side->blackRect.width < SCREEN_WIDTH) side->blackRect.x = SCREEN_WIDTH-side->blackRect.width;

}

//SE --

void drawSide(side side){
    DrawRectangleRec(side.blackRect, DARKGRAY);
    DrawTexture(side.Texture, side.blackRect.x+side.imgX, side.imgY, WHITE);
}

int getMax(element array[], int SCREEN_WIDTH, int SCREEN_HEIGHT){
    int max = array[0].value, i;

    for (i = 1; i < (int)(SCREEN_WIDTH/DEVIDER); i++)
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
