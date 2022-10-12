#include "head.h"

/*
    print error to the terminal, the call should look like print_error(the line where the error occured, error format, variable to replace...)
    when first or second pass or when we finish with a file should call print_error(-1, "") so that the function reset. the function will then
    return if it gotten in this pass an error.
*/
bool print_error(int lineNum, char *ErrorFormat, ...) 
{
    static bool gottenError = false;    /* static meaning it won't change with new instance of function */
    bool tmp;
    va_list ap;
    if (lineNum < 0)          /* when a function want to reset error (meaning that it want to know if it gotten any and want to reset gottenError) it will send -1 as lineNum */
    {
        tmp = gottenError;
        gottenError = false;
        return !tmp;    /* true if we didn't got an error */
    }
    
    va_start(ap, ErrorFormat);
    vfprintf(stdout, ErrorFormat, ap);
    printf(" at line %d\n", lineNum);
    va_end(ap);
    gottenError = true;     /* we got an error */
    return gottenError;
}
