#include "exit.h"
#include "caldate.h"
#include "buffer.h"
#include "strerr.h"
#include "sgetopt.h"
#include "scan.h"
#include "stralloc.h"
#include "getln.h"

#define FATAL "calday: fatal: "

struct stralloc date = {0};
struct stralloc line = {0};
struct caldate cd = {0};
struct caldate scancd = {0};
struct caldate precd = {0};
struct caldate offcd = {0};
struct caldate inccd = {0};
int flagfilter = 0;
int flagperiod = 0;
int flagbasic_in = 0;
int flagbasic_out = 0;
int flagy = 0;
int flagm = 0;
int flagd = 0;
int flagw = 0;
int flaginc = 0;
int flaglimit = 0;
int match;
int weekday;
int yearday;
long mjd;
long prevmjd;
long limit = 0;
unsigned long range = 0;
char days[] = {1,1,1,1,1,1,1};

void usage() {
  strerr_warn1("calday: usage: calday [ -bBfWMY -D days -L limit -y year -m month -d day -o caldate -O caldate -i caldate -w weekdays ]",0);
  _exit(100);
}

void die_nomem() {
  strerr_die2x(111,FATAL,"out of memory");
}

int fmtday(char *d,struct caldate *c) {
  if (flagbasic_out)
    return caldate_fmt_basic(d,c);
  else
    return caldate_fmt(d,c);
}

void calrange() {
  int r;

  if (!flaginc) {
    inccd.year = 0;
    inccd.month = 0;
    inccd.day = 1;
  }

  cd.day += offcd.day;
  cd.month += offcd.month;
  cd.year += offcd.year;
  
  mjd = caldate_mjd(&cd);
  if (!flaglimit)
    limit = mjd + range;
  for (;;) {
    caldate_frommjd(&cd,mjd,&weekday,&yearday);
    if (days[weekday]) {
      r = fmtday(0,&cd);
      if (!stralloc_ready(&date,r + 1)) die_nomem();
      date.len = r + 1;
      fmtday(date.s,&cd);
      date.s[r] = '\n';
      if (buffer_put(buffer_1,date.s,r + 1) == -1)
	strerr_die2sys(111,FATAL,"unable to write date string: ");
    }
    prevmjd = mjd;
    cd.year += inccd.year;
    cd.month += inccd.month;
    cd.day += inccd.day;
    mjd = caldate_mjd(&cd);
    if (mjd == prevmjd) break;
    if (mjd > prevmjd && mjd >= limit) break;
    if (mjd < prevmjd && mjd <= limit) break;
  }
}

void calday() {
  range = 1;
  calrange();
}

void calweek() {
  range = 7;
  offcd.day -= weekday;
  calrange();
}

void calmonth() {
  ++cd.month;
  cd.day = 0;
  caldate_normalize(&cd);
  range = cd.day;
  cd.day = 1;
  calrange();
}

void calyear() {
  cd.month = 13;
  cd.day = 1;
  range = caldate_mjd(&cd);
  cd.month = 1;
  cd.day = 1;
  range = range - caldate_mjd(&cd);
  calrange();
}

void scanday(const char *d,struct caldate *c) {
  int r;

  if (flagbasic_in) {
    r = caldate_scan_basic(d,c);
    if (!r || d[r])
      strerr_die3x(111,FATAL,"illegal ISO basic date (YYYYMMDD): ",d);
  }
  else {
    r = caldate_scan(d,c);
    if (!r || d[r])
      strerr_die3x(111,FATAL,"illegal ISO date (YYYY-MM-DD): ",d);
  }
}

int main(int argc,char * const *argv) {
  const char *day;
  int d = 0;
  int m = 0;
  int y = 0;
  int x = 0;
  int opt;
  unsigned int u;

  while ((opt = getopt(argc,argv,"bBd:m:y:w:WMYD:L:i:fo:O:")) != opteof)
    switch(opt) {
      case 'b':
	flagbasic_in = 1;
        break;
      case 'B':
	flagbasic_out = 1;
        break;
      case 'd':
	flagd = 1;
	scan_uint(optarg + scan_plusminus(optarg,&x),&d); d *= x;
	break;
      case 'm':
	flagm = 1;
	scan_uint(optarg + scan_plusminus(optarg,&x),&m); m *= x;
	break;
      case 'y':
	flagy = 1;
	scan_uint(optarg + scan_plusminus(optarg,&x),&y); y *= x;
	break;
      case 'w':
	for (u = 0;u < 7;++u) days[u] = 0;
	for (;;) {
	  if (!*optarg) break;
	  if (*optarg == ',') ++optarg;
	  optarg += scan_uint(optarg,&u);
	  if (*optarg && *optarg != ',')
	    strerr_die3x(100,FATAL,"malformed weekday list: ",optarg);
	  if (u > 6) continue;
	  days[u] = 1;
	}
	break;
      case 'W':
	flagperiod = 1;
	flaglimit = 0;
        break;
      case 'M':
	flagperiod = 2;
	flaglimit = 0;
        break;
      case 'Y':
	flagperiod = 3;
	flaglimit = 0;
        break;
      case 'D':
	flagperiod = 4;
	flaglimit = 0;
	scan_ulong(optarg,&range);
	break;
      case 'L':
	scanday(optarg,&scancd);
	limit = caldate_mjd(&scancd);
	flagperiod = 4;
	flaglimit = 1;
	break;
      case 'f': flagfilter = 1; break;
      case 'o':
	scanday(optarg,&scancd);
	precd.year += scancd.year;
	precd.month += scancd.month;
	precd.day += scancd.day;
	break;
      case 'O':
	scanday(optarg,&scancd);
	offcd.year += scancd.year;
	offcd.month += scancd.month;
	offcd.day += scancd.day;
	break;
      case 'i':
	flaginc = 1;
	scanday(optarg,&scancd);
	inccd.year += scancd.year;
	inccd.month += scancd.month;
	inccd.day += scancd.day;
	break;
      default: usage();
    }
  argc -= optind;
  argv += optind;

  for (;;) {
    if (flagfilter) {
      if (getln(buffer_0,&line,&match,'\n') == -1)
	die_nomem();
      if (!line.len) {
	if (buffer_flush(buffer_1) == -1)
	  strerr_die2sys(111,FATAL,"unable to write date string: ");
	_exit(0);
      }
      if (!match)
	strerr_die2x(111,FATAL,"incomplete line");

      line.s[line.len - 1] = 0;
      day = line.s;
    }
    else {
      day = *argv++;
      if (!day) {
	if (buffer_flush(buffer_1) == -1)
	  strerr_die2sys(111,FATAL,"unable to write date string: ");
	_exit(0);
      }
    }
    scanday(day,&cd);

    caldate_normalize(&cd);
    if (flagd) cd.day = d;
    if (flagm) cd.month = m;
    if (flagy) cd.year = y;
    cd.year += precd.year;
    cd.month += precd.month;
    cd.day += precd.day;
    caldate_frommjd(&cd,caldate_mjd(&cd),&weekday,&yearday);

    switch (flagperiod) {
      case 0:
	calday();
	break;
      case 1:
	calweek();
	break;
      case 2:
	calmonth();
	break;
      case 3:
	calyear();
	break;
      case 4:
	calrange();
	break;
      default:
	usage();
	break;
    }
  }
}
