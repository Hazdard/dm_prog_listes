#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_CAP 100 

typedef struct elem_s elem_t; 
struct elem_s {
    int     x;
    int     y;
    bool    is_free;
    int     next;
    int     prev;
};

typedef struct tlist_s tlist_t; 
struct tlist_s {elem_t tab[MAX_CAP]; int size ; int first ; int last ; } ;


int tlist_print(tlist_t* l){
    int compt = 0 ;
    for(int i=(l->first); compt<(l->size) ; i=(l->tab)[i].next, ++compt){
        printf("(%d,%d) ",(l->tab)[i].x,(l->tab)[i].y);
    }
    printf("\n");
    return compt;
}

int tab_print(tlist_t* l){
    for(int i=0; i<MAX_CAP; ++i){
        if (l->tab[i].is_free)
            printf("(%d,%d,next=%d,prev=%d) ",(l->tab)[i].x,(l->tab)[i].y,(l->tab)[i].next,(l->tab)[i].prev);
        
    }
    printf("\n");
    return 0;
}

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


double dist(elem_t a){
    double x=(double)(a.x) ;
    double y=(double)(a.y) ;
    return (x*x + y*y);
}

bool est_str_avant(tlist_t *l, int i, int j){
    if (i==(l->last))
            return false;
    while (j != (l->last)){
        j=(l->tab)[j].next;
        if (j==i)
            return false;
    }
    return true ;
}

int tlist_swap(tlist_t* l, int i, int j) {
    if ((l->size >= i) && (l->size >= j)){
        int indi=-1;
        int indj=-1;
        for(int k=(l->first),compt=0 ;(indj==-1)||(indi==-1);k=(l->tab)[k].next,++compt){
            if (compt==i) {
                indi=k;
            }
            if (compt==j){
                indj=k;
            }
        } 
        printf("%d,%d\n",indi,indj);
        elem_t temp ;
        temp.x=(l->tab)[indi].x;
        temp.y=(l->tab)[indi].y;
        temp.is_free=(l->tab)[indi].is_free;
        temp.next=(l->tab)[indi].next;
        temp.prev=(l->tab)[indi].prev;

        (l->tab)[indi].x=(l->tab)[indj].x;
        (l->tab)[indi].y=(l->tab)[indj].y;
        (l->tab)[indi].is_free=(l->tab)[indj].is_free;
        (l->tab)[indi].next=(l->tab)[indj].next;
        (l->tab)[indi].prev=(l->tab)[indj].prev;

        (l->tab)[indj].x=temp.x;
        (l->tab)[indj].y=temp.y;
        (l->tab)[indj].is_free=temp.is_free;
        (l->tab)[indj].next=temp.next;
        (l->tab)[indj].prev=temp.prev;
        return 1 ;
    }
    return 0;
}


void quick_sort(tlist_t *l, int first, int last) {
    int pivot, i, j;
    pivot = first;
    i = first;
    j = last;
    while (est_str_avant(l,i,j)) {
        printf("Cas général \n");
        while(dist((l->tab)[i]) <= dist((l->tab)[pivot]) && (i!=(l->last))){
            i=(l->tab)[i].next;
            printf("Cas 1 en cours \n");
        }
        while(dist((l->tab)[j]) > dist((l->tab)[pivot])){
            j=(l->tab)[j].prev ;
            printf("Cas 2 en cours \n");
        }
        if(est_str_avant(l,i,j)) {
            tlist_swap(l,i,j);
            printf("Cas 3 en cours \n");
        }
    }
    tlist_swap(l,pivot,j);
    quick_sort(l, first, (l->tab)[j].prev);
    quick_sort(l, (l->tab)[j].next, last);
}

int tlist_sort(tlist_t* l){
    if (l->size==0)
        return 0;
    quick_sort(l,(l->first),(l->last));
    return 1;
}

int main() {
    tlist_t* l=tlist_new();
    tlist_add(l,2,3);
    tlist_add(l,0,0);
    tlist_add(l,1,2);
    tab_print(l);
    
    tlist_swap(l,2,12);
    
    tab_print(l);
    return 0 ;
}



