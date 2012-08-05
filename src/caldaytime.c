#include "exit.h"
#include "caltime.h"
#include "tai.h"
#include "buffer.h"
#include "strerr.h"
#include "sgetopt.h"
#include "scan.h"
#include "stralloc.h"
#include "getln.h"

#define FATAL "caldaytime: fatal: "

struct stralloc date = {0};
struct stralloc line = {0};
struct caltime ct = {0};
struct caltime prect = {0};
struct caltime offct = {0};
struct caltime scanct = {0};
struct caltime incct = {0};
struct tai t = {0};
struct tai prevt = {0};
struct tai limit = {0};
int flaglimit = 0;
int flaginc = 0;
int flagfilter = 0;
int flagperiod = 0;
int flagbasic_in = 0;
int flagbasic_out = 0;
int flagy = 0;
int flagm = 0;
int flagd = 0;
int flagh = 0;
int flagu = 0;
int flags = 0;
int flagz = 0;
int match;
int weekday;
int yearday;
int o = 0;
unsigned long range = 0;
char days[] = {1,1,1,1,1,1,1};

void usage() {
  strerr_warn1("caldaytime: usage: caldaytime [ -bBfWMY -D days -y year -m month -d day -h hr -u min -s sec -z tzoffset -o caltime -w weekdays ]",0);
  _exit(100);
}

void die_nomem() {
  strerr_die2x(111,FATAL,"out of memory");
}

int fmtdaytime(char *d,struct caltime *c) {
  if (flagbasic_out)
    return caltime_fmt_basic(d,c);
  else
    return caltime_fmt_t(d,c);
}

void calrange() {
  int r;

  if (!flaginc) {
    incct.date.year = 0;
    incct.date.month = 0;
    incct.date.day = 1;
    incct.hour = 0;
    incct.minute = 0;
    incct.second = 0;
    incct.offset = 0;
  }

  ct.date.day += offct.date.day;
  ct.date.month += offct.date.month;
  ct.date.year += offct.date.year;
  ct.hour += offct.hour;
  ct.minute += offct.minute;
  ct.second += offct.second;
  ct.offset += offct.offset;
  
  caltime_tai(&ct,&t);
  if (!flaglimit) {
    caltime_utc(&scanct,&t,0,0);
    scanct.date.day += range;
    caltime_tai(&scanct,&limit);
  }

  for (;;) {
    caltime_utc(&ct,&t,&weekday,&yearday);
    if (days[weekday]) {
      r = fmtdaytime(0,&ct);
      if (!stralloc_ready(&date,r + 1)) die_nomem();
      date.len = r + 1;
      fmtdaytime(date.s,&ct);
      date.s[r] = '\n';
      if (buffer_put(buffer_1,date.s,r + 1) == -1)
	strerr_die2sys(111,FATAL,"unable to write datetime string: ");
    }
    tai_sub(&prevt,&prevt,&prevt);
    tai_add(&prevt,&prevt,&t);
    ct.date.year += incct.date.year;
    ct.date.month += incct.date.month;
    ct.date.day += incct.date.day;
    ct.hour += incct.hour;
    ct.minute += incct.minute;
    ct.second += incct.second;
    ct.offset += incct.offset;
    caltime_tai(&ct,&t);
    if (tai_equal(&t,&prevt)) break;
    if (tai_less(&prevt,&t) && !tai_less(&t,&limit)) break;
    if (tai_less(&t,&prevt) && !tai_less(&limit,&t)) break;
  }
}

void calday() {
  range = 1;
  calrange();
}

void calweek() {
  range = 7;
  offct.date.day -= weekday;
  calrange();
}

void calmonth() {
  ++ct.date.month;
  ct.date.day = 0;
  caltime_tai(&ct,&t);
  caltime_utc(&ct,&t,0,0);
  range = ct.date.day;
  ct.date.day = 1;
  calrange();
}

void calyear() {
  ct.date.month = 13;
  ct.date.day = 1;
  caltime_tai(&ct,&t);
  caltime_utc(&ct,&t,0,0);
  range = caldate_mjd(&ct.date);
  ct.date.year -= 1;
  ct.date.month = 1;
  ct.date.day = 1;
  caltime_tai(&ct,&t);
  caltime_utc(&ct,&t,0,0);
  range = range - caldate_mjd(&ct.date);
  calrange();
}

