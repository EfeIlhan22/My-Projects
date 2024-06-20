/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

void initialize(int frames[], int time[], int frame_number);
int findLRU(int time[], int frame_number);
void processPageReference(int pages[], int frames[], int time[], int frame_number, int page_count);

int main() {
int frame_number, page_count;
printf("Enter number of frames: ");
scanf("%d", &frame_number);

printf("Enter number of pages: ");

scanf("%d", &page_count);

int frames[frame_number], pages[page_count];
initialize(frames, NULL, frame_number);

printf("Enter reference string: ");
for(int i = 0; i < page_count; ++i) {
scanf("%d", &pages[i]);
}

int time[frame_number];
initialize(NULL, time, frame_number);
processPageReference(pages, frames, time, frame_number, page_count);

return 0;
}


void initialize(int frames[], int time[], int frame_number) {
if (frames != NULL) {
for(int i = 0; i < frame_number; ++i) {
frames[i] = -1;
}
}
if (time != NULL) {
for(int i = 0; i < frame_number; ++i) {
time[i] = 0;
}
}
}

int findLRU(int time[], int frame_number) {
int minimum = time[0], pos = 0;
for(int i = 1; i < frame_number; ++i) {
    if(time[i] < minimum) {
    minimum = time[i];
    pos = i;
    }
    }
return pos;
}

void processPageReference(int pages[], int frames[], int time[], int frame_number, int page_count) {
int counter = 0;
int faults = 0;
for(int i = 0; i < page_count; ++i) {
int found = 0;
    for(int j = 0; j < frame_number; ++j) {
        if(frames[j] == pages[i]) {
        counter++;
        time[j] = counter;
        found = 1;
        break;
        
    }    
        if(frames[j] == -1) {
        counter++;
        faults++;
        frames[j] = pages[i];
        time[j] = counter;
        found = 1;
        break;
    }
}
if(found==0){
    int pos = findLRU(time, frame_number);
    counter++;
    faults++;
    frames[pos] = pages[i];
    time[pos] = counter;
}

printf("\n");
for(int j = 0; j < frame_number; ++j) {
    printf("%d\t", frames[j]);
    }
}

printf("\n\nTotal Page Faults = %d\n", faults);
}
