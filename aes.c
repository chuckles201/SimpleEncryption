#include <stdio.h>
#include <string.h>
#include <stdint.h>



uint8_t rc[7][4] = {
                            {0x01,0x00,0x00,0x00},
                            {0x02,0x00,0x00,0x00},
                            {0x04,0x00,0x00,0x00},
                            {0x08,0x00,0x00,0x00},
                            {0x10,0x00,0x00,0x00},
                            {0x20,0x00,0x00,0x00},
                            {0x40,0x00,0x00,0x00}};

const uint8_t sbox[256] = {
    //0     1     2     3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };


const uint8_t rsbox[256] = {
    //0     1     2     3     4    5     6     7      8    9     A      B    C     D     E     F
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

#define R_SIZE 4
#define C_SIZE 4
#define BLOCK_SIZE 16
#define NUM_KEYS 15

// padding 
void addPadding(uint8_t* arrPtr,uint8_t fileSize,uint8_t expectedSize) {   

    uint8_t difference = expectedSize-fileSize;
    printf("DIFFERENCE:%d\n",difference);

    if (difference == 0) {
        ;
    }
    else {
        for (uint8_t i = 0; i < difference; i++) {
            arrPtr[i+fileSize] = difference;
            
        }
    }
}
///////////

///////////KEY EXPANSION//////////////

void print_ascii(uint8_t* arr) {
    for (int i = 0; i < BLOCK_SIZE; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// gets key, adding padding!
void get_key(uint8_t key[32]) {
    printf("Enter Key (max %d bytes ASCII) :",32);
    fgets((char *)key,32,stdin);

    // length of key string
    // removing \n
    uint8_t size = strlen((char*)key);
    key[size-1] = 0;
    size -= 1;

    addPadding(key,size,BLOCK_SIZE*2);
    printf("\nKey :%s\n",key);
    print_ascii(key);
}
void x_or_array(uint8_t inArray[4],uint8_t outArray[4]) {
    for (int i = 0; i < 4; i++) {
        outArray[i] ^= inArray[i];
    }
}
// Rotate collumns
// Confuse word a little,
// each round bits affect different positons
// original key bits affect almost all positions
void rot_col(uint8_t inArray[4],uint8_t outArray[4]) {
    // save 0th position...
    uint8_t tmp_place = inArray[0];
    for (int i = 0; i < C_SIZE-1; i++) {
        // save just vector of values
        // save to collumn before!
        outArray[i] = inArray[(i+1)%4];
    }
    // saving at final spot
    outArray[3] = tmp_place;

}

// substitute bytes for collumn!
void sub_bytes_key(uint8_t inArray[4],uint8_t outArray[4]) {
    // substitute first and switch around!
    for (int i = 0; i < C_SIZE; i++) {
        // if 10 = 0x0A --> 26 = 0x1F
        // then, 26 is at 10th index!
        outArray[i] = sbox[inArray[i]];
    }
}

// Entire algo!
/*
First do all necessary things to first row,
then xor with prev first row (0s if none), and
the round constant.

After this, we simply xor the prev. matrix with
the prev row, and repeat for each val, until we do
8 words, then the next matrix!

- AES 256, every 4 words we must do subbyte!

Fill matrix like:
| b0   b4   b8  b12 |
| b1   b5   b9  b13 |
| b2   b6  b10  b14 |
| b3   b7  b11  b15 |
*/
void keyExpansion(uint8_t inKey[32],uint8_t full_key[60][4]) {
    // key --> collumn (word) --> row
    // extracting thiss from key:
    for (int c = 0; c < 8; c++) {
        for(int r = 0; r < 4; r++) {
            full_key[c][r] = inKey[c*4+r];
        }
    }

    // operating on individual words
    for (int word = 8; word < 15*4; word++){
        if (word % 8 == 0){ // do full operation
            // take last key, rot,sub,rc/xor
            rot_col(full_key[word-1],full_key[word]);
            sub_bytes_key(full_key[word],full_key[word]);
            x_or_array(rc[(int)(word-8) / 8],full_key[word]); 

            x_or_array(full_key[word-8],full_key[word]);


        }
        else if (word % 4 == 0){
            // just add subytes to step
            x_or_array(full_key[word-1],full_key[word]);
            sub_bytes_key(full_key[word-1],full_key[word]);
            x_or_array(full_key[word-8],full_key[word]);
            
        } else {
            // simple xor w/ prev block and prev word
             x_or_array(full_key[word-1],full_key[word]);
             x_or_array(full_key[word-8],full_key[word]);
        }
        // do what we alwasy do; xor with prev one!
        
        
    }

}


// adding to round constant

// 4. derive rest of keys, do N rounds


/////////////////////////

// bytes per block
// hold block in memory
uint8_t block[BLOCK_SIZE];

///////////BLOCK ENCRYPTION////////////


// 1. ADD ROUND KEY
void x_or( uint8_t* arr_key,uint8_t* inArray) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        inArray[i] = arr_key[i] ^ inArray[i];
    }
}

// 2. SUB BYTES

void sub_bytes(uint8_t* inArray) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        // if 10 = 0x0A --> 26 = 0x1F
        // then, 26 is at 10th index!
        inArray[i] = sbox[inArray[i]];
    }
}

