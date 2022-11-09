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
struct tlist_s {
    elem_t  tab[MAX_CAP]; 
    int     size ; 
    int     first ; 
    int     last ; 
};


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

int tlist_size(tlist_t *l){
    int taille = 0;
    for(int i=1 ; i<MAX_CAP ; ++i)
        if((l->tab)[i].is_free)
            ++taille ;
    return taille ;
}

int ind_libre(tlist_t *l){
    for(int i=0 ; i<MAX_CAP ; ++i){
        if ((l->tab)[i].is_free==false)
            return i ;
    }
    return -42 ;
}
int tlist_add(tlist_t* l, int a, int b) {
    if ((l->size) == MAX_CAP)
        return 1;
    else {
        if ((l->size) == 0){
            (l->first)=0 ;
            (l->last) = 0 ;
            (l->tab)[0].x=a;
            (l->tab)[0].y=b;
            (l->tab)[0].is_free=true;
            (l->tab)[0].prev=-42;
            (l->tab)[0].next=-42;
            ++(l->size);
        }
        else {
            int newlast = ind_libre(l);
            int prevlast=(l->last);
            (l->tab)[prevlast].next= newlast;
            (l->last) = newlast ;
            (l->tab)[newlast].x=a;
            (l->tab)[newlast].y=b;
            (l->tab)[newlast].is_free=true;
            (l->tab)[newlast].prev=prevlast;
            (l->tab)[newlast].next=-42;
            ++(l->size);
        }
        
        return 0;
    }
}

/* l'entrée doit  un pointeur car sinon l'ajout ne serait pas appliqué de manière effective lors d'un appel dans une autre fonction, on a besoin de simuler un passage par référence à l'aide d'un pointeur. */

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
    if ((l->size) == MAX_CAP)
        return 1;
    else {
        if ((l->size) == 0){
            (l->first)= 0 ;
            (l->last) = 0 ;
            (l->tab)[0].x=x;
            (l->tab)[0].y=y;
            (l->tab)[0].is_free=true;
            (l->tab)[0].prev=-42;
            (l->tab)[0].next=-42;
            ++(l->size);
        }
        else {
            int newfirst = ind_libre(l);
            int prevfirst=(l->first);
            (l->tab)[prevfirst].prev= newfirst;
            (l->first) = newfirst ;
            (l->tab)[newfirst].x=x;
            (l->tab)[newfirst].y=y;
            (l->tab)[newfirst].is_free=true;
            (l->tab)[newfirst].prev=-42;
            (l->tab)[newfirst].next=prevfirst;
            ++(l->size);
        }
        
        return 0;
    }
}


int dist(elem_t a){
    int abs=a.x;
    int ord = a.y ;
    return (abs*abs + ord*ord);
}

elem_t acces(tlist_t *l, int i){
    int indi=-1;
    for(int k=(l->first),compt=0;indi==-1;k=(l->tab)[k].next,++compt){
        if (compt==i) {
            indi=k;
            }
    }
    return(l->tab[indi]);
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
        elem_t temp ;
        temp.x=(l->tab)[indi].x;
        temp.y=(l->tab)[indi].y;

        (l->tab)[indi].x=(l->tab)[indj].x;
        (l->tab)[indi].y=(l->tab)[indj].y;

        (l->tab)[indj].x=temp.x;
        (l->tab)[indj].y=temp.y;
        return 1 ;
    }
    return 0;
}


void quick_sort(tlist_t *l, int first, int last) {
    int pivot, i, j;
    if(first < last) {    
        pivot = first;
        i = first;
        j = last;
        while (i<j) {
            while(dist(acces(l,i)) <= dist(acces(l,pivot)) && i<(l->size))
                i++;
            while(dist(acces(l,j)) > dist(acces(l,pivot)))
                j-- ;
            if(i<j){
                tlist_swap(l,i,j);
            }
        }
        tlist_swap(l,pivot,j);
        quick_sort(l, first, j-1);
        quick_sort(l,j+1,last);
    }
}

int tlist_sort(tlist_t* l){
    if (l->size==0)
        return 0;
    quick_sort(l,0,(l->size)-1);
    return 1;
}

int tlist_print(tlist_t* l){
    int compt = 0 ;
    for(int i=(l->first); compt<(l->size) ; i=(l->tab)[i].next, ++compt){
        printf("(%d,%d) ",(l->tab)[i].x,(l->tab)[i].y);
        
    }
    printf("\n");
    return compt;
}

elem_t extract(char* str){
    int taille_abs=0 ;
    int taille_ord=0 ;
    bool avant=true;
    for(int i=0; str[i]!='\0' ;++i){
        if (str[i]==',') 
            avant=false;
        else {
            if (avant) 
                taille_abs++;
            else 
                taille_ord++;
        }
    }
    char abs[taille_abs];
    char ord[taille_ord];
    for(int i=0; str[i]!='\0'; ++i){
        if (i<taille_abs){
            abs[i]=str[i];
        }
        if (i>taille_abs){
                ord[i]=str[i];
                printf("%c\n",ord[i]);
        }
            
    }
    int x = atoi(abs);
    int y = atoi(ord);
    elem_t retour ;
    retour.x=x;
    retour.y=y;
    return retour ;

}

int main(int argc, char* argv[]) {
    tlist_t* l=tlist_new();
    for(int i=1; i<argc; i++){
        elem_t retour = extract(argv[i]);
        tlist_add(l,retour.x,retour.y);
    }
    tlist_print(l);
    return 0 ;
}


