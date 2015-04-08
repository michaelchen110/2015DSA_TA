#include <iostream>
#include "bigdata_link.h"

using namespace std;

Data_link* init_bigdata_link(char* trackpath) {
    
    // open file
    FILE* trackfd = fopen(trackpath, "r");
    
    // init links' head
    Data_link* link_head = new Data_link;
    init_link(link_head);
    int i = 0;

    // read data
    Rawinput* entry = new Rawinput;
    Data_link* link = new Data_link;
    init_link(link);
    
    while(~fscanf(trackfd, "%d", &entry->click)) {
        
        fscanf(trackfd, "%d", &entry->impression);
        entry->displayURL = new char[100];
        fscanf(trackfd, "%s", entry->displayURL);
        fscanf(trackfd, "%lld", &entry->adID);
        fscanf(trackfd, "%d", &entry->adserID);
        fscanf(trackfd, "%d", &entry->depth);
        fscanf(trackfd, "%d", &entry->position);
        fscanf(trackfd, "%d", &entry->queryID);
        fscanf(trackfd, "%d", &entry->keywordID);
        fscanf(trackfd, "%d", &entry->titleID);
        fscanf(trackfd, "%d", &entry->description);
        fscanf(trackfd, "%lld", &entry->userID);
        link->entry = entry;
        
        // add link
        add_link(link_head, link);
        
        // new next link and entry
        entry = new Rawinput;
        link = new Data_link;
        init_link(link);
        i++;
        if(i%1000 == 0)
            printf("---%10d---\n", i);
    }
    printf("\n");

    return link_head;
}

/* important functions */

void get(Data_link* link_head, long long int u, long long int a, int q, int p, int d) {
    Data_link* cur_link = link_head->user_link;
    while(cur_link != NULL && cur_link->entry->userID <= u) {
        if(cur_link->entry->userID == u && cur_link->entry->adID == a && cur_link->entry->queryID == q && cur_link->entry->position == p && cur_link->entry->depth == d) {
            printf("%12d%12d\n", cur_link->entry->click, cur_link->entry->impression);
        }
        cur_link = cur_link->user_link;
    }
}
void clicked(Data_link* link_head, long long int u) {
    Data_link* cur_link = link_head->user_link;
    while(cur_link != NULL && cur_link->entry->userID <= u) {
        if(cur_link->entry->userID == u && cur_link->entry->click > 0) {
            printf("%lld,%d\n", cur_link->entry->adID, cur_link->entry->queryID);
        }
        cur_link = cur_link->user_link;
    }
}
void impressed(Data_link* link_head, long long int u1, long long int u2) {
    Data_link* cur_link = link_head->ad_link;
    Data_link* cur_adID_start = cur_link;
    Rawinput* r;
    long long int cur_adID = 0;
    int flag1 = 0, flag2 = 0;
    
    while(cur_link != NULL){
        
        // check change adID
        if(cur_link->entry->adID != cur_adID) {
            cur_adID = cur_link->entry->adID;
            cur_adID_start = cur_link;
            flag1 = 0;
            flag2 = 0;
        }

        //check match userID
        if(cur_link->entry->userID == u1)
            flag1 = 1;
        else if(cur_link->entry->userID == u2)
            flag2 = 1;
        
        // check flag1 & flag2
        if(flag1 == 1 && flag2 == 1) {
            // print adID
            cur_link = cur_adID_start;
            printf("%lld:\n", cur_adID);
            while(cur_link->entry->adID == cur_adID) {
                r = cur_link->entry;
                printf("  %15s%10d%10d%10d%10d\n", r->displayURL, r->adserID, r->keywordID, r->titleID, r->description);
                cur_link = cur_link->ad_link;
            }
        }
        else
            cur_link = cur_link->ad_link;
    }
}
void profit(Data_link* linl_head, long long int a, double theta) {
}

/* basic implemetations */

void init_link(Data_link* link) {
    link->user_link = NULL;
    link->ad_link = NULL;
    link->query_link = NULL;
}

