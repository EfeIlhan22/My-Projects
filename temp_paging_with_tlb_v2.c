#include <stdio.h>
#include <stdlib.h>
#define N 10
#define ptsize 10
#define tlbsize 5
#define phymemsize 9

int tlbindex = 0; // Global index for the next available slot in the TLB

struct address {
int id; // Page number
int offset; // Offset within the page
} va;

// Initializes the address structure
void address_init(struct address* va, int id, int offset) {
va->id = id;
va->offset = offset;
}

// Initializes the page table
void pagetable_init(int pt[]) {
for (int i = 0; i < ptsize; i++)
{
pt[i] = i;
}
}

// Initializes the TLB to default values (0)
void tlb_init(int tlb[tlbsize][2]) {
for (int i = 0; i < tlbsize; i++)
{
tlb[i][0] = 0;
tlb[i][1] = 0;
}

}

// Prints the contents of the page table
void print_table(int pt[]) {
printf("Inside the Page Table:\n");
for (int i = 0; i < ptsize; i++) {
printf("%d ", pt[i]);
}
printf("\n");
}

// Prints the contents of the TLB
void print_tlb(int tlb[][2]) {
printf("TLB inside\n");
for (int i = 0; i < tlbsize; i++)
{
printf("Page no: %d, Frame no: %d\n", tlb[i][0], tlb[i][1]);
}
}

// Searches for a page number in the TLB and returns the frame number if found
int search_in_tlb(int val, int tlb[][2]){
for (int i = 0; i < tlbsize; i++) {
if (tlb[i][0] == val) {
return tlb[i][1];
}
}
return -1;
}

// Fetches the value from physical memory using addresses translated via TLB or page table
int findvalue(struct address* va, int tlb[][2], int pt[], int phymem[][N]) {
int frameNo, valOffset = va->offset;
int found = search_in_tlb(va->id,tlb);

if (found != -1)
{
printf("\nPage found in tlb!\n");
printf("Found in TLB! Page no: %d, Frame no: %d\n", va->id, found);
frameNo = found;
}else
{
printf("\nNot Found in TLB! Search in page table please!\n");
printf("Accessing to Page Table! \n");
frameNo = pt[va->id];
printf("Page no: %d, Frame no: %d\n", va->id, frameNo);
tlb[tlbindex][0] = va->id;
tlb[tlbindex][1] = frameNo;
tlbindex = (tlbindex + 1) % tlbsize;
}
return phymem[frameNo][valOffset]; // Return the value from physical memory
}

int main() {
int tlb[tlbsize][2];
int pt[ptsize];
int phymem[phymemsize][N]; // Physical memory represented as frames and offsets
int value;

// Initialize physical memory
for (int i = 0; i < phymemsize; i++) {
for (int j = 0; j < N; j++) {
phymem[i][j] = -1;
}
}
phymem[1][5] = 19;
phymem[0][6] = 55;
phymem[2][6] = 99;

printf("Physical MEMORY:\n");
for (int i = 0; i < phymemsize; i++) {
for (int j = 0; j < N; j++) {
printf("%d ", phymem[i][j]);
}
printf("\n");
}


srand(992); // Seed for random number generation

pagetable_init(pt);
printf("FIRST VERSION OF PAGE TABLE:\n");
print_table(pt);
tlb_init(tlb);
printf("\nFIRST VERSION OF TBL:\n");
print_tlb(tlb);

address_init(&va, 2, 5);
value = findvalue(&va, tlb, pt, phymem);
printf("Value: %d\n\n", value);
print_tlb(tlb);

address_init(&va, 1, 5);
value = findvalue(&va, tlb, pt, phymem);
printf("Value: %d\n\n", value);
print_tlb(tlb);

address_init(&va, 2, 6);
value = findvalue(&va, tlb, pt, phymem);
printf("Value: %d\n\n", value);
print_tlb(tlb);

address_init(&va, 2, 6);
value = findvalue(&va, tlb, pt, phymem);
printf("Value: %d\n\n", value);
print_tlb(tlb);

return 0;
}
