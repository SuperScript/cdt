
default: \
it


alloc.o: \
default.o.build \
compile \
alloc.c \
alloc.h \
error.h
	sh makefile.build default.o.build alloc.o alloc

alloc_re.o: \
default.o.build \
compile \
alloc_re.c \
alloc.h \
byte.h
	sh makefile.build default.o.build alloc_re.o alloc_re

buffer.o: \
default.o.build \
compile \
buffer.c \
buffer.h
	sh makefile.build default.o.build buffer.o buffer

buffer_0.o: \
default.o.build \
compile \
buffer_0.c \
buffer.h
	sh makefile.build default.o.build buffer_0.o buffer_0

buffer_1.o: \
default.o.build \
compile \
buffer_1.c \
buffer.h
	sh makefile.build default.o.build buffer_1.o buffer_1

buffer_2.o: \
default.o.build \
compile \
buffer_2.c \
buffer.h
	sh makefile.build default.o.build buffer_2.o buffer_2

buffer_get.o: \
default.o.build \
compile \
buffer_get.c \
buffer.h \
byte.h \
error.h
	sh makefile.build default.o.build buffer_get.o buffer_get

buffer_put.o: \
default.o.build \
compile \
buffer_put.c \
buffer.h \
str.h \
byte.h \
error.h
	sh makefile.build default.o.build buffer_put.o buffer_put

buffer_read.o: \
default.o.build \
compile \
buffer_read.c \
buffer.h
	sh makefile.build default.o.build buffer_read.o buffer_read

buffer_write.o: \
default.o.build \
compile \
buffer_write.c \
buffer.h
	sh makefile.build default.o.build buffer_write.o buffer_write

byte_chr.o: \
default.o.build \
compile \
byte_chr.c \
byte.h
	sh makefile.build default.o.build byte_chr.o byte_chr

byte_copy.o: \
default.o.build \
compile \
byte_copy.c \
byte.h
	sh makefile.build default.o.build byte_copy.o byte_copy

byte_cr.o: \
default.o.build \
compile \
byte_cr.c \
byte.h
	sh makefile.build default.o.build byte_cr.o byte_cr

caldate_fmjd.o: \
default.o.build \
compile \
caldate_fmjd.c \
caldate.h
	sh makefile.build default.o.build caldate_fmjd.o caldate_fmjd

caldate_fmt.o: \
default.o.build \
compile \
caldate_fmt.c \
caldate.h
	sh makefile.build default.o.build caldate_fmt.o caldate_fmt

caldate_mjd.o: \
default.o.build \
compile \
caldate_mjd.c \
caldate.h
	sh makefile.build default.o.build caldate_mjd.o caldate_mjd

caldate_norm.o: \
default.o.build \
compile \
caldate_norm.c \
caldate.h
	sh makefile.build default.o.build caldate_norm.o caldate_norm

caldate_scan.o: \
default.o.build \
compile \
caldate_scan.c \
str.h \
caldate.h
	sh makefile.build default.o.build caldate_scan.o caldate_scan

calday: \
default.build \
calday=x \
load \
calday.o \
unix.a
	sh makefile.build default.build calday calday

calday.o: \
default.o.build \
compile \
calday.c \
exit.h \
caldate.h \
strerr.h \
subgetopt.h \
sgetopt.h \
scan.h \
buffer.h \
gen_alloc.h \
stralloc.h \
getln.h
	sh makefile.build default.o.build calday.o calday

caldaytime: \
default.build \
caldaytime=x \
load \
caldaytime.o \
unix.a
	sh makefile.build default.build caldaytime caldaytime

caldaytime.o: \
default.o.build \
compile \
caldaytime.c \
exit.h \
caldate.h \
caltime.h \
uint64.h \
tai.h \
strerr.h \
subgetopt.h \
sgetopt.h \
scan.h \
buffer.h \
gen_alloc.h \
stralloc.h \
getln.h
	sh makefile.build default.o.build caldaytime.o caldaytime

