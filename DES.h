/*
 * DES.h
 *
 *  Created on: Mar 22, 2015
 *      Author: ashton
 */

#ifndef DES_H_
#define DES_H_

void convertKeyToBinary(char*, unsigned long long *);
void convert3KeysToBinary(char *, unsigned long long[3]);
unsigned long long convertCharArrayToBinary(unsigned char *);
void convertBinaryToCharArray(unsigned long long, unsigned char[9]);
void computeInversePerm(int *, int *);
void circularLeftShift(unsigned long long *, int);
unsigned long long permute(int *, unsigned long long *, unsigned long long *);
void keyScheduler(unsigned long long, unsigned long long[16], int[56], int[48], int[16]);
void keySchedulerForEncrypt3(unsigned long long, unsigned long long[16], int[56], int[48], int[16]);
void keySchedulerForDecrypt(unsigned long long, unsigned long long[16], int[56], int[48], int[16]);
void keySchedulerForDecrypt3(unsigned long long, unsigned long long[16], int[56], int[48], int[16]);
void applyIP(int *, unsigned long long , unsigned int *, unsigned int *);
unsigned long long applyIPinv(int *, unsigned int , unsigned int );
unsigned int f(unsigned long long, unsigned int, int[32], int[4][16], int[4][16], int[4][16], int[4][16], int[4][16], int[4][16], int[4][16], int[4][16], int[48]);
void fiestelCipher(unsigned int , unsigned int , unsigned int*, unsigned int*, unsigned long long, int[32], int[4][16], int[4][16], int[4][16], int[4][16], int[4][16], int[4][16], int[4][16], int[4][16], int[48]);

#endif /* DES_H_ */
