#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

unsigned char s_box[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};
unsigned char inv_s_box[16][16] = {
    { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb } ,
    { 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb } ,
    { 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e } ,
    { 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25 } ,
    { 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92 } ,
    { 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84 } ,
    { 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06 } ,
    { 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b } ,
    { 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73 } ,
    { 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e } ,
    { 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b } ,
    { 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4 } ,
    { 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f } ,
    { 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef } ,
    { 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61 } ,
    { 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d }
    };
unsigned int Rcon[] = { 
    0x00000000, 
    0x01000000, 0x02000000, 0x04000000, 0x08000000, 
    0x10000000, 0x20000000, 0x40000000, 0x80000000, 
    0x1B000000, 0x36000000, 0x6C000000, 0xD8000000, 
    0xAB000000, 0x4D000000, 0x9A000000, 0x2F000000, 
    0x5E000000, 0xBC000000, 0x63000000, 0xC6000000, 
    0x97000000, 0x35000000, 0x6A000000, 0xD4000000, 
    0xB3000000, 0x7D000000, 0xFA000000, 0xEF000000, 
    0xC5000000, 0x91000000, 0x39000000, 0x72000000, 
    0xE4000000, 0xD3000000, 0xBD000000, 0x61000000, 
    0xC2000000, 0x9F000000, 0x25000000, 0x4A000000, 
    0x94000000, 0x33000000, 0x66000000, 0xCC000000, 
    0x83000000, 0x1D000000, 0x3A000000, 0x74000000, 
    0xE8000000, 0xCB000000, 0x8D000000};
int Nr;
unsigned char ffAdd(unsigned char a, unsigned char b);
unsigned char xtime(unsigned char a);
unsigned char ffMultiply(unsigned char a, unsigned char b);
unsigned int subWord(unsigned int word);
unsigned int rotWord(unsigned int word);
void keyExpansion(unsigned char key[], unsigned int w[], int Nk);
void subBytes(unsigned char state[4][4]);
void shiftRows(unsigned char state[4][4]);
void mixColumns(unsigned char state[4][4]);
void addRoundKey(unsigned char state[4][4], unsigned int w[], int roundNb);
void cipher(unsigned char in[16], unsigned char out[16], unsigned int w[]);
void invSubBytes(unsigned char state[4][4]);
void invShiftRows(unsigned char state[4][4]);
void invMixColumns(unsigned char state[4][4]);
void invCipher(unsigned char in[16], unsigned char out[16], unsigned int w[]);
void toString(int round, char* currentStep, unsigned char arr[16]);
void toString2d(int round, char* currentStep, unsigned char arr[4][4]);
void toStringSch(int round, char* currentStep, unsigned int arr[]);
void toStringSchInv(int round, char* currentStep, unsigned int arr[]);


int main()
{
    ///////////////////////////////
    // AES-128 (Nk = 4, Nr = 10)
    ///////////////////////////////

    Nr = 10;
    unsigned int w[4 * (Nr + 1)];
    unsigned char key[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

    keyExpansion(key, w, 4);

    unsigned char in[16]  = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };

    unsigned char out[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    printf("CIPHER (ENCRYPT):\n");
    toString(0, "input", in);
    cipher(in, out, w);
    toString(Nr, "output", out);

    printf("\nINVERSE CIPHER (DECRYPT):\n");
    toString(0, "iinput", out);
    invCipher(out, in, w);
    toString(Nr, "ioutput", in);


    ///////////////////////////////
    // AES-192 (Nk = 6, Nr = 12)
    ///////////////////////////////

    Nr = 12;
    unsigned int w2[4 * (Nr + 1)];
    unsigned char key2[24] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 
            0x13, 0x14, 0x15, 0x16, 0x17};

    keyExpansion(key2, w2, 6);

    unsigned char in2[16]  = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };

    unsigned char out2[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    printf("\nCIPHER (ENCRYPT):\n");
    toString(0, "input", in2);
    cipher(in2, out2, w2);
    toString(Nr, "output", out2);

    printf("\nINVERSE CIPHER (DECRYPT):\n");
    toString(0, "iinput", out2);
    invCipher(out2, in2, w2);
    toString(Nr, "ioutput", in2);



    ///////////////////////////////
    // AES-256 (Nk = 8, Nr = 14)
    ///////////////////////////////

    Nr = 14;
    unsigned int w3[4 * (Nr + 1)];
    unsigned char key3[32] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 
            0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};

    keyExpansion(key3, w3, 8);

    unsigned char in3[16]  = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };

    unsigned char out3[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    printf("\nCIPHER (ENCRYPT):\n");
    toString(0, "input", in3);
    cipher(in3, out3, w3);
    toString(Nr, "output", out3);

    printf("\nINVERSE CIPHER (DECRYPT):\n");
    toString(0, "iinput", out3);
    invCipher(out3, in3, w3);
    toString(Nr, "ioutput", in3);



    return 0;
}

unsigned char ffAdd(unsigned char a, unsigned char b) {
    return a ^ b;
}

unsigned char xtime(unsigned char a) {
    unsigned char result = a << 1;

    if (a & 0x80)
        return result ^ 0x1B;
    else
        return result;
}

