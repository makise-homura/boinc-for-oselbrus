#ifndef EINSTEINFIXES_H
#define EINSTEINFIXES_H
#define VPARAMS(ARGS) ARGS
#define VA_OPEN(AP, VAR) { va_list AP; va_start(AP, VAR); { struct Qdmy
#define VA_CLOSE(AP) } va_end(AP); }
#define VA_FIXEDARG(AP, T, N) struct Qdmy
#define TARGET "einsteinbinary"
#endif
