#include <stdbool.h>

int main(){
    int array[] = {0, 5, 2, 3};
    int i, start = 0, tempData, end = 4-1;
    bool swapped = true;

    while (swapped){
        swapped = false;

        for (i = start; i < end; i++)
            if (array[i] > array[i+1]){
                tempData = array[i];
                array[i] = array[i+1];
                array[i+1] = tempData;

                swapped = true;
            }
        if (!swapped) break;
        swapped = false; end -= 1;

        for (i = end-1; i > start-1; i--)
            if (array[i] > array[i+1]){
                tempData = array[i];
                array[i] = array[i+1];
                array[i+1] = tempData;

                swapped = true;
            }
        start += 1;
    }
    return 0;
}