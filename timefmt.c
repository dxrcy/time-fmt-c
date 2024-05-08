#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int concat_int(char *str, unsigned int len, size_t max_len,
               unsigned int value) {
    for (int i = len - 1; i >= 0; i--) {
        if (i < max_len) {
            str[i] = (value % 10) + 0x30;
        }
        value /= 10;
    }
    return len;
}

int weekday_name_abbr(char *str, const struct tm *time, size_t max_len) {
    switch (time->tm_wday) {
        case 0:
            strncat(str, "Sun", max_len);
            break;
        case 1:
            strncat(str, "Mon", max_len);
            break;
        case 2:
            strncat(str, "Tue", max_len);
            break;
        case 3:
            strncat(str, "Wed", max_len);
            break;
        case 4:
            strncat(str, "Thu", max_len);
            break;
        case 5:
            strncat(str, "Fri", max_len);
            break;
        case 6:
            strncat(str, "Sat", max_len);
            break;
        default:
            return 0;
    }
    return 3;
}
int weekday_name_full(char *str, const struct tm *time, size_t max_len) {
    switch (time->tm_wday) {
        case 0:
            strncat(str, "Sunday", max_len);
            return 6;
        case 1:
            strncat(str, "Monday", max_len);
            return 6;
        case 2:
            strncat(str, "Tuesday", max_len);
            return 7;
        case 3:
            strncat(str, "Wednesday", max_len);
            return 9;
        case 4:
            strncat(str, "Thurday", max_len);
            return 7;
        case 5:
            strncat(str, "Friday", max_len);
            return 6;
        case 6:
            strncat(str, "Saturday", max_len);
            return 8;
        default:
            return 0;
    }
}

void fmt_time(char *str, size_t max_len, const char *fmt,
              const struct tm *time) {
    bool is_specifier = false;
    char *start = str;

    while (str - start < max_len) {
        char ch = fmt++[0];
        if (ch == '\0') {
            if (is_specifier) {
                *str++ = '%';
            }
            break;
        }

        if (!is_specifier) {
            if (ch == '%') {
                is_specifier = true;
                continue;
            } else {
                *str++ = ch;
            }
        } else {
            int remaining = max_len - (str - start);
            switch (ch) {
                case 'a':
                    str += weekday_name_abbr(str, time, remaining);
                    break;
                case 'A':
                    str += weekday_name_full(str, time, remaining);
                    break;

                case 'M':
                    str += concat_int(str, 2, remaining, time->tm_min);
                    break;
                case 'H':
                    str += concat_int(str, 2, remaining, time->tm_hour);
                    break;

                // idk
                case 'U':
                    str += concat_int(str, 2, remaining,
                                      (time->tm_yday - time->tm_wday) / 7);
                    break;
                case 'w':
                    str += concat_int(str, 2, remaining, time->tm_wday);
                    break;
                case 'W':
                    str += concat_int(str, 2, remaining,
                                      (time->tm_yday - time->tm_wday) / 7);
                    break;

                default:
                    str++[0] = '%';
                    break;
            }
            is_specifier = false;
        }
    }
}
