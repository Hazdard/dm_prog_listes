#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_CAP 100 

typedef struct elem_s elem_t; 
struct elem_s { int x ; int y ; bool is_free ; int next ; int prev ; } ;

typedef struct tlist_s tlist_t; 
struct tlist_s {elem_t tab[MAX_CAP]; int size ; int first ; int last ; } ;

tlist_t *tlist_new() {
    tlist_t *l = malloc(sizeof(tlist_t));
    (l->size) = 0;
    for(int i = 0; i<MAX_CAP ; i++)
        (l->tab)[i].is_free = false ;
    return l ;
}

int tlist_free(tlist_t *l) {
    free(l);
    return sizeof(tlist_t);
}

int ind_libre(tlist_t *l){
    for(int i=0 ; i<MAX_CAP ; ++i){
        if ((l->tab)[i].is_free==false)
            return i ;
    }
    return -1 ;
}

int tlist_add(tlist_t* l, int a, int b) {
    int newlast, prevlast ;
    if ((l->size) == MAX_CAP)
        return 1;
    else {
        if ((l->size) == 0){
            (l->first)=0;
            int prevlast=0 ;
            int newlast=0;
            (l->last) = newlast ;
            (l->tab)[newlast].prev=prevlast;
            (l->tab)[newlast].x=a;
            (l->tab)[newlast].y=b;
            (l->tab)[newlast].is_free=true;
            ++(l->size);
        }
        else {
            int newlast = ind_libre(l);
            int prevlast=(l->last);
            (l->tab)[prevlast].next= newlast;
            (l->last) = newlast ;
            (l->tab)[newlast].prev=prevlast;
            (l->tab)[newlast].x=a;
            (l->tab)[newlast].y=b;
            (l->tab)[newlast].is_free=true;
            ++(l->size);
        }
        
        return 0;
    }
}

/* l'entrée doit  un pointeur car sinon l'ajout ne serait pas appliqué de manière efefctive lors d'un appel dans une autre fonction, on a besoin de simuler un passage par référence à l'aide d'un pointeur. */

int tlist_remove(tlist_t *l, int x, int y){
    for(int i=0 ; i<MAX_CAP; ++i){
        if (((l->tab)[i].is_free) && ((l->tab)[i].x == x) && ((l->tab)[i].y = y)){
            --(l->size);
            (l->tab)[i].is_free=false ;
            int inext=(l->tab)[i].next ;
            int iprev =(l->tab)[i].prev ;
            (l->tab)[iprev].next = inext ;
            (l->tab)[inext].prev = iprev ;
            if (i==(l->first))
                l->first=inext ;
            if (i==(l->last))
                l->last=iprev ;
            return 1 ;
        }
    }
return 0;
}

int tlist_pop(tlist_t* l){
    return(tlist_remove(l , (l->tab)[l->first].x , (l->tab)[l->first].y)) ;
}

int tlist_top(tlist_t* l, int *x, int *y){
    if (l->size == 0)
        return 0;
    else {
        *x=(l->tab)[l->first].x ;
        *y=(l->tab)[l->first].y;
        return 1;
    }
}

int tlist_push(tlist_t* l, int x, int y){
    if (l->size == MAX_CAP)
        return 0 ;
    int *a;
    int *b;
    tlist_top(l, a, b);
    tlist_pop(l);
    tlist_add(l, x, y);
    if (l->size > 0)
        tlist_add(l, *a, *b);
    return 1;
}

int tlist_swap(tlist_t* l, int i, int j) {
    if ((l->size >= i) && (l->size >= j)){
        int indi=-1;
        int indj=-1;
        for(int k=(l->first), compt=1;(indj==-1)||(indi==-1);k=(l->tab)[k].next, ++compt){
            if (compt==i) {
                printf("%d pour i \n",k);
                indi=k;
            }
            if (compt==j){
                printf("%d pour j \n",k);
                indj=k;
            }
        } 
        printf("%d,%d\n",indi,indj);
        elem_t temp=(l->tab)[indi] ;
        (l->tab)[indi]=(l->tab)[indj];
        (l->tab)[indj]=temp;
        return 1 ;
    }
    return 0;
}

int tlist_print(tlist_t* l){
    int compt = 0 ;
    for(int i=(l->first); compt<(l->size) ; i=(l->tab)[i].next, ++compt){
        printf("(%d,%d) ",(l->tab)[i].x,(l->tab)[i].y);
    }
    printf("\n");
    return compt;
}

int main() {
    tlist_t* l=tlist_new();
    tlist_add(l,0,0);
    tlist_add(l,0,0);
    tlist_add(l,1,2);
    tlist_add(l,2,3);
    tlist_add(l,0,0);
    tlist_print(l);
    
    tlist_swap(l,3,4);
    
    tlist_print(l);
    return 0 ;
}



