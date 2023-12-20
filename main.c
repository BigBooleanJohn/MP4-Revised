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

/*this is the main program, which provides statistical analysis
and visualization of the players on the 2014 San francisco Giants
baseball team. I will use a while loop to allow the user to select a
pick from a variety of statistical options*/

int main(int argc, char *argv[])
{
    if (argc < 3) // checking for erroneous command line arguments
    {
        printf("Error: incorrect command line arguments\n");
        printf("we need two text files for input and output in the command line\n"); // to show an error was given
    }
    else
    {
        int numplayers = num_players_on_team(argv[1]);
        player_t *teamList = file_to_list(numplayers, argv[1]);
        int option = 0;
        while (option != 6)
        {
            printf("this program allows you to interact with data from the 2013 SF giants\n");
            printf("what would you like to do?\n");
            printf("option 1: view team roster\n");
            printf("option 2: view team averages compared to league averages\n");
            printf("option 3: view players sorted by shortest to tallest and print it to an output file\n");
            printf("option 4: view players sorted by least heavy to heaviest and print it to an outout file\n");
            printf("option 5: view players sorted by youngest to oldest and write it to an outout file\n");
            printf("put in the number you would like:");
            scanf("%d", &option);
            if (option == 1)
            {
                printList(teamList);
            }
            else if (option == 2)
            {
                /*source: https://www.espn.com/mlb/stats/rosters/_/sort/average_weight/order/true*/
                printf("\nin 2013, the league average height is 6.08333333333 feet\n");
                printf("in 2013, the league average age is 27.8066666667 years\n");
                printf("in 2013, the league average age is 207 pounds\n");
                printf("average age of the 2013 giants is %lf\n", averageField(teamList, numplayers, "age"));
                printf("average height of the 2013 giants is %lf\n", averageField(teamList, numplayers, "height"));
                printf("average weight of the 2013 giants is %lf\n", averageField(teamList, numplayers, "weight"));
            }
            else if (option == 3)
            {
                sortstruct_t *sortedByHeight = sort_by_field(teamList, numplayers, "height");
                print_sorted_structure(sortedByHeight, numplayers, argv[2], "height(feet)");
            }
            else if (option == 4)
            {
                sortstruct_t *sortedByWeight = sort_by_field(teamList, numplayers, "weight");
                print_sorted_structure(sortedByWeight, numplayers, argv[2], "weight(pounds)");
            }
            else if (option == 5)
            {
                sortstruct_t *sortedByAge = sort_by_field(teamList, numplayers, "age");
                print_sorted_structure(sortedByAge, numplayers, argv[2], "age(years)");
            }
            else if (option == 6)
            {
                printf("thank you!\n");
            }
            else
            {
                printf("\nBad input\n\n");
            }
        }
    }
    return 0;
}