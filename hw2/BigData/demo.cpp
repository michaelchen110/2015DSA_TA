#include <iostream>
#include "bigdata.h"
#include "bigdata_link.h"
#include <string.h>

int main(int args, char** argv) {
    if(args < 2)
        printf("Wrong execution command!\n");

    /* Read input data */
    char* trackpath = argv[1];

    // Init
    Data_link* link_head = init_bigdata_link(trackpath);
    // print_link(link_head);
    char* cmd = new char[100];
    
    printf("> ");
    while(~scanf("%s", cmd)) {
        
        if(strcmp(cmd, "listuser") == 0) {
            print_link(link_head, -1, -1, -1);
        
        } else if(strcmp(cmd, "listad") == 0) {
            print_link(link_head, -2, -1, -1);
        
        } else if(strcmp(cmd, "listquery") == 0) {
            print_link(link_head, -3, -1, -1);
        
        } else if(strcmp(cmd, "user") == 0) {
            int a, b;
            scanf("%d%d", &a, &b);
            print_link(link_head, -1, a, b);
        
        } else if(strcmp(cmd, "ad") == 0) {
            int a, b;
            scanf("%d%d", &a, &b);
            print_link(link_head, -2, a, b);
        
        } else if(strcmp(cmd, "query") == 0) {
            int a, b;
            scanf("%d%d", &a, &b);
            print_link(link_head, -3, a, b);
        
        } else if(strcmp(cmd, "get") == 0) {
            long long int u,a;
            int q, p, d;
            scanf("%lld%lld%d%d%d", &u, &a, &q, &p, &d);
            get(link_head, u, a, q, p, d);
        
        } else if(strcmp(cmd, "clicked") == 0) {
            long long int u;
            scanf("%lld", &u);
            clicked(link_head, u);
        
        } else if(strcmp(cmd, "impressed") == 0) {
            long long int u1, u2;
            scanf("%lld%lld", &u1, &u2);
            impressed(link_head, u1, u2);
        
        } else if(strcmp(cmd, "profit") == 0) {
            long long int a;
            double theta;
            scanf("%lld%lf", &a, &theta);
            profit(link_head, a, theta);

        } else if(strcmp(cmd, "quit") == 0)
            break;
        
        printf("> ");
    }

    /*
    // Initialize 
    int size = 10000;
    Rawinput* entry = init_bigdata(trackpath, size);
   
    // Test get 
    Rawinput r = entry[49];
    printf("\n------------------------------------------------------------------------------------\n");
    printf("GET(%lld,%lld,%d,%d,%d)\n", r.userID, r.adID, r.queryID, r.position, r.depth);
    get(entry, size, r.userID, r.adID, r.queryID, r.position, r.depth);
    printf("------------------------------------------------------------------------------------\n\n");

    // Test Clicked 
    r = entry[1];
    printf("\n------------------------------------------------------------------------------------\n");
    printf("CLICKED(%lld)\n", r.userID);
    clicked(entry, size, r.userID);
    printf("------------------------------------------------------------------------------------\n\n");
    */

    return 0;
}
