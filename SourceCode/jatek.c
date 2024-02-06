#include "lista.h"
#include "jatek.h"
#include "debugmalloc.h"
char valasz()
{
    char v;
    printf("Válaszod: ");
    scanf(" %c",&v);
    while(getchar() != '\n') //be kell olvasni az entert hogy legyen ures a stdin
        ;
    return v;
}
void print_fejlec()
{
    printf("      _                                    ____          _      \n");
    printf("     | |                                  / __ \\        (_)     \n");
    printf("     | |     ___  __ _ _   _  ___ _ __   | |  | |_ __    _ ___  \n");
    printf("     | |    / _ \\/ _` | | | |/ _ \\ '_ \\  | |  | | '_ \\  | / __| \n");
    printf("     | |___|  __/ (_| | |_| |  __/ | | | | |__| | | | | | \\__ \\ \n");
    printf("     |______\\___|\\__, |\\__, |\\___|_| |_|  \\____/|_| |_| |_|___/ \n");
    printf("                  __/ | __/ |                                   \n");
    printf("         __  __ _|___/_|___/                                    \n");
    printf("        |  \\/  (_) | (_)                                        \n");
    printf("        | \\  / |_| | |_  ___  _ __ ___   ___  ___               \n");
    printf("        | |\\/| | | | | |/ _ \\| '_ ` _ \\ / _ \\/ __|              \n");
    printf("        | |  | | | | | | (_) | | | | | | (_) \\__ \\              \n");
    printf("        |_|  |_|_|_|_|_|\\___/|_| |_| |_|\\___/|___/              \n");
    printf("                                                                \n");
    printf("                                                                \n");
}
void kiir_top_10(ListaElem *l_ranglista) {
    int szamlalo = 0;
    while (l_ranglista != NULL && szamlalo < 10) {
        adat_ranglista *jatekos = (adat_ranglista*)l_ranglista->adat;
        printf("%d. Játékos: %s, Pontszám: %d, Idő: %d\n",
               szamlalo + 1, jatekos->nev, jatekos->pontszam, jatekos->ido);
        l_ranglista = l_ranglista->kov;
        szamlalo++;
    }
}
void teendokFomenu(menu_valtozoi* m_v)
{
    printf("[1] Start\n[2] Ranglista\n[3] User\n[4] Adatok Mentése\n[5] Kilép\n\n");
    printf("Tipp: választáshoz ird be a kapcsos zárójelben lévő karaktert\n");
    m_v->v = valasz();
    switch(m_v->v)
    {
    case '1':
        m_v->menu = Start;
        break;
    case '2':
        m_v->menu = Ranglista;
        break;
    case '3':
        m_v->menu = User;
        break;
    case '4':
        m_v->menu = AdatokMentese;
        break;
    case '5':
        m_v->menu = Kilep;
    }
}
void teendokStart(menu_valtozoi* m_v)
{
    printf("Válaszd ki a nehézségi szintet 1 - től 12  - ig, hexadecimális számrendszerben(10 = A, 11 = B, 12 = C)\n");
    m_v->v = valasz();
    if(m_v->v >= '1' && m_v->v <= '9')
        m_v->szint = m_v->v - '0';
    else if(m_v->v >= 'A' && m_v->v <= 'C')
        m_v->szint = 10 + m_v->v - 'A';
    else
        return;
    // itt tudunk inicializalni változókat, melyek kellenek a játék során
    m_v->hanyadik_kerdes = 1;
    m_v->hossz = lista_hossza(m_v->l_kerdesek[m_v->szint]);
    m_v->gep_segitseget_hasznalt = false;
    m_v->kozonseg_segitseget_hasznalt = false;
    m_v->start_t = time(NULL);
    m_v->nyert = false;
    //
    m_v->menu = UjKerdes;
}
void teendokUser(menu_valtozoi *m_v)
{
    printf("Ird be a beceneved(max 10 karakter): ");
    int user_i = 0;
    bool volt_enter = false;
    while(user_i < 10)
    {
        m_v->user[user_i] = getchar();
        if(m_v->user[user_i] == '\n')
        {
            m_v->user[user_i] = '\0';
            volt_enter = true;
            break;
        }
        if((m_v->user[user_i] >= 'a' && m_v->user[user_i] <= 'z') || (m_v->user[user_i] >= 'A' && m_v->user[user_i] <= 'Z'))
            user_i++;
    }
    if(!volt_enter)
    {
        while(getchar() != '\n') // ha nem volt enter, be kell olvasni azt, hogy üres legyen a stdin
            ;
        m_v->user[user_i] = '\0';
    }
    m_v->p = ranglista_keres(m_v->l_ranglista, m_v->user);
    if(m_v->p != NULL)
    {
        m_v->pontszam = ((adat_ranglista*)m_v->p->adat)->pontszam;
        m_v->jatszott_ido = ((adat_ranglista*)m_v->p->adat)->ido;
    }
    else
    {
        m_v->pontszam = 0;
        m_v->jatszott_ido = 0;
    }
    m_v->menu = Fomenu;
}
void teendokRanglista(menu_valtozoi* m_v)
{
    kiir_top_10(m_v->rendezett_ranglista);
    printf("\n[1] Kilép\n");
    m_v->v = valasz();
    if(m_v->v == '1')
        m_v->menu = Fomenu;
}
void teendokUjKerdes(menu_valtozoi *m_v)
{
    //Itt is inicializalunk valtozokat kerdesek kozott
    m_v->valaszolt = false;
    while(true)
    {
        int random_szam = rand()%m_v->hossz + 1;
        m_v->p = lista_n_elem(m_v->l_kerdesek[m_v->szint], random_szam);
        if(lista_kerdesek_keres(m_v-> l_kerdesek_voltak, m_v->p) == 0)
            break;
    }
    adat_kerdes* ujAdat = (adat_kerdes*)m_v->p->adat;
    m_v->l_kerdesek_voltak = lista_vegere_beszur(m_v->l_kerdesek_voltak, ujAdat);
    m_v->adat = m_v->p->adat;
    for(int i =1; i<=4; i++)
        m_v->show[i] = true;

    m_v->menu = Jatek;
}
void teendokJatek(menu_valtozoi* m_v)
{
    printf("%d. %s\n\n", m_v->hanyadik_kerdes, m_v->adat->kerdes);
    if(m_v->show[1])
        printf("[a] %s", m_v->adat->a);
    printf("\t\t");
    if(m_v->show[2])
        printf("[b] %s", m_v->adat->b);
    printf("\n\n");
    if(m_v->show[3])
        printf("[c] %s", m_v->adat->c);
    printf("\t\t");
    if(m_v->show[4])
        printf("[d] %s", m_v->adat->d);
    printf("\n\n");
    if(!m_v->gep_segitseget_hasznalt)
        printf("[1] 50/50");
    if(!m_v->kozonseg_segitseget_hasznalt)
        printf("\t\t[2] Közönség segitsége");
    printf("\n\n");
    if(m_v->valaszolt)
    {
        if(m_v->helyes)
            printf("A válaszod helyes!\n");
        else
            printf("A válaszod hibás:( helyes válasz volt: %c\n", m_v->adat->helyes + 32);
        printf("[T] Tovább\n");
    }
    if(m_v->kozonseg_segitseget_megjelenit)
    {
        printf("\n\ta | ");
        for(int i = 1; i <= m_v->szazalek[1]; i++) printf("█");
        printf("\n");
        printf("\tb | ");
        for(int i = 1; i <= m_v->szazalek[2]; i++) printf("█");
        printf("\n");
        printf("\tc | ");
        for(int i = 1; i <= m_v->szazalek[3]; i++) printf("█");
        printf("\n");
        printf("\td | ");
        for(int i = 1; i <= m_v->szazalek[4]; i++) printf("█");
        printf("\n");

    }
    m_v->v = valasz();
    if((m_v->v >= 'a' && m_v->v <= 'd') && !m_v->valaszolt)
    {
        m_v->valaszolt = true;
        m_v->kozonseg_segitseget_megjelenit = false;
        if(m_v->v - 32 == m_v->adat->helyes)
            m_v->helyes = true;
        else
            m_v->helyes = false;
    }
    if(m_v->valaszolt)
    {
        if(m_v->v == 'T')
        {
            if(m_v->helyes)
            {
                if(m_v->hanyadik_kerdes == 15)
                {
                    m_v->menu = JatekVege;
                    m_v->nyert = true;
                }

                else
                {
                    m_v->hanyadik_kerdes++;
                    m_v->menu = UjKerdes;
                }
            }
            else
                m_v->menu = JatekVege;
        }

    }
    else if(m_v->v == '1' && !m_v->gep_segitseget_hasznalt)
    {
        m_v->gep_segitseget_hasznalt = true;
        int szamlalo = 0;
        while(szamlalo < 2)
        {
            int random_szam = rand() % 4;
            if(('a' + random_szam - 32 != m_v->adat->helyes) && m_v->show[random_szam + 1])
            {
                szamlalo++;
                m_v->show[random_szam + 1] = false;
            }
        }
    }
    else if(m_v->v == '2' && !m_v->kozonseg_segitseget_hasznalt)
    {
        m_v->kozonseg_segitseget_hasznalt = true;
        m_v->kozonseg_segitseget_megjelenit = true;
        for(int i = 1; i <= 4; i++)
            m_v->szazalek[i] = 0;
        int szamlalo = 0;
        while(szamlalo < 10)
        {
            int random_szam = rand() % 8 + 1;
            if(random_szam > 4)
            {
                m_v->szazalek[m_v->adat->helyes + 32 - 'a' + 1]++;
                szamlalo++;
            }
            else
            {
                if(m_v->show[random_szam])
                {
                    szamlalo++;
                    m_v->szazalek[random_szam]++;
                }
            }
        }
    }
}
void teendokJatekVege(menu_valtozoi* m_v, int prize[])
{
    lista_free_listaelem(m_v->l_kerdesek_voltak);
    m_v->l_kerdesek_voltak = NULL;
    if(!m_v->nyert)
        m_v->pontszam += prize[m_v->hanyadik_kerdes - 1];
    else
        m_v->pontszam += prize[15];
    m_v->veg_t = time(NULL);
    m_v->jatszott_ido = (int)(m_v->veg_t - m_v->start_t) / 60;
    if(!m_v->nyert)
        printf("Vesztettél a %d - dik kérdésnél; Pontszámod: %d, Játszott idő: %d perc;\n\n", m_v->hanyadik_kerdes, m_v->pontszam, m_v->jatszott_ido);
    else
        printf("Nyertél! Pontszámod: %d, Játszott idő: %d perc;\n\n", m_v->pontszam, m_v->jatszott_ido);
    printf("[T] Tovább\n");
    m_v->hanyadik_kerdes = 0;
    m_v->v = valasz();
    if(m_v->v == 'T')
        m_v->menu = Fomenu;
}
void teendokAdatokMentese(menu_valtozoi* m_v)
{
    if(m_v->user[0] != '\0')
    {
        m_v->p = ranglista_keres(m_v->l_ranglista, m_v->user);
        if(m_v->p != NULL)
        {
            ((adat_ranglista*)m_v->p->adat)->pontszam = m_v->pontszam;
            ((adat_ranglista*)m_v->p->adat)->ido = m_v->jatszott_ido;
            printf("Adatai sikeresen frissültek!\n\n");
        }
        else
        {
            adat_ranglista* ujadat = (adat_ranglista*)malloc(sizeof(adat_ranglista));
            strcpy(ujadat->nev, m_v->user);
            ujadat->pontszam = m_v->pontszam;
            ujadat->ido = m_v->jatszott_ido;
            lista_vegere_beszur(m_v->l_ranglista, ujadat);
            printf("Adatai sikeresen tárolódtak!\n\n");
        }
        lista_free_ranglista(m_v->rendezett_ranglista);
        m_v->rendezett_ranglista = rendez_ranglista(m_v->l_ranglista);
    }
    else
        printf("Először válasszon becenevet!\n\n");
    printf("[T] Tovább\n");
    m_v->v = valasz();
    if(m_v->v == 'T')
        m_v->menu = Fomenu;
}
void menuKezelo(menu_valtozoi* m_v)
{
    int prize[16] = {0,10000,20000,50000,100000,250000,500000,750000,1000000,1500000,2000000,5000000,10000000,150000000,25000000,50000000};
    while(m_v->menu != Kilep)
    {
        system("clear");
        print_fejlec();
        if(m_v->user[0] != '\0')
            printf("\tUsername: %s;\tPontszám:%d; \tJátszott idő: %d;\n", m_v->user, m_v->pontszam, m_v->jatszott_ido);
        if(m_v->hanyadik_kerdes != 0)
        {
            for(int i = 1; i <= 15; i++)
            {
                printf("\t");
                if(m_v->hanyadik_kerdes == i)
                    printf("->");
                else
                    printf("  ");
                printf(" %d | %d\n", i, prize[i]);
            }
        }
        printf("\n");
        switch (m_v->menu)
        {
            case Fomenu:
                teendokFomenu(m_v);
                break;
            case Start:
                teendokStart(m_v);
                break;
            case User:
                teendokUser(m_v);
                break;
            case Ranglista:
                teendokRanglista(m_v);
                break;
            case UjKerdes:
                teendokUjKerdes(m_v);
                break;
            case Jatek:
                teendokJatek(m_v);
                break;
            case JatekVege:
                teendokJatekVege(m_v, prize);
                break;
            case AdatokMentese:
                teendokAdatokMentese(m_v);
                break;
            case Kilep:
                break;
        }
    }
}

void jatekIndit(menu_valtozoi* m_v)
{
    m_v->menu = Fomenu;
    m_v->user[0] = '\0';
    m_v->hanyadik_kerdes = 0;
    m_v->l_kerdesek_voltak = NULL;
    m_v->pontszam = 0;
    menuKezelo(m_v);
}
