/* Public domain. */

#include "str.h"
#include "caldate.h"

unsigned int caldate_scan(const char *s,struct caldate *cd) {
  int sign = 1;
  const char *t = s;
  unsigned long z;
  unsigned long c;

  if (*t == '-') { ++t; sign = -1; }
  z = 0; while ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
  cd->year = z * sign;

  if (*t++ != '-') return 0;
  z = 0; while ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
  cd->month = z;

  if (*t++ != '-') return 0;
  z = 0; while ((c = (unsigned char) (*t - '0')) <= 9) { z = z * 10 + c; ++t; }
  cd->day = z;

  return t - s;
}

unsigned int caldate_scan_basic(const char *s,struct caldate *cd) {
  int sign = 1;
  const char *t = s;
  unsigned long z;
  unsigned long c;
  int i;

  if (*t == '-') { ++t; sign = -1; }
  z = 0; 
  i = str_len(t);
  if (i < 4) return 0;
  i -= 4;
  while (i--) {
    if ((c = (unsigned char) (*t - '0')) <= 9) {
      z = z * 10 + c; ++t;
    }
    else
      return 0;
  }
  cd->year = z * sign;

  z = 0;
  for (i = 0;i < 2;++i) {
    if ((c = (unsigned char) (*t - '0')) <= 9) {
      z = z * 10 + c; ++t;
    }
    else
      return 0;
  }
  cd->month = z;

  z = 0;
  for (i = 0;i < 2;++i) {
    if ((c = (unsigned char) (*t - '0')) <= 9) {
      z = z * 10 + c; ++t;
    }
    else
      return 0;
  }
  cd->day = z;

  return t - s;
}
