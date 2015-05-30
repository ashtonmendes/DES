#include<stdio.h>
#include<stdlib.h>


void convertKeyToBinary(char *key, unsigned long long *keyBytes)
{
	int i=0;
	unsigned char byte = 0;
	unsigned char temp = 0;
	while(key[i] != '\0')
	{
		//get next 4bits, represented by next character in hexstring
		if(key[i]=='0'){temp=0;}
		if(key[i]=='1'){temp=1;}
		if(key[i]=='2'){temp=2;}
		if(key[i]=='3'){temp=3;}
		if(key[i]=='4'){temp=4;}
		if(key[i]=='5'){temp=5;}
		if(key[i]=='6'){temp=6;}
		if(key[i]=='7'){temp=7;}
		if(key[i]=='8'){temp=8;}
		if(key[i]=='9'){temp=9;}
		if(key[i]=='a'){temp=10;}
		if(key[i]=='b'){temp=11;}
		if(key[i]=='c'){temp=12;}
		if(key[i]=='d'){temp=13;}
		if(key[i]=='e'){temp=14;}
		if(key[i]=='f'){temp=15;}

		byte = (byte<<4) | temp;

		//process 1 byte at a time
		if((i+1)%2==0)
		{
			(*keyBytes) = ((*keyBytes) << 8) | byte;
			byte=0;
		}

		i++;
	}

	//printf("%lx \n", *keyBytes);
}

void convert3KeysToBinary(char *key, unsigned long long keyBytes[3])
{
	int i=0, j=0;
	unsigned char byte = 0;
	unsigned char temp = 0;
	while(key[i] != '\0')
	{
		//get next 4bits, represented by next character in hexstring
		if(key[i]=='0'){temp=0;}
		if(key[i]=='1'){temp=1;}
		if(key[i]=='2'){temp=2;}
		if(key[i]=='3'){temp=3;}
		if(key[i]=='4'){temp=4;}
		if(key[i]=='5'){temp=5;}
		if(key[i]=='6'){temp=6;}
		if(key[i]=='7'){temp=7;}
		if(key[i]=='8'){temp=8;}
		if(key[i]=='9'){temp=9;}
		if(key[i]=='a'){temp=10;}
		if(key[i]=='b'){temp=11;}
		if(key[i]=='c'){temp=12;}
		if(key[i]=='d'){temp=13;}
		if(key[i]=='e'){temp=14;}
		if(key[i]=='f'){temp=15;}

		byte = (byte<<4) | temp;

		//process 1 byte at a time
		if((i+1)%2==0)
		{
			(keyBytes[j]) = ((keyBytes[j]) << 8) | byte;
			byte=0;
		}

		i++;

		if(i%16==0)j++;
	}
}

unsigned long long convertCharArrayToBinary(unsigned char *buffer)
{
	unsigned long long binary = 0;

	//Read 8 bytes and generate 64-bit long stream. Pad 0 at the end if not enough bits
	int i=0;
	for(i=0; i<8; i++)
		binary = (binary<<8) | buffer[i];

	return binary;
}

void convertBinaryToCharArray(unsigned long long cipherStream, unsigned char cipherText[9])
{
	unsigned long long bitmask = ((unsigned long long)(~(unsigned char)0))<<(64-8);

	int i=0;
	for(i=0; i<8; i++)
	{
		cipherText[i] = (cipherStream & bitmask)>>(64-(i+1)*8);
		bitmask = bitmask >> 8;
	}
}

void computeInversePerm(int *IP, int *IP_inv)
{
	int i=0;
	for(i=0; i<64; i++)
		IP_inv[IP[i]-1] = (i+1);
}

void circularLeftShift(unsigned long long *Number, int amount)
{
	unsigned int MSB = 0;
	int i=0;
	for(i=0; i<amount; i++)
	{
		MSB = (((unsigned long long)1<<27) & (*Number)) >> 27;
		*Number = *Number & ~((unsigned long long)1<<27);
		*Number = *Number << 1;
		*Number = *Number | MSB;
	}
}

