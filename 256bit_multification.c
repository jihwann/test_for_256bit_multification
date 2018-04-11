#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long u64;
typedef unsigned int u32;

int main(void) {
	u64 right = 0x00000000FFFFFFFF;

	int i = 0, j = 0;
	u32 final_result[8] = { 0, };
	u64 result[4][4] = {{0,},};
	u32 a[4] = { 0xD94B0DCB,0x81896E34 , 0xC649CEF6,0x5DBDD571 };
	u32 b[4] = { 0xDAC1A3A4,0x1305DC93, 0x45086119,0xD66A3A39 };

	u32 mul0[4][8] = { {0,}, };
	u32 mul1[4][8] = { { 0, }, };
	u32 mul2[4][8] = { { 0, }, };
	u32 mul3[4][8] = { { 0, }, };

	u32 carry[8] = { 0, };

	u64 test[8] = { 0, };

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			result[i][j] = (u64)a[3 - j] * (u64)b[3 - i];
		}
	}
	
	mul0[0][6] = (u32)(result[0][0] >> 32);  
	mul0[0][7] = (u32)(result[0][0]);
	mul0[1][5] = (u32)(result[0][1] >> 32);
	mul0[1][6] = (u32)(result[0][1]);
	mul0[2][4] = (u32)(result[0][2] >> 32);
	mul0[2][5] = (u32)(result[0][2]);
	mul0[3][3] = (u32)(result[0][3] >> 32);
	mul0[3][4] = (u32)(result[0][3]);
	
	mul1[0][5] = (u32)(result[1][0] >> 32);
	mul1[0][6] = (u32)(result[1][0]);
	mul1[1][4] = (u32)(result[1][1] >> 32);
	mul1[1][5] = (u32)(result[1][1]);
	mul1[2][3] = (u32)(result[1][2] >> 32);
	mul1[2][4] = (u32)(result[1][2]);
	mul1[3][2] = (u32)(result[1][3] >> 32);
	mul1[3][3] = (u32)(result[1][3]);

	mul2[0][4] = (u32)(result[2][0] >> 32);
	mul2[0][5] = (u32)(result[2][0]);
	mul2[1][3] = (u32)(result[2][1] >> 32);
	mul2[1][4] = (u32)(result[2][1]);
	mul2[2][2] = (u32)(result[2][2] >> 32);
	mul2[2][3] = (u32)(result[2][2]);
	mul2[3][1] = (u32)(result[2][3] >> 32);
	mul2[3][2] = (u32)(result[2][3]);

	mul3[0][3] = (u32)(result[3][0] >> 32);
	mul3[0][4] = (u32)(result[3][0]);
	mul3[1][2] = (u32)(result[3][1] >> 32);
	mul3[1][3] = (u32)(result[3][1]);
	mul3[2][1] = (u32)(result[3][2] >> 32);
	mul3[2][2] = (u32)(result[3][2]);
	mul3[3][0] = (u32)(result[3][3] >> 32);
	mul3[3][1] = (u32)(result[3][3]);

	//test[7] = mul0[0][7]; 
	final_result[7] = mul0[0][7];   

	test[6] = ((u64)mul0[0][6]&right) + ((u64)mul0[1][6] & right) + ((u64)mul1[0][6] & right);
	if (test[6] > right) {
		carry[6] = (u32)(test[6] >> 32);
		final_result[6] = (u32)(test[6] & right);
	}
	else {
		final_result[6] = (u32)(test[6]);
	}

	test[5] = ((u64)mul0[1][5] & right) + ((u64)mul0[2][5] & right) + ((u64)mul1[0][5] & right) +
		((u64)mul1[1][5] & right) + ((u64)mul2[0][5] & right)+ ((u64)carry[6] & right);
	if (test[5] > right) {
		carry[5] = (u32)(test[5] >> 32);
		final_result[5] = (u32)(test[5] & right);
	}
	else {
		final_result[5] = (u32)(test[5]);
	}
	
	test[4] = ((u64)mul0[2][4] & right) + ((u64)mul0[3][4] & right) + ((u64)mul1[1][4] & right) + ((u64)mul1[2][4] & right) +
		((u64)mul2[0][4] & right) + ((u64)mul2[1][4] & right) + ((u64)mul3[0][4] & right) + ((u64)carry[5] & right);
	if (test[4] > right) {
		carry[4] = (u32)(test[4] >> 32);
		final_result[4] = (u32)(test[4] & right); 
	}
	else {
		final_result[4] = (u32)(test[4]);
	}
	
	test[3] = ((u64)mul0[3][3] & right) + ((u64)mul1[2][3] & right) + ((u64)mul1[3][3] & right) + ((u64)mul2[1][3] & right) + ((u64)mul2[2][3] & right) +
		((u64)mul3[0][3] & right) + ((u64)mul3[1][3] & right) + ((u64)carry[4] & right);
	if (test[3] > right) {
		carry[3] = (u32)(test[3] >> 32);
		final_result[3] = (u32)(test[3] & right);
	}
	else {
		final_result[3] = (u32)(test[3]);
	}

	test[2] = ((u64)mul1[3][2] & right) + ((u64)mul2[2][2] & right) + ((u64)mul2[3][2] & right) + ((u64)mul3[1][2] & right) +
		((u64)mul3[2][2] & right) + ((u64)carry[3] & right);
	if (test[2] > right) {
		carry[2] = (u32)(test[2] >> 32);
		final_result[2] = (u32)(test[2] & right);
	}
	else {
		final_result[2] = (u32)(test[2]);
	}

	test[1] = ((u64)mul2[3][1] & right) + ((u64)mul3[2][1] & right) + ((u64)mul3[3][1] & right) + ((u64)carry[2] & right);
	if (test[1] > right) {
		carry[1] = (u32)(test[1] >> 32);
		final_result[1] = (u32)(test[1] & right);
	}
	else {
		final_result[1] = (u32)(test[1]);
	}

	test[0] = ((u64)mul3[3][0] & right) + ((u64)carry[1] & right);
	if (test[0] > right) {
		carry[0] = (u32)(test[0] >> 32);
		final_result[0] = (u32)(test[0] & right);
	}
	else {
		final_result[0] = (u32)(test[0]);
	}


	printf("0x ");
	if (carry[0] != 0) {
		printf("%p ", carry[0]);
	}
	for (i = 0; i < 8; i++) {
		printf("%08p ", final_result[i]);
	}
	
	return 0;
}