#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"

typedef struct adat_ranglista
{
    char nev[11];
    int pontszam;
    int ido;
}adat_ranglista;
typedef struct adat_kerdes
{
    int szint;
    char* kerdes;
    char* a;
    char* b;
    char* c;
    char* d;
    char helyes;
}adat_kerdes;
typedef struct ListaElem {
    void *adat;
    struct ListaElem *kov;
} ListaElem;

int lista_hossza(ListaElem* eleje);

void lista_free_ranglista(ListaElem *eleje) ;

void lista_free_kerdesek(ListaElem *eleje);

void lista_free_listaelem(ListaElem *eleje);

ListaElem *lista_elejere_beszur(ListaElem *eleje, void *data) ;

ListaElem *lista_vegere_beszur(ListaElem *eleje, void *data) ;

ListaElem *lista_n_elem(ListaElem* eleje, int n);

ListaElem* ranglista_keres(ListaElem* eleje, char s[]);

ListaElem* rendez_ranglista(ListaElem *l_ranglista) ;

int lista_kerdesek_keres(ListaElem* l_kerdesek,ListaElem* p);

#endif // LISTA_H_INCLUDED
