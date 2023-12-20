/*************************************
 * Name: John Miller
 *Assignment Name: Homework 2
 *
 *Assignment for <friday, May 11>
 **************************************/

/**************************************
 *
 * Academic honesty certification:
 *    My signature below confirms that the
 *   above list of sources is complete AND
 *    that I/we have not talked to anyone else
 *    (e.g. CSC 161 students) about the solution
 *   to the problem
 *
 *   Signature: John Richard Miller
 *
 *
 ***************************************/

#include "homework2.h"

/*this function takes a pointer to the list of players, and the number of players on the
roster. The function returns a structure containing arrays of data that represent the roster of
characters sorted by their weights*/
/*precond: list is a valid pointer to the list, and numonroster is a valid integer that
represents the number of players on the roster*/
/*postconditions: the function returns a pointer to the sortstruct structure containing the
sorted data in the appropriate array fields*/
sortstruct_t *sort_by_field(player_t *list, int numOnRoster, char *field)
{
    sortstruct_t *sortedweights = malloc(sizeof(sortstruct_t) * 1);
    char *weight = "weight";
    char *height = "height";
    char *age = "age";
    if (strcmp(field, weight) == 0)
    {
        for (int i = 0; i < numOnRoster; i++)
        {
            (*sortedweights).data[i] = (*list).weight;
            (*sortedweights).lastname[i] = (*list).lastname;
            list = (*list).next;
        }
    }
    else if (strcmp(field, age) == 0)
    {
        for (int i = 0; i < numOnRoster; i++)
        {
            (*sortedweights).data[i] = (*list).age;
            (*sortedweights).lastname[i] = (*list).lastname;
            list = (*list).next;
        }
    }
    else if (strcmp(field, height) == 0)
    {
        for (int i = 0; i < numOnRoster; i++)
        {
            (*sortedweights).data[i] = (*list).height;
            (*sortedweights).lastname[i] = (*list).lastname;
            list = (*list).next;
        }
    }
    for (int j = 0; j < numOnRoster - 1; j++) // had to subtract one to not go over the index
    {
        for (int x = 0; x < numOnRoster - 1; x++) // had to subtract one to not go over the index
        {
            if ((*sortedweights).data[x] > (*sortedweights).data[x + 1])
            {
                double tempdub = (*sortedweights).data[x + 1]; // save the data for the switch
                char *temp = (*sortedweights).lastname[x + 1]; // save the data for the switch
                (*sortedweights).data[x + 1] = (*sortedweights).data[x];
                (*sortedweights).lastname[x + 1] = (*sortedweights).lastname[x];
                (*sortedweights).data[x] = tempdub;
                (*sortedweights).lastname[x] = temp;
            }
        }
    }
    return sortedweights;
}
/*this is a procedure that opens a file, check the number of players on the roster, and
returns an integer representing it. This function is key because we can use it's output
to loop through the file, and scan each player into a structure representing the player*/

/*precondition: char*filename is a valif string that represents a text file.
this file must have each player on it's individual line*/

/*postcondition: returns an integer representing the number of players*/
int num_players_on_team(char *filename)
{
    FILE *fp = fopen(filename, "r"); // opening up the file
    char ch;                         /*This variable is the variable that will step through the text file, char by char*/
    int NumPlayersOnRoster = 0;      /*This variable is the variable that will step through the text file, char by char*/
    if (fp == NULL)
    {
        printf("Unable to open file. an incorrect file name was given\n"); // handling file-opening error
        exit(EXIT_FAILURE);                                                // force an exit
    }
    while ((ch = fgetc(fp)) != EOF) //
    {
        if (ch == '\n')
        {
            NumPlayersOnRoster++; /*if we are at the end of a line representing
         a player's stats, we will tally it up as another player*/
        }
    }
    NumPlayersOnRoster++;      /*I will add one to the number of players on the roster, because the last player on the
         roster is ended by an EOF character, and not a newline character*/
    fclose(fp);                // closing the file
    return NumPlayersOnRoster; // return the number of players in the roster.
}

/*this function will take the data in the file representing the players on the roster,
and will then convert each player into a node in a linked list containing it's data */

/*preconditions: numPlayers is a number that respesents the number of players in the file*/

