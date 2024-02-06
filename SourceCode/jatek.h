#ifndef JATEK_H_INCLUDED
#define JATEK_H_INCLUDED
#include "lista.h"
enum Menuk
{
    Fomenu = 1,
    Start,
    User,
    Ranglista,
    Jatek,
    JatekVege,
    Kilep,
    UjKerdes,
    AdatokMentese
};
typedef struct menu_valtozoi
{
    ListaElem* l_ranglista;
    ListaElem* l_kerdesek[16];
    ListaElem* l_kerdesek_voltak;
    ListaElem* p;
    ListaElem* rendezett_ranglista;
    adat_kerdes* adat;
    char v;
    enum Menuk menu;
    char user[11];
    int hossz, szint, hanyadik_kerdes, pontszam, jatszott_ido;
    bool helyes, nyert, valaszolt, kozonseg_segitseget_hasznalt, gep_segitseget_hasznalt, kozonseg_segitseget_megjelenit, show[5];
    int szazalek[5];
    time_t start_t, veg_t;
} menu_valtozoi;
void jatekIndit(menu_valtozoi* );
#endif // JATEK_H_INCLUDE