caltime_fmt.o: \
default.o.build \
compile \
caltime_fmt.c \
caldate.h \
uint64.h \
tai.h \
caltime.h
	sh makefile.build default.o.build caltime_fmt.o caltime_fmt

caltime_scan.o: \
default.o.build \
compile \
caltime_scan.c \
str.h \
caldate.h \
uint64.h \
tai.h \
caltime.h
	sh makefile.build default.o.build caltime_scan.o caltime_scan

caltime_tai.o: \
default.o.build \
compile \
caltime_tai.c \
leapsecs.h \
caldate.h \
uint64.h \
tai.h \
caltime.h
	sh makefile.build default.o.build caltime_tai.o caltime_tai

caltime_utc.o: \
default.o.build \
compile \
caltime_utc.c \
leapsecs.h \
caldate.h \
uint64.h \
tai.h \
caltime.h
	sh makefile.build default.o.build caltime_utc.o caltime_utc

choose: \
default.build \
choose=s \
makeinclude \
makescrip \
warn-auto.sh \
choose.sh
	sh makefile.build default.build choose choose

compile: \
default.build \
conf-cc \
print-compile.sh \
systype \
warn-auto.sh
	sh makefile.build default.build compile compile

error.o: \
default.o.build \
compile \
error.c \
error.h
	sh makefile.build default.o.build error.o error

error_str.o: \
default.o.build \
compile \
error_str.c \
error.h
	sh makefile.build default.o.build error_str.o error_str

getln.o: \
default.o.build \
compile \
getln.c \
byte.h \
buffer.h \
gen_alloc.h \
stralloc.h \
getln.h
	sh makefile.build default.o.build getln.o getln

getln2.o: \
default.o.build \
compile \
getln2.c \
byte.h \
buffer.h \
gen_alloc.h \
stralloc.h \
getln.h
	sh makefile.build default.o.build getln2.o getln2

home: \
home.build
	sh makefile.build home.build home 

install: \
default.build
	sh makefile.build default.build install install

it: \
default.build \
it=d \
calday \
caldaytime
	sh makefile.build default.build it it

it.command: \
default.command.build \
it \
it=d
	sh makefile.build default.command.build it.command it

it.install: \
default.install.build \
it.command \
it=d
	sh makefile.build default.install.build it.install it

it.rts: \
default.rts.build \
it.command
	sh makefile.build default.rts.build it.rts it

leapsecs_add.o: \
default.o.build \
compile \
leapsecs_add.c \
leapsecs.h \
uint64.h \
tai.h
	sh makefile.build default.o.build leapsecs_add.o leapsecs_add

leapsecs_init.o: \
default.o.build \
compile \
leapsecs_init.c \
leapsecs.h
	sh makefile.build default.o.build leapsecs_init.o leapsecs_init

leapsecs_read.o: \
default.o.build \
compile \
leapsecs_read.c \
uint64.h \
tai.h \
alloc.h \
leapsecs.h
	sh makefile.build default.o.build leapsecs_read.o leapsecs_read

leapsecs_sub.o: \
default.o.build \
compile \
leapsecs_sub.c \
leapsecs.h \
uint64.h \
tai.h
	sh makefile.build default.o.build leapsecs_sub.o leapsecs_sub

load: \
default.build \
conf-ld \
print-load.sh \
warn-auto.sh
	sh makefile.build default.build load load

makeinclude: \
default.build \
makeinclude.sh \
warn-auto.sh
	sh makefile.build default.build makeinclude makeinclude

makelib: \
default.build \
print-ar.sh \
systype \
warn-auto.sh
	sh makefile.build default.build makelib makelib

makescrip: \
default.build \
warn-auto.sh \
print-makescrip.sh \
conf-scrip \
home
	sh makefile.build default.build makescrip makescrip

mkfile: \
mkfile.build \
mkfile=d \
it
	sh makefile.build mkfile.build mkfile 

