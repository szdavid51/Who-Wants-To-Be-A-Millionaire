#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "lista.h"



int lista_hossza(ListaElem *eleje) {
    ListaElem *p = eleje;
    int n = 0;
    while (p != NULL) {
        n++;
        p = p->kov;
    }
    return n;
}

void lista_free_ranglista(ListaElem *eleje) {
    ListaElem *p1, *p2;
    p2 = eleje;
    while (p2 != NULL) {
        p1 = p2;
        p2 = p2->kov;
        free(p1->adat);
        free(p1);
    }
}
void lista_free_kerdesek(ListaElem *eleje)
{
    ListaElem *p1, *p2;
    p2 = eleje;
    while (p2 != NULL) {
        p1 = p2;
        p2 = p2->kov;
        adat_kerdes* adat = p1->adat;
        free(adat->kerdes); free(adat->a); free(adat->b); free(adat->c); free(adat->d);
        free(p1->adat);
        free(p1);
    }
}
void lista_free_listaelem(ListaElem *eleje)
{
    ListaElem *p1, *p2;
    p2 = eleje;
    while (p2 != NULL) {
        p1 = p2;
        p2 = p2->kov;
        free(p1);
    }
}
ListaElem *lista_elejere_beszur(ListaElem *eleje, void *data) {
    ListaElem *ujadat = (ListaElem*)malloc(sizeof(ListaElem));
    if(ujadat == NULL) perror("Memoria hiba");
    ujadat->kov = eleje;
    ujadat->adat = data;
    return ujadat;
}

ListaElem *lista_vegere_beszur(ListaElem *eleje, void *data) {
    if (eleje == NULL)
        return lista_elejere_beszur(eleje, data);

    ListaElem *p = eleje;
    while (p->kov != NULL)
        p = p->kov;

    ListaElem *ujadat = (ListaElem*)malloc(sizeof(ListaElem));
    if(ujadat == NULL) perror("Memoria hiba");
    ujadat->kov = NULL;
    ujadat->adat = data;
    p->kov = ujadat;

    return eleje;
}
ListaElem *lista_n_elem(ListaElem* eleje, int n)
{
    ListaElem* p = eleje;
    for(int i=1;i<n;i++)
        p = p->kov;
    return p;
}
ListaElem* ranglista_keres(ListaElem* eleje, char s[])
{
    ListaElem *p = eleje;
    if(eleje == NULL)
        return NULL;
    while(p!=NULL)
    {
        if(strcmp(((adat_ranglista*)p->adat)->nev,s)==0)
            return p;
        p=p->kov;
    }
    return NULL;
}
ListaElem* rendez_ranglista(ListaElem *l_ranglista) {
    ListaElem *rendezett_lista = NULL;
    ListaElem *jelenlegi = l_ranglista;
    ListaElem* jelenlegi_r;
    ListaElem* elozo_r;
    while (jelenlegi != NULL) {
        jelenlegi_r = rendezett_lista;
        elozo_r = NULL;
        while(jelenlegi_r!=NULL && ((adat_ranglista*)jelenlegi_r->adat)->pontszam > ((adat_ranglista*)jelenlegi->adat)->pontszam)
        {
            elozo_r = jelenlegi_r;
            jelenlegi_r = jelenlegi_r->kov;
        }
        ListaElem* ujElem = (ListaElem*)malloc(sizeof(ListaElem));
        if(ujElem == NULL) perror("Memoria hiba");
        adat_ranglista* ujAdat = (adat_ranglista*)malloc(sizeof(adat_ranglista));
        if(ujAdat == NULL) perror("Memoria hiba");
        *ujAdat = *((adat_ranglista*)jelenlegi->adat);
        ujElem->adat = ujAdat;
        ujElem->kov = jelenlegi_r;
        if(elozo_r!=NULL)
            elozo_r->kov = ujElem;
        else
            rendezett_lista = ujElem;
        jelenlegi = jelenlegi->kov;
    }
    return rendezett_lista;
}
int lista_kerdesek_keres(ListaElem* l_kerdesek,ListaElem* p)
{
    ListaElem* k = l_kerdesek;
    while(k!=NULL)
    {
        if(strcmp(((adat_kerdes*)k->adat)->kerdes, ((adat_kerdes*)p->adat)->kerdes) == 0)
            return 1;
        k=k->kov;
    }
    return 0;
}