unsigned long long permute(int *PC2, unsigned long long *Ci, unsigned long long *Di)
{
	unsigned long long CiDi = ((*Ci)<<28) | (*Di);
	unsigned long long roundKey = 0;
	int i=0;
	for(i=0; i<48; i++)
	{
		roundKey = (roundKey<<1) | ((CiDi & ((unsigned long long)1<<(56-PC2[i])))>>(56-PC2[i]));
	}
	return roundKey;
}

void keyScheduler(unsigned long long keyBytes, unsigned long long roundKeys[16], int PC1[56], int PC2[48], int V[16])
{
	//Initialize C0 and D0 using PC1
	//Ci <- (Ci-1 <<* Vi)
	//Di <- (Di-1 <<* Vi)
	//Ki <- PC2(Ci, Di)
	unsigned long long Ci = 0, Di = 0;
	int i=0;

	//find C0
	for(i=0; i<28; i++)
		Ci = (Ci<<1) | ((keyBytes & ((unsigned long long)1<<(64-PC1[i])))>>(64-PC1[i]));

	//find D0
	for(i=28; i<56; i++)
		Di = (Di<<1) | ((keyBytes & ((unsigned long long)1<<(64-PC1[i])))>>(64-PC1[i]));

	//Print C0, D0
	fprintf(stderr, "(C0,D0)=%07llx%07llx\n", Ci, Di);

	for(i=0; i<16; i++)
	{
		circularLeftShift(&Ci, V[i]);
		circularLeftShift(&Di, V[i]);

		//Print Ci, Di
		fprintf(stderr, "(C%d,D%d)=%07llx%07llx\n", (i+1), (i+1), Ci, Di);

		roundKeys[i] = permute(PC2, &Ci, &Di);

		//Print roundkey
		fprintf(stderr, "k%d=%012llx\n", (i+1), roundKeys[i]);
	}
}

void keySchedulerForEncrypt3(unsigned long long keyBytes, unsigned long long roundKeys[16], int PC1[56], int PC2[48], int V[16])
{
	//Initialize C0 and D0 using PC1
	//Ci <- (Ci-1 <<* Vi)
	//Di <- (Di-1 <<* Vi)
	//Ki <- PC2(Ci, Di)
	unsigned long long Ci = 0, Di = 0;
	int i=0;

	//find C0
	for(i=0; i<28; i++)
		Ci = (Ci<<1) | ((keyBytes & ((unsigned long long)1<<(64-PC1[i])))>>(64-PC1[i]));

	//find D0
	for(i=28; i<56; i++)
		Di = (Di<<1) | ((keyBytes & ((unsigned long long)1<<(64-PC1[i])))>>(64-PC1[i]));

	for(i=0; i<16; i++)
	{
		circularLeftShift(&Ci, V[i]);
		circularLeftShift(&Di, V[i]);

		roundKeys[i] = permute(PC2, &Ci, &Di);
	}
}

void keySchedulerForDecrypt(unsigned long long keyBytes, unsigned long long roundKeys[16], int PC1[56], int PC2[48], int V[16])
{
	//Initialize C0 and D0 using PC1
	//Ci <- (Ci-1 <<* Vi)
	//Di <- (Di-1 <<* Vi)
	//Ki <- PC2(Ci, Di)
	unsigned long long Ci = 0, Di = 0;
	int i=0;

	//find C0
	for(i=0; i<28; i++)
		Ci = (Ci<<1) | ((keyBytes & ((unsigned long long)1<<(64-PC1[i])))>>(64-PC1[i]));

	//find D0
	for(i=28; i<56; i++)
		Di = (Di<<1) | ((keyBytes & ((unsigned long long)1<<(64-PC1[i])))>>(64-PC1[i]));

	//Print C0, D0
	fprintf(stderr, "(C0,D0)=%07llx%07llx\n", Ci, Di);

	for(i=0; i<16; i++)
	{
		circularLeftShift(&Ci, V[i]);
		circularLeftShift(&Di, V[i]);

		//Print Ci, Di
		fprintf(stderr, "(C%d,D%d)=%07llx%07llx\n", (i+1), (i+1), Ci, Di);

		roundKeys[15-i] = permute(PC2, &Ci, &Di);

		//Print roundkey
		fprintf(stderr, "k%d=%012llx\n", (i+1), roundKeys[15-i]);
	}
}

