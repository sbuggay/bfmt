//bfmt version 1.0
//todo
//do convert code
//do interactive bfmt
//make a better parser

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


char *convert(char *code, char *lang) //Convert pseudocode
{
    if(strcmp(lang, "c") == 0)
        printf("c");
    if(strcmp(lang, "python") == 0)
        printf("python");
    return "lol";
}

int isBFChar(char c) //Determines if the character is a BF character
{
    if(c == '+' || c == '-' || c == '<' || c == '>' || c == '[' || c == ']' || c == '.' || c == ',')
    {
        return 1;
    }
    return 0;
}

int fileCount(char *fileName) //Counts the number of characters in a file
{
    FILE *file;
    file = fopen(fileName, "r");
    int bfCount = 0;
    char temp;
    while((temp=fgetc(file)) != EOF)
        if(isBFChar(temp))
            bfCount++;
    fclose(file);
    return bfCount;
}

char *readFile(char *fileName) //Reads all BF characters into a code string
{
    FILE *file;
    file = fopen(fileName, "r");
    int fileLength = fileCount(fileName);
    char *code = malloc(fileLength * sizeof(char));
    char *orig = code;
    char c;
    file = fopen(fileName, "r");

    while((c = (char)fgetc(file)) != EOF)
    {
        if(isBFChar(c))
        {
            *code = c;
            code++;
        }
    }
    *code = '\0';
    printf("[CODE]:\n");
    char *temp = orig;
    int i;
    for(i = 0; i < fileLength; i++, temp++)
    {
        printf("%c", *temp);
    }
    printf("\n");
    fclose(file);
    return orig;
}

int writeFile(char *oFileName, char *output) //Writes only the BF code to a file
{
    FILE *ofile;
    int outputLength = strlen(output);
    ofile = fopen(oFileName, "w");
    int i;
    for(i = 0; i < outputLength; i++, output++)
    {
        fputc(*output, ofile);
    }
    fclose(ofile);
    return 0;
}

int interpret(char *input) //Interprets the input
{
    printf("[INTERPRETING]:\n");
    unsigned char loopDepth = 0;
    unsigned char *cells = malloc(30000 * sizeof(char));
    while(*input != EOF)
    {
        switch(*input)
        {
        case '>': //Move cell right
            ++cells;
            break;
        case '<': //Move cell left
            --cells;
            break;
        case '+': //Increase current cell by 1
            ++*cells;
            break;
        case '-': //Decrease current cell by 1
            --*cells;
            break;
        case '[': //Starting loop
            loopDepth = 1;
            if(*cells == 0)
            {
                do
                {
                    *input++;
                    if(*input == '[') loopDepth++;
                    if(*input == ']') loopDepth--;
                } while(loopDepth > 0);
            }
            break;

        case ']': //Ending loop
            loopDepth = 1;
            if(*cells != 0)
            {
                do
                {
                    *input--;
                    if(*input == '[') loopDepth--;
                    if(*input == ']') loopDepth++;
                } while(loopDepth > 0);

            }
            break;
        case '.': //Print current cell
            putchar(*cells);
            break;
        case ',':
            *cells = getchar();
            break;
        }
        *input++;
    }
    return 0;
}

int main(int argc, char *argv[]) // Main duh
{
    printf("bfmt v1.0\n");
    char *input = NULL;
    char *iFileName = NULL;
    char *oFileName = NULL;
    int de = 0;
    char c;

    while((c = getopt(argc, argv, "qiodn:")) != -1)
    {

        switch (c)
        {

        case 'n': //An output file with the code only
            oFileName = optarg;
            break;

        case 'd': //Toggles debug mode
            de = 1;
            break;

        case 'o': //An output file for the BF output

            break;

        case 'i': //A input file containing all input asked for the program

            break;

        case 'q': //Places optimization in an output file

            break;

        }

    }
    if(argc > 1)
    {
        iFileName = argv[optind];
        if((input = readFile(iFileName)) == NULL) return 0;
        interpret(input);
        if(oFileName != NULL) writeFile(oFileName, input);
    }
    else
    {
        iFileName = "bfcode.txt";
        if((input = readFile(iFileName)) == NULL) return 0;
        interpret(input);
        if(oFileName != NULL) writeFile(oFileName, input);
    }
	int i;
	scanf("%d",&i);
    free(input);
    return 0;
}


