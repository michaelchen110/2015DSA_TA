#include <iostream>
#include "bigdata.h"

using namespace std;

Rawinput* init_bigdata(char* trackpath, int size) {
    FILE* trackfd = fopen(trackpath, "r");
    int i = 0;
    Rawinput* entry = new Rawinput[size];
    while(~fscanf(trackfd, "%d", &entry[i].click)) {
        fscanf(trackfd, "%d", &entry[i].impression);
        entry[i].displayURL = new char[100];
        fscanf(trackfd, "%s", entry[i].displayURL);
        fscanf(trackfd, "%lld", &entry[i].adID);
        fscanf(trackfd, "%d", &entry[i].adserID);
        fscanf(trackfd, "%d", &entry[i].depth);
        fscanf(trackfd, "%d", &entry[i].position);
        fscanf(trackfd, "%d", &entry[i].queryID);
        fscanf(trackfd, "%d", &entry[i].keywordID);
        fscanf(trackfd, "%d", &entry[i].titleID);
        fscanf(trackfd, "%d", &entry[i].description);
        fscanf(trackfd, "%lld", &entry[i].userID);
        
        i++;
    }
    return entry;
}


void get(Rawinput* entry, int size, long long int u, long long int a, int q, int p, int d) {
    Rawinput tmp;
    printf("%12s%12s\n", "Click", "Impression");
    for(int i = 0; i < size; i++) {
        tmp = entry[i];
        if(tmp.userID == u && tmp.adID == a && tmp.queryID == q && tmp.position == p && tmp.depth == d) {
            printf("%12d%12d\n", tmp.click, tmp.impression);
        }
    }
}

void clicked(Rawinput* entry, int size,long long int u) {
    Rawinput tmp;
    printf("%12s%12s\n", "AdID", "QueryID");
    for(int i = 0; i < size; i++) {
        tmp = entry[i];
        if(tmp.userID == u && tmp.click != 0) {
            printf("%12lld%12d\n", tmp.adID, tmp.queryID);
        }
    }
}


