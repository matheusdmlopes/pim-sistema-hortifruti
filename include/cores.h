#ifndef CORES_H
#define CORES_H

#define ANSI_RESET "\x1b[0m"
#define ANSI_TEXT_RED "\x1b[31m"
#define ANSI_TEXT_GREEN "\x1b[32m"
#define ANSI_TEXT_YELLOW "\x1b[33m"
#define ANSI_TEXT_BLUE "\x1b[34m"
#define ANSI_TEXT_MAGENTA "\x1b[35m"
#define ANSI_TEXT_CYAN "\x1b[36m"

#define ANSI_BG_RED "\x1b[41m"
#define ANSI_BG_GREEN "\x1b[42m"
#define ANSI_BG_YELLOW "\x1b[43m"
#define ANSI_BG_BLUE "\x1b[44m"
#define ANSI_BG_MAGENTA "\x1b[45m"
#define ANSI_BG_CYAN "\x1b[46m"

#define ANSI_BOLD "\x1b[1m"
#define ANSI_UNDERLINE "\x1b[4m"

void setTextColor(const char* color);
void setBackgroundColor(const char* color);
void setTextStyle(const char* style);
void resetColors();

#endif // CORES_H
