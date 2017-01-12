/* !* Text-Replacement
 *
 * \description Text replacement program
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at>
 *
 * \version Rev.: 01, 17.12.2016 - Created
 *          Rev.: 02, 17.12.2016 - Added first parts of the program, input and
 *                                 output, with case-sensitive and
 *                                 case-insensitive for every word, string replacement
 *                                 is comming later.
 *          Rev.: 03, 18.12.2016 - allocating memory with malloc instead of static
 *                                 memory
 *          Rev.: 04, 18.12.2016 - could also include myHeader.h for ASCII formation
 *                                 clear, clearNoHelp
 *
 *
 *
 *
 * \information FINAL is not working currently
 *              tested on mac (sierra 10.12.2), windows 10, and linux(ubuntu14.04)
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//#include "myHeader.h"

#define DEBUG 0
#define FINAL 0       //Activate this for final program (with string change)
#define PROTOTYPE 1   //Activate this for prototype program (full buffer change)

/*------------------------------------------------------------------*/
/* S T A R T   O F   P R O G R A M                                  */
/*------------------------------------------------------------------*/

#if defined(__APPLE__) && defined(__MACH__) || defined(__linux__)

/* ---- ASCII FORMAT FOR TERMINAL ---- */

#define RESET   "\033[0m"
#define BLACK   "\033[30m"                 /* Black */
#define RED     "\033[31m"                 /* Red */
#define GREEN   "\033[32m"                 /* Green */
#define CYAN    "\033[36m"                 /* Cyan */
#define BOLD    "\033[1m"                  /* Bold */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#endif

#if defined(_WIN32) || defined(_WIN64)

/* ---- ASCII FORMAT NOT SUPPORTED IN WINDOWS ---- */

#define RESET   ""
#define BLACK   ""
#define RED     ""
#define GREEN   ""
#define CYAN    ""
#define BOLD    ""
#define BOLDRED     ""
#define BOLDGREEN   ""
#define BOLDBLACK   ""
#define BOLDCYAN    ""
#define BOLDWHITE   ""

#endif

/* ---- SUBROUTINE LINE DECLARATION ---- */

void helpdesk_1(void);
void clearNoHelp(void);

/* ---- MAIN PROGRAM ---- */