scan_sign.o: \
default.o.build \
compile \
scan_sign.c \
scan.h
	sh makefile.build default.o.build scan_sign.o scan_sign

scan_uint.o: \
default.o.build \
compile \
scan_uint.c \
scan.h
	sh makefile.build default.o.build scan_uint.o scan_uint

scan_ulong.o: \
default.o.build \
compile \
scan_ulong.c \
scan.h
	sh makefile.build default.o.build scan_ulong.o scan_ulong

sgetopt.o: \
default.o.build \
compile \
sgetopt.c \
buffer.h \
sgetopt.h \
subgetopt.h
	sh makefile.build default.o.build sgetopt.o sgetopt

str_len.o: \
default.o.build \
compile \
str_len.c \
str.h
	sh makefile.build default.o.build str_len.o str_len

stralloc_catb.o: \
default.o.build \
compile \
stralloc_catb.c \
gen_alloc.h \
stralloc.h \
byte.h
	sh makefile.build default.o.build stralloc_catb.o stralloc_catb

stralloc_eady.o: \
default.o.build \
compile \
stralloc_eady.c \
alloc.h \
gen_alloc.h \
stralloc.h \
gen_allocdefs.h
	sh makefile.build default.o.build stralloc_eady.o stralloc_eady

stralloc_opyb.o: \
default.o.build \
compile \
stralloc_opyb.c \
gen_alloc.h \
stralloc.h \
byte.h
	sh makefile.build default.o.build stralloc_opyb.o stralloc_opyb

strerr_die.o: \
default.o.build \
compile \
strerr_die.c \
buffer.h \
exit.h \
strerr.h
	sh makefile.build default.o.build strerr_die.o strerr_die

strerr_sys.o: \
default.o.build \
compile \
strerr_sys.c \
error.h \
strerr.h
	sh makefile.build default.o.build strerr_sys.o strerr_sys

subgetopt.o: \
default.o.build \
compile \
subgetopt.c \
subgetopt.h
	sh makefile.build default.o.build subgetopt.o subgetopt

systype: \
default.build \
find-systype.sh \
trycpp.c \
x86cpuid.c
	sh makefile.build default.build systype systype

tai_add.o: \
default.o.build \
compile \
tai_add.c \
uint64.h \
tai.h
	sh makefile.build default.o.build tai_add.o tai_add

tai_sub.o: \
default.o.build \
compile \
tai_sub.c \
uint64.h \
tai.h
	sh makefile.build default.o.build tai_sub.o tai_sub

tai_unpack.o: \
default.o.build \
compile \
tai_unpack.c \
uint64.h \
tai.h
	sh makefile.build default.o.build tai_unpack.o tai_unpack

uint64.h: \
uint64.h.build \
choose \
compile \
load \
tryulong64.c \
uint64.h1 \
uint64.h2
	sh makefile.build uint64.h.build uint64.h 

unix.a: \
default.a.build \
unix=l \
makelib \
alloc.o \
alloc_re.o \
buffer.o \
buffer_0.o \
buffer_1.o \
buffer_2.o \
buffer_get.o \
buffer_put.o \
buffer_read.o \
buffer_write.o \
byte_chr.o \
byte_copy.o \
byte_cr.o \
caldate_fmjd.o \
caldate_fmt.o \
caldate_mjd.o \
caldate_norm.o \
caldate_scan.o \
caltime_fmt.o \
caltime_scan.o \
caltime_tai.o \
caltime_utc.o \
error.o \
error_str.o \
getln.o \
getln2.o \
leapsecs_add.o \
leapsecs_init.o \
leapsecs_read.o \
leapsecs_sub.o \
scan_sign.o \
scan_uint.o \
scan_ulong.o \
sgetopt.o \
subgetopt.o \
str_len.o \
stralloc_eady.o \
stralloc_catb.o \
stralloc_opyb.o \
strerr_die.o \
strerr_sys.o \
tai_add.o \
tai_sub.o \
tai_unpack.o
	sh makefile.build default.a.build unix.a unix
