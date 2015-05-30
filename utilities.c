#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void fetchTables(char* tableFileName, int IP[64], int E[48], int P[32], int S1[4][16], int S2[4][16], int S3[4][16], int S4[4][16], int S5[4][16], int S6[4][16], int S7[4][16], int S8[4][16], int V[16], int PC1[56], int PC2[48])
{
	//Read from tablefile
	char line[200];
	char *keyword;
	char *value;
	int i=0;
	FILE *tableFile = fopen(tableFileName, "rb");
	while(fgets(line, 200, tableFile) != NULL) //Read 1 line at a time
	{
		//Get table name
		keyword = strtok(line, "=");

		//Get values
		int values[64];
		for(i=0; i<64; i++)
			values[i] = -1;
		i=0;
		value = strtok(NULL, ",");
		while(value!=NULL)
		{
			values[i++] = atoi(value);
			value = strtok(NULL, ",");
		}

		//Get values according to tablename
		if(strcmp(keyword, "IP") == 0)
		{
			for(i=0; i<64; i++)
				IP[i] = values[i];
		}

		if(strcmp(keyword, "E") == 0)
		{
			for(i=0; i<48; i++)
				E[i] = values[i];
		}

		if(strcmp(keyword, "P") == 0)
		{
			for(i=0; i<32; i++)
				P[i] = values[i];
		}

		if(strcmp(keyword, "S1") == 0)
		{
			int row = -1, col = 0;
			for(i=0; i<64; i++)
			{
				col = i%16;
				if(col==0)row++;
				S1[row][col] = values[i];
			}
		}

		if(strcmp(keyword, "S2") == 0)
		{
			int row = -1, col = 0;
			for(i=0; i<64; i++)
			{
				col = i%16;
				if(col==0)row++;
				S2[row][col] = values[i];
			}
		}

		if(strcmp(keyword, "S3") == 0)
		{
			int row = -1, col = 0;
			for(i=0; i<64; i++)
			{
				col = i%16;
				if(col==0)row++;
				S3[row][col] = values[i];
			}
		}

		if(strcmp(keyword, "S4") == 0)
		{
			int row = -1, col = 0;
			for(i=0; i<64; i++)
			{
				col = i%16;
				if(col==0)row++;
				S4[row][col] = values[i];
			}
		}

		if(strcmp(keyword, "S5") == 0)
		{
			int row = -1, col = 0;
			for(i=0; i<64; i++)
			{
				col = i%16;
				if(col==0)row++;
				S5[row][col] = values[i];
			}
		}

		if(strcmp(keyword, "S6") == 0)
		{
			int row = -1, col = 0;
			for(i=0; i<64; i++)
			{
				col = i%16;
				if(col==0)row++;
				S6[row][col] = values[i];
			}
		}

		if(strcmp(keyword, "S7") == 0)
		{
			int row = -1, col = 0;
			for(i=0; i<64; i++)
			{
				col = i%16;
				if(col==0)row++;
				S7[row][col] = values[i];
			}
		}

		if(strcmp(keyword, "S8") == 0)
		{
			int row = -1, col = 0;
			for(i=0; i<64; i++)
			{
				col = i%16;
				if(col==0)row++;
				S8[row][col] = values[i];
			}
		}

		if(strcmp(keyword, "V") == 0)
		{
			for(i=0; i<16; i++)
				V[i] = values[i];
		}

		if(strcmp(keyword, "PC1") == 0)
		{
			for(i=0; i<56; i++)
				PC1[i] = values[i];
		}

		if(strcmp(keyword, "PC2") == 0)
		{
			for(i=0; i<48; i++)
				PC2[i] = values[i];
		}
	}
}
