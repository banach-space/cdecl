#include "cdecl.h"

/* Holds the token just read */
static token_t this;

/* Holds tokens we read before reaching first identifier */
static token_t stack[MAXTOKENS];
static int token_id;

/*==========================================================================*/
/* FUNCTION DEFINITIONS                                                     */
/*==========================================================================*/
void classify_string()
{
    if (!strcmp(this.string, "char") || !strcmp(this.string, "int"))
    {
        this.type = TYPE;
        //printf("[CS] {1}\n");
    } else if (!strcmp(this.string, "const") || !strcmp(this.string, "volatile"))
    {
        this.type = QUALIFIER;
        //printf("[CS] {2}\n");
    }
    else
    {
        this.type = IDENTIFIER;
        //printf("[CS] {3}\n");
    }
    
    return;
}

int gettoken( char *c)
{
    /* Length of the token */
    int length = 0;
    /* Number of whitespaces read */
    int whitespaces_len = 0;
    /* Current character */
    char *current_c = c;

    /* Skip leading white-spaces */
    while (*current_c == ' ')
    {
        whitespaces_len++;
        current_c++;
    }

    if (!isalnum(*current_c) && *current_c != 0)
    {
        this.type = *current_c;
        this.string[0] = *current_c;
        this.string[1] = 0;
        length++;
        //printf("[GT] here\n");
        //printf("[GT] current_c = %d\n", *current_c);
    } else
    {
        /* Read until whitespace or NUL*/
        while (isalnum(*current_c))
        {
            current_c++;
            length++;    
        }
        memcpy(this.string, c+whitespaces_len, (size_t)length); 
        this.string[length] = '\0'; 
    }

    /* Get token type */
    if (isalnum(this.string[0]))
        classify_string();

    //printf("[GT] Just read: %s\n", this.string);

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
        //printf("[M] len = %d\n", len);
        //printf("[M] this.type = %d\n", this.type);
    }
    printf("Declare %s as ", this.string);
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

    deal_with_any_pointers();
    while (token_id)
    {
        this = stack[token_id--];
        printf(" %s ", this.string);  
    }

    printf("\n");

}

char* deal_with_arrays(char *input)
{
    int len;
    int array_len = 0;
    len = gettoken(input);

    printf("an array of length ");
    if (isdigit(this.string[0]))
    {
        array_len = atoi(this.string);
        printf("%d", array_len);
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

void deal_with_any_pointers()
{
    if (stack[token_id].type == '*')
    {
        printf(" pointer to");
        token_id--;
    }

}
char* deal_with_function_args(char *input)
{
    
}

int main(int argc, char *argv[])
{
    assert(argc >= 2);
    char *input = argv[1];

    input = read_to_first_identifier(input);
    deal_with_declarator(input);

    return 0;
}
