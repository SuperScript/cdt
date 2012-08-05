/* Public domain. */

#include "str.h"
#include "caltime.h"

unsigned int caltime_scan(s,ct)
const char *s;
struct caltime *ct;
{
  const char *t = s;
  unsigned long z;
  unsigned long c;
  int sign;

  t += caldate_scan(t,&ct->date);

  while ((*t == ' ') || (*t == '\t') || (*t == 'T')) ++t;
  z = 0; while ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
  ct->hour = z;

  if (*t++ != ':') return 0;
  z = 0; while ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
  ct->minute = z;

  if (*t != ':')
    ct->second = 0;
  else {
    ++t;
    z = 0; while ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
    ct->second = z;
  }

  while ((*t == ' ') || (*t == '\t')) ++t;
  if (*t == '+') sign = 1; else if (*t == '-') sign = -1; else return 0;
  ++t;
  c = (unsigned char) (*t++ - '0'); if (c > 9) return 0; z = c;
  c = (unsigned char) (*t++ - '0'); if (c > 9) return 0; z = z * 10 + c;
  c = (unsigned char) (*t++ - '0'); if (c > 9) return 0; z = z * 6 + c;
  c = (unsigned char) (*t++ - '0'); if (c > 9) return 0; z = z * 10 + c;
  ct->offset = z * sign;

  return t - s;
}

unsigned int caltime_scan_basic(const char *s,struct caltime *ct) {
  int sign = 1;
  const char *t = s;
  unsigned long z;
  unsigned long c;
  int i;

  if (*t == '-') { ++t; sign = -1; }
  z = 0;
  i = str_len(t);
  if (i < 10) return 0;
  i -= 10;
  while (i--) {
    if ((c = (unsigned char) (*t - '0')) <= 9) {
      z = z * 10 + c; ++t;
    }
    else
      return 0;
  }
  ct->date.year = z * sign;

  z = 0;
  for (i = 0;i < 2;++i) {
    if ((c = (unsigned char) (*t - '0')) <= 9) {
      z = z * 10 + c; ++t;
    }
    else
      return 0;
  }
  ct->date.month = z;

  z = 0;
  for (i = 0;i < 2;++i) {
    if ((c = (unsigned char) (*t - '0')) <= 9) {
      z = z * 10 + c; ++t;
    }
    else
      return 0;
  }
  ct->date.day = z;

  z = 0;
  if ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
  else return 0;
  if ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
  else return 0;
  ct->hour = z;

  z = 0;
  if ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
  else return 0;
  if ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
  else return 0;
  ct->minute = z;

  z = 0;
  if ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
  else return 0;
  if ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
  else return 0;
  ct->second = z;

  ct->offset = 0;

  return t - s;
}
