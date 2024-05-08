#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "timefmt.c"

int main() {
    time_t t = time(NULL);
    struct tm *tp = localtime(&t);
    /* struct tm *tp = gmtime(&t); */

    const char *fmt = "(%a)(%H)(%M)";

    char s[20] = "";
    fmt_time((char *)s, 20, fmt, tp);
    printf("%s\n", s);

    char s2[20] = "";
    strftime((char *)s2, 20, fmt, tp);
    printf("%s\n", s2);

    return 0;
}