/*postconditions: returns a pointer to the first node of the linked list containing the data
of the players*/
player_t *file_to_list(int numPlayers, char *dataFile)
{
    player_t *topCopy;               // making a pointer to the firstnode to save the first node
    player_t *tracingPointer;        // making a pointer to traverse the list as I make it
    FILE *fh = fopen(dataFile, "r"); // opening the file to read
    int heightFeet = 0;              // var for scanning in players height in feet
    double heightInches = 0;         // var for scanning in players remaining height in inches
    bool firstTime = true;           // boolean to check if the loop is at it's first iteration
    if (fh == NULL)
    {
        printf("Unable to open file. an incorrect file name was given\n");
        exit(EXIT_FAILURE); // force an exit
    }
    else
    {
        for (int i = 0; i < numPlayers; i++) // the loop will scan for the number of players returned by the numplayers function
        {
            player_t *nextplayer = malloc(sizeof(player_t) * 1);                                                 // allocating space for the new player in the list
            int firstscan = fscanf(fh, "%s %s", (*nextplayer).firstname, (*nextplayer).lastname);                // scanning in the names of players
            int secondscan = fscanf(fh, "%d%s%s", &(*nextplayer).age, (*nextplayer).bats, (*nextplayer).throws); // scanning in ages and the way the player bats and throws
            int thirdscan = fscanf(fh, "%d%lf%d", &heightFeet, &heightInches, &(*nextplayer).weight);            // scanning in height values
            if (firstscan + secondscan + thirdscan != 8)                                                         // if we have not scanned in the correct number of items
            {
                printf("\nimproper input file formatting has occured, the data could not be scanned in\n");
                exit(EXIT_FAILURE); // force an exit
            }
            heightInches = heightInches / 12;                 // turning the number of inches into a decimal
            (*nextplayer).height = heightFeet + heightInches; // totaling up the height to set the player's field to be an accurate double number
            (*nextplayer).next = NULL;                        // setting the next player pointer to null for the time being, which changes each loop iteration
            if (firstTime == true)                            // if we are at the first iteration, the player we just made is the top node
            {
                topCopy = nextplayer;
                tracingPointer = topCopy;
                firstTime = false; // setting the boolean to false now that the first iteration is over
            }
            else
            {
                (*tracingPointer).next = nextplayer;     // the current players "next" pointer is the new player
                tracingPointer = (*tracingPointer).next; // the current player (tracing pointer) is set to tracingpointer
            }
        }
        fclose(fh);     // closing the file
        return topCopy; // return the top of the list
    }
}
/* averageHeight is a function that returns the average of the data field that
you give it in the form of a string of*/

/*preconditions: NumOnRoster is a number that respesents the number of players in the file,
list is a valid pointer to the head of the players list*/

/*postconditions: returns a double representing the average of each player of the specified field*/
double averageField(player_t *list, int NumOnRoster, char *field)
{
    char *weight = "weight";
    char *height = "height";
    char *age = "age";
    double dataSum = 0.0; // this will total up the data field in the list
    if (strcmp(weight, field) == 0)
    {
        while (list != NULL) // while we are not at the end of the list:
        {
            dataSum += (*list).weight; // add the height field to the sum
            list = (*list).next;       // make list the "next" pointer in the field
        }
    }
    else if (strcmp(height, field) == 0)
    {
        while (list != NULL) // while we are not at the end of the list:
        {
            dataSum += (*list).height; // add the height field to the sum
            list = (*list).next;       // make list the "next" pointer in the field
        }
    }
    else if (strcmp(age, field) == 0)
    {
        while (list != NULL) // while we are not at the end of the list:
        {
            dataSum += (*list).age; // add the height field to the sum
            list = (*list).next;    // make list the "next" pointer in the field
        }
    }
    else
    {
        printf("there was a bad input. make sure to use lowercase letters of your data field\n");
    }
    double *Average = malloc(sizeof(double));
    *Average = dataSum / NumOnRoster; // set the average to be the sum divided by the number of players
    return *Average;                  // return the average, even if the average was never changed, then it will just return 0
}

/* this procedure prints the player roster list.*/

/*preconditions: list is a valid pointer to a list*/
/*postconditions: none*/
void printList(struct player *list)
{
    int i = 1;
    while (list != NULL) // while we are not at the end of the list
    {
        printf("player %d: name: %s %s, age %d, bats %s, throws %s, height %lf, weight: %d\n",
               i, (*list).firstname, (*list).lastname, (*list).age,
               (*list).bats, (*list).throws, (*list).height, (*list).weight);
        printf("\n");
        i++;
        list = (*list).next; // the current node is set to be the "next" of the previous player node
    }
}

/*this function prints the output to the terminal and to a file called "outputFile.txt*/
/*preconditions: sortedlist is a valid pointer to a sortstruct structure, int numplayers
represents the number of players on the roster, and char* datatype is something like height,
weight, or age*/
/*postconditions: */
void print_sorted_structure(sortstruct_t *sortedList, int numPlayers, char *outputFile, char *datatype)
{
    FILE *filePointer = fopen(outputFile, "a"); // we are appending to the end of the output file
    if (filePointer == NULL)
    {
        printf("error opening file\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numPlayers; i++)
    {
        printf("player %d by %s is %s:  %lf\n", i + 1, datatype, (*sortedList).lastname[i], (*sortedList).data[i]);               // output to terminal
        fprintf(filePointer, "player %d by %s is %s:  %lf\n", i + 1, datatype, (*sortedList).lastname[i], (*sortedList).data[i]); // output to the file
    }
    fprintf(filePointer, "\n");
    fclose(filePointer); // close the output file
    printf("\n");        // write a newline character
}
