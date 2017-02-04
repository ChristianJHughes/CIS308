//Program: SpeechStatsAssignment3.c
//Author: Christian Hughes - 1.0
//CIS 308: Tuesday 2:30-4:20

//DESCRIPTION:
//The program accepts a text file, and will the top 10 most frequently occuring words (Does not include ties).
//
//RULES:
//1) Words are separated by text or punctuation.
//2) The program should not be case-sensitive.
//3) Words of 2 letters or less will be ignored, unless both letters are in
//uppercase.
//4) If two words only differ by a final “s” or a final “d”, they will be recognized
//as the same word and stored in the shortest form if a shortest form is found. If you really want to, you can try to handle a few irregular plurals (man, woman) and irregular verbs, but this
//isn’t required.
//
//INPUT: 
//Command line argument in the form ./SpeechStatsAssignment3 [wordsToIgnore .txt file] < [input .txt file]
//
//EXAMPLE INPUT:
//./SpeechStatsAssignment3 wordsToIgnore.txt < Kennedy.txt
//
//EXAMPLE OUTPUT:
//Here is a list of the most frequently occuring words (Words in argument .txt file are ignored):
//The - 121 occurences
//and - 110 occurences
//this - 43 occurences
//for - 27 occurences
//that - 26 occurences
//will - 24 occurences
//space - 23 occurences
//new - 22 occurences
//all - 15 occurences
//but - 14 occurences

//Import all required libraries.
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

//Defines a constant value for word length. Can be changed in the future.
#define  WORD_LEN   20

//Defines the structure for a binary tree. Each node contains a word and a counter of how many times that word has been read in. It is arranged alphabetically. 
//Each node has pointers to left and right nodes.
typedef struct Binary_Tree 
{
	char word[WORD_LEN];
	int counter;
	
	struct Binary_Tree *right_node;
	struct Binary_Tree *left_node;
} NODE;

//A function that returns whether or not the given word is in the tree (1 for yes, 0 for no). It will incrament the word counter of the node containting the desired word, should it be found.
int isInTree(NODE **tree, char *wordToCompare)
{
	//First check to see if the tree is empty. THIS IS THE RECURSIVE BASE CASE.
	if (!(*tree))
	{
		return 0; //There is no tree here.
	}
	
	//If the strings only differ by a final 's' or 'd' character, incrament the shortest version of that word, and return 1.
	if (strlen(wordToCompare) - strlen(((*tree)->word)) == -1 || strlen(wordToCompare) - strlen(((*tree)->word)) == 1)
	{
		int wordInTreeLength = strlen(((*tree)->word));
		int wordToCompareLength = strlen(wordToCompare);
		
		//if word to compare is smaller, and all letters save for the last are the same...
		if (wordToCompareLength - wordInTreeLength == -1 && strncmp(wordToCompare, ((*tree)->word), wordToCompareLength) == 0)
		{
			//If the last letter is an 's' or a 'd'...
			if (((*tree)->word)[wordInTreeLength - 1] == 's' || ((*tree)->word)[wordInTreeLength - 1] == 'd')
			{
				//Copy the shortest form of the word into that node. Incrament the counter. Return that it was found.
				strncpy(((*tree)->word), wordToCompare, WORD_LEN);
				(*tree)->counter++;
				return 1;
			}
		}
		//Else if the word already in the tree is ALREADY the shortest form, and all letters in both words are the same (save for the last letter of the word being passed in)...
		else if (wordToCompareLength - wordInTreeLength == 1 && strncmp(wordToCompare, ((*tree)->word), wordInTreeLength) == 0)
		{
			if (wordToCompare[wordToCompareLength - 1] == 's' || wordToCompare[wordToCompareLength - 1] == 'd')
			{
				(*tree)->counter++;
				return 1;
			}
		}
	}
	
	//If the strings are equal, then incrament the counter at that node, and return 1 (indicates that the word is already in the tree).
	if (strcasecmp(wordToCompare, ((*tree)->word)) == 0)
	{
		(*tree)->counter++;
		return 1; //We found the node we are looking for, and incremeted the counter.
	}
	//Else if the word passed in is less (alphabetically) than the word at the current node, we want to make a recursive call on the left child.
	else if (strcasecmp(wordToCompare, ((*tree)->word)) < 0)
	{
		return isInTree(&((*tree)->left_node), wordToCompare);
	}
	//Else if the word passed in is more (alphabetically) than the word at the current node, we want to make a recursive call on the right child.
	else if (strcasecmp(wordToCompare, ((*tree)->word)) > 0)
	{
		return isInTree(&((*tree)->right_node), wordToCompare);
	}
	//Return 0 at the end to make the compiler happy - the program should never reach this line. 
	return 0;
}

