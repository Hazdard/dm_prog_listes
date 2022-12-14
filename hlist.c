#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


/* Question 1 */

typedef struct hnode_s hnode_t; 
struct hnode_s {
    int         value;
    bool        is_minf;
    bool        is_pinf;
    hnode_t*    next ;
    hnode_t*    prev ;
    hnode_t*    proj ;
};


/* Question 2 */

typedef struct hlist_s hlist_t; 
struct hlist_s {
    hnode_t*    head;
    int         height;
};


/* Question 3 */

hlist_t* hlist_new(){
    hlist_t* l = malloc(sizeof(hlist_t));
    hnode_t* minf = malloc(sizeof(hnode_t));
    hnode_t* pinf = malloc(sizeof(hnode_t));
    
    l->head=minf;
    l->height=1;

    minf->is_minf=true;
    minf->is_pinf=false;
    minf->prev=minf;     /* L'antécédent du premier élément est lui même afin d'éviter les comportements non prévus, tout comme pour le dernier élément */
    minf->next=pinf;

    pinf->is_minf=false;
    pinf->is_pinf=true;
    pinf->prev=minf;
    pinf->next=pinf;

    return l ;
}


/* Question 4 */

int hlist_free(hlist_t *l){
    hnode_t* to_free = l->head;
    int etage = 1 ;
    while(etage<=l->height){
        hnode_t* next=to_free->next ;
        free(to_free);
        if((to_free->is_pinf)&&(etage==l->height))
            free(l);
            return 1 ;
        to_free=next;
    }
    return 0 ;
}


/* Question 5 */

int hlist_search(hlist_t *l, int v, hnode_t** path){
    hnode_t* candidat = l->head ;
    int etage = 1 ;
    while(etage<=l->height){
        while(!((candidat->next)->is_pinf)&&((candidat->next)->value < v)){
            candidat=candidat->next ;
        }
        path[etage]=candidat ;
        if(etage<l->height)
            candidat=candidat->proj;
        ++etage ;
    }
    return(!(candidat->is_minf)&&(candidat->value == v));
}


/* Question 6 */

void hlist_add_layer(hlist_t *l){  /* Fonction auxiliaire qui ajoute l'étage (-inf ; +inf) par dessus la liste l */
    hnode_t* minf = malloc(sizeof(hnode_t));
    hnode_t* pinf = malloc(sizeof(hnode_t));

    pinf->is_minf=false;
    pinf->is_pinf=true;
    pinf->prev=minf;
    pinf->next=l->head;
    hnode_t* inf_search=l->head;
    while(!(inf_search->is_pinf))
        inf_search=inf_search->next ;
    pinf->proj=inf_search;

    minf->is_minf=true;
    minf->is_pinf=false;
    minf->prev=minf;
    minf->next=pinf;
    minf->proj=l->head;

    l->head=minf;
    ++l->height;
}

int hlist_add(hlist_t *l, int v){
    hnode_t** path = malloc(sizeof(hnode_t [l->height]));
    hlist_search(l,v,path);
    int etage = l->height;
    bool first = true ;
    while(first||(random()%2)){
        first=false ;
        hnode_t* new = malloc(sizeof(hnode_t)); 
        new->value=v;
        new->is_minf=false;
        new->is_pinf=false;
        if(etage>=1){
            new->prev=path[etage];
            new->next=(path[etage]->next);
            if(etage<l->height)
                new->proj=path[etage+1]->next ;
            (path[etage]->next)->prev=new;
            path[etage]->next=new;
            if(etage==1)
                hlist_add_layer(l);
            --etage;
        }
        else{
            new->prev=l->head;
            new->next=(l->head)->next;
            new->proj=(((l->head)->next)->next)->next;
            ((l->head)->next)->prev=new;
            (l->head)->next=new;
            hlist_add_layer(l);
        }
    }
    free(path);
    return 0;
}


/* Question 7 */

int hlist_remove(hlist_t *l, int v){
    hnode_t** path = malloc(sizeof(hnode_t [l->height]));
    hlist_search(l,v,path);
    int compt = 0 ;
    for(int etage = l->height; etage>=1; --etage){
        if((path[etage]->next)->value==v){
            ++compt;
            hnode_t* old=path[etage]->next;
            hnode_t* new_prev=path[etage];
            hnode_t* new_next= path[etage]->next->next;
            new_prev->next=new_next;
            new_next->prev=new_prev;
            if(etage<l->height && path[etage]->is_minf && path[etage]->next->is_pinf){ /* Si l'élément à supprimer est seul dans l'étage, par construction, on sait que les étages suivants seront identiques, donc on peut directement tout supprimer jusqu'à l'étage actuel */
                hnode_t *to_free=l->head ;
                while(to_free!=path[etage]){ /* On libère donc la mémoire occupée par la partie supérieure, puis on retourne la nouvelle liste doublement chainée */
                    hnode_t *temp=to_free->next;
                    free(to_free);
                    to_free=temp;
                }
                l->head=path[etage];
                l->height-=etage; 
                return compt>0;
            }
            free(old);
        }
        else 
            return compt>0;
    }
    return compt>0;
}


/* Question 8 */

void hlist_print(hlist_t* l){
    hnode_t* to_print = l->head ;
    int etage = 1 ;
    while(etage<=l->height){
        while(!to_print->is_pinf){
            if(to_print->is_minf)
                printf("-inf ");
            else 
                printf(" %d ",to_print->value);
            to_print=to_print->next ;
        }
        printf(" +inf\n");
        to_print=to_print->next ;
        ++etage ;
    }
}

int main(int argc, char* argv[]){
    srandom(time(NULL));
    hlist_t* l = hlist_new();
    for(int i=1; i<argc; ++i){
        hlist_add(l,atoi(argv[i]));
    }
    hlist_print(l);
    hlist_free(l);
    return 0;
}