void keySchedulerForDecrypt3(unsigned long long keyBytes, unsigned long long roundKeys[16], int PC1[56], int PC2[48], int V[16])
{
	//Initialize C0 and D0 using PC1
	//Ci <- (Ci-1 <<* Vi)
	//Di <- (Di-1 <<* Vi)
	//Ki <- PC2(Ci, Di)
	unsigned long long Ci = 0, Di = 0;
	int i=0;

	//find C0
	for(i=0; i<28; i++)
		Ci = (Ci<<1) | ((keyBytes & ((unsigned long long)1<<(64-PC1[i])))>>(64-PC1[i]));

	//find D0
	for(i=28; i<56; i++)
		Di = (Di<<1) | ((keyBytes & ((unsigned long long)1<<(64-PC1[i])))>>(64-PC1[i]));

	for(i=0; i<16; i++)
	{
		circularLeftShift(&Ci, V[i]);
		circularLeftShift(&Di, V[i]);

		roundKeys[15-i] = permute(PC2, &Ci, &Di);
	}
}

void applyIP(int *IP, unsigned long long msgStream, unsigned int *L0, unsigned int *R0)
{
	int i=0;
	unsigned long long permutedMsgStream = 0;

	//Permute the message stream
	for(i=0; i<64; i++)
	{
		permutedMsgStream = (permutedMsgStream<<1) | ((msgStream & ((unsigned long long)1<<(64-IP[i])))>>(64-IP[i]));
	}

	//Separate 64 bits into L0 and R0, of 32 bits each
	unsigned long long allOnes = ~(unsigned int)0; //right hand side 32 bits all equal to 1
	*R0 = permutedMsgStream & allOnes;
	allOnes = allOnes << 32; //now left hand side 32 bits all equal to 1
	*L0 = (permutedMsgStream & allOnes)>>32;
}

unsigned long long applyIPinv(int *IP_inv, unsigned int L16, unsigned int R16)
{
	unsigned long long R16L16 = 0;

	//Combine R16 and L16 into one binary stream.
	R16L16 = R16L16 | R16;
	R16L16 = (R16L16<<32) | L16;

	int i=0;
	unsigned long long cipherStream = 0;

	//Permute the message stream
	for(i=0; i<64; i++)
	{
		cipherStream = (cipherStream<<1) | ((R16L16 & ((unsigned long long)1<<(64-IP_inv[i])))>>(64-IP_inv[i]));
	}

	return cipherStream;
}

