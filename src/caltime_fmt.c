/* Public domain. */

#include "caldate.h"
#include "caltime.h"

unsigned int caltime_fmt(s,ct)
char *s;
struct caltime *ct;
{
  unsigned int result;
  long x;

  result = caldate_fmt(s,&ct->date);

  if (s) {
    s += result;
  
    x = ct->hour;
    s[0] = ' ';
    s[2] = '0' + (x % 10); x /= 10;
    s[1] = '0' + (x % 10);
    s += 3;
  
    x = ct->minute;
    s[0] = ':';
    s[2] = '0' + (x % 10); x /= 10;
    s[1] = '0' + (x % 10);
    s += 3;
    
    x = ct->second;
    s[0] = ':';
    s[2] = '0' + (x % 10); x /= 10;
    s[1] = '0' + (x % 10);
    s += 3;

    s[0] = ' ';
    x = ct->offset;
    if (x < 0) { s[1] = '-'; x = -x; } else s[1] = '+';

    s[5] = '0' + (x % 10); x /= 10;
    s[4] = '0' + (x % 6); x /= 6;
    s[3] = '0' + (x % 10); x /= 10;
    s[2] = '0' + (x % 10);
  }

  return result + 15;
}

unsigned int caltime_fmt_t(s,ct)
char *s;
struct caltime *ct;
{
  unsigned int result;
  long x;

  result = caldate_fmt(s,&ct->date);

  if (s) {
    s += result;
  
    x = ct->hour;
    s[0] = 'T';
    s[2] = '0' + (x % 10); x /= 10;
    s[1] = '0' + (x % 10);
    s += 3;
  
    x = ct->minute;
    s[0] = ':';
    s[2] = '0' + (x % 10); x /= 10;
    s[1] = '0' + (x % 10);
    s += 3;
    
    x = ct->second;
    s[0] = ':';
    s[2] = '0' + (x % 10); x /= 10;
    s[1] = '0' + (x % 10);
    s += 3;

    x = ct->offset;
    if (x < 0) { s[0] = '-'; x = -x; } else s[0] = '+';

    s[4] = '0' + (x % 10); x /= 10;
    s[3] = '0' + (x % 6); x /= 6;
    s[2] = '0' + (x % 10); x /= 10;
    s[1] = '0' + (x % 10);
  }

  return result + 14;
}

unsigned int caltime_fmt_basic(s,ct)
char *s;
struct caltime *ct;
{
  unsigned int result;
  long x;

  result = caldate_fmt_basic(s,&ct->date);

  if (s) {
    s += result;
  
    x = ct->hour;
    s[1] = '0' + (x % 10); x /= 10;
    s[0] = '0' + (x % 10);
    s += 2;
  
    x = ct->minute;
    s[1] = '0' + (x % 10); x /= 10;
    s[0] = '0' + (x % 10);
    s += 2;
    
    x = ct->second;
    s[1] = '0' + (x % 10); x /= 10;
    s[0] = '0' + (x % 10);
    s += 2;
  }

  return result + 6;
}
