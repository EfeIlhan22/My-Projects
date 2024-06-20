#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 8

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int find_index(int arr[], int n, int head) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (arr[i] <= head && arr[i + 1] >= head) {
            return i;
        }
    }
    return n - 1;
}

void FCFS(int temp[], int head) {
    int i;
    int distance, total_distance = 0;

    printf("Seek Sequence: \n");
    for (i = 0; i < SIZE; i++) {
        printf("head = %d", head);
        distance = abs(temp[i] - head);
        printf(" --> %d seek_count = %d\n", temp[i], distance);
        total_distance += distance;
        head = temp[i];
    }
    printf("\nTotal seek count = %d\n", total_distance);
}

void SSTF(int temp[], int head) {
    int i, j, index;
    int minimum, distance, total_distance = 0;
    int done[SIZE] = {0};

    printf("Seek Sequence: \n");
    for (i = 0; i < SIZE; i++) {
        minimum = INT_MAX;
        for (j = 0; j < SIZE; j++) {
            if (!done[j] && abs(temp[j] - head) < minimum) {
                minimum = abs(temp[j] - head);
                index = j;
            }
        }
        done[index] = 1;
        printf("head = %d", head);
        distance = abs(temp[index] - head);
        printf(" --> %d seek_count = %d\n", temp[index], distance);
        total_distance += distance;
        head = temp[index];
    }
    printf("\nTotal seek count = %d\n", total_distance);
}

void Scan(int temp[], int head, int rotation) {
    int sorted[SIZE + 1], i, pos;
    int distance, total_distance = 0;

    for (i = 0; i < SIZE; i++) {
        sorted[i] = temp[i];
    }
    sorted[SIZE] = head;
    mergeSort(sorted, 0, SIZE);
    pos = find_index(sorted, SIZE + 1, head);

    printf("Seek Sequence: \n");
    if (rotation == 2) { // Right
        for (i = pos + 1; i <= SIZE; i++) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
        for (i = pos - 1; i >= 0; i--) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
    } else { // Left
        for (i = pos - 1; i >= 0; i--) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
        for (i = pos + 1; i <= SIZE; i++) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
    }
    printf("\nTotal seek count = %d\n", total_distance);
}

void Cscan(int temp[], int head, int rotation) {
    int sorted[SIZE + 2], i, pos;
    int distance, total_distance = 0;

    for (i = 0; i < SIZE; i++) {
        sorted[i] = temp[i];
    }
    sorted[SIZE] = head;
    sorted[SIZE + 1] = 199; // Assuming max disk size of 199
    mergeSort(sorted, 0, SIZE + 1);
    pos = find_index(sorted, SIZE + 2, head);

    printf("Seek Sequence: \n");
    if (rotation == 2) { // Right
        for (i = pos + 1; i < SIZE + 2; i++) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
        for (i = 0; i <= pos; i++) {
            if (i == 0) {
                printf("head = %d", head);
                printf(" --> %d Jump!!\n", sorted[i]);
                head = sorted[i];
            } else {
                printf("head = %d", head);
                distance = abs(sorted[i] - head);
                printf(" --> %d seek_count = %d\n", sorted[i], distance);
                total_distance += distance;
                head = sorted[i];
            }
        }
    } else { // Left
        for (i = pos; i >= 0; i--) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
        for (i = SIZE + 1; i > pos; i--) {
            if (i == SIZE + 1) {
                printf("head = %d", head);
                printf(" --> %d Jump!!\n", sorted[i]);
                head = sorted[i];
            } else {
                printf("head = %d", head);
                distance = abs(sorted[i] - head);
                printf(" --> %d seek_count = %d\n", sorted[i], distance);
                total_distance += distance;
                head = sorted[i];
            }
        }
    }
    printf("\nTotal seek count = %d\n", total_distance);
}

void Look(int temp[], int head, int rotation) {
    int sorted[SIZE + 1], i, pos;
    int distance, total_distance = 0;

    for (i = 0; i < SIZE; i++) {
        sorted[i] = temp[i];
    }
    sorted[SIZE] = head;
    mergeSort(sorted, 0, SIZE);
    pos = find_index(sorted, SIZE + 1, head);

    printf("Seek Sequence: \n");
    if (rotation == 2) { // Right
        for (i = pos + 1; i < SIZE + 1; i++) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
        for (i = pos - 1; i >= 0; i--) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
    } else { // Left
        for (i = pos - 1; i >= 0; i--) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
        for (i = pos + 1; i < SIZE + 1; i++) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
    }
    printf("\nTotal seek count = %d\n", total_distance);
}

void Clook(int temp[], int head, int rotation) {
    int sorted[SIZE], i, pos;
    int distance, total_distance = 0;

    for (i = 0; i < SIZE; i++) {
        sorted[i] = temp[i];
    }
    mergeSort(sorted, 0, SIZE - 1);
    pos = find_index(sorted, SIZE, head);

    printf("Seek Sequence: \n");
    if (rotation == 2) { // Right
        for (i = pos + 1; i < SIZE; i++) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
        for (i = 0; i <= pos; i++) {
            if (i == 0) {
                printf("head = %d", head);
                printf(" --> %d Jump!!\n", sorted[i]);
                head = sorted[i];
            } else {
                printf("head = %d", head);
                distance = abs(sorted[i] - head);
                printf(" --> %d seek_count = %d\n", sorted[i], distance);
                total_distance += distance;
                head = sorted[i];
            }
        }
    } else { // Left
        for (i = pos; i >= 0; i--) {
            printf("head = %d", head);
            distance = abs(sorted[i] - head);
            printf(" --> %d seek_count = %d\n", sorted[i], distance);
            total_distance += distance;
            head = sorted[i];
        }
        for (i = SIZE - 1; i > pos; i--) {
            if (i == SIZE - 1) {
                printf("head = %d", head);
                printf(" --> %d Jump!!\n", sorted[i]);
                head = sorted[i];
            } else {
                printf("head = %d", head);
                distance = abs(sorted[i] - head);
                printf(" --> %d seek_count = %d\n", sorted[i], distance);
                total_distance += distance;
                head = sorted[i];
            }
        }
    }
    printf("\nTotal seek count = %d\n", total_distance);
}

int main() {
    int arr[SIZE] = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;
    int direction;
    int choice;
    int i = 1;
    
    printf("----Disk Management Algorithms----\n");
    while (i != 0) {
        printf("\n\nSelect The Disk Management Algorithms You Want To Use: \n\n");
        printf("First Come First Serve--1 \n");
        printf("Shortest Seek Time First--2 \n");
        printf("Scan (Elevator)--3 \n");
        printf("C-Scan (Circular Scan)--4 \n");
        printf("Look--5 \n");
        printf("C-Look (Circular Look)--6 \n");
        printf("Exit--0\n");

        printf("Choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1: FCFS(arr, head); break;
            case 2: SSTF(arr, head); break;
            case 3: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Scan(arr, head, direction);
                    break;
            case 4: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Cscan(arr, head, direction); break;
            case 5: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Look(arr, head, direction); break;
            case 6: printf("Please Enter Your Disk Rotation (1 for Left & 2 for Right): \t");
                    scanf("%d", &direction);
                    Clook(arr, head, direction); break;
            case 0: i = 0; break;
            default: printf("\n Error--\n");
        }
    }
    return 0;
}
