#include <string.h>
#include <stdio.h> 
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKENLEN (200)
#define MAXTOKENS (10)

typedef struct token { 
    char type; 
    char string[MAXTOKENLEN]; 
} token_t;

enum type_tag
{
    TYPE, 
    QUALIFIER, 
    IDENTIFIER
};

/* Look at the current token and return a value of "type" "qualifier" or "identifier"
   in this.type  */
void classify_string(void);

/* Read the next token into this.string if it is alphanumeric, classify_string
   else it must be a single character token this.type = the token itself; terminate this.string 
   with a nul.*/
int gettoken(char *);

/* Gettoken and push it onto the stack until the first identifier is read. Print "identifier is", this.string */
char * read_to_first_identifier(char *input);

// Read past closing ')' print out "function returning"
void deal_with_function_args(void);

// While you've got "[size]" print it out and read past it
char* deal_with_arrays(char *input);

// While you've got "*" on the stack print "pointer to" and pop it
void deal_with_any_pointers(void);

// if this.type is '[' deal_with_arrays
// if this.type is '(' deal_with_function_args
void deal_with_declarator(char *);
