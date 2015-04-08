/* header file for bigdata link */
#ifndef __RAWINPUT_H_INCLUDED__
#define __RAWINPUT_H_INCLUDED__
#include "rawinput.h"
#endif

// Map structure
typedef struct Data_link Data_link;
struct Data_link {
    Rawinput* entry;
    Data_link* user_link;
    Data_link* ad_link;
    Data_link* query_link;
};

Data_link* init_bigdata_link(char* trackpath);
void init_link(Data_link* link);
void add_link(Data_link* link_head, Data_link* link);
void print_link(Data_link* link_head, int type, int start, int num);
void get(Data_link* link_head, long long int u, long long int a, int q, int p, int d);
void clicked(Data_link* link_head, long long int u);
void impressed(Data_link* link_head, long long int u1, long long int u2);
void profit(Data_link* linl_head, long long int a, double theta);
void print_entry(Rawinput* r);

