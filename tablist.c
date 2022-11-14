#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/* Question 1 */

typedef struct elem_s elem_t; 
struct elem_s {
    int     x;
    int     y;
    bool    is_free;
    int     next;
    int     prev;
};


/* Question 2 */

#define MAX_CAP 100 


/* Question 3 */

typedef struct tlist_s tlist_t; 
struct tlist_s {
    elem_t  tab[MAX_CAP]; 
    int     size ; 
    int     first ; 
    int     last ; 
};


/* Question  4 */

tlist_t *tlist_new() {
    tlist_t *l = malloc(sizeof(tlist_t));
    (l->size) = 0;
    for(int i = 0; i<MAX_CAP ; i++)
        (l->tab)[i].is_free = false ;
    return l ;
}


/* Question  5 */

int tlist_free(tlist_t *l) {
    free(l);
    return sizeof(tlist_t);
}


/* Question 6 */

int tlist_size(tlist_t *l){
    return l->size ;
}


/* Question 7 */

int ind_libre(tlist_t *l){  /* Fonction auxiliaire permettant de trouver le premier indice pour une insertion dans le tableau */
    for(int i=0 ; i<MAX_CAP ; ++i){
        if ((l->tab)[i].is_free==false)
            return i ;
    }
    return 0 ;
}
int tlist_add(tlist_t* l, int a, int b) {
    if ((l->size) == MAX_CAP)
        return 1;
    else {
        if ((l->size) == 0){ /* Si la liste est vide, le point est non seulement à la queue de la liste mais aussi à la tête, ce cas est donc traité à part */
            (l->first)=0 ;
            (l->last) = 0 ;
            (l->tab)[0].x=a;
            (l->tab)[0].y=b;
            (l->tab)[0].is_free=true;
            (l->tab)[0].prev=0;
            (l->tab)[0].next=0;
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
            (l->tab)[newlast].next=0;
            ++(l->size);
        }
        
        return 0;
    }
}

/* L'entrée doit  un pointeur car sinon l'ajout ne serait pas appliqué de manière effective lors d'un appel dans une autre fonction, on a besoin de simuler un passage par référence à l'aide d'un pointeur. */


/* Question  8 */

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


/* Question 9 */

int tlist_pop(tlist_t* l){
    return(tlist_remove(l , (l->tab)[l->first].x , (l->tab)[l->first].y)) ;
}


/* Question 10 */

int tlist_top(tlist_t* l, int *x, int *y){
    if (l->size == 0)
        return 0;
    else {
        *x=(l->tab)[l->first].x ;
        *y=(l->tab)[l->first].y;
        return 1;
    }
}


/* Question 11 */

int tlist_push(tlist_t* l, int x, int y){
    if ((l->size) == MAX_CAP)
        return 1;
    else {
        if ((l->size) == 0){ /* Même remarque que pour la fonction add */
            (l->first)= 0 ;
            (l->last) = 0 ;
            (l->tab)[0].x=x;
            (l->tab)[0].y=y;
            (l->tab)[0].is_free=true;
            (l->tab)[0].prev=0;
            (l->tab)[0].next=0;
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
            (l->tab)[newfirst].prev=0;
            (l->tab)[newfirst].next=prevfirst;
            ++(l->size);
        }
        
        return 0;
    }
}


/* Question 12 */

int tlist_swap(tlist_t* l, int i, int j) { /* Fonction auxiliaire pour le tri rapide permettant de permutter les i-ème et j-ème éléments de la liste */
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


/* Question 13 */

int dist(elem_t a){
    int abs=a.x;
    int ord = a.y ;
    return (abs*abs + ord*ord);
}

elem_t acces(tlist_t *l, int i){ /* Fonction auxiliaire pour le tri rapide permettant d'acceder au i-ème élément de la liste l */
    int indi=-1;
    for(int k=(l->first),compt=0;indi==-1;k=(l->tab)[k].next,++compt){
        if (compt==i) {
            indi=k;
            }
    }
    return(l->tab[indi]);
}

void quick_sort(tlist_t *l, int first, int last) { /* tri rapide classique adapté pour le type particulier de tablist */
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


/* Question 14 */

int tlist_print(tlist_t* l){
    int compt = 0 ;
    for(int i=(l->first); compt<(l->size) ; i=(l->tab)[i].next, ++compt){
        printf("(%d,%d) ",(l->tab)[i].x,(l->tab)[i].y);
        
    }
    printf("\n");
    return compt;
}


/* Question 15 */

elem_t extract(char* str){ /* Fonction auxiliaire pour le main permettant de correctement récupérer l'entrée fournie par l'utilisateur */
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
            ord[i-(taille_abs+1)]=str[i];
        }
    }
    int x = atoi(abs);
    int y = atoi(ord);
    elem_t retour ;
    retour.x=x;
    retour.y=y;
    return retour ;

}

int main(int argc, char* argv[]) { /* Le passage en argument se fait de la façon suivante : ./tablist 3,7 9,12 21,33 */
    tlist_t* l=tlist_new();
    for(int i=1; i<argc; i++){
        elem_t retour = extract(argv[i]);
        tlist_add(l,retour.x,retour.y);
    }
    tlist_sort(l);
    tlist_print(l);
    tlist_free(l);
    return 0 ;
}
