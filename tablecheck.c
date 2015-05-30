#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int checkTable(char* tableFileName)
{
	FILE *tableFile = fopen(tableFileName, "rb");

	//Check if file exists
	if(tableFile == NULL)
	{
		fprintf(stderr, "Unable to open tablefile.\n");
		return 1;
	}

	char line[200];
	char *keyword;
	char *value;
	int linesRead = 0;
	int i=0;
	while(fgets(line, 200, tableFile) != NULL) //Read 1 line at a time
	{
		linesRead++;

		//Check whether too many lines present
		if(linesRead > 14)
		{
			fprintf(stderr, "%s contains too many lines.\n", tableFileName);
			return 1;
		}

		//Get table name
		keyword = strtok(line, "=");

		//Check whether valid keyword
		if(strcmp(keyword, "IP") != 0 &&
		   strcmp(keyword, "E") != 0 &&
		   strcmp(keyword, "P") != 0 &&
		   strcmp(keyword, "S1") != 0 &&
		   strcmp(keyword, "S2") != 0 &&
		   strcmp(keyword, "S3") != 0 &&
		   strcmp(keyword, "S4") != 0 &&
		   strcmp(keyword, "S5") != 0 &&
		   strcmp(keyword, "S6") != 0 &&
		   strcmp(keyword, "S7") != 0 &&
		   strcmp(keyword, "S8") != 0 &&
		   strcmp(keyword, "V") != 0 &&
		   strcmp(keyword, "PC1") != 0 &&
		   strcmp(keyword, "PC2") != 0 )
		{
			fprintf(stderr, "%s contains invalid keywords.\n", tableFileName);
			return 1;
		}

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

		/*int q=0;
		for(q=0; q<i; q++)
			printf("%d ", values[q]);
		printf("\n");*/

		//Check if number of values are proper
		if(strcmp(keyword, "IP") == 0 && i!=64){fprintf(stderr, "IP contains %d values. It should contain 64 values.\n", i);return 1;}
		if(strcmp(keyword, "E") == 0 && i!=48){fprintf(stderr, "E contains %d values.It should contain 48 values.\n", i);return 1;}
		if(strcmp(keyword, "P") == 0 && i!=32){fprintf(stderr, "P contains %d values. It should contain 32 values.\n", i);return 1;}
		if(strcmp(keyword, "S1") == 0 && i!=64){fprintf(stderr, "S1 contains %d values. It should contain 64 values.\n", i);return 1;}
		if(strcmp(keyword, "S2") == 0 && i!=64){fprintf(stderr, "S2 contains %d values. It should contain 64 values.\n", i);return 1;}
		if(strcmp(keyword, "S3") == 0 && i!=64){fprintf(stderr, "S3 contains %d values. It should contain 64 values.\n", i);return 1;}
		if(strcmp(keyword, "S4") == 0 && i!=64){fprintf(stderr, "S4 contains %d values. It should contain 64 values.\n", i);return 1;}
		if(strcmp(keyword, "S5") == 0 && i!=64){fprintf(stderr, "S5 contains %d values. It should contain 64 values.\n", i);return 1;}
		if(strcmp(keyword, "S6") == 0 && i!=64){fprintf(stderr, "S6 contains %d values. It should contain 64 values.\n", i);return 1;}
		if(strcmp(keyword, "S7") == 0 && i!=64){fprintf(stderr, "S7 contains %d values. It should contain 64 values.\n", i);return 1;}
		if(strcmp(keyword, "S8") == 0 && i!=64){fprintf(stderr, "S8 contains %d values. It should contain 64 values.\n", i);return 1;}
		if(strcmp(keyword, "V") == 0 && i!=16){fprintf(stderr, "V contains %d values. It should contain 16 values.\n", i);return 1;}
		if(strcmp(keyword, "PC1") == 0 && i!=56){fprintf(stderr, "PC1 contains %d values. It should contain 56 values.\n", i);return 1;}
		if(strcmp(keyword, "PC2") == 0 && i!=48){fprintf(stderr, "PC2 contains %d values. It should contain 48 values.\n", i);return 1;}

		//Check each table separately
		if(strcmp(keyword, "IP") == 0)
		{
			//This table contains a random permutation of the values from 1 through 64, inclusive.
			//Check whether proper permutation.
			int temp[65];
			int j=1;
			for(j=1; j<65; j++)
				temp[j] = 0;
			for(j=0; j<64; j++)
			{
				//invalid value
				if(values[j]<1 || values[j]>64)
				{fprintf(stderr, "IP contains %d, which is an invalid value for IP.\n", values[j]);return 1;}

				temp[values[j]] = 1;
			}
			for(j=1; j<65; j++)
				if(temp[j]==0)
				{fprintf(stderr, "IP does not contain %d, hence it is not a proper permutation.\n", j);return 1;}
		}

		if(strcmp(keyword, "E") == 0)
		{
			//This table contains 48 values. The allowed values are between 1 through 32, inclusive. All 32 numbers must appear in this table at least once and at most twice.
			int counts[33];
			int j=0;
			for(j=1; j<33; j++)
				counts[j] = 0;
			for(j=0; j<48; j++)
			{
				if(values[j]<1 || values[j]>32)
				{fprintf(stderr, "E contains %d, which is an invalid value for E.\n", values[j]);return 1;}

				counts[values[j]]++;
			}
			for(j=1; j<33; j++)
			{
				if(counts[j]<1)
				{fprintf(stderr, "%d occurs 0 times in E.\n", j);return 1;}
				if(counts[j]>2)
				{fprintf(stderr, "%d occurs %d times in E.\n", j, counts[j]);return 1;}
			}
		}

		if(strcmp(keyword, "P") == 0)
		{
			//Check whether proper permutation.
			int temp[33];
			int j=1;
			for(j=1; j<33; j++)
				temp[j] = 0;
			for(j=0; j<32; j++)
			{
				//invalid value
				if(values[j]<1 || values[j]>32)
				{fprintf(stderr, "P contains %d, which is an invalid value for P.\n", values[j]);return 1;}

				temp[values[j]] = 1;
			}
			for(j=1; j<33; j++)
				if(temp[j]==0)
				{fprintf(stderr, "P does not contain %d, hence it is not a proper permutation.\n", j);return 1;}
		}

		if(strcmp(keyword, "S1") == 0 || strcmp(keyword, "S2") == 0 || strcmp(keyword, "S3") == 0 || strcmp(keyword, "S4") == 0 ||
		   strcmp(keyword, "S5") == 0 || strcmp(keyword, "S6") == 0 || strcmp(keyword, "S7") == 0 || strcmp(keyword, "S8") == 0)
		{
			//This table contains 64 values, in a group of 16. Each group is a random permutation of the values from 0 through 15, inclusive.
			int counts[16];
			int j=0;
			for(j=0; j<16; j++)
				counts[j] = 0;
			for(j=0; j<64; j++)
			{
				if(values[j]<0 || values[j]>15)
				{fprintf(stderr, "%s contains %d, which is an invalid value for %s.\n", keyword, values[j], keyword);return 1;}

				counts[values[j]]++;
			}
			for(j=0; j<16; j++)
				if(counts[j]!=4)
				{fprintf(stderr, "%d occurred %d times in %s, hence it is not a proper permutation.\n", j, counts[j], keyword);return 1;}
		}

		if(strcmp(keyword, "V") == 0)
		{
			//This table contains 16 values. Each value can be either 1 or 2. There should be 4 ones and 12 twos.
			int ones = 0;
			int twos = 0;
			int j=0;
			for(j=0; j<16; j++)
				if(values[j]==1) ones++;
				else if (values[j]==2) twos++;
			if(ones+twos < 16 || ones != 4 || twos != 12)
			{fprintf(stderr, "V contains %d ones and %d twos. Each value in V can be either 1 or 2. There should be 4 ones and 12 twos.\n", ones, twos);return 1;}
		}

		if(strcmp(keyword, "PC1") == 0)
		{
			//This table contains 56 values. These values are a random permutation of the numbers from 1 through 64, inclusive, with the values which are multiples of 8 removed.
			//Check whether proper permutation.
			int temp[65];
			int j=1;
			for(j=1; j<65; j++)
				temp[j] = 0;
			for(j=0; j<56; j++)
			{
				//invalid value
				if(values[j]<1 || values[j]>64 || values[j]%8==0)
				{fprintf(stderr, "PC1 contains %d, which is an invalid value for PC1.\n", values[j]);return 1;}

				temp[values[j]] = 1;
			}
			for(j=1; j<65 && j%8!=0; j++)
				if(temp[j]==0)
				{fprintf(stderr, "PC1 does not contain %d, hence it is not a proper permutation.\n", j);return 1;}
		}

		if(strcmp(keyword, "PC2") == 0)
		{
			//This table contains 48 values. These values are a random permutation of the numbers from 1 through 56, inclusive, with 8 randomly chosen numbers removed.
			int temp[57];
			int j=1;
			for(j=1; j<57; j++)
				temp[j] = 0;
			for(j=0; j<48; j++)
			{
				//invalid value
				if(values[j]<1 || values[j]>56)
				{fprintf(stderr, "PC2 contains %d, which is an invalid value for PC2.\n", values[j]);return 1;}

				temp[values[j]] = 1;
			}
			int removed = 0;
			for(j=1; j<57; j++)
				if(temp[j]==0) removed++;
			if(removed>8){fprintf(stderr, "More than 8 values were removed from PC2.Hence it is not a proper permutation.\n");return 1;}
		}
	}

	//tablefile is okay.
	return 0;
}
