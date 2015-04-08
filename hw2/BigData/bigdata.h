/* Header file for bigdata */
#include <string>
#ifndef __RAWINPUT_H_INCLUDED__
#define __RAWINPUT_H_INCLUDED__
#include "rawinput.h"
#endif

Rawinput* init_bigdata(char* trackpath, int size);
void print_Rawinput(Rawinput entry);
void get(Rawinput* entry, int size, long long int u, long long int a, int q, int p, int d);
void clicked(Rawinput* entry, int size, long long int u);
void impressed(Rawinput* entry, int size, long long int u1, long long int u2);