unsigned int f(unsigned long long roundKey, unsigned int R_in, int P[32], int S1[4][16], int S2[4][16], int S3[4][16], int S4[4][16], int S5[4][16], int S6[4][16], int S7[4][16], int S8[4][16], int E[48])
{
	unsigned int output = 0;

	//Expansion phase: Expand R_in from 32 bit to 48 bit.
	unsigned long long temp = 0;
	int i=0;
	for(i=0; i<48; i++)
	{
		temp = (temp<<1) | ((R_in & ((unsigned long long)1<<(32-E[i])))>>(32-E[i]));
	}

	//EX_OR with round key.
	temp = temp ^ roundKey;

	//Apply S-boxes.
	unsigned long long mask = 0;
	char sixBits = 0, b1 = 0, b6 = 0, b2tob5 = 0;
	int row = 0, col = 0;

	//S1
	mask = (unsigned long long)63<<(48-6); //1st 6 bits set to 1, among 48 bits.
	sixBits = (temp & mask)>>(48-6); //extract 1st 6 bits.
	b1 = (sixBits & 32) >> 5;
	b6 = (sixBits & 1);
	b2tob5 = (sixBits & 30) >> 1;
	row = 2*b1 + b6;
	col = b2tob5;
	output = (output<<4) | S1[row][col];

	//S2
	mask = (unsigned long long)63<<(48-6-6); //next 6 bits
	sixBits = (temp & mask)>>(48-6-6); //extract next 6 bits.
	b1 = (sixBits & 32) >> 5;
	b6 = (sixBits & 1);
	b2tob5 = (sixBits & 30) >> 1;
	row = 2*b1 + b6;
	col = b2tob5;
	output = (output<<4) | S2[row][col];

	//S3
	mask = (unsigned long long)63<<(48-6-6-6); //next 6 bits
	sixBits = (temp & mask)>>(48-6-6-6); //extract next 6 bits.
	b1 = (sixBits & 32) >> 5;
	b6 = (sixBits & 1);
	b2tob5 = (sixBits & 30) >> 1;
	row = 2*b1 + b6;
	col = b2tob5;
	output = (output<<4) | S3[row][col];

	//S4
	mask = (unsigned long long)63<<(48-6-6-6-6); //next 6 bits
	sixBits = (temp & mask)>>(48-6-6-6-6); //extract next 6 bits.
	b1 = (sixBits & 32) >> 5;
	b6 = (sixBits & 1);
	b2tob5 = (sixBits & 30) >> 1;
	row = 2*b1 + b6;
	col = b2tob5;
	output = (output<<4) | S4[row][col];

	//S5
	mask = (unsigned long long)63<<(48-6-6-6-6-6); //next 6 bits
	sixBits = (temp & mask)>>(48-6-6-6-6-6); //extract next 6 bits.
	b1 = (sixBits & 32) >> 5;
	b6 = (sixBits & 1);
	b2tob5 = (sixBits & 30) >> 1;
	row = 2*b1 + b6;
	col = b2tob5;
	output = (output<<4) | S5[row][col];

	//S6
	mask = (unsigned long long)63<<(48-6-6-6-6-6-6); //next 6 bits
	sixBits = (temp & mask)>>(48-6-6-6-6-6-6); //extract next 6 bits.
	b1 = (sixBits & 32) >> 5;
	b6 = (sixBits & 1);
	b2tob5 = (sixBits & 30) >> 1;
	row = 2*b1 + b6;
	col = b2tob5;
	output = (output<<4) | S6[row][col];

	//S7
	mask = (unsigned long long)63<<(48-6-6-6-6-6-6-6); //next 6 bits
	sixBits = (temp & mask)>>(48-6-6-6-6-6-6-6); //extract next 6 bits.
	b1 = (sixBits & 32) >> 5;
	b6 = (sixBits & 1);
	b2tob5 = (sixBits & 30) >> 1;
	row = 2*b1 + b6;
	col = b2tob5;
	output = (output<<4) | S7[row][col];

	//S8
	mask = (unsigned long long)63<<(48-6-6-6-6-6-6-6-6); //next 6 bits
	sixBits = (temp & mask)>>(48-6-6-6-6-6-6-6-6); //extract next 6 bits.
	b1 = (sixBits & 32) >> 5;
	b6 = (sixBits & 1);
	b2tob5 = (sixBits & 30) >> 1;
	row = 2*b1 + b6;
	col = b2tob5;
	output = (output<<4) | S8[row][col];

	//Apply P
	unsigned int finalOutput = 0;
	for(i=0; i<32; i++)
	{
		finalOutput = (finalOutput<<1) | ((output & ((unsigned long long)1<<(32-P[i])))>>(32-P[i]));
	}

	return finalOutput;
}

void fiestelCipher(unsigned int L_in, unsigned int R_in, unsigned int *L_out, unsigned int *R_out, unsigned long long roundKey, int P[32], int S1[4][16], int S2[4][16], int S3[4][16], int S4[4][16], int S5[4][16], int S6[4][16], int S7[4][16], int S8[4][16], int E[48])
{
	*L_out = R_in;
	*R_out = L_in ^ f(roundKey, R_in, P, S1, S2, S3, S4, S5, S6, S7, S8, E);
}
