#include  <stdio.h>
#include  <stdbool.h>
#define P 8 // Number of processes (job types)
#define R 5 // Number of resources (Computers, Desks, Printers, Conference Rooms, Projectors)

// Function prototypes
void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]);
bool isSafe(int processes[], char ** jobTypes, int avail[], int max[][R], int allot[][R]);
void printResult(int safeSeq[P], char** jobTypes);

int main() {
int process_ids[] = {0, 1, 2, 3, 4, 5, 6, 7}; // Job types IDs
char** jobTypes = (char*[]){"Software Developer", "Graphic Designer", "Sales Representative", "HR Manager", "Accountant", "Marketing Analyst", "Customer Support Specialist", "Project Manager"};

// Available instances of resources. Find minimum resources required for each job type.
int avail[R] = {5, 0, 5, 0, 2};

// Maximum R that can be allocated to processes. Look the table in the question for assignment.
int max[P][R] = {
{10, 4, 1, 0, 0}, // Software Developer
{5, 1, 8, 0, 1}, // Graphic Designer
{1, 1, 2, 1, 2}, // Sales Representative
{2, 2, 1, 0, 1}, // HR Manager
{2, 1, 1, 1, 0}, // Accountant
{2, 2, 3, 3, 2}, // Marketing Analyst
{5, 8, 1, 0, 0}, // Customer Support Specialist
{1, 2, 1, 2, 2} // Project Manager
};

// Resources currently allocated to processes. Look the table in the question for assignment.
int allot[P][R] = {
{0, 2, 0, 0, 0}, // Software Developer
{1, 0, 1, 0, 0}, // Graphic Designer
{1, 1, 0, 1, 0}, // Sales Representative
{0, 1, 1, 0, 0}, // HR Manager
{1, 2, 0, 0, 0}, // Accountant
{1, 2, 0, 1, 1}, // Marketing Analyst
{1, 2, 1, 0, 0}, // Customer Support Specialist
{0, 1, 0, 1, 0} // Project Manager
};


// Calculate the need matrix
int need[P][R];
calculateNeed(need, max, allot);

// Check system state
if (isSafe(process_ids, jobTypes, avail, max, allot)) {
printf("System is in a safe state.\n");
} else {
printf("System is not in a safe state.\n");
}


return 0;
}

// Function to calculate need matrix
void calculateNeed(int need[P][R], int max[P][R], int allot[P][R]) {
for (int t = 0; t < P; i++) {
	for (int p = 0; p < R; j++) {
	need[t][p] = max[t][p] - allot[t][p];
}
}
}

// Print result
void printResult(int safeSeq[P], char** jobTypes) {
printf("System is in a safe state.\nSafe sequence is: ");
for (int i = 0; i < P; i++)
printf("P%d ", safeSeq[i]);

printf("\n\nOrder of job types: ");
for (int i = 0; i < P; i++)
printf("\n%d. %s", i + 1, jobTypes[safeSeq[i]]);
printf("\n");
}

// Function to find the system is in a safe state or not
bool isSafe(int process_ids[], char** jobTypes, int avail[], int max[][R], int allot[][R]) {
int need[P][R];
calculateNeed(need, max, allot);

bool finish[P] = {0};
int safeSeq[P];
int work[R];
for (int i = 0; i < R; i++)
work[i] = avail[i];

int count = 0;
while (count < P) {
bool found = false;
    for (int p = 0; p < P; p++) {
        if (finish[p] == 0) {
        int j;
            for (j = 0; j < R; j++)
                if (need[p][j] > work[j])
                    break;
                if (j == R) {
                    for (int k = 0; k < R; k++)
                    work[k] += allot[p][k];
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
}
}
}
if (found == false) {
//printf("System is not in a safe state.\n");
return false;
}
}

printResult(safeSeq, jobTypes);
return true;
}