int main(int argc, char *argv[])
{
    FILE* pFin = NULL;
    FILE* pFout = NULL;
    
#if FINAL
    char *StringFind = NULL;
    char *StringReplace = NULL;
    char *buffer_word = NULL;
    char *buffer2 = NULL;
    int j = 0;
#endif
    
#if DEBUG
    int i = 0;
#endif
    
    char *buffer = NULL;
    
    int casesensitive;
    int checksum = 0;
    int counter = 0;
    
    
/* ---- ALLOCATING MEMORY FOR BUFFER ---- */
    
    buffer = (char *)malloc(104857600 * sizeof(char));
    if (buffer == NULL)
    {
        free(buffer);
        printf(BOLD"ERROR: Malloc Error!\n"RESET);
        return -1;
    }
    
#if FINAL
    buffer_word = (char *)malloc(104857600 * sizeof(char));
    if (buffer_word == NULL)
    {
        free(buffer_word);
        printf(BOLD"ERROR: Malloc Error!\n"RESET);
        return -1;
    }
    
    buffer2 = (char *)malloc(104857600 * sizeof(char));
    if (buffer2 == NULL)
    {
        free(buffer2);
        printf(BOLD"ERROR: Malloc Error!\n"RESET);
        return -1;
    }
    
    StringFind = (char *)malloc(104857600 * sizeof(char));
    if (StringFind == NULL)
    {
        free(StringFind);
        printf(BOLD"ERROR: Malloc Error!\n"RESET);
        return -1;
    }
    
    StringReplace = (char *)malloc(104857600 * sizeof(char));
    if (StringReplace == NULL)
    {
        free(StringReplace);
        printf(BOLD"ERROR: Malloc Error!\n"RESET);
        return -1;
    }
#endif
    
/*------------------------------------------------------------------*/
/* S T A R T S C R E E N                                            */
/*------------------------------------------------------------------*/
    
   clearNoHelp();
    
/*------------------------------------------------------------------*/
/* E R R O R M E S S A G E S                                        */
/*------------------------------------------------------------------*/
    
    if (argc == 2 && (argv[1][0] == 'h' || argv[1][0] == 'H' || argv[1][0] == '?'))
    {
        helpdesk_1();
        return 0;
    }
    
    if (argc == 1)
    {
        helpdesk_1();
        return -1;
    }
    
/* ---- USED IN FINAL VERSION ---- */

#if FINAL
    if (argc == 8)
    {
        if (argv[1][0] != 'o' || argv[3][0] != 'n' || argv[5][0] != 'f' ||
            (argv[7][0] != 'i' && argv[7][0] != 's'))
        {
            printf(BOLD"ERROR: Wrong Parameter Input!\n"RESET);
            helpdesk_1();
            return -1;
        }
    }
#endif
    
/* ---- USED IN PROTOTYPE VERSION ---- */

#if PROTOTYPE
    if (argc == 4)
    {
        if (argv[1][0] != 'f' || (argv[3][0] != 'i' && argv[3][0] != 's'))
        {
            printf(BOLD"ERROR: Wrong Parameter Input!\n"RESET);
            helpdesk_1();
            return -1;
        }
    }
    
#if DEBUG
    printf(RED"argv[1][0] %c\n"RESET, argv[1][0]);
    printf(RED"argv[3][0] %c\n"RESET, argv[3][0]);
    printf(RED"%d\n"RESET,argc);
#endif
#endif
    
/*------------------------------------------------------------------*/
/* S T A R T   O F   P R O G R A M                                  */
/*------------------------------------------------------------------*/
    
/* ---- WRITE OLD STRING, NEW STRING FROM PARAMETER INPUT ---- */
    
#if FINAL
    StringFind = argv[2];
    StringReplace = argv[4];
#endif
    
/* ---- OPENING READ FILE ---- */
    
/* ---- USED IN FINAL VERSION (FOR STRING CHANGE) ---- */
    
#if FINAL
    pFin = fopen(argv[6], "r");
    if (pFin == NULL)
    {
        printf(BOLD"ERROR: Could not open input file for reading!\n"RESET);
        return -1;
    }
#endif
    
/* ---- USED IN PROTOTYPE VERSION (FULL BUFFER CHANGE) ---- */
    
#if PROTOTYPE
    pFin = fopen(argv[2], "r");
    if (pFin == NULL)
    {
        printf(BOLD"ERROR: Could not open input file for reading!\n"RESET);
        return -1;
    }
#endif
    
    pFout = fopen("output.txt", "w+");
    if (pFout == NULL)
    {
        printf(BOLD"ERROR: Could not write output file!\n"RESET);
        return -1;
    }
    
/* ---- USED IN FINAL VERSION ---- */

#if FINAL
    if (argv[7][0] == 'i')
    {
        casesensitive = 0;
    }
    
    if (argv[7][0] == 's')
    {
        casesensitive = 1;
    }
#endif
    
/* ---- USED IN PROTOTYPE VERSION ---- */
    
#if PROTOTYPE
    if (argv[3][0] == 'i')
    {
        casesensitive = 0;
    }
    
    if (argv[3][0] == 's')
    {
        casesensitive = 1;
    }
#endif

/*------------------------------------------------------------------*/
/* W R I T I N G   F I L E   I N T O   B U F F E R                  */
/*------------------------------------------------------------------*/
    
    while (!feof(pFin))
    {
        buffer[counter] = fgetc(pFin);
        
/* ---- WRITE WITH CASE-SENSIVITE ---- */
        
        if (casesensitive == 1)
        {
            buffer[counter] = buffer[counter];
        }
        
/* ---- WRITE WITH CASE-INSENSITIVE ---- */
        
        if (casesensitive == 0)
        {
            buffer[counter] = tolower(buffer[counter]);
        }
        
        counter++;
    }
    
/* ---- REMOVING LAST CHARACTER, LOOP CHECKS 1 CHARACTER AFTER FILE ---- */
    
    buffer[strlen(buffer)-1] = '\0';
    
/* ---- CHECK EVERY WORD IN BUFFER (NOT WORKING CURRENTLY) ---- */
    
#if FINAL
    
/* ---- WRITE BUFFER INTO BUFFER2 ---- */
    
    buffer2 = buffer;
    
/* ---- CHANGES VALUES IN BUFFER ---- */

    for (j = 0; j < strlen(buffer2); j++)
    {
        if(strstr(buffer2, StringFind) != NULL)
        {
            buffer2 = StringReplace;
        }
        
/* ---- PRINTING BUFFER TO OUTPUT FILE ---- */
        
        checksum = fprintf(pFout,"%s",buffer2);
    }
 
#endif
    
/* ---- PRINTING BUFFER TO OUTPUT FILE ---- */
    
#if PROTOTYPE
    checksum = fprintf(pFout,"%s",buffer);
#endif
    
#if FINAL
    
#endif
    
/* ---- DEBUG MESSAGES ---- */
    
#if DEBUG

    while (i < strlen(buffer))
    {
        printf(RED"%3d %c\n"RESET, i, buffer[i]);
        
        i++;
    }
    
    printf(RED"Beispiel buffer: %s\n\n"RESET, buffer);
    printf(RED"Bufferadress:\t%p\n\n"RESET, buffer);
#if FINAL
    printf(RED"Beispiel buffer2: %s\n\n"RESET, buffer2);
    printf(RED"Bufferadresse:\t%p\n\n"RESET, buffer2);
#endif
#if defined(__APPLE__) && defined(__MACH__)
    printf(RED"Strlen of buffer:\t%lu\n"RESET,strlen(buffer));
    printf(RED"Sizeof of buffer:\t%lu\n\n"RESET, sizeof(buffer));
    printf(RED"Filepointer pFin:\t%p sizeof:%lu\n"RESET, pFin, sizeof(pFin));
    printf(RED"Filepointer pFout:\t%p sizeof:%lu\n"RESET, pFout, sizeof(pFout));
#endif
#if defined (__linux__) || defined(_WIN32) || defined(_WIN64)
    printf(RED"Strlen of buffer:\t%d\n"RESET,strlen(buffer));
    printf(RED"Sizeof of buffer:\t%d\n\n"RESET, sizeof(buffer));
    printf(RED"Filepointer pFin:\t%p sizeof:%d\n"RESET, pFin, sizeof(pFin));
    printf(RED"Filepointer pFout:\t%p sizeof:%d\n"RESET, pFout, sizeof(pFout));
#endif
#if FINAL
    printf(RED"StringFind:\t%s\n"RESET, StringFind);
    printf(RED"StringReplace:\t%s\n"RESET, StringReplace);
#endif
#endif
    
/* ---- USERFRIENDLY INFORMATION FOR OUTPUT ---- */
    
    helpdesk_1();
    
#if PROTOTYPE
    printf(""BOLD"OUTPUT:"RESET"\n%s\n\n", buffer);
#endif

#if FINAL
    printf(""BOLD"OUTPUT:"RESET"\n%s\n\n", buffer2);
#endif
    
/* ---- CHECK IF FPRINTF WORKED FINE ---- */
    
    if (checksum >= 1)
    {
        printf(BOLD"Output file created!\n"RESET);
    }
    else
    {
        printf(BOLD"Faild creating output file!\n"RESET);
    }

/* ---- FREE MEMORY & CLOSE FILES ---- */
    
    buffer = 0;
#if FINAL
    buffer_word = 0;
    buffer2 = 0;
    StringFind = 0;
    StringReplace = 0;
#endif
    
    fclose(pFin);
    fclose(pFout);
    free(buffer);
#if FINAL
    free(buffer2);
    free(buffer_word);
    free(StringFind);
    free(StringReplace);
#endif
    return 0;
}

/*------------------------------------------------------------------*/
/* S U B R O U T I N E   L I N E S                                  */
/*------------------------------------------------------------------*/


void helpdesk_1(void)
{
    printf("\n");
    printf(BOLD"TEXT REPLACEMENT @ v1.0\n"RESET);
    printf(BOLD"Created by Sebastian Dichler, 2016\n"RESET);
    printf("Use \"./replace.out h\" for more information\n");
    
/* ---- USED IN FINAL VERSION ---- */
    
#if FINAL
    printf("Correct format for program "BOLD"./replace.out o muhh n maehh f file.txt i"RESET".\n");
#endif
    
/* ---- USED IN PROTOTYPE VERSION ---- */

#if PROTOTYPE
    printf("Correct format for program "BOLD"./replace.out f file.txt i\n"RESET);
#endif
    
    printf("Use "BOLD"i"RESET" for \"case-insensitive\" or"
           " "BOLD"s"RESET" for \"case-sensitive\" formating\n\n");
#if DEBUG
    printf(BOLDRED"!!!! DEBUG MODE ACTIVE !!!!\n"RESET);
    printf(BOLDRED"EVERYTHING APPEARING RED IS A DEBUGMESSAGE (not with windows)\n\n"RESET);
#endif
}

void clearNoHelp(void)
{
#if defined(__APPLE__) && defined(__MACH__) || defined(__linux__)
    system("clear");
#endif
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}
