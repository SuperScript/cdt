/* Public domain. */

#include "caldate.h"

unsigned int caldate_fmt(s,cd)
char *s;
struct caldate *cd;
{
  long x;
  int i = 0;

  x = cd->year; if (x < 0) x = -x; do { ++i; x /= 10; } while(x);

  if (s) {
    x = cd->year;
    if (x < 0) { x = -x; *s++ = '-'; }
    s += i; do { *--s = '0' + (x % 10); x /= 10; } while(x); s += i;

    x = cd->month;
    s[0] = '-'; s[2] = '0' + (x % 10); x /= 10; s[1] = '0' + (x % 10);

    x = cd->day;
    s[3] = '-'; s[5] = '0' + (x % 10); x /= 10; s[4] = '0' + (x % 10);
  }

  return (cd->year < 0) + i + 6;
}

unsigned int caldate_fmt_basic(char *s,struct caldate *cd) {
  long x;
  int i = 0;

  x = cd->year;
  if (x < 0) x = -x; do { ++i; x /= 10; } while(x);

  if (s) {
    x = cd->year;
    if (x < 0) { x = -x; *s++ = '-'; }
    s += i;
    do { *--s = '0' + (x % 10); x /= 10; } while(x); s += i;

    x = cd->month;
    s[1] = '0' + (x % 10); x /= 10; s[0] = '0' + (x % 10);

    x = cd->day;
    s[3] = '0' + (x % 10); x /= 10; s[2] = '0' + (x % 10);
  }

  return (cd->year < 0) + i + 4;
}
