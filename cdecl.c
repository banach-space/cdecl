//=============================================================================
// FILE:
//      cdecl.c
//
// AUTHOR:
//      zimzum@github 
//
// DESCRIPTION:
//      Implementation of all functions
//
//  License: GNU GPL v2.0 
//=============================================================================

#include "cdecl.h"

//===-----------------------------------------------------------------------===
// GLOBAL VARIABLES                                                         
//===-----------------------------------------------------------------------===
// Holds the token just read
static token_t this;

// Holds tokens we read before reaching first identifier
static token_t stack[MAXTOKENS];
static int token_id;

//===-----------------------------------------------------------------------===
// FUNCTION DEFINITIONS                                                     
//===-----------------------------------------------------------------------===
void classify_string(token_t* input)
{
    if (!strcmp(input->string, "char"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "int"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "short"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "void"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "unsigned"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "signed"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "long"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "float"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "double"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "struct"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "union"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "enum"))
    {
        input->type = TYPE;
        return;
    }
    if (!strcmp(input->string, "const")) 
    {
        input->type = QUALIFIER;
        memcpy(input->string, "read-only", 10);
        return;
    }
    if (!strcmp(input->string, "volatile")) 
    {
        input->type = QUALIFIER;
        return;
    }
    
    input->type = IDENTIFIER;
    return;
}

int gettoken(char *c)
{
    // Length of the current token
    int length = 0;
    // Number of whitespaces read
    int whitespaces_len = 0;
    // Current character
    char *current_c = c;

    // 1. Skip leading white-spaces
    while (*current_c == ' ')
    {
        whitespaces_len++;
        current_c++;
    }

    // 2. Populate the 'this' token
    if (!isalnum(*current_c) && *current_c != 0)
    {
        // It's neither type, nor qualifier nor identifier
        if (*current_c == '*')
        {
            // It's a pointer
            this.type = POINTER;
        } else
        {
            // Other language-spacific character (e.g. '(', '[')
            this.type = *current_c;
        }

        // this.string becomes the value of the token (saved as a C string)
        this.string[0] = *current_c;
        this.string[1] = 0;

        length++;
    } else
    {
        // It's either a type, qualifier or identifier. Read until whitespace or NUL.
        while (isalnum(*current_c))
        {
            current_c++;
            length++;    
        }

        // Copy the value of the token into this.strin
        memcpy(this.string, c+whitespaces_len, (size_t)length); 
        this.string[length] = '\0'; 

        // Determine this.type
        classify_string(&this);
    }

    return length+whitespaces_len;
}

char* read_to_first_identifier(char *input)
{
    int len = 0;

    while (this.type != IDENTIFIER)
    {
        len = gettoken(input);
        stack[++token_id] = this;

        input += len;
    }

    printf("Declare %s as", this.string);
    token_id--;
    len = gettoken(input);
    input += len;

    return input;
}

void deal_with_declarator(char* input)
{
    if (this.type == '[')
    {
        deal_with_arrays(input); 
    } else if (this.type == '(')
    {
        deal_with_function_args(input);
    }

    // Deal with "const", "volatile" and "*"
    deal_with_special_tokens();

    // Print everything that's left on the stack. Print it in order that
    // it was typed in (this gives more natural 'plain English').
    int temp = 1;
    while (token_id)
    {
        this = stack[temp];
        temp++;
        token_id--;
        printf(" %s", this.string);  
    }

    // We are done. 
    printf("\n");

}

char* deal_with_arrays(char *input)
{
    int len;
    int array_len = 0;
    len = gettoken(input);

    printf(" an array of length");
    if (isdigit(this.string[0]))
    {
        array_len = atoi(this.string);
        printf(" %d", array_len);
        input += len; 
        len = gettoken(input);
    } else
    {
        assert(this.string[0] == ']');
        printf("unspecified");
        len = gettoken(input);    
        input += len;
    }

    printf(" of");

    return input;

}

void deal_with_special_tokens()
{
    while (token_id && ((stack[token_id].type == POINTER || stack[token_id].type == QUALIFIER)))
    {
        this = stack[token_id];
        token_id--;

        if (this.type != POINTER)
        {
            printf(" %s", this.string);
        } else
        {
            printf(" pointer to");
        }
        continue;
    }

    return;
}

char* deal_with_function_args(char *input)
{
    int len;
    len = gettoken(input);

    while (this.type != ')')
    {
        input += len;
        len = gettoken(input);
    } 

    printf(" a function returning");
    return input;
}
