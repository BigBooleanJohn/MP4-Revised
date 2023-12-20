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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#define MAX_CHARS 50          // defining a max charactes macro
#define MAX_FOR_HANDS 2       // for the arrays that only have the characters L or R
#define MAX_ROSTER_PLAYERS 60 // MLB has a 40 man roster
typedef struct player player_t;

struct player // player declaration
{
    char firstname[MAX_CHARS];
    char lastname[MAX_CHARS];
    int age;
    int weight;
    char bats[MAX_FOR_HANDS];
    char throws[MAX_FOR_HANDS];
    double height;
    struct player *next;
};

typedef struct sortstruct sortstruct_t;
struct sortstruct
{
    char *lastname[MAX_ROSTER_PLAYERS];
    double data[MAX_ROSTER_PLAYERS];
};

sortstruct_t *sort_by_field(player_t *list, int numOnRoster, char *field);

int num_players_on_team(char *filename);

player_t *file_to_list(int numPlayers, char *dataFile);

double averageField(player_t *list, int NumOnRoster, char *field);

void printList(struct player *list);

void print_sorted_structure(sortstruct_t *sortedList, int numPlayers, char *outputFile, char *datatype);
