//Program: CommandLineFieldOutput.c
//Author: Christian Hughes - 1.0
//CIS 308: Tuesday 2:30-4:20

//Description: The program accepts a text file, and will output specific fields from said file based on command line input.
//Input: Command line argument in the form ./proj_name [field number as integer >=1, seperated by spaces] ... < [input file]
//Example Input: ./my_proj 1 4 5 < text.txt
//Example Output aaa ddd eee
//               aaa ddd eee

#include <stdio.h>
#include <string.h>
#include <ctype.h>

//The main implementation method for the program.
int main(int argc, char *argv[])
{
	//The line being read in.
	char line[500];
	//The current field being processed.
	int fieldCounter;;
	//The index in the command line argument array that must be fufilled.
	int argumentCounterIndex;
	//Returns 1 if we have reached the end of the line.
	int endOfLine;
	//A pointer that will refer to the beginging of each field.
	char *line_ptr = NULL;
	//A pointer that will refer to the '\0' character at the end of each field.
	char *line_ptr2 = NULL;
	//The number of the field that the user is looking to have printed.
	int fieldArgumentNumber = 1;

	//Insert a newline character at the beginning of the file for cosmetic affect. 
	putchar('\n');
	
	//While there are still lines to process in the file...
	while (fgets(line, 500, stdin))
	{
		//Create a pointer to the begining of the line.
		line_ptr = line;
		//Initally set to false.
		endOfLine = 0;
		//Initialize the argument counter index to the first command line argument after file name (user defined field number).
		argumentCounterIndex = 1;
		//Initialize the current field that is being processed to 0.
		fieldCounter = 0;
		//Intitalize the user defined field, to be printed out, to 1.
		fieldArgumentNumber = 1;
		
		//While we are still reading the current line...
		while (endOfLine == 0)
		{
			//Incrament the field that is currently being processed.
			fieldCounter++;
			
			//Move the first pointer onwards to eliminate spaces (This will end up at the first letter of the first word).
			while (isspace(*line_ptr))
			{
				line_ptr++;
			}
			
			line_ptr2 = line_ptr;
			
			//If this statement is true, that means that we are already at the end of the line.
			if (*line_ptr2 == '\0')
			{
				endOfLine = 1;
			}
			//Otherwise, we need to process the line.
			else
			{
			
				while (!isspace(*line_ptr2)) 
				{
					line_ptr2++;
				}
				
				*line_ptr2 = '\0';

				int allInt = sscanf(argv[argumentCounterIndex], "%d", &fieldArgumentNumber);
				
				//Do error checking to ensure that all arguments are integers.
				if (allInt != 1)
				{
					fprintf(stderr, "All arguments must be integers\n. Please run the program again with valid input.\n\n");
					return 1;
				}
				
				//Do error checking to ensure that field are in numerical order.
				int firstField;
				int currentField;
				sscanf(argv[1], "%d", &firstField);
				for (int i = 1; i < argc; i++)
				{
					sscanf(argv[i], "%d", &currentField);
					if (currentField < firstField)
					{
						fprintf(stderr, "Field arguments must be in numerical order.\nPlease run the program again with valid input.\n\n");
						return 1;
					} 
				}
				
				//Do error checking to ensure that no fields are repeated.
				for (int i = 1; i < argc - 1; i++)
				{
					sscanf(argv[i], "%d", &firstField);
					for (int j = i + 1; j < argc; j++)
					{
						sscanf(argv[j], "%d", &currentField);
						if (firstField == currentField)
						{
							fprintf(stderr, "Field arguments cannot be repeated. All numbers must be unique.\nPlease run the program again with valid input.\n\n");
							return 1;
						}
					}
				}
				
				
				//Print out the given field.
				if (fieldCounter == fieldArgumentNumber)
				{
					printf("%s ", line_ptr);
					if (argumentCounterIndex + 1 != argc)
					{
						argumentCounterIndex++;
					}
				}
				
				line_ptr = line_ptr2 + 1;
			}
		}
		//Insert a newline character before processing the next line in the file.
		putchar('\n');
	}
	//Insert a newline character before the program ends.
	putchar('\n');
}