//This function adds a node to the binary search tree. PARAMETERS: tree = root of tree to be added to. wordToCompare = word to add to the tree.
void addNodeToTree(NODE ** tree, char *wordToCompare)
{
	//Creates a temporary node to be added to the tree.
	NODE *nodeToBeInserted = NULL;
	//If the tree is empty at this location... Add a node!
	if (!(*tree))
	{
		nodeToBeInserted = (NODE*) malloc(sizeof(NODE));
		nodeToBeInserted->left_node = NULL;
		nodeToBeInserted->right_node = NULL;
		nodeToBeInserted->counter = 1;
		strncpy(nodeToBeInserted->word, wordToCompare, WORD_LEN);
		*tree = nodeToBeInserted;
		return;
	}
	//If the tree is not empty at this location, then we need to recursively get to a spot where we can insert a new node.
	//if the word passed in is less (alphabetically) than the word at the current node, we want to make a recursive call on the left child.
	if (strcasecmp(wordToCompare, ((*tree)->word)) < 0)
	{
		addNodeToTree(&((*tree)->left_node), wordToCompare);
	}
	//Else if the word passed in is more (alphabetically) than the word at the current node, we want to make a recursive call on the right child.
	else if (strcasecmp(wordToCompare, ((*tree)->word)) > 0)
	{
		addNodeToTree(&((*tree)->right_node), wordToCompare);
	}
}

//Returns the node with the highest count in the tree. PARAMATERS: tree - the root of the tree to be searched. previousMaximum - The current maximum that has been found in the tree thus far.
NODE* inorderTraversal(NODE *tree, int previousMaximum)
{
	//Keeps track of the higest counter that we have found in the tree thus far.
	NODE *highest = NULL;
	NODE *highest2 = NULL;
	
	//If the tree is not null...
	if (tree)
	{
		//Find the highest value among the left children.
		highest = inorderTraversal(tree->left_node, previousMaximum);
		//Find the higest value among the right children.
		highest2 = inorderTraversal(tree->right_node, previousMaximum);
		
		//Make sure that NODE* highest refers to the higher of these two outcomes.
		if ((highest2 && highest && highest2->counter > highest->counter) || (highest2 && !highest)) 
		{
			highest = highest2;
		}
		//If the root is more than the highest that we found among the children, then the highest becomes the root. Otherwise, it stays the same.
		if (((highest == NULL) || (tree->counter > highest->counter)) && tree->counter < previousMaximum)
		{
			highest = tree;
		}

	}
	//return what is now the node with the highest word frequency count.
	return highest;
}

//Frees all of the memory allocated for the tree. To be called after all output is properly printed. PARAMETERS: tree = The root of the tree.
void freeTree(NODE *tree)
{
	free(tree->right_node);
	free(tree->left_node);
	free(tree);
}

//Returns 1 if the given word is in the file. PARAMETERS: fp = the file that we are reading from. wordToLookup = the word that we want to lookup. fileName = The name of the .txt file.
int isAWordToIgnore(char *wordToLookup, FILE *fp, char *fileName)
{
	//The line being read in.
	char line[500];
	//Returns 1 if we have reached the end of the line.
	int endOfLine;
	//A pointer that will refer to the beginging of each field.
	char *line_ptr = NULL;
	//A pointer that will refer to the '\0' character at the end of each field.
	char *line_ptr2 = NULL;
	
	fp = fopen(fileName, "r");

	//While there are still lines to process in the file...
	while (fgets(line, 500, fp))
	{
		//Create a pointer to the begining of the line.
		line_ptr = line;
		//Initally set endOfLine to false (we are at the begining of the line).
		endOfLine = 0;
		
		//While we are still reading the current line...
		while (endOfLine == 0)
		{
			//Move the first pointer onwards to eliminate spaces and punctuation (This will end up at the first letter of the first word).
			while (isspace(*line_ptr) || ispunct(*line_ptr))
			{
				line_ptr++;
			}
			
			line_ptr2 = line_ptr;
			
			//If this statement is true, that means that we are already at the end of the line.
			if (line_ptr2[0] == '\0')
			{
				endOfLine = 1;
			}
			//Otherwise, we need to process the line.
			else
			{
				//While we are actually dealing with letters (I.E. Not spaces or punctionation)...
				while (!isspace(*line_ptr2) && !ispunct(*line_ptr2) && *line_ptr2 != '\0') 
				{
					line_ptr2++;
				}
				
				//Add a \0 to signify that we have reached the end of this particular string.
				if (line_ptr2[0] == '\0')
				{
					endOfLine = 1;
				}
				else
				{
					*line_ptr2 = '\0';
				}
				
				if (strcasecmp(line_ptr, wordToLookup) == 0)
				{
					fclose(fp);
					return 1;
				}
				//We can confidently reset the counters and move on to the next word.
				if (endOfLine == 0)
				{
					line_ptr = line_ptr2 + 1;
				}
				
			}
		}
	}
	fclose(fp);
	return 0;
}