// 3, Shift rows 
/*
R  Action
1. Push 0
2. Push 3
3. Push 2
4. Push 1

Really this is just the best
permutation we can acheive
given the amount of rows we have.

Think of all things traveling at
diff speed they can (with all used), this is always
best!
*/
void shift_rows(uint8_t* inArray){
    // bc modified, save 1st!
    static uint8_t temp[BLOCK_SIZE];
    memcpy(temp,inArray,BLOCK_SIZE);
    // col-major
    for (int r = 0; r < C_SIZE; r++) { // dont do first row!
        // each col
        for (int c = 0; c < R_SIZE; c++) {
            // push back by r, new pos is r forward!
            int8_t new_pos = r +C_SIZE*( (4-r+c) % 4);
            inArray[r + c*C_SIZE] = temp[new_pos];
        }
    }
}

// 4. Mix Collumns
/*
Most important step for diffusion, ensures
each small change in a number in the collumns
ensures a change throughout the collumns (and 
after multiple rounds, everything affects everything!).

We have to do 'finite' multiplication
such that when we multiply numbers, they have
inverses, and satisfy normal properties of multiplication,
but do NOT go outside of the 256 range for our bytes!

- Our addition is just simply xor, this satisfies the properties
for addition in a finite field
- Our multiplication, similarly, is polynomial multiplication,
that is done mod with 'prime' irreducible polynomial:
    ---> x^8+x^4+x^3+x+1
    - Doing this multiplication ensures that bits are mixed well
    (each bit plays a little part), and when values get larger, the
    modulo will be hard to predict (semi-random behavior)
    - Furthermore, we can reverse the operation of multiplcation
    because the field has an inverse
*/
// mix-matrix
uint8_t mix_matrix[4][4] = {
    {0x02, 0x03, 0x01, 0x01}, // row 1

    {0x01, 0x02, 0x03, 0x01}, // row 2

    {0x01, 0x01, 0x02, 0x03}, // row 3

    {0x03, 0x01, 0x01, 0x02} // row 4
};

uint8_t r_mix_matrix[4][4] = {
    {14,11,13,9}, // row 1

    {9,14,11,13},

    {13,9,14,11},

    {11,13,9,14}
};

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
void mix_cols(uint8_t m1[4][4], uint8_t* m2,uint8_t* output) {
    uint8_t tempMat[BLOCK_SIZE]; // temp, copy to m2 later
    for (int c = 0; c < C_SIZE; c++) {
        for (int r = 0; r < R_SIZE;r++){
            //  dot product of mBy row=r, inMat col=c
            // element r,c computed
            uint8_t tempint = 0;
            for (int i = 0; i < 4; i++) {
                // given row * collumn, xor
                tempint ^= gf_mul(m1[r][i], m2[c*4 + i]);
            }
            tempMat[c*4+r] = tempint;
        }

    }
    memcpy(output,tempMat,BLOCK_SIZE);

}



///////////\BLOCK ENCRYPTION\///////////




