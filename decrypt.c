#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tablecheck.h"
#include "utilities.h"
#include "DES.h"

void decrypt(char* key, char* tableFileName, char* fileName)
{
	//Check whether the tablefile is valid.
	int isTableFileInvalid = checkTable(tableFileName);
	if(isTableFileInvalid==1){return;}

	//Check if inputfile is accessible
	FILE *file = fopen(fileName, "rb");
	if(strlen(fileName)!=0 && file==NULL)
	{
		fprintf(stderr, "Unable to open %s.\n", fileName);
		return;
	}
	if(strlen(fileName)==0)
		file = stdin;

	//Declare all tables required
	int IP[64];
	int E[48];
	int P[32];
	int S1[4][16], S2[4][16], S3[4][16], S4[4][16], S5[4][16], S6[4][16], S7[4][16], S8[4][16];
	int V[16];
	int PC1[56], PC2[48];

	//read from tablefile
	fetchTables(tableFileName, IP, E, P, S1, S2, S3, S4, S5, S6, S7, S8, V, PC1, PC2);

	//convert key from hexstring to binary
	unsigned long long keyBytes = 0;
	convertKeyToBinary(key, &keyBytes);

	//calculate IP^-1 (inverse permutation)
	int IP_inv[64];
	computeInversePerm(IP, IP_inv);

	//generate round keys
	unsigned long long roundKeys[16]; //16 rounds, 48-bit keys per round
	keySchedulerForDecrypt(keyBytes, roundKeys, PC1, PC2, V);

	unsigned char buffer[8];
	unsigned char cipherText[9];
	cipherText[8]='\0';
	int bytesRead = -1, i=0;
	unsigned long long msgStream = 0, cipherStream = 0;
	unsigned int L0 = 0, R0 = 0, L_in = 0, R_in = 0, L_out = 0, R_out = 0;
	int blockNumber = 0;

	while(bytesRead != 0)
	{
		blockNumber++;

		for(i=0; i<8; i++)
			buffer[i] = 0;

		bytesRead = fread(buffer, sizeof(char), 8, file);
		if(bytesRead == 0) break;

		//convert char array into stream of bytes
		msgStream = convertCharArrayToBinary(buffer);

		//INITIAL PERMUTATION
		applyIP(IP, msgStream, &L0, &R0);
		if(blockNumber == 1)
			fprintf(stderr, "(L0,R0)=%08x%08x\n", L0, R0);

		//16 ROUNDS OF FIESTEL CIPHER
		L_in = L0;
		R_in = R0;
		for(i=0; i<16; i++)
		{
			fiestelCipher(L_in, R_in, &L_out, &R_out, roundKeys[i], P, S1, S2, S3, S4, S5, S6, S7, S8, E);

			//print Li, Ri for 1st 8-byte block only.
			if(blockNumber == 1)
				fprintf(stderr, "(L%d,R%d)=%08x%08x\n", (i+1), (i+1), L_out, R_out);

			//Initialize L_in and R_in for next round.
			L_in = L_out;
			R_in = R_out;
		}

		//INVERSE PERMUTATION
		cipherStream = applyIPinv(IP_inv, L_out, R_out);

		//convert binary to 8-byte character array
		convertBinaryToCharArray(cipherStream, cipherText);

		//print ciphertext
		for(i=0; i<8; i++)
			printf("%c", cipherText[i]);
	}
}
