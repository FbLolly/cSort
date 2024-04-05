#include <stdbool.h>
#include <time.h>
#include "raylib.h"

typedef struct{
    int value;
    Color color;
    Color should;
    Rectangle Rect;
    Rectangle bottomRect;
}element;

typedef struct{
    bool active;
    Texture Texture;
    Rectangle Rect;
    Image Image;
}button;

typedef struct{
    Image Image;
    Texture Texture;
    Rectangle Rect;
}bottom;

typedef struct{
    Rectangle blackRect;
    Rectangle mouse;
    Image Image;
    Texture Texture;
    int imgX;
    int imgY;
}side;

typedef struct{
    long comparison;
    long forCicles;
    long swaps;
    long writesMain;
    long writesSecond;
}algorithm;

typedef struct{
    Rectangle Rect;
    int num;
    Color color;
    Image Image;
    Texture Texture;
}menuRect;

typedef struct{
    Rectangle Rect;
    Image Image;
    Texture Texture;
    Rectangle slider;
}slider;

typedef struct{
    Rectangle Rect;
    int R, G, B;
    Rectangle slider;
    Color Color;
    char strcolor[20];
}colorSlider;

int menu(int *SCREEN_WIDTH, int*SCREEN_HEIGHT);
extern void setMenuRects(menuRect rects[], int SCREEN_WIDTH);
extern void setArray(element array[], int SCREEN_WIDTH, int SCREEN_HEIGHT);
extern void drawArray(element array[], Rectangle iiRect, int SCREEN_WIDTH, int SCREEN_HEIGHT);
extern void swap(int *n1, int *n2);
extern void intToString(char *string, int num);
extern void menuCollisions(menuRect rects[], Rectangle mouse, int *choice);

extern void settings();
extern void setDeviderSlider(slider *slider);
extern void manageDeviderSlider(slider *slider);
extern int getX(Color color);
extern bool sameColors(Color color1, Color color2);

extern void selectionSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int);
extern void bubbleSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int);
extern void gnomeSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int);
extern void insertionSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int);
extern void oddEvenSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int);
extern void badSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int);
extern void shakerSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int);
extern void countingSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int);
extern void shellSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int);
extern void combSort(bool* playing, button topBar[], algorithm *algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT, const int);

extern void catchPlaying(bool* playing, int* fps, button array[]);
extern void through(element array[], bool* playing, int SCREEN_WIDTH, int SCREEN_HEIGHT);
extern void drawTopBar(button array[], int SCREEN_WIDTH, int SCREEN_HEIGHT);
extern void topBarInteraction(button array[], bool *playing);
extern void setTopBar(button array[]);
extern void catchFullScreen(int *SCREEN_WIDTH, int *SCREEN_HEIGHT);

extern bool checkSorted(element array[], int SCREEN_WIDTH, int SCREEN_HEIGHT);
extern void drawAll(element array[], button topBar[], char sort[], int i, int ii, bottom *bottom, side side, algorithm algorithm, int SCREEN_WIDTH, int SCREEN_HEIGHT);
extern void setBottom(element array[], bottom *bottom, int SCREEN_WIDTH, int SCREEN_HEIGHT);
extern void drawUpdateBottom(element array[], int i, int ii, bottom *bottom);
extern void setSideAnimation(side *side, char type, int SCREEN_WIDTH, int SCREEN_HEIGHT);
extern void manageAnimation(side *side, int SCREEN_WIDTH, int SCREEN_HEIGHT);
extern void drawSide(side side);
extern int nextGap(int gap);
extern void drawBox(algorithm algorithm);
extern int getMax(element array[], int SCREEN_WIDTH, int SCREEN_HEIGHT);
extern int partition(element array[], int l, int h);

extern void betterSortingCode(element array[], button* topBar, bool* playing, int SCREEN_WIDTH, int SCREEN_HEIGHT, int i, int ii, bottom bottom, side *side, int* fps, algorithm *algorithm, char string[]);
extern void sortingInit(int SCREEN_WIDTH, int SCREEN_HEIGHT, element array[], char type, bottom *bottom, side *side);
extern bool compareColor(Color color1, Color color2);
