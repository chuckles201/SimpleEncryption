#include <stdio.h>

// this means we
unsigned int x[5]  = {1,1,1,1,2};



// going thru memory
void showBytes(unsigned int x[],int n){
    unsigned char* ptr = (unsigned char*)&x[0];
    int perbyte = sizeof(x[0]);

    // for each element in order
    for (int i = 0; i < n; i++){
        // for each byte, backwards
        for (int k = (perbyte-1); k >= 0; k += -1) {
            printf("0x%02X ",ptr[k + i*perbyte]); // points to where to print!
        } printf("\n");
    }
}

// go through each int 4 byte
int main() {
    // 4 bytes, -2147483648,2147483648
    showBytes(x, (sizeof(x) / sizeof(x[0])) );
    return 0;
}