unsigned char ffMultiply(unsigned char a, unsigned char b) {
    int numOfShifts = -1;
    unsigned char tmp = b;

    while(tmp != 0) {
        tmp = tmp >> 1;
        numOfShifts++;
    }

    unsigned char results[numOfShifts + 1];
    results[0] = a;
    for (int i = 0; i < numOfShifts; i++) {
        results[i + 1] = xtime(results[i]);
    }

    unsigned char value = 0, mask = 0x01;
    int index = 0;

    for (int i = 0; i < numOfShifts + 1; i++) {
        // Check each bit in b to see if it is set
        // If it is set, ffAdd the value with the xtime result at that bit
        if (mask & b) {
            value = ffAdd(value, results[index]);
        }

        mask = mask << 1;
        index++;
        // printf("temp value: %x\n", value);
    }

    return value;
}

unsigned int subWord(unsigned int word) {
    unsigned int word_cpy = word, tmp = 0, result = 0;

    for (int i = 0; i < 25; i += 8) {
        // Extract each byte of the word
        tmp = (word_cpy >> i) & 0xFF;

        // Look up the replacement byte in the s_box
        tmp = s_box[tmp >> 4][tmp & 0xF];

        // Build the new word with the results from s_box
        result = result | tmp << i;
    }

    return result;
}

unsigned int rotWord(unsigned int word) {
    unsigned int result = 0;

    // Put the first byte of word at the end of result
    result = result | (word >> 24);

    // Move everything in word over a byte
    result = result | (word << 8);

    return result;
}

void keyExpansion(unsigned char key[], unsigned int w[], int Nk) {
    unsigned int temp;
    int i = 0, Nb = 4;

    while (i < Nk) {
        temp = 0;
        // Build word
        temp = key[4 * i] << 24 | key[4 * i + 1] << 16 | key[4 * i + 2] << 8| key[4 * i + 3];
        w[i] = temp;
        i++;
    }

    i = Nk;

    while (i < Nb * (Nr + 1)) {
        temp = w[i - 1];
        // printf("i: %d temp: %x ", i, temp);
        if (i % Nk == 0)
            temp = subWord(rotWord(temp)) ^ Rcon[i / Nk];
        else if ((Nk > 6) && (i % Nk == 4))
            temp = subWord(temp);

        // printf("Rcon[i/Nk]: %x w[i-Nk]: %x ", Rcon[i / Nk], temp);

        w[i] = w[i - Nk] ^ temp;
        // printf("w[i] = temp XOR w[i-Nk]: %x\n", w[i]);
        i++;
    }
}

void subBytes(unsigned char state[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = s_box[state[j][i] >> 4][state[j][i] & 0xF];
        }
    }
}

void shiftRows(unsigned char state[4][4]) {
    int size = 4;
    unsigned char tempArr[4];

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            // Use circular array arithmetic
            tempArr[j] = state[i][(j + i) % size];
        }
        for (size_t j = 0; j < size; j++) {
            state[i][j] = tempArr[j];
        }
    }
}

void mixColumns(unsigned char state[4][4]) {
    int size = 4;
    unsigned char tempArr[4];

    for (size_t i = 0; i < size; i++) {
        unsigned char s0 = state[0][i], s1 = state[1][i], s2 = state[2][i], s3 = state[3][i];

        tempArr[0] = ffMultiply(0x02, s0) ^ ffMultiply(0x03, s1) ^ s2 ^ s3;
        tempArr[1] = s0 ^ ffMultiply(0x02, s1) ^ ffMultiply(0x03, s2) ^ s3;
        tempArr[2] = s0 ^ s1 ^ ffMultiply(0x02, s2) ^ ffMultiply(0x03, s3);
        tempArr[3] = ffMultiply(0x03, s0) ^ s1 ^ s2 ^ ffMultiply(0x02, s3);

        for (size_t j = 0; j < size; j++)
            state[j][i] = tempArr[j];
    }
    
}

void addRoundKey(unsigned char state[4][4], unsigned int w[], int roundNb) {
    int size = 4;
    unsigned int column = 0;

    for (size_t i = 0; i < size; i++) {
        // Turn each column of state into a word
        column = state[0][i] << 24 | state[1][i] << 16 | state[2][i] << 8 | state[3][i];

        // XOR that word with the corresponding word from the key schedule
        column = w[roundNb + i] ^ column;

        // Replace the original column in the state with the new one
        state[0][i] = column >> 24 & 0xFF;
        state[1][i] = column >> 16 & 0xFF;
        state[2][i] = column >> 8 & 0xFF;
        state[3][i] = column & 0xFF;
    }
}

