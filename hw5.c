#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "tablecheck.h"
#include "encrypt.h"
#include "encrypt3.h"
#include "decrypt.h"
#include "decrypt3.h"

void printUsage()
{
	fprintf(stderr, "Usage:\nhw5 tablecheck -t=tablefile\nhw5 encrypt -k=key -t=tablefile [file]\nhw5 decrypt -k=key -t=tablefile [file]\nhw5 encrypt3 -k=key3 -t=tablefile [file]\nhw5 decrypt3 -k=key3 -t=tablefile [file]\n");
}

int main(int argc, char *argv[])
{
	//skip argv[0]
	argc--;
	argv++;

	if(argc <= 0)
	{
		fprintf(stderr, "Please enter command line arguments.\n");
		printUsage();
		return EXIT_FAILURE;
	}

	//tablefile
	if(strcmp(*argv, "tablecheck") == 0)
	{
		if(argc-1 < 1 || argc-1 > 1)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		char* tablefile = malloc(100*sizeof(char));

		for(argc--; argc>0; argc--)
		{
			argv++;

			if(strlen(*argv) < 4)
			{
				fprintf(stderr, "Malformed command.\n");
				printUsage();
				return EXIT_FAILURE;
			}

			//tablefile
			if(argv[0][0]=='-' && argv[0][1]=='t' && argv[0][2]=='=')
			{
				//Get tablefile from argv
				int i=0;
				for(i=3; i<strlen(*argv); i++)
				{
					tablefile[i-3] = argv[0][i];
				}
				tablefile[i-3] = '\0';
			}
		}

		checkTable(tablefile);
	}


	//Encrypt
	else if(strcmp(*argv, "encrypt") == 0 || strcmp(*argv, "encrypt3") == 0 || strcmp(*argv, "decrypt") == 0 || strcmp(*argv, "decrypt3") == 0)
	{
		char command[10]="";
		if(strcmp(*argv, "encrypt") == 0)strcpy(command, "encrypt");
		if(strcmp(*argv, "encrypt3") == 0)strcpy(command, "encrypt3");
		if(strcmp(*argv, "decrypt") == 0)strcpy(command, "decrypt");
		if(strcmp(*argv, "decrypt3") == 0)strcpy(command, "decrypt3");


		//Get hold of arguments
		char* key = malloc(100*sizeof(char));
		char* tableFileName = malloc(100*sizeof(char));
		char* file = malloc(100*sizeof(char));
		*file='\0';

		//No, less or extra parameters
		if(argc-1 < 2 || argc-1 > 3)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}

		for(argc--; argc>0; argc--)
		{
			argv++;

			//Commanldine option encountered
			if(argv[0][0] == '-')
			{
				if(strlen(*argv) < 4)
				{
					fprintf(stderr, "Malformed command.\n");
					printUsage();
					return EXIT_FAILURE;
				}

				//key
				if(argv[0][0]=='-' && argv[0][1]=='k' && argv[0][2]=='=')
				{
					//Get key from argv
					int i=0;
					for(i=3; i<strlen(*argv); i++)
					{
						key[i-3] = argv[0][i];
					}
					key[i-3] = '\0';
				}
				else if(argv[0][0]=='-' && argv[0][1]=='t' && argv[0][2]=='=')
				{
					//Get tableFileName from argv
					int i=0;
					for(i=3; i<strlen(*argv); i++)
					{
						tableFileName[i-3] = argv[0][i];
					}
					tableFileName[i-3] = '\0';
				}
				else
				{
					fprintf(stderr, "Malformed command.\n");
					printUsage();
					return EXIT_FAILURE;
				}
			}

			//file
			else if(strlen(*argv) > 0)
			{
				//Get file from argv
				int i=0;
				for(i=0; i<strlen(*argv); i++)
				{
					file[i] = argv[0][i];
				}
				file[i] = '\0';
			}
		}

		//Check for errors
		if(strlen(key)==0 || strlen(tableFileName)==0)
		{
			fprintf(stderr, "Malformed command.\n");
			printUsage();
			return EXIT_FAILURE;
		}
		else
		{
			if(strcmp(command, "encrypt")==0 || strcmp(command, "decrypt")==0)
			{
				if(strlen(key)!=16)
				{
					fprintf(stderr, "Key should be 8-bytes long, in hexstring format.\n");
					printUsage();
					return EXIT_FAILURE;
				}
				else if(strlen(key)==16)
				{
					int k=0;
					for(k=0; k<16; k++)
					{
						if(key[k] < 48 || (key[k] > 57 && key[k] < 97) || key[k] > 102)
						{
							fprintf(stderr, "Key is not in hexstring format.\n");
							printUsage();
							return EXIT_FAILURE;
						}
					}
				}
			}
			else //encrypt3 or decrypt3
			{
				if(strlen(key)!=48)
				{
					fprintf(stderr, "Key should be 24-bytes long, in hexstring format.\n");
					printUsage();
					return EXIT_FAILURE;
				}
				else if(strlen(key)==48)
				{
					int k=0;
					for(k=0; k<48; k++)
					{
						if(key[k] < 48 || (key[k] > 57 && key[k] < 97) || key[k] > 102)
						{
							fprintf(stderr, "Key is not in hexstring format.\n");
							printUsage();
							return EXIT_FAILURE;
						}
					}
				}
			}
		}

		if(strcmp(command, "encrypt") == 0)encrypt(key, tableFileName, file);
		if(strcmp(command, "encrypt3") == 0)encrypt3(key, tableFileName, file);
		if(strcmp(command, "decrypt") == 0)decrypt(key, tableFileName, file);
		if(strcmp(command, "decrypt3") == 0)decrypt3(key, tableFileName, file);


		free(key);
		free(tableFileName);
		free(file);
	}

	else
	{
		fprintf(stderr, "Malformed command.\n");
		printUsage();
		return EXIT_SUCCESS;
	}

	return EXIT_SUCCESS;
}