//////////// BLOCK DECRYPTION////////////

// 1. ADD BYTES --> Xor reverses self


// 2. REVERSE SUBBYTES --> Reverse byte-sub

void r_sub_bytes(uint8_t* inArray) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        // if 10 = 0x0A --> 26 = 0x1F
        // then, 26 is at 10th index!
        inArray[i] = rsbox[inArray[i]];
    }
}

// 3. Shift rows --> undo shift
void r_shift_rows(uint8_t* inArray){
    // bc modified, save 1st!
    static uint8_t temp[BLOCK_SIZE];
    memcpy(temp,inArray,BLOCK_SIZE);
    // col-major
    for (int r = 0; r < C_SIZE; r++) { // dont do first row!
        for (int c = 0; c < R_SIZE; c++) {
            int8_t new_pos = r +C_SIZE*( (r+c) % 4);
            inArray[r + c*C_SIZE] = temp[new_pos];
        }
    }
}

// 4. Mix colls --> do inverse matrix

/*
uint8_t r_mix_matrix[16] = {
    14,11,13,9,
    9,14,11,13,
    13,9,14,11,
    11,13,9,14
};
(able to compute because working in a nice field!)
*/


///////////\BLOCK DECRYPTION\///////////


// for key_xor
void x_or_key(uint8_t full_key[60][4], uint8_t block[32],int round) {
    // collumn-major!
    for(int c = 0; c < 4; c++) {
        for(int r = 0; r<4; r++){
            block[c*4+r]^=full_key[round*4+c][r];
        }
        
    }
}


// take in amt of arguments and array of ptrs to chars (filename)
int main(int argc, char* argv[]) {


    // getting keys
    uint8_t key[32];
    get_key(key);
    uint8_t full_key[60][4] = {{0}};
    keyExpansion(key,full_key);
    printf("\n\n<KEYS>\n\n");
    for(int k = 0; k< 15; k++) {
        printf("\n***KEY %d***\n",k);
        for(int r = 0; r<4; r++) {
            for(int c = 0; c<4;c++){
                printf("%02X ",full_key[k*4+c][r]);
            }printf("\n");
        }
    }
    printf("\n\n</KEYS>\n\n");
 
    // reading/writing in binary-mode
    FILE *input_file, *output_file;
    char filename[100];
    sprintf(filename,"data/%s",argv[1]);
    input_file = fopen(filename,"rb");
    sprintf(filename,"data/%s",argv[2]);
    output_file = fopen(filename,"wb");

    // opening blocks, reading/writing
    uint8_t bytes_read;
    while ( (bytes_read = fread(block,1,BLOCK_SIZE,input_file)) > 0) {
        if (bytes_read != BLOCK_SIZE) {
            addPadding(block,bytes_read,BLOCK_SIZE);
            printf("UNDER!\n");
            for(int i = 0; i<16; i++){
                printf("%02X ",block[i]);
            }printf("\n");
            break; // breaking from loop!

        }
        // encrypt mode
        if (strcmp(argv[3], "-e") == 0){
            for (int round = 0; round < NUM_KEYS; round++){
                // x_or 
                x_or_key(full_key,block,round);  
                // sub bytes inp, output
                sub_bytes(block);
                // shift rows
                shift_rows(block);
                // mix cols
                mix_cols(mix_matrix,block,block);
            }

        } 
        // decrypt mode
        else if (strcmp(argv[3],"-d") == 0){
            for (int round = NUM_KEYS-1; round >= 0; round--){
                // reversed.
                mix_cols(r_mix_matrix,block,block);
                r_shift_rows(block);
                r_sub_bytes(block);
                x_or_key(full_key,block,round); 
                
            }
        }


        
        // writing  to file
        fwrite(block,1,BLOCK_SIZE,output_file);


    }
    

    
    // final write --> ignore padding!
    // still operates as if padding was there though
    fwrite(block,1,bytes_read,output_file);
    fclose(input_file);
    fclose(output_file);
    return 0;
}

// ./run.sh students.csv encrypted.txt -e
// ./run.sh encrypted.txt decrypted.txt -d

// 123password--123!@#!@