//The main entry point of the program. 
int main(int argc, char *argv[])
{
	//The line being read in.
	char line[500];
	//Returns 1 if we have reached the end of the line.
	int endOfLine;
	//A pointer that will refer to the beginging of each field.
	char *line_ptr = NULL;
	//A pointer that will refer to the '\0' character at the end of each field.
	char *line_ptr2 = NULL;
	//An integer that will store the highest word occurences in the tree (for 10 words).
	int currentMaxWordCount = 1000;
	//An integer that keeps track of how many total nodes are in the binary search tree.
	int nodesInTree = 0;
	//This a node in the binary tree representing the root -- All other nodes in the tree will extend from this one.
	NODE *root;
	
	
	//Insert a newline character at the beginning of the file for cosmetic affect. 
	putchar('\n');
	
	//First to check whether or not the user has passed in a valid Command Line Argument
	if (argc != 2)
	{
		printf("Invalid command line arguments. Please enter your input in the form ./ProgramName WordsToIgnore.txt < InputFile.txt\nA TEXT FILE IS REQUIRED.\nUse a blank .txt file if there are no words that you would like to ignore.\n\n");
		return 1;
	}
	
	//Check whether or not the user passed in a valid .txt file.
	FILE *fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		printf("Invalid file passed in for words to ignore.\nPlease ensure that you are passing in a valid .txt file as an argument.\n\n");
		return 1;
	}
	
	
	//While there are still lines to process in the file...
	while (fgets(line, 500, stdin))
	{
		//Create a pointer to the begining of the line.
		line_ptr = line;
		//Initally set endOfLine to false (we are at the begining of the line).
		endOfLine = 0;
		
		//While we are still reading the current line...
		while (endOfLine == 0)
		{
			//Move the first pointer onwards to eliminate spaces and punctuation (This will end up at the first letter of the first word).
			while (isspace(*line_ptr) || ispunct(*line_ptr))
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
				//While we are actually dealing with letters (I.E. Not spaces or punctionation)...
				while (!isspace(*line_ptr2) && !ispunct(*line_ptr2) && *line_ptr2 != '\0') 
				{
					line_ptr2++;
				}
				
				//Add a \0 to signify that we have reached the end of this particular string.
				*line_ptr2 = '\0';
						
						//If the given word is more than two letters (Or it is two letters that are both uppercase)...
						if ((strlen(line_ptr) >= 2))
						{
							if (((isupper(line_ptr[0])) && (isupper(line_ptr[1])) && (strlen(line_ptr) == 2)) || strlen(line_ptr) > 2)
							{ 
								//AND THE WORD IS NOT IN OUR IGNORE LIST...
								if (isAWordToIgnore(line_ptr, fp, argv[1]) == 0)
								{
									//Check to see if the given word is NOT in the tree... If it was in the tree, then the function call below 
									//incramented the counter of the node containing that word.
									if (isInTree(&root, line_ptr) == 0) 
									{
										//The word was not found in the tree, so we add it, and incrament the total number of nodes.
										addNodeToTree(&root, line_ptr);
										nodesInTree++; //This varaible exists for testing purposes.
									}
								}
							}
						}
						//We can confidently reset the counters and move on to the next word.
						line_ptr = line_ptr2 + 1;
			}
		}
	}
	
	//ALL WORDS ARE NOW IN THE BINARY SEARCH TREE. HOORAY!
	
	//Prints for cosmetic effect...
	printf("Here is a list of the most frequently occuring words (Words in argument .txt file are ignored): \n");
	
	//Creates a new NODE* denoting the node with the current highest word count.
	NODE *highest;
		
	//Create index the of the for loop.
	int i;

	//Prints out the top 10 words (or all of the words, should there be fewer than 10 words meeting the criteria) and thier frequnecy counters, line by line.
	for (i = 0; i < 10; i++)
	{
		if (i < nodesInTree)
		{
			highest = inorderTraversal(root, currentMaxWordCount);
			if (highest != NULL)
			{
				printf("%s - %d occurences\n", highest->word, highest->counter);
				currentMaxWordCount = highest->counter;
			}
			
		}
	}
	
	//Print a newline at the end of the file for cosmetic effect.
	printf("\n");
	//Close the file containing Words to Ignore.
	fclose(fp);
	//Free all of the memory allocated for the tree. 
	freeTree(root);
}	

