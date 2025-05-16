/*
Cracking a given cipher.
This code takes cipher text (up to 100 characters) and tries to decrypt it.
This code follows a simple brute force attack since there's only 312 possiblities
and scans against English words found in wordlist.txt and dictionary.txt to output
plain texts that got the highest amount of matches.
Use gcc to compile this code. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Finding inverse
int inv(int a)
{
	int i, j;
	for (i=0; i<26; i++)
	{
		j = (i * a) % 26;
		if (j == 1)
		{
			return i;
		}
	}
	return 0;	
}

//Decryption using every possible key
//returns plain text
char* bruteForce(int a, int b, char cipher_txt[])
{
	static char plain_txt[1000];
	int i, j;
	for (i=0;i<1000;i++)
	{
		if (cipher_txt[i]-'A' < 0 || cipher_txt[i]-'A' > 25)
		{
			plain_txt[i] = cipher_txt[i];
		} 
		else 
		{
			if ((cipher_txt[i] - 'A' - b) < 0)
				{
					plain_txt[i] = (a * (cipher_txt[i] - 'A' - b) % 26) +'A' + 26;
				}
			else if ((cipher_txt[i] - 'A' - b) >= 0)
				{					
					plain_txt[i] = (a * (cipher_txt[i] - 'A' - b) % 26) +'A';
				}	
		}
	}
	return plain_txt;
}

//Finding English words in every possible plain text 
//Uses a short list of common English words
//returns number of matches
int isEnglish(char* str1)
{
	char *p;
	char arr[847][30];
		
	FILE *fptr;
	fptr = fopen(".\\wordlist.txt","r");
	
	int i, match = 0;
	
    for (i = 0; i < 847; i++)
    {
        fscanf(fptr, "%s", &arr[i]);
    }
	 
	for (i = 0; i < 847; i++)
	{
		p = strstr(str1, arr[i]);
		
		if (p) 
		{
			match++;
		}
	}
	
	return match;
		
	fclose(fptr);
}

//This is in case user inpts only one word
//This function scans against a dictionary file of over 45000 words
//returns true if a match has been found
int wordFind(char* str)
{
	int i;
	str[strlen(str)-1] = '\0';
	char arr[45333][30];
	int result;
	
	FILE *fptr;
	fptr = fopen(".\\dictionary.txt","r");
	
	for (i = 0; i < 45333; i++)
    {
        fscanf(fptr, "%s", &arr[i]);
    }

	for (i = 0; i < 45333; i++)
		{	
	
			result = strcmp(str, arr[i]);
			
			if (result == 0)
			{
				return 1;
			}
			else
			{
				continue;
			}	
		}
		
	fclose(fptr);
}

void main()
{
	char input[1000], letter;
	char* output;
	int a_values[12] = {1,3,5,7,9,11,15,17,19,21,23,25};
	int a, b, i = 0, j = 0, x = 0, state = 1;
	
	while (state) 
	{		
		printf("\nEnter cipher text to crack (min characters = 4 ; max characters = 100): ");
		fgets(input, 1000, stdin);
			
		if (strlen(input) < 5 || strlen(input) == 1)
		{
			printf ("\nPlease input a string within the specified range.\n");
			continue;
		}
		else if (input[0] == ' ')
		{
			printf ("\nPlease remove the space at the start of your text.\n");
			continue;
		}
		else
		{	
			while (input[i]) 
			{
				letter = input[i];
				input[i] = toupper(letter);
				i++;
			}
			break;	
		}	
	}	 
	
	while (state) 
	{
		for (i=0;i<12;i++)
		{
			for (j=0;j<26;j++)
			{	
				a = a_values[i];
				b = j;
				
				output = bruteForce(inv(a), b, input);
				
				if (isEnglish(output) > 1 || wordFind(output) == 1) 
				{
					printf("\nPlain text is: %s\nKeys are: a = %d ; b = %d (Matches = %d)\n", output, a, b, isEnglish(output));
					x++;
					state = 0;
				}	
				else
				{
					continue;
				}	
			}
		}
		if (x == 0)
		{	
			printf("Sorry, couldn't crack your cipher!");
			break;
		}
	}
}	