void scandaytime(const char *d,struct caltime *c) {
  int r;

  if (flagbasic_in) {
    r = caltime_scan_basic(d,c);
    if (!r || d[r])
      strerr_die3x(111,FATAL,"illegal ISO basic datetime (YYYYMMDDHHMISS): ",d);
  }
  else {
    r = caltime_scan(d,c);
    if (!r || d[r])
      strerr_die3x(111,FATAL,"illegal ISO datetime (YYYY-MM-DD HH:MI:SS +OOOO): ",d);
  }
}


int main(int argc,char * const *argv) {
  const char *dt;
  int d = 0;
  int m = 0;
  int y = 0;
  int h = 0;
  int i = 0;
  int s = 0;
  int z = 0;
  int x = 0;
  int u = 0;
  int opt;

  while ((opt = getopt(argc,argv,"bBy:m:d:h:u:s:z:WMYfo:O:i:w:D:L:")) != opteof)
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
      case 'h':
	flagh = 1;
	scan_uint(optarg + scan_plusminus(optarg,&x),&h); h *= x;
	break;
      case 'u':
	flagu = 1;
	scan_uint(optarg + scan_plusminus(optarg,&x),&i); i *= x;
	break;
      case 's':
	flags = 1;
	scan_uint(optarg + scan_plusminus(optarg,&x),&s); s *= x;
	break;
      case 'z':
	flagz = 1;
	scan_uint(optarg + scan_plusminus(optarg,&x),&z); z *= x;
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
      case 'W': flagperiod = 1; break;
      case 'M': flagperiod = 2; break;
      case 'Y': flagperiod = 3; break;
      case 'D':
	flagperiod = 4;
	scan_ulong(optarg,&range);
	flaglimit = 0;
	break;
      case 'L':
	scandaytime(optarg,&scanct);
	caltime_tai(&scanct,&limit);
	flagperiod = 4;
	flaglimit = 1;
	break;
      case 'f': flagfilter = 1; break;
      case 'o':
        scandaytime(optarg + scan_plusminus(optarg,&x),&scanct);
	prect.date.year += x * scanct.date.year;
	prect.date.month += x * scanct.date.month;
	prect.date.day += x * scanct.date.day;
	prect.hour += x * scanct.hour;
	prect.minute += x * scanct.minute;
	prect.second += x * scanct.second;
	prect.offset += x * scanct.offset;
	break;
      case 'O':
        scandaytime(optarg + scan_plusminus(optarg,&x),&scanct);
	offct.date.year += x * scanct.date.year;
	offct.date.month += x * scanct.date.month;
	offct.date.day += x * scanct.date.day;
	offct.hour += x * scanct.hour;
	offct.minute += x * scanct.minute;
	offct.second += x * scanct.second;
	break;
      case 'i':
	flaginc = 1;
	scandaytime(optarg + scan_plusminus(optarg,&x),&scanct);
	incct.date.year += x * scanct.date.year;
	incct.date.month += x * scanct.date.month;
	incct.date.day += x * scanct.date.day;
	incct.hour += x * scanct.hour;
	incct.minute += x * scanct.minute;
	incct.second += x * scanct.second;
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
      dt = line.s;
    }
    else {
      dt = *argv++;
      if (!dt) {
	if (buffer_flush(buffer_1) == -1)
	  strerr_die2sys(111,FATAL,"unable to write date string: ");
	_exit(0);
      }
    }
    scandaytime(dt,&ct);

    caltime_tai(&ct,&t);
    caltime_utc(&ct,&t,0,0);
    if (flagd) ct.date.day = d;
    if (flagm) ct.date.month = m;
    if (flagy) ct.date.year = y;
    if (flagh) ct.hour = h;
    if (flagu) ct.minute = i;
    if (flags) ct.second = s;
    if (flagz) ct.offset = z;
    ct.date.year += prect.date.year;
    ct.date.month += prect.date.month;
    ct.date.day += prect.date.day;
    ct.hour += prect.hour;
    ct.minute += prect.minute;
    ct.second += prect.second;
    ct.offset += prect.offset;
    caltime_tai(&ct,&t);
    caltime_utc(&ct,&t,&weekday,&yearday);

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
