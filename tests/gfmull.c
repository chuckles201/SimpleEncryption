#include <stdio.h>
#include <string.h>
#include <stdint.h>



#define R_SIZE 4
#define C_SIZE 4
#define SIZE R_SIZE*C_SIZE



///////HELPER////////
// print BITS helper
void print_bits(uint8_t n) {
    // print largest bit, smallest
    // shifting moves and replaces w/zero
    for(int i = 7; i >= 0; i--) {
        printf("%d",(n>>i)&0b00000001);
    }printf("\n");
}


//////\HELPER\///////

// mix-matrix
uint8_t mix_matrix[16] = {
    0x02, 0x03, 0x01, 0x01,
    0x01, 0x02, 0x03, 0x01,
    0x01, 0x01, 0x02, 0x03,
    0x03, 0x01, 0x01, 0x02
};

uint8_t block[16];

// xor
void x_or( uint8_t* arr_key,uint8_t* inArray) {
    for (int i = 0; i < SIZE; i++) {
        inArray[i] = arr_key[i] ^ inArray[i];
    }
}

///////////GF(2^8) mull!///////////
// lookup eventually?

// no need to actually have a larger representation,
// just a way to track if bits too-large!

// Gallois Field multiplication!
// russian peasent equivalence


// 0b100011011 -- irreducible
// ignore 1st, implied destroys
const uint8_t irreducible = 0b00011011;
uint8_t gf_mul(uint8_t n1, uint8_t n2){
    uint8_t result = 0;
    uint8_t temp;
    uint8_t overflow = 0;

    // double/half 8 times
    while(n2) {
        // check if we do multiplication,
        // or pass...
        if (n2 & 0b00000001){
            result ^= n1;
        }

        // check overflow
        if (n1 & 0x80) {
            overflow = 1;
        }

        // double a
        n1 <<= 1;

        

        // equivalent to modular reduction!
        if (overflow) {
            n1 ^= irreducible;
            overflow = 0;
        }

        // check if next higher is active
        // == to russian peasent mul
        n2 >>= 1;

    }
    return result;
}
//////////\GF(2^8) mull!\//////////

///////////MIXCOLLS///////////
// full mix collumns
void mix_cols(uint8_t* m1, uint8_t* m2,uint8_t* output) {
    uint8_t tempMat[SIZE]; // temp, copy to m2 later
    // each row
    for (int r = 0; r < C_SIZE; r++) {
        // each collumns
        for (int c = 0; c < R_SIZE; c++){
            //  dot product of mBy row=r, inMat col=c
            // element r,c computed
            uint8_t tempint = 0;
            printf("\nDot %d,%d == ",r,c);
            for (int i = 0; i < 4; i++) {
                // given row * collumn, xor
                printf("%d*%d+",m1[r*4 + i], m2[c + i*4]);
                tempint ^= gf_mul(m1[r*4 + i], m2[c + i*4]);
            }
            printf("\n == %d\n",tempint);
            tempMat[r*4+c] = tempint;
        }

    }
    memcpy(output,tempMat,SIZE);

}

// reverse mix collumns
/*
This is the inverse matrix, which is possible because:
- Multiplication has inverse (bc irreducible is 'prime')
- Addition is its own inverse!

When we have the ability to inverse, it becomes
possible to take the inverse of the matrix.
*/
// use lookup table irl
uint8_t r_mix_matrix[16] = {
    14,11,13,9,
    9,14,11,13,
    13,9,14,11,
    11,13,9,14
};

///////////\MIXCOLLS\//////////



int main () {
    // copying block...
    uint8_t state[SIZE] = {
        0x63,0xf2,0x01,0xd4,
        0x47,0x0a,0x01,0xd4,
        0xa2,0x22,0x01,0xd4,
        0xf0,0x5c,0x01,0xd5
    };
    // mixer,input
    mix_cols(mix_matrix,state,state);
    mix_cols(r_mix_matrix,state,state);
    for (int i = 0; i< SIZE; i++) {
        if(i%4 == 0 && (int)(i / 4) != 0) {
            printf("\n");
        }
        printf("%02X ",state[i]);
    }
    

    return 0;
}