void cipher(unsigned char in[16], unsigned char out[16], unsigned int w[]) {
    unsigned char state[4][4];
    int index = 0;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            state[j][i] = in[index];
            index++;
        }
    }

    addRoundKey(state, w, 0 * 4);
    toStringSch(0, "k_sch", w);
    for (size_t round = 1; round < Nr; round++) {
        toString2d(round, "start", state);
        subBytes(state);
        toString2d(round, "s_box", state);
        shiftRows(state);
        toString2d(round, "s_row", state);
        mixColumns(state);
        toString2d(round, "m_col", state);
        addRoundKey(state, w, round * 4);
        toStringSch(round, "k_sch", w);
    }

    toString2d(Nr, "start", state);
    subBytes(state);
    toString2d(Nr, "s_box", state);
    shiftRows(state);
    toString2d(Nr, "s_row", state);
    addRoundKey(state, w, Nr * 4);
    toStringSch(Nr, "k_sch", w);

    index = 0;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            out[index] = state[j][i];
            index++;
        }
    }
}

void invSubBytes(unsigned char state[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = inv_s_box[state[j][i] >> 4][state[j][i] & 0xF];
        }
    }
}

void invShiftRows(unsigned char state[4][4]) {
    int size = 4;
    unsigned char tempArr[4];

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            // Use circular array arithmetic
            tempArr[j] = state[i][(j - i + size) % size];
        }
        for (size_t j = 0; j < size; j++) {
            state[i][j] = tempArr[j];
        }
    }
}

void invMixColumns(unsigned char state[4][4]) {
    int size = 4;
    unsigned char tempArr[4];

    for (size_t i = 0; i < size; i++) {
        unsigned char s0 = state[0][i], s1 = state[1][i], s2 = state[2][i], s3 = state[3][i];

        tempArr[0] = ffMultiply(0x0e, s0) ^ ffMultiply(0x0b, s1) ^ ffMultiply(0x0d, s2) ^ ffMultiply(0x09, s3);
        tempArr[1] = ffMultiply(0x09, s0) ^ ffMultiply(0x0e, s1) ^ ffMultiply(0x0b, s2) ^ ffMultiply(0x0d, s3);
        tempArr[2] = ffMultiply(0x0d, s0) ^ ffMultiply(0x09, s1) ^ ffMultiply(0x0e, s2) ^ ffMultiply(0x0b, s3);
        tempArr[3] = ffMultiply(0x0b, s0) ^ ffMultiply(0x0d, s1) ^ ffMultiply(0x09, s2) ^ ffMultiply(0x0e, s3);

        for (size_t j = 0; j < size; j++)
            state[j][i] = tempArr[j];
    }
}

void invCipher(unsigned char in[16], unsigned char out[16], unsigned int w[]) {
    unsigned char state[4][4];
    int index = 0;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            state[j][i] = in[index];
            index++;
        }
    }

    printf("round [ %d].%s      ", 0, "ik_sch");
    for (size_t i = 0; i < 4; i++) 
        printf("%08x", w[Nr * 4 + i]);
    printf("\n");
    addRoundKey(state, w, Nr * 4);

    for (size_t round = Nr - 1; round > 0; round--) {
        toString2d(abs(round - Nr), "istart", state);
        invShiftRows(state);
        toString2d(abs(round - Nr), "is_row", state);
        invSubBytes(state);
        toString2d(abs(round - Nr), "is_box", state);
        addRoundKey(state, w, round * 4);
        toStringSchInv(round, "ik_sch", w);
        toString2d(abs(round - Nr), "ik_add", state);
        invMixColumns(state);
    }

    toString2d(Nr, "istart", state);
    invShiftRows(state);
    toString2d(Nr, "is_row", state);
    invSubBytes(state);
    toString2d(Nr, "is_box", state);
    addRoundKey(state, w, 0 * 4);
    printf("round [%d].%s      ", Nr, "ik_sch");
    for (size_t i = 0; i < 4; i++) 
        printf("%08x", w[0 * 4 + i]);
    printf("\n");

    index = 0;
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            out[index] = state[j][i];
            index++;
        }
    }
}

void toString(int round, char* currentStep, unsigned char arr[16]) {
    if (round < 10)
        printf("round [ %d].%s     ", round, currentStep);
    else
        printf("round [%d].%s     ", round, currentStep);

    if (strcmp(currentStep, "output") && strcmp(currentStep, "ioutput"))
        printf(" ");

    for (size_t i = 0; i < 16; i++) 
        printf("%02x", arr[i]);
    printf("\n");
}

void toStringSch(int round, char* currentStep, unsigned int arr[]) {
    if (round < 10)
        printf("round [ %d].%s      ", round, currentStep);
    else
        printf("round [%d].%s      ", round, currentStep);

    for (size_t i = 0; i < 4; i++) 
        printf("%08x", arr[round * 4 + i]);
    printf("\n");
}

void toStringSchInv(int round, char* currentStep, unsigned int arr[]) {
    if (round < 10)
        printf("round [ %d].%s      ", abs(round - Nr), currentStep);
    else
        printf("round [%d].%s      ", abs(round - Nr), currentStep);

    for (size_t i = 0; i < 4; i++) 
        printf("%08x", arr[round * 4 + i]);
    printf("\n");
}

void toString2d(int round, char* currentStep, unsigned char arr[4][4]) {
    if (round < 10)
        printf("round [ %d].%s      ", round, currentStep);
    else
        printf("round [%d].%s      ", round, currentStep);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) 
            printf("%02x", arr[j][i]);
    }
    printf("\n");
}