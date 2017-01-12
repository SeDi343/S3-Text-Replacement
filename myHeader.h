* !* Headerfile
 *
 * \description Headerfile for useful functions
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at><sedi343@gmail.com>
 *
 * \version Rev.: 01, 17.12.2016 - Created
 *          Rev.: 02, 17.12.2016 - Adding function clear, clearNoHelp, clearString
 *
 */

#ifndef _myHeader_
#define _myHeader_

/*------------------------------------------------------------------*/
/* I N C L U D E   L I B R A R I E S                                */
/*------------------------------------------------------------------*/

/* ---- GOOD LINKER ONLY LINKS NEEDED FUNCTIONS OF LIBRARIES ---- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

/*------------------------------------------------------------------*/
/* T E R M I N A L   A S C I I   F O R M A T I O N                  */
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

/*------------------------------------------------------------------*/
/* F U N C T I O N   D E C L A R A T I O N                          */
/*------------------------------------------------------------------*/

extern void helpdesk_1(void);
void clear(void);
void clearNoHelp(void);
unsigned int clearString(char *input);

/*------------------------------------------------------------------*/
/* F U N C T I O N   D E F I N I T I O N                            */
/*------------------------------------------------------------------*/

void clear(void)
{
#if defined(__APPLE__) && defined(__MACH__) || defined(__linux__)
    system("clear");
#endif
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
    helpdesk_1();
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

unsigned int clearString(char *input)
{
    int i;
    
    for (i = 0; i < strlen(input); i++)
    {
        if (input[i] == '\r')
        {
            input[i] = '\0';
        }
        if (input[i] == '\n')
        {
            input[i] = '\0';
        }
        if (input[i] == '\t')
        {
            input[i] = '\0';
        }
    }
    
    return 0;
}

#endif /* myHeader_h */
