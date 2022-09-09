#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Used the InsertionSort.java file linked in assignment as reference.
void insertionsort(int array[], int max){

    // Defining all variables. 
    int i = 0, j = 0, key = 0;

    /*
        Loop through array, sorting from 0 to 9th element of array
        checking each value against the value in the position ahead,
        and moving each index accordingly.
    */
    for(i=1; i<max; i++){
        // Set key equal to the current index being evaluated.
        key = array[i];
        j = i - 1;
        // Move each element that is greater than key ahead by 1.
        while(j>=0 && array[j] > key){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }

    // Print the sorted array along with proper formatting.
    printf("\nSorted array using Insertion Sort: \n[");
    for(i=0; i<max; i++){
        if(i == (max-1)){
            printf("%d]\n", array[i]);
            continue;
        }
        printf("%d, ", array[i]);
    }

    return;
}

void main(){

    // Defining all variables.
    int i = 0, max = 0;
    srand((unsigned int)time(NULL));

    printf("Enter the length you want for the array: ");
    scanf("%d", &max);

    int arr[max];

    // Loop to scan each input value and fill array.
    for(i=0; i<max; i++){
        arr[i] = rand();
    }
    
    // Print inital array with proper formatting.
    printf("\nInitial array: \n[");
    for(i=0; i<max; i++){
        if(i == (max-1)){
            printf("%d]\n", arr[i]);
            continue;
        }
        printf("%d, ", arr[i]);
    }

    // Call insertion sort function.
    insertionsort(arr, max);

    return;
}