#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Struct holds time content was written
//and content as a 2d char array
//Also the number of rows the content has
struct JEntry
{
    int rows;
    char *time;
    char **content;
};

//My Delimiter to split journal entries in the file.
char entryDelimiter = (char)007;

//Add a line to the content array of a JEntry struct
//Returns a pointer to the new realloc() array
char **addContentRow(char **array, char line[], int *rows)
{
    int lineSize = 0;
    //Finds how long the line[] array is
    while(1 == 1)
    {
        if (line[lineSize] == '\n')
        {
            if (lineSize == 0)
                break;
            else
            {
                lineSize++;
                break;
            }
        }
        lineSize++;
    }

    // If this is the first row of the content array then init it rather than realloc it.
    if (*rows == 0)
    {
        *rows += 1;
        array = malloc(sizeof(char**));
        array[*rows-1] = malloc(lineSize);
        strcpy(array[*rows-1],line);
        return array;
    }
    else //Run as long as it isn't the first entry
    {
        *rows += 1;
        array = realloc(array, *(rows)*sizeof(char**));
        array[*rows-1] = malloc(lineSize);
        strcpy(array[*rows-1],line);
        return array;
    }
}

//Add a new JEntry to the JEntry list and return the new pointer.
struct JEntry *addJEntry(struct JEntry *list, int *length, char initRow[])
{
    //Get current time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //Use these to convert grab the hour, minutes, seconds to char arrays
    char hour[12] = "";
    char minute[12] = "";
    char second[12] = "";
    char myTime[8] = "";

    sprintf(hour,"%d",tm.tm_hour);
    sprintf(minute,"%d",tm.tm_min);
    sprintf(second,"%d",tm.tm_sec);

    //Add 0 to char array if the time is less than 10.
    //Makes 9 -> 09 and 4 -> 04
    //For Consistant spacing and array size
    if ((tm.tm_hour) < 10)
        strcat(myTime, "0");
    strcat(myTime, hour);
    strcat(myTime, ":");
    if ((tm.tm_min) < 10)
        strcat(myTime, "0");
    strcat(myTime, minute);
    strcat(myTime, ":");
    if ((tm.tm_sec) < 10)
        strcat(myTime, "0");
    strcat(myTime, second);

    //Init if first Entry
    if (*length == 0)
    {
        *length += 1;
        list = malloc(sizeof(struct JEntry));
        list[*length-1].rows = 0;
        //Start new content array
        list[*length-1].content = addContentRow(list[*length-1].content, initRow, &(list[*length-1].rows));
        list[*length-1].time = malloc(sizeof(myTime));
        strcpy(list[*length-1].time, myTime);
        return list;
    }
    else //Realloc entry array
    {
        *length += 1;
        list = realloc(list, *(length)*sizeof(struct JEntry));
        list[*length-1].rows = 0;
        list[*length-1].content = addContentRow(list[*length-1].content, initRow, &(list[*length-1].rows));
        list[*length-1].time = malloc(sizeof(myTime));
        strcpy(list[*length-1].time, myTime);
        return list;
    }
}

//Remember to close the file stream!
void aWriteArray(FILE *fstream, char ** content)
{
    //Go through content until we run into end of file character
    int i = 0;
    while (content[i][0] != '\0')
    {
        fprintf(fstream, "%s", content[i]);
        i++;
    }
}

//Write a Journal Entry
void aWriteJEntry(char file[], struct JEntry doc)
{
    FILE *fstream;
    //Open file in append mode
    fstream = fopen(file, "a");
    fprintf(fstream, "%c\n", entryDelimiter);
    fprintf(fstream, "%s\n", doc.time);
    //Write the content of the Entry
    aWriteArray(fstream, doc.content);
    fclose(fstream);
}

//Read and print Journal Entry File
void aReadJEntrys(char file[])
{
    //Read everything one character at a time
    //Easiest way to duplicate the .txt file
    char buff = 0;
    char buffLast = ' ';
    FILE *fstream = fopen(file, "r");
    int entryIndex = 0;
    int line = 0;

    //Read till end of file character
    while (buff != EOF)
    {
        if (buff == '\n')
            printf("\n");
        else if (buff == entryDelimiter)
            printf("\n");
        else
            printf("%c", buff);
        buff = fgetc(fstream);
    }
    fclose(fstream);
}

//Init Journal file string
char journalFile[13] = "";

//JEntry array and array size
struct JEntry *myDoc;
int myDocLength = 0;

int exitN = 0;

int main(void)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //Start a File from today.
    //Create file based on date
    char year[12] = "";
    char month[12] = "";
    char day[12] = "";
    sprintf(year,"%d",tm.tm_year + 1900);
    sprintf(month,"%d",tm.tm_mon + 1);
    sprintf(day,"%d",tm.tm_mday);

    strcat(journalFile, year);
    if ((tm.tm_mon + 1) < 10)
        strcat(journalFile, "0");
    strcat(journalFile, month);
    if ((tm.tm_mday) < 10)
        strcat(journalFile, "0");
    strcat(journalFile, day);
    strcat(journalFile, ".txt");

    int menuSelector = -1;
    while (exitN == 0)
    {
        printf("Current File: %s\n\n", journalFile);
        printf("[0] Add entry\n");
        printf("[1] Read Today's File\n");
        printf("[2] EXIT!\n");
        while(menuSelector > 2 || menuSelector < 0)
        {
            printf("Select a Menu option:\n");
            scanf(" %d", &menuSelector);
            getchar();
        }
        if (menuSelector == 0)
        {
            system("clear");
            printf("Enter your Journal Entry:\n");
            printf("(Type ^ to exit entry mode.)\n\n");
            menuSelector = -1;
            char entry[200];

            //init New entry
            int iteration = 0;
            while (entry[0] != '^')
            {
                fgets(entry, 200, stdin);
                if (entry[0] == '^')
                {
                    if (iteration == 0)
                    {
                        system("clear");
                        break;
                    }
                    else
                    {
                        system("clear");
                        myDoc[myDocLength-1].content = addContentRow(myDoc[myDocLength-1].content, "\0", &(myDoc[myDocLength-1].rows));
                        aWriteJEntry(journalFile, myDoc[myDocLength-1]);
                        break;
                    }
                }
                if (iteration == 0)
                {
                    myDoc = addJEntry(myDoc, &myDocLength, entry);
                }
                else
                {
                    myDoc[myDocLength-1].content = addContentRow(myDoc[myDocLength-1].content, entry, &(myDoc[myDocLength-1].rows));
                }
                //printf("%s\n", entry);
                iteration++;
            }
            entry[0] = ' ';
        }
        else if (menuSelector == 1)
        {
            system("clear");
            aReadJEntrys(journalFile);
            printf("\n[Enter to continue or Ctrl+Shift+UP to scroll up]\n");
            menuSelector = -1;
            getchar();
            system("clear");
        }
        else if (menuSelector == 2)
        {
            exitN = 1;
            break;
        }
    }
}
