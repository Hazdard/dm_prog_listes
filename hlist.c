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

hlist_t* hlist_new(){
    hlist_t* l = malloc(sizeof(hlist_t));
    hnode_t* minf = malloc(sizeof(hnode_t));
    hnode_t* pinf = malloc(sizeof(hnode_t));
    l->head=minf;
    l->height=1;

    minf->is_minf=true;
    minf->is_pinf=false;
    minf->prev=minf;
    minf->next=pinf;

    pinf->is_minf=false;
    pinf->is_pinf=true;
    pinf->prev=minf;
    pinf->next=pinf;

    return l ;
}

void hlist_free(hlist_t *l){
    hnode_t* n = l->head;
    int etage = 1 ;
    while((etage<l->height)||!(n->is_pinf)){
        hnode_t* next_n=n->next;
        free(n);
        n=next_n;
    }
}

/* Penser a remettre les crochets de path */

int hlist_search(hlist_t *l, int v, hnode_t** path){
    hnode_t* candidat = l->head ;
    int etage = 1 ;
    while(etage<=l->height){
        while(!((candidat->next)->is_pinf)&&((candidat->next)->value <= v)){
            candidat=candidat->next ;
        }
        path[etage]=candidat ;
        ++etage ;
        while(!(candidat->is_minf)){
            candidat=candidat->next ;
        }
    }
    return(!(candidat->is_minf)&&(candidat->value == v));
}

int hlist_add(hlist_t *l, int v){
    
}

int main(){
    hlist_t* l = hlist_new();
    int v = 42 ;
    hnode_t** path = malloc(sizeof(hnode_t* [l->height]));
    printf("Résultat de la recherche : %d\n",hlist_search(l,v,path));
    hlist_free(l);
    return 0;
}
