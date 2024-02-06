#include <stdio.h>
#include "debugmalloc.h"
#include "lista.h"
#include "file_kezeles.h"

char* beolvas_mondat(FILE* file)
{
    char x;
    char* s = (char*)malloc(sizeof(char));
    if(s == NULL) perror("Memoria hiba");
    int slength = 0;
    while(fscanf(file,"%c",&x) == 1)
    {
        if(x != '\t' && x!= '\n')
        {
            slength++;
            s = (char*)realloc(s,(slength+1)*sizeof(char));
            if(s == NULL) perror("Memoria hiba");
            s[slength-1] = x;
            s[slength] = '\0';
        }
        else
            return s;
    }
    return s;
}
void file_beolvas(ListaElem** l_ranglista, ListaElem* l_kerdesek[])
{
    FILE *file;
    file = fopen("ranglista.txt", "r");
    if (file == NULL) {
        perror("Ranglista file hiba");
        return;
    }

    *l_ranglista = NULL;
    adat_ranglista* x= (adat_ranglista*)malloc(sizeof(adat_ranglista));
    if(x == NULL) perror("Memoria hiba");
    while(fscanf(file,"%s\t%d\t%d\n", x->nev, &x->pontszam, &x->ido)==3)
    {
         *l_ranglista=lista_vegere_beszur(*l_ranglista, x);
         x = (adat_ranglista*)malloc(sizeof(adat_ranglista));
         if(x == NULL) perror("Memoria hiba");
    }
    free(x);
    fclose(file);

    ///most beolvassuk a kerdesek.txt - t

    file = fopen("kerdesek.txt", "r");
    if (file == NULL) {
        perror("Kérdések.txt file hiba");
        return;
    }
    for(int i =1;i<=15;i++)
        l_kerdesek[i] = NULL;
    adat_kerdes *y= (adat_kerdes*)malloc(sizeof(adat_kerdes));
    if(y == NULL) perror("Memoria hiba");
    while(fscanf(file,"%d\t",&y->szint) == 1)
    {
        y->kerdes = beolvas_mondat(file);
        y->a = beolvas_mondat(file);
        y->b = beolvas_mondat(file);
        y->c = beolvas_mondat(file);
        y->d = beolvas_mondat(file);
        fscanf(file,"%c",&y->helyes);
        l_kerdesek[y->szint]=lista_vegere_beszur(l_kerdesek[y->szint], y);
        y = (adat_kerdes*)malloc(sizeof(adat_kerdes));
        if(y == NULL) perror("Memoria hiba");
    }
    free(y);
    fclose(file);
}
void ranglista_mentese_fileba(ListaElem *l_ranglista)
{
    FILE *file;
    file = fopen("ranglista.txt","w");
    if(file !=NULL)
    {
        ListaElem* p = l_ranglista;
        while(true)
        {
            adat_ranglista* adat = p->adat;
            fprintf(file, "%s\t%d\t%d\n",adat->nev,adat->pontszam, adat->ido);
            if(p->kov!=NULL)
                p=p->kov;
            else
                break;
        }
    }
    else
        perror("File mentés hiba");
}

