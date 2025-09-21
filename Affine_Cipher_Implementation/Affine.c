/*
Implementation of affine cipher.
This code encrypts and decrypts user input (max characters = 100).
Keys are to be provided by the user.
Use gcc to compile this code.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Euclidean algorithm - returns remainder
int gcd(int a, int b)
{
	int i;
	while (b != 0)
	{
		i = a % b;
		a = b;
		b = i;
	}
	return a;
}

//Finding inverse of the first key to use for decryption
int inv(int a)
{
	int i, j;
	for (i=0; i<26; i++)
	{
		j = (i * a) % 26;
		if (j == 1)
			return i;
	}
	return 0;	
}

/* Input Validation for keys and option - checks if user input is a number.
Returns true if input is numeric or false if input is not numeric */
int valInput(char* str)
{
  int i = 0, ref = 0;
  if (strlen(str) != 1) //string length if the user only presses enter when asked for input is 1
  {
	for (i=0;i<strlen(str)-1;i++)
	{
		if (isdigit(str[i])) //isdigit() return a non-zero integer when argument is numeric
		{
			ref = 1;
			continue;
		}		
		else
		{	
			printf("\nInput is not a number!");
			printf("\n");
			ref = 0;
			break;   
		}
	}	
  }
  else
  {
	  printf("\nPressing Enter doesn't count!\n");
  }
  return ref;
}

//Encryption
//E(x) = (ax+b) mod 26
void enc(char plain_text[], int a, int b)
{	
    int i;
    for(i=0;i<strlen(plain_text)-1;i++)
    {
		if (plain_text[i] != ' ') //ignores spaces
		{	
			if (plain_text[i]-'A' < 0 || plain_text[i]-'A' > 25)
			{
				printf("%c", plain_text[i]); //ignores non-alphabetical characters
			} 
			else 
			{
				printf("%c",((a* (plain_text[i]-'A') + b) % 26 + 'A')); 
			}	
		}
		else
		{
			printf(" "); 
		}	
	}	
}

//Decryption
//D(x) = a^(-1) (x - b) mod 26
void dec(char cipher_text[], int modinv, int b)
{
	int i;
    for(i=0;i<strlen(cipher_text)-1;i++)
    {
		if (cipher_text[i] != ' ') //ignores spaces
		{	
			if (cipher_text[i] - 'A' < 0 || cipher_text[i] - 'A' > 25) //ignores non-alphabetical characters
			{
				printf("%c", cipher_text[i]);
			}
			else
			{
				if ((modinv * (cipher_text[i] - 'A' - b) % 26) < 0) 
				{
					printf("%c", ((modinv * (cipher_text[i] - 'A' - b) % 26) + 'A') + 26); //result will be negative if one of the characters is 'A' thus 26 is added to the result
				}
				else
				{					
					printf("%c", (((modinv * (cipher_text[i] - 'A' - b)) % 26) + 'A'));
				}
			}
		}	
		else
		{
			printf(" ");
		}	
	}
}
	
void main()
{
	char input[101], letter;
	char a[10];
	char b[10];
	char option[10];
	int state = 1;
	
	while (state)
	{		
		printf("\nEnter your text (max characters = 100): ");
		fgets(input, 101, stdin);
	
		if (strlen(input) != 1) //string length if the user only presses enter when asked for input is 1
		{
			int i=0;
			//Converts user input to upper case
			while (input[i]) 
			{
				letter = input[i];
				input[i] = toupper(letter);
				i++;
			}
			
			while(state)
			{
				printf("\nEnter the first key (must be a number, and relatively prime to 26)(1-25): ");
				fgets(a, 10, stdin);
				
				if (valInput(a) != 1)
				{
					continue;
				}
				else 
				{	
					if (atoi(a) < 1 || atoi(a) > 25) //a connot be 0 and highest value would be 25
					{
						printf("\nOut of range!\n");
						continue;
					}
					else
					{
						if (gcd(atoi(a), 26) != 1) //fist key must be relatively prime to 26 to be used in encryption/decryption
						{
							printf("\nNot relatively prime to 26!\n");	
							continue;
						}
						else
						{
							break;
						}
					}
				}	
			}
			
			while(state)
			{	
				printf("\nEnter second key (0-25): ");
				fgets(b, 10, stdin);
				
				if (valInput(b) != 1)
				{
					continue;
				}
				else
				{
					if (atoi(b) < 0 || atoi(b) > 25) //b must be between 0 and 25
					{
						printf("\nOut of range!\n");
						continue;
					}
					else
					{
						
						break;
					}
				}		
			}
			
			while(state)
			{
				printf("\n1: Encryption\n2: Decryption\nPlease select an option: ");
				fgets(option, 10, stdin);
				
				if (valInput(option) != 1)
				{
					continue;
				}
				else
				{
					switch (atoi(option)) 
					{
						case 1: 
							printf("\nYour cipher text is: ");
							enc(input, atoi(a), atoi(b));
							break;
						case 2:
							printf("\nYour plain text is: ");
							dec(input, inv(atoi(a)), atoi(b));
							break;
						default:
							printf("\nOut of range!\n");
							continue;
					}
					printf("\n");
					break;
				}	
			}
		}				
		else
		{
			printf("\nPressing Enter doesn't count!\n");
			continue;
		}
		break;
	}	

}
