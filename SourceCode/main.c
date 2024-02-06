#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include "lista.h"
#include "debugmalloc.h"
#include "file_kezeles.h"
#include "jatek.h"



int main()
{
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    menu_valtozoi m_v;
    file_beolvas(&m_v.l_ranglista, m_v.l_kerdesek);
    m_v.rendezett_ranglista = rendez_ranglista(m_v.l_ranglista);
    jatekIndit(&m_v);
    ranglista_mentese_fileba(m_v.l_ranglista);
    lista_free_ranglista(m_v.l_ranglista);
    lista_free_ranglista(m_v.rendezett_ranglista);
    for(int i =1; i<=15; i++)
        lista_free_kerdesek(m_v.l_kerdesek[i]);
    return 0;
}