void add_link(Data_link* link_head, Data_link* link) {
    Data_link* cur_link;
    Data_link* pre_link;
    int link_flag;

    // user link
    pre_link = link_head;
    cur_link = link_head->user_link;
    long long int userID = link->entry->userID;
    link_flag = 0;
    
    while(cur_link != NULL) {
        if(cur_link->entry->userID < userID) { // go next
            pre_link = cur_link;
            cur_link = cur_link->user_link;
        } else { // add
            pre_link->user_link = link;
            link->user_link = cur_link;
            cur_link = link;
            link_flag = 1;
            break;
        }
    }
    if(link_flag == 0) { // last
        pre_link->user_link = link;
    }
    
    // ad link
    pre_link = link_head;
    cur_link = link_head->ad_link;
    long long int adID = link->entry->adID;
    link_flag = 0;
    
    while(cur_link != NULL) {
        if(cur_link->entry->adID < adID) { // go next
            pre_link = cur_link;
            cur_link = cur_link->ad_link;
        } else { // add
            pre_link->ad_link = link;
            link->ad_link = cur_link;
            cur_link = link;
            link_flag = 1;
            break;
        }
    }
    if(link_flag == 0) { // last
        pre_link->ad_link = link;
    }

    // query link
    pre_link = link_head;
    cur_link = link_head->query_link;
    long long int queryID = link->entry->queryID;
    link_flag = 0;
    
    while(cur_link != NULL) {
        if(cur_link->entry->queryID < queryID) { // go next
            pre_link = cur_link;
            cur_link = cur_link->query_link;
        } else { // queryd
            pre_link->query_link = link;
            link->query_link = cur_link;
            cur_link = link;
            link_flag = 1;
            break;
        }
    }
    if(link_flag == 0) { // last
        pre_link->query_link = link;
    }
}

void print_link(Data_link* link_head, int type, int start, int num) {
    int cnt = 1;
    if(type == -1) { // user
        Data_link* cur_link = link_head->user_link;
        long long int cur_userID = 0;
        while(cur_link != NULL) {
            if(start == -1 && cur_userID != cur_link->entry->userID) {
                printf("%lld\n", cur_link->entry->userID);
                cur_userID = cur_link->entry->userID;
                cnt++;
            } else {
                if(cnt >= start) {
                    print_entry(cur_link->entry);
                }
                cnt++;
                if(cnt > num) break;
            }
            
            cur_link = cur_link->user_link;
        }
    } else if(type == -2) { // ad 
        Data_link* cur_link = link_head->user_link;
        long long int cur_adID = 0;
        while(cur_link != NULL) {
            if(start == -1 && cur_adID != cur_link->entry->adID) {
                printf("%lld\n", cur_link->entry->adID);
                cur_adID = cur_link->entry->adID;
                cnt++;
            } else {
                if(cnt >= start) {
                    print_entry(cur_link->entry);
                }
                cnt++;
                if(cnt > num) break;
            }
            cur_link = cur_link->ad_link;
        }
    } else if(type == -3) { // query
        Data_link* cur_link = link_head->query_link;
        int cur_queryID = 0;
        while(cur_link != NULL) {
            if(start == -1 && cur_queryID != cur_link->entry->queryID) {
                printf("%d\n", cur_link->entry->queryID);
                cur_queryID = cur_link->entry->queryID;
                cnt++;
            } else {
                if(cnt >= start) {
                    print_entry(cur_link->entry);
                }
                cnt++;
                if(cnt > num) break;
            }
            cur_link = cur_link->query_link;
        }
    }
    printf("Total nuber: %d\n", cnt-1);
}

void print_entry(Rawinput* r) {
        printf("C: %d ", r->click);
        printf("I: %d ", r->impression);
        printf("URL: %s ", r->displayURL);
        printf("A: %lld ", r->adID);
        printf("AS:%d ", r->adserID);
        printf("DP: %d ", r->depth);
        printf("P: %d ", r->position);
        printf("Q: %d ", r->queryID);
        printf("K: %d ", r->keywordID);
        printf("T: %d ", r->titleID);
        printf("DC: %d ", r->description);
        printf("U: %lld\n", r->userID);
}

