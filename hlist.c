#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct hnode_s hnode_t; 
struct hnode_s {
    int         value;
    bool        is_minf;
    bool        is_pinf;
    hnode_t*    next ;
    hnode_t*    prev ;
};

typedef struct hlist_s hlist_t; 
struct hlist_s {
    hnode_t*    head;
    int         height;
};


