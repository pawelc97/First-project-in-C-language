#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int menu()
{
    int choose;

    printf("-----Personal database------\n");
    printf("****************************\n*           MENU           *\n****************************\n");
    printf("1.Wyswietl liste wszystkich klientow\n2.Dodaj klienta\n3.Edytuj kilenta\n4.Usun klienta\n");
    printf("5.Wyswietl klientow posortowanych wedlug wybranego parametru\n6.Zapisz wybrane informacje o kliencie do pliku\n7.Zakoncz program\n");
    scanf("%d", &choose);
    printf("Wybrales opcje nr: %d\n\n", choose);
    return (choose);
}
struct clients
{
    int client_id;
    char first_name[20];
    char last_name[40];
    int age;
    char country[50];
    char town[50];
    char street[50];
    char house_number[13];
    int phone_number[15];
};
struct clients *item = NULL;

int count()//FUNKCJA ZLICZA WSZYSTKIE WIERSZE W TEKSCIE
{
    int size=233;
    char *tab;

    tab=malloc(size*sizeof(*tab));

    FILE*plik=fopen("plik0.txt", "r");

    int i=0;

    if(feof(plik)==0)
    {
        while(!feof(plik))
        {
            fgets(tab,233,plik);
            if(!feof(plik))
            {
                i++;
            }
        }
    }
    else
    {
        i=0;
    }
    fclose(plik);
    free(tab);
    return i;
}
int return_last_id()//FUNKCJA ZNAJDUJE I ZWRACA OSTATNI NUMER ID(WYKORZYSTYWANA DO NADANIA NOWEGO)
{
    int a, b, i;
    a=count();

    item = (struct clients*) malloc(a*sizeof(struct clients));

    FILE*plik;
    plik=fopen("plik0.txt", "r");

    //WCZYTYWANIE WSZYSTKICH KLIENTOW Z PLIKU DO STRUKTUR
    for(i=0;i<a;i++)
    {
        fscanf(plik, "%d %s %s %d %s %s %s %s %s", &(*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, &(*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
    }
    b=(*(item+i-1)).client_id;
    fclose(plik);
    free(plik);
    return(b);
}
void add_client()
{
    FILE*plik=fopen("plik0.txt", "a");

    int b, i;
    i=count();
    item = (struct clients*) malloc(sizeof(struct clients));

    if(i==0)
    {
        b=1001;
    }
    else
    {
        b=return_last_id();
        b++;
    }
    printf("Numer identyfikatora: %d", b);
    (*(item)).client_id=b;
    printf("\nPodaj imie: ");
    scanf(" %s", (*(item)).first_name);
    printf("\nPodaj nazwisko: ");
    scanf(" %s", (*(item)).last_name);
    printf("\nPodaj wiek: ");
    scanf(" %d", &(*(item)).age);
    printf("\nPodaj kraj: ");
    scanf(" %s", (*(item)).country);
    printf("\nPodaj miasto: ");
    scanf(" %s", (*(item)).town);
    printf("\nPodaj ulice: ");
    scanf(" %s", (*(item)).street);
    printf("\nPodaj numer domu: ");
    scanf(" %s", (*(item)).house_number);
    printf("\nPodaj numer telefonu: ");
    scanf(" %s", (*(item)).phone_number);
    fprintf(plik, "%d %s %s %d %s %s %s %s %s\n", (*(item)).client_id, (*(item)).first_name, (*(item)).last_name, (*(item)).age, (*(item)).country, (*(item)).town, (*(item)).street, (*(item)).house_number, (*(item)).phone_number);
    fclose(plik);
    free(item);
}
void view_clients()
{
    FILE*plik=fopen("plik0.txt", "r");
    int a, b, i, j=0;
    a=count();

    item = (struct clients*) malloc(a*sizeof(struct clients));

    //WCZYTYWANIE WSZYSTKICH KLIENTOW Z PLIKU DO STRUKTUR
    for(i=0;i<a;i++)
    {
        fscanf(plik, "%d %s %s %d %s %s %s %s %s", &(*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, &(*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
    }
    fclose(plik);
    printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
    printf("\n");
    while(j<a)
    {
        printf("Id_Klienta: %d| Imie: %s| Nazwisko: %s| Wiek: %d| Kraj: %s| Miasto: %s| Ulica: %s| Nr domu: %s| Telefon: %s|", (*(item+j)).client_id, (*(item+j)).first_name, (*(item+j)).last_name, (*(item+j)).age, (*(item+j)).country, (*(item+j)).town, (*(item+j)).street, (*(item+j)).house_number, (*(item+j)).phone_number);
        printf("\n");
        printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
        printf("\n");
        j++;
    }
    free(item);
}
void edit(int t)
{
    int a, b, i, j, k;
    int c=count();

    item = (struct clients*) malloc(c*sizeof(struct clients));

    FILE*plik;
    plik=fopen("plik0.txt", "r");

    //WCZYTYWANIE WSZYSTKICH KLIENTOW Z PLIKU DO STRUKTUR
    for(k=0;k<c;k++)
    {
        fscanf(plik, "%d %s %s %d %s %s %s %s %s", &(*(item+k)).client_id, (*(item+k)).first_name, (*(item+k)).last_name, &(*(item+k)).age, (*(item+k)).country, (*(item+k)).town, (*(item+k)).street, (*(item+k)).house_number, (*(item+k)).phone_number);
    }
    fclose(plik);
    //WYSZUKIWANIE KLIENTA PO NUMERZE ID
    for(i=0; i<count(); i++)
    {
        if((*(item+i)).client_id==t)
        {
            printf("Klient ktorego chcesz edytowac:\n");
            printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
            printf("\n");
            printf("Id_Klienta: %d| Imie: %s| Nazwisko: %s| Wiek: %d| Kraj: %s| Miasto: %s| Ulica: %s| Nr domu: %s| Telefon: %s|", (*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, (*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
            printf("\n");
            printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
            printf("\n");
            printf("\n\n");
            break;
        }
    }
    do
    {
        printf("Wybierz parametr ktory chcesz edytowac:\n1.Imie\n2.Nazwisko\n3.Wiek\n4.Kraj\n5.Miasto\n6.Ulica");
        printf("\n7.Nr doum\n8.Telefon\n9.Zapisz zmiany i/lub wroc do glownego menu\n");
        scanf("%d", &a);
        switch(a)
        {
            case 1:
            printf("\nPodaj nowe imie: ");
            scanf(" %s", (*(item+i)).first_name);
            break;

            case 2:
            printf("\nPodaj nowe nazwisko: ");
            scanf(" %s", (*(item+i)).last_name);
            break;

            case 3:
            printf("\nPodaj nowy wiek: ");
            scanf(" %d", &(*(item+i)).age);
            break;

            case 4:
            printf("\nPodaj nowa nazwe kraju: ");
            scanf(" %s", (*(item+i)).country);
            break;

            case 5:
            printf("\nPodaj nowa nazwe miasta: ");
            scanf(" %s", (*(item+i)).town);
            break;

            case 6:
            printf("\nPodaj nowa nazwe ulicy: ");
            scanf(" %s", (*(item+i)).street);
            break;

            case 7:
            printf("\nPodaj nowy nr domu: ");
            scanf(" %s", (*(item+i)).house_number);
            break;

            case 8:
            printf("\nPodaj nowy numer telefonu: ");
            scanf(" %s", (*(item+i)).phone_number);
            break;

            case 9:
            a=10;
            break;
        }

    }while((a!=10));

    FILE*plik1;
    plik1=fopen("plik0.txt", "w");

    for(j=0; j<c; j++)
    {
        fprintf(plik1, "%d %s %s %d %s %s %s %s %s\n", (*(item+j)).client_id, (*(item+j)).first_name, (*(item+j)).last_name, (*(item+j)).age, (*(item+j)).country, (*(item+j)).town, (*(item+j)).street, (*(item+j)).house_number, (*(item+j)).phone_number);
    }
    fclose(plik1);
    free(item);
}
void delete_n()
{
    int a, b, i, j, k, l, t;
    a=count();

    do
    {
        printf("Wybierz co chcesz usunac:\n1.Pojedynczy rekord\n2.Wszystkie rekordy\n3.Wroc do glownego menu\n");
        scanf(" %d", &b);

        if(b==1)
        {
            item = (struct clients*) malloc(a*sizeof(struct clients));

            FILE*plik;
            plik=fopen("plik0.txt", "r");

            //WCZYTYWANIE WSZYSTKICH KLIENTOW Z PLIKU DO STRUKTUR
            for(i=0;i<a;i++)
            {
            fscanf(plik, "%d %s %s %d %s %s %s %s %s", &(*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, &(*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
            }
            fclose(plik);
            //WYSZUKIWANIE KLIENTA w STRUKTURZE PO NUMERZE ID
            printf("Podaj numer id klienta ktorego chczesz usunac: \n");
            scanf(" %d", &t);
            for(j=0; j<a; j++)
            {
                if((*(item+j)).client_id==t)
                {
                    printf("Klient ktorego chcesz usunac:\n");
                    printf("Id_Klienta: %d| Imie: %s| Nazwisko: %s| Wiek: %d| Kraj: %s| Miasto: %s| Ulica: %s| Nr domu: %s| Telefon: %s|", (*(item+j)).client_id, (*(item+j)).first_name, (*(item+j)).last_name, (*(item+j)).age, (*(item+j)).country, (*(item+j)).town, (*(item+j)).street, (*(item+j)).house_number, (*(item+j)).phone_number);
                    printf("\n\n");
                    break;
                }
            }
            //ZAPIS KLIENTÓW Z STRUKTURY DO PLIKU Z POMINIECIEM KLIENTA WYBRANEGO DO USUNIECIA
            FILE*plik1;
            plik1=fopen("plik0.txt", "w");

            for(k=0;k<j;k++)
            {
                fprintf(plik1, "%d %s %s %d %s %s %s %s %s\n", (*(item+k)).client_id, (*(item+k)).first_name, (*(item+k)).last_name, (*(item+k)).age, (*(item+k)).country, (*(item+k)).town, (*(item+k)).street, (*(item+k)).house_number, (*(item+k)).phone_number);
            }

            l=j+1;

            while(l<a)
            {
                fprintf(plik1, "%d %s %s %d %s %s %s %s %s\n", (*(item+l)).client_id, (*(item+l)).first_name, (*(item+l)).last_name, (*(item+l)).age, (*(item+l)).country, (*(item+l)).town, (*(item+l)).street, (*(item+l)).house_number, (*(item+l)).phone_number);
                l++;
            }
            printf("Usuwanie pojedynczego rekordu przebieglo pomyslnie!\n");
            fclose(plik1);
            break;
        }
        //NADPISANIE ISTNIEJACEGO PLIKU
        if(b==2)
        {
            FILE*plik2;
            plik2=fopen("plik0.txt", "w");
            printf("Usuwanie wszystkich rekordow przebieglo pomyslnie!\n");
            fclose(plik2);
            break;
        }
        if(b==3)
        {
            break;
        }
        if((b!=1)||(b!=2)||(b!=3))
        {
            printf("Wybrales zla opcje. Wybierz jeszcze raz\n");
        }
    }while((b!=1)||(b!=2)||(b!=3));
    free(item);
}
void sort()
{
    int i;
    do
    {
        printf("Wybierz parametr wedlug ktorego chcesz posortowac:\n1.Imie\n2.Nazwisko\n3.Wiek\n4.Kraj\n5.Miasto\n6.Ulica\n7.Powrot do menu\n");
        scanf("%d", &i);

        switch(i)
        {
            case 1:
            sort_by_first_name(0);
            break;

            case 2:
            sort_by_last_name(0);
            break;

            case 3:
            sort_by_age(0);
            break;

            case 4:
            sort_by_country(0);
            break;

            case 5:
            sort_by_town(0);
            break;

            case 6:
            sort_by_street(0);
            break;
        }
    }while(i!=7);
}
void sort_by_first_name(int q)
{
    int a, b, i, j, k, m;
    a=count();

    item = (struct clients*) malloc(a*sizeof(struct clients));

    FILE*plik;
    plik=fopen("plik0.txt", "r");

    //WCZYTYWANIE WSZYSTKICH KLIENTOW Z PLIKU DO STRUKTUR
    for(i=0;i<a;i++)
    {
        fscanf(plik, "%d %s %s %d %s %s %s %s %s", &(*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, &(*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
    }
    fclose(plik);

    char *tf;
    tf=(char*)malloc(a*sizeof(*tf));
    char temp[20];
    char tempf;

    for(i=0;i<count(); i++)
    {
        tf[i]=i;
    }
    //SORTOWANIE WG IMIENIA
    for(j=0; j<a-1; j++)
    {
        for(k=j; k<a; k++)
        {
            if(strncmp(item[k].first_name, item[j].first_name, 20)<0)
            {
                strcpy(temp, (*(item+k)).first_name);
                tempf=tf[k];
                strcpy((*(item+k)).first_name, (*(item+j)).first_name);
                tf[k]=tf[j];
                strcpy((*(item+j)).first_name, temp);
                tf[j]=tempf;
            }
        }
    }
    if(q!=1)
    {
        printf("Sortowanie alfabetyczne wg imienia:\n");
        printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
        printf("\n");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            printf("Id_Klienta: %d| Imie: %s| Nazwisko: %s| Wiek: %d| Kraj: %s| Miasto: %s| Ulica: %s| Nr domu: %s| Telefon: %s|", (*(item+m)).client_id, (*(item+i)).first_name, (*(item+m)).last_name, (*(item+m)).age, (*(item+m)).country, (*(item+m)).town, (*(item+m)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
            printf("\n");
            printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
            printf("\n");
        }
        printf("\n\n");
    }
    if(q==1)
    {
        FILE*plik1=fopen("wyeksportowany.txt", "w");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            fprintf(plik1, "%d %s %s %d %s %s %s %s %s\n", (*(item+m)).client_id, (*(item+i)).first_name, (*(item+m)).last_name, (*(item+m)).age, (*(item+m)).country, (*(item+m)).town, (*(item+m)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
        }
        printf("Wyeksportowanie przebieglo pomyslnie!\n\n");
        fclose(plik1);
    }

    free(tf);
    free(item);
}
void sort_by_last_name(int q)
{
    int a, b, i, j, k, m;
    a=count();

    item = (struct clients*) malloc(a*sizeof(struct clients));

    FILE*plik;
    plik=fopen("plik0.txt", "r");

    //WCZYTYWANIE WSZYSTKICH KLIENTOW Z PLIKU DO STRUKTUR
    for(i=0;i<a;i++)
    {
        fscanf(plik, "%d %s %s %d %s %s %s %s %s", &(*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, &(*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
    }
    fclose(plik);

    char *tf;
    tf=(char*)malloc(a*sizeof(*tf));
    char temp[40];
    char tempf;

    for(i=0;i<count(); i++)
    {
        tf[i]=i;
    }
    //SORTOWANIE WG NAZWISKA
    for(j=0; j<a-1; j++)
    {
        for(k=j; k<a; k++)
        {
            if(strncmp(item[k].last_name, item[j].last_name, 40)<0)
            {
                strcpy(temp, (*(item+k)).last_name);
                tempf=tf[k];
                strcpy((*(item+k)).last_name, (*(item+j)).last_name);
                tf[k]=tf[j];
                strcpy((*(item+j)).last_name, temp);
                tf[j]=tempf;
            }
        }
    }
    if(q!=1)
    {
        printf("Sortowanie alfabetyczne wg nazwiska:\n");
        printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
        printf("\n");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            printf("Id_Klienta: %d| Imie: %s| Nazwisko: %s| Wiek: %d| Kraj: %s| Miasto: %s| Ulica: %s| Nr domu: %s| Telefon: %s|", (*(item+m)).client_id, (*(item+m)).first_name, (*(item+i)).last_name, (*(item+m)).age, (*(item+m)).country, (*(item+m)).town, (*(item+m)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
            printf("\n");
            printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
            printf("\n");
        }
        printf("\n\n");
    }
    if(q==1)
    {
        FILE*plik1=fopen("wyeksportowany.txt", "w");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            fprintf(plik1, "%d %s %s %d %s %s %s %s %s\n", (*(item+m)).client_id, (*(item+m)).first_name, (*(item+i)).last_name, (*(item+m)).age, (*(item+m)).country, (*(item+m)).town, (*(item+m)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
        }
        printf("Wyeksportowanie przebieglo pomyslnie!\n\n");
        fclose(plik1);
    }
    free(tf);
    free(item);
}
void sort_by_age(int q)
{
    int a, b, i, j, k, m;
    a=count();

    item = (struct clients*) malloc(a*sizeof(struct clients));

    FILE*plik;
    plik=fopen("plik0.txt", "r");

    //WCZYTYWANIE WSZYSTKICH KLIENTOW Z PLIKU DO STRUKTUR
    for(i=0;i<a;i++)
    {
        fscanf(plik, "%d %s %s %d %s %s %s %s %s", &(*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, &(*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
    }
    fclose(plik);

    char *tf;
    tf=(char*)malloc(a*sizeof(*tf));
    char temp;
    char tempf;

    for(i=0;i<count(); i++)
    {
        tf[i]=i;
    }
    //SORTOWANIE WG WIEKU
    for(j=0; j<a-1; j++)
    {
        for(k=j; k<a; k++)
        {
            if(item[k].age<item[j].age)
            {
                temp=(*(item+k)).age;
                tempf=tf[k];
                (*(item+k)).age=(*(item+j)).age;
                tf[k]=tf[j];
                (*(item+j)).age=temp;
                tf[j]=tempf;
            }
        }

    }
    if(q!=1)
    {
        printf("Sortowanie wg wieku rosnaco:\n");
        printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
        printf("\n");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            printf("Id_Klienta: %d| Imie: %s| Nazwisko: %s| Wiek: %d| Kraj: %s| Miasto: %s| Ulica: %s| Nr domu: %s| Telefon: %s|", (*(item+m)).client_id, (*(item+m)).first_name, (*(item+m)).last_name, (*(item+i)).age, (*(item+m)).country, (*(item+m)).town, (*(item+m)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
            printf("\n");
            printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
            printf("\n");
        }
        printf("\n\n");
    }
    if(q==1)
    {
        FILE*plik1=fopen("wyeksportowany.txt", "w");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            fprintf(plik1, "%d %s %s %d %s %s %s %s %s\n", (*(item+m)).client_id, (*(item+m)).first_name, (*(item+m)).last_name, (*(item+i)).age, (*(item+m)).country, (*(item+m)).town, (*(item+m)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
        }
        printf("Wyeksportowanie przebieglo pomyslnie!\n\n");
        fclose(plik1);
    }
    free(tf);
    free(item);
}
void sort_by_country(int q)
{
    int a, b, i, j, k, m;
    a=count();

    item = (struct clients*) malloc(a*sizeof(struct clients));

    FILE*plik;
    plik=fopen("plik0.txt", "r");

    //WCZYTYWANIE WSZYSTKICH KLIENTOW Z PLIKU DO STRUKTUR
    for(i=0;i<a;i++)
    {
        fscanf(plik, "%d %s %s %d %s %s %s %s %s", &(*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, &(*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
    }
    fclose(plik);

    char *tf;
    tf=(char*)malloc(a*sizeof(*tf));
    char temp[50];
    char tempf;

    for(i=0;i<count(); i++)
    {
        tf[i]=i;
    }
    //SORTOWANIE WG KRAJU
    for(j=0; j<a-1; j++)
    {
        for(k=j; k<a; k++)
        {
            if(strncmp(item[k].country, item[j].country, 50)<0)
            {
                strcpy(temp, (*(item+k)).country);
                tempf=tf[k];
                strcpy((*(item+k)).country, (*(item+j)).country);
                tf[k]=tf[j];
                strcpy((*(item+j)).country, temp);
                tf[j]=tempf;
            }
        }
    }
    if(q!=1)
    {
        printf("Sortowanie alfabetyczne wg kraju:\n");
        printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
        printf("\n");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            printf("Id_Klienta: %d| Imie: %s| Nazwisko: %s| Wiek: %d| Kraj: %s| Miasto: %s| Ulica: %s| Nr domu: %s| Telefon: %s|", (*(item+m)).client_id, (*(item+m)).first_name, (*(item+m)).last_name, (*(item+m)).age, (*(item+i)).country, (*(item+m)).town, (*(item+m)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
            printf("\n");
            printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
            printf("\n");
        }
        printf("\n\n");
    }
    if(q==1)
    {
        FILE*plik1=fopen("wyeksportowany.txt", "w");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            fprintf(plik1, "%d %s %s %d %s %s %s %s %s\n", (*(item+m)).client_id, (*(item+m)).first_name, (*(item+m)).last_name, (*(item+i)).age, (*(item+m)).country, (*(item+m)).town, (*(item+m)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
        }
        printf("Wyeksportowanie przebieglo pomyslnie!\n\n");
        fclose(plik1);
    }
    free(tf);
    free(item);
} void sort_by_town(int q)
{
    int a, b, i, j, k, m;
    a=count();

    item = (struct clients*) malloc(a*sizeof(struct clients));

    FILE*plik;
    plik=fopen("plik0.txt", "r");

    //WCZYTYWANIE WSZYSTKICH KLIENTOW Z PLIKU DO STRUKTUR
    for(i=0;i<a;i++)
    {
        fscanf(plik, "%d %s %s %d %s %s %s %s %s", &(*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, &(*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
    }
    fclose(plik);

    char *tf;
    tf=(char*)malloc(a*sizeof(*tf));
    char temp[50];
    char tempf;

    for(i=0;i<count(); i++)
    {
        tf[i]=i;
    }
    //SORTOWANIE WG MIASTA
    for(j=0; j<a-1; j++)
    {
        for(k=j; k<a; k++)
        {
            if(strncmp(item[k].town, item[j].town, 50)<0)
            {
                strcpy(temp, (*(item+k)).town);
                tempf=tf[k];
                strcpy((*(item+k)).town, (*(item+j)).town);
                tf[k]=tf[j];
                strcpy((*(item+j)).town, temp);
                tf[j]=tempf;
            }
        }
    }
    if(q!=1)
    {
        printf("Sortowanie alfabetyczne wg miasta:\n");
        printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
        printf("\n");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            printf("Id_Klienta: %d| Imie: %s| Nazwisko: %s| Wiek: %d| Kraj: %s| Miasto: %s| Ulica: %s| Nr domu: %s| Telefon: %s|", (*(item+m)).client_id, (*(item+m)).first_name, (*(item+m)).last_name, (*(item+m)).age, (*(item+m)).country, (*(item+i)).town, (*(item+m)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
            printf("\n");
            printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
            printf("\n");
        }
        printf("\n\n");
    }
    if(q==1)
    {
        FILE*plik1=fopen("wyeksportowany.txt", "w");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            fprintf(plik1, "%d %s %s %d %s %s %s %s %s\n", (*(item+m)).client_id, (*(item+m)).first_name, (*(item+m)).last_name, (*(item+m)).age, (*(item+m)).country, (*(item+i)).town, (*(item+m)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
        }
        printf("Wyeksportowanie przebieglo pomyslnie!\n\n");
        fclose(plik1);
    }
    free(tf);
    free(item);
}

void sort_by_street(int q)
{
    int a, b, i, j, k, m;
    a=count();

    item = (struct clients*) malloc(a*sizeof(struct clients));

    FILE*plik;
    plik=fopen("plik0.txt", "r");

    //WCZYTYWANIE WSZYSTKICH KLIENTOW Z PLIKU DO STRUKTUR
    for(i=0;i<a;i++)
    {
        fscanf(plik, "%d %s %s %d %s %s %s %s %s", &(*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, &(*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
    }
    fclose(plik);

    char *tf;
    tf=(char*)malloc(a*sizeof(*tf));
    char temp[50];
    char tempf;

    for(i=0;i<count(); i++)
    {
        tf[i]=i;
    }
    //SORTOWANIE WG ULICY
    for(j=0; j<a-1; j++)
    {
        for(k=j; k<a; k++)
        {
            if(strncmp(item[k].street, item[j].street, 50)<0)
            {
                strcpy(temp, (*(item+k)).street);
                tempf=tf[k];
                strcpy((*(item+k)).street, (*(item+j)).street);
                tf[k]=tf[j];
                strcpy((*(item+j)).street, temp);
                tf[j]=tempf;
            }
        }
    }
    if(q!=1)
    {
        printf("Sortowanie alfabetyczne wg ulicy:\n");
        printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
        printf("\n");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            printf("Id_Klienta: %d| Imie: %s| Nazwisko: %s| Wiek: %d| Kraj: %s| Miasto: %s| Ulica: %s| Nr domu: %s| Telefon: %s|", (*(item+m)).client_id, (*(item+m)).first_name, (*(item+m)).last_name, (*(item+m)).age, (*(item+m)).country, (*(item+m)).town, (*(item+i)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
            printf("\n");
            printf("__________________________________________________________________________________________________________________________________________________________________________________________________________________");
            printf("\n");
        }
        printf("\n\n");
    }
    if(q==1)
    {
        FILE*plik1=fopen("wyeksportowany.txt", "w");
        for(i=0;i<a;i++)
        {
            m=tf[i];
            fprintf(plik1, "%d %s %s %d %s %s %s %s %s\n", (*(item+m)).client_id, (*(item+m)).first_name, (*(item+m)).last_name, (*(item+m)).age, (*(item+m)).country, (*(item+m)).town, (*(item+i)).street, (*(item+m)).house_number, (*(item+m)).phone_number);
        }
        printf("Wyeksportowanie przebieglo pomyslnie!\n\n");
        fclose(plik1);
    }
    free(tf);
    free(item);
}
void export_data_to_file()
{
    int a, b, c, i, j, k, m, t;
    a=count();

    do
    {
        printf("1.Wyeksportuj dane jednego klienta do odrebnego pliku\n2.Wyeksportuj dane wszystkich klientow posortowane wg wybranego parametru\n");
        printf("3.Wroc do glownego menu\n");
        scanf(" %d", &c);

        if(c==1)
        {
            item = (struct clients*) malloc(a*sizeof(struct clients));

            FILE*plik;
            plik=fopen("plik0.txt", "r");
            FILE*plik1;
            plik1=fopen("wyeksportowany.txt", "w");

            //WCZYTYWANIE WSZYSTKICH KLIENTOW Z PLIKU DO STRUKTUR
            for(i=0;i<a;i++)
            {
                fscanf(plik, "%d %s %s %d %s %s %s %s %s", &(*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, &(*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
            }
            fclose(plik);

            printf("Podaj id klienta: \n");
            scanf(" %d", &t);
            for(i=0; i<a; i++)
            {
                if((*(item+i)).client_id==t)
                {
                    fprintf(plik1, "%d %s %s %d %s %s %s %s %s\n", (*(item+i)).client_id, (*(item+i)).first_name, (*(item+i)).last_name, (*(item+i)).age, (*(item+i)).country, (*(item+i)).town, (*(item+i)).street, (*(item+i)).house_number, (*(item+i)).phone_number);
                    printf("Wyeksportowanie przebieglo pomyslnie!\n\n");
                    break;
                }
            }
            fclose(plik1);
            free(item);
        }
        if(c==2)
        {
            printf("Wybierz sposob posortowania danych w  wyeksportowanym pliku\n");
            printf("1.Imie\n2.Nazwisko\n3.Wiek\n4.Kraj\n5.Miasto\n6.Ulica\n7.Powrot do menu\n");
            scanf(" %d", &b);

            switch(b)
            {
                case 1:
                sort_by_first_name(1);
                break;

                case 2:
                sort_by_last_name(1);
                break;

                case 3:
                sort_by_age(1);
                break;

                case 4:
                sort_by_country(1);
                break;

                case 5:
                sort_by_town(1);
                break;

                case 6:
                sort_by_street(1);
                break;
            }
        }
        if(c==3)
        {
            break;
        }
    }while((c!=1)||(c!=2)||(c!=3));
}
int main()
{
    int choose, i, j;
    do
    {
        choose=menu();
        switch(choose)
        {
            case 1:
            view_clients();
            break;

            case 2:
            add_client();
            break;

            case 3:;
            printf("Podaj numer id klienta: ");
            scanf(" %d", &i);
            edit(i);
            break;

            case 4:
            delete_n();
            break;

            case 5:
            sort();
            break;

            case 6:
            export_data_to_file();
            break;

            case 7:
            printf("\nNacisniecie DOWOLNEGO klawisza spowoduje zakonczenie programu");
            break;

            case 8:
            j=count();
            printf("Wartosc count = %d\n\n", j);
            break;

            case 9:
            j=return_last_id();
            printf("Ostatni numer id: %d\n\n", j);
            break;
        }
    }while(choose!=7);

    return 0;
}
