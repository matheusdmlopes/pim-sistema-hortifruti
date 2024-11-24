#include <cores.h>
#include <stdio.h>

void setTextColor(const char* color)
{
    printf("%s", color);
}

void setBackgroundColor(const char* color)
{
    printf("%s", color);
}

void resetColors()
{
    printf("%s", ANSI_RESET);
}
