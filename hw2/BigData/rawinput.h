
// entry storing input
typedef struct {
    int click;
    int impression;
    char* displayURL;
    long long int adID;
    int adserID;
    int depth;
    int position;
    int queryID;
    int keywordID;
    int titleID;
    int description;
    long long int userID;
} Rawinput;

void print_rawinput(Rawinput* r);
