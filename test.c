#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CMAX 10

int solde, choix, x;
typedef struct SClient
{
    int Code_cli;
    char Nom[CMAX];
    char Prenom[CMAX];
} SClient;

int comparer(const void *a, const void *b)
{
    const SClient *c1 = a;
    const SClient *c2 = b;
    return strcmp(c1->Nom, c2->Nom);
}

typedef struct Date
{
    int Jour;
    int Mois;
    int Annee;
} Date;

typedef struct SCompte
{
    int code_cpt;
    int Code_cli;
    int somme;
    struct Date d_compte;
} SCompte;

SClient clients[20];
SCompte comptes[20];

void menu();
void sous_menu(int a);
void gerer_client(int a);
void gerer_compte(int a);
void gerer_operation(int a);

void saveClientsToFile() {
    FILE *file = fopen("client.txt", "w");
    for (int i = 0; i < 20; i++) {
        if (clients[i].Code_cli != 0) {
            fprintf(file, "%d %s %s\n", clients[i].Code_cli, clients[i].Nom, clients[i].Prenom);
        }
    }
    fclose(file);
}

void loadClientsFromFile() {
    FILE *file = fopen("client.txt", "r");
    int i = 0;
    while (fscanf(file, "%d %s %s", &clients[i].Code_cli, clients[i].Nom, clients[i].Prenom) != EOF) {
        i++;
    }
    fclose(file);
}

void saveComptesToFile() {
    FILE *file = fopen("compte.txt", "w");
    for (int i = 0; i < 20; i++) {
        if (comptes[i].code_cpt != 0) {
            fprintf(file, "%d %d %d %d %d %d\n", comptes[i].code_cpt, comptes[i].Code_cli, comptes[i].somme, comptes[i].d_compte.Jour, comptes[i].d_compte.Mois, comptes[i].d_compte.Annee);
        }
    }
    fclose(file);
}

void loadComptesFromFile() {
    FILE *file = fopen("compte.txt", "r");
    int i = 0;
    while (fscanf(file, "%d %d %d %d %d %d", &comptes[i].code_cpt, &comptes[i].Code_cli, &comptes[i].somme, &comptes[i].d_compte.Jour, &comptes[i].d_compte.Mois, &comptes[i].d_compte.Annee) != EOF) {
        i++;
    }
    fclose(file);
}

void menu()
{
    printf("1- Gestion des clients\n");
    printf("2- Gestion des comptes\n");
    printf("3- Gestion des operations\n");
    printf("4- Quitter le programme\n");
    printf("Choisir le menu : ");
    scanf("%d", &choix);
    sous_menu(choix);
}

void sous_menu(int a)
{
    if (a == 1)
    {
        printf("1- Ajouter\n");
        printf("2- Modifier\n");
        printf("3- Supprimer\n");
        printf("4- Afficher\n");
        printf("5- Retour\n");
        printf("Choisir un sous menu : ");
        scanf("%d", &x);
        gerer_client(x);
    }
    else if (a == 2)
    {
        printf("1- Ajouter\n");
        printf("2- Rechercher\n");
        printf("3- Afficher la liste\n");
        printf("4- Supprimer\n");
        printf("5- Retour\n");
        printf("Choisir un sous menu : ");
        scanf("%d", &x);
        gerer_compte(x);
    }
    else if (a == 3)
    {
        printf("1- Retrait d'argent\n");
        printf("2- Versement d'argent\n");
        printf("Choisir un sous menu : ");
        scanf("%d", &x);
        gerer_operation(x);
    }
    else if (a == 4)
        exit(0);
    else
    {
        printf("mauvais choix");
        exit(0);
    }
}

void gerer_client(int a)
{
    loadClientsFromFile();
    if (a == 1)
    {
        SClient client;

        printf("Code Client : ");
        scanf("%d", &client.Code_cli);
        printf("Nom : ");
        scanf("%s", client.Nom);
        printf("Prenom : ");
        scanf("%s", client.Prenom);

        clients[client.Code_cli - 1] = client;
        saveClientsToFile();

        printf("client ajouté avec succès");
    }
    else if (a == 2)
    {
        int code;
        SClient nvClient;

        printf("Code Client a modifier : ");
        scanf("%d", &nvClient.Code_cli);
        printf("Nouveau nom : ");
        scanf("%s", nvClient.Nom);
        printf("Nouveau prenom : ");
        scanf("%s", nvClient.Prenom);

        clients[nvClient.Code_cli - 1] = nvClient;
        saveClientsToFile();

        printf("Client modifié avec succès");
    }
    else if (a == 3)
    {
        int code;

        printf("Code Client a supprimer : ");
        scanf("%d", &code);

        clients[code - 1].Code_cli = 0; // mark as deleted
        saveClientsToFile();

        printf("Client supprimé avec succès");
    }
    else if (a == 4)
    {
        qsort(clients, 20, sizeof(SClient), comparer);
        for (int c = 0; c < 20; c++)
        {
            if (clients[c].Code_cli != 0)
            {
                printf("\nCode client : %d", clients[c].Code_cli);
                printf("\nNom: %s | Prenom: %s", clients[c].Nom, clients[c].Prenom);
                printf("\n");
            }
        }
    }
    else if (a == 5)
        menu();
}

void gerer_compte(int a)
{
    loadComptesFromFile();
    if (a == 1)
    {
        SCompte compte;

        printf("Code Compte : ");
        scanf("%d", &compte.code_cpt);

        for (int i = 0; i < 20; i++)
        {
            if (comptes[i].code_cpt == compte.code_cpt)
            {
                printf("Code existant\n");
                return;
            }
        }

        printf("Code Client : ");
        scanf("%d", &compte.Code_cli);
        printf("Date de creation du compte (Jour Mois Annee) : ");
        scanf("%d %d %d", &compte.d_compte.Jour, &compte.d_compte.Mois, &compte.d_compte.Annee);
        printf("Somme : ");
        scanf("%d", &compte.somme);
        
        for (int i = 0; i < 20; i++)
        {
            if (comptes[i].code_cpt == 0)
            {
                comptes[i] = compte;
                break;
            }
        }

        

        saveComptesToFile();

        printf("Compte ajouté avec succès");
    }
    else if (a == 2)
    {
        int code;

        printf("Code compte : ");
        scanf("%d", &code);

        for (int i = 0; i < 20; i++)
        {
            if (comptes[i].code_cpt == code)
            {
                printf("\n Code compte : %d", comptes[i].code_cpt);
                printf("\n Code client : %d", comptes[i].Code_cli);
                printf("\n Date creation %d / %d / %d", comptes[i].d_compte.Jour, comptes[i].d_compte.Mois, comptes[i].d_compte.Annee);
                printf("\n Somme %d", comptes[i].somme);
                break;
            }
        }

        printf("Code non existant\n");
    }
    else if (a == 3)
    {
        for (int i = 0; i < 20; i++)
        {
            if (comptes[i].code_cpt != 0)
            {
                printf("\n Code compte : %d", comptes[i].code_cpt);
                printf("\n Code client : %d", comptes[i].Code_cli);
                printf("\n Date creation %d / %d / %d", comptes[i].d_compte.Jour, comptes[i].d_compte.Mois, comptes[i].d_compte.Annee);
                printf("\n Somme %d", comptes[i].somme);
                printf("\n-----------------------------------------");
            }
        }
    }
    else if (a == 4)
    {
        int code;

        printf("Code Compte a supprimer : ");
        scanf("%d", &code);

        for (int i = 0; i < 20; i++)
        {
            if (comptes[i].code_cpt == code)
            {
                comptes[i].code_cpt = 0; // mark as deleted
                saveComptesToFile();

                printf("Compte supprimé avec succès");
                return;
            }
        }

        printf("Code non existant\n");
    }
    else if (a == 5)
        menu();
}

void gerer_operation(int a)
{
    loadComptesFromFile();
    if (a == 1)
    {
        int code, m;

        printf("Code Compte : ");
        scanf("%d", &code);

        for (int i = 0; i < 20; i++)
        {
            if (comptes[i].code_cpt == code)
            {
                do
                {
                    printf("\n Montant : ");
                    scanf("%d", &m);
                    if (m > 1000)
                        printf("\n Le montant ne doit pas dépasser 1000 DT");
                    solde = comptes[i].somme - m;
                    if (solde < 10)
                        printf("\n Le solde ne doit pas être inférieur à 10 DT");
                } while (m > 1000 || solde < 10);

                comptes[i].somme -= m;

                printf("\n Code compte %d", comptes[i].code_cpt);
                printf("\n Code client %d", comptes[i].Code_cli);
                printf("\n Nouveau solde : %d", comptes[i].somme);
                printf("\n Date creation %d / %d / %d", comptes[i].d_compte.Jour, comptes[i].d_compte.Mois, comptes[i].d_compte.Annee);
                printf("\n-----------------------------------------");
            }
        }

        saveComptesToFile();
    }
    else if (a == 2)
    {
        int code1, code2, m;

        printf("Code Compte de départ : ");
        scanf("%d", &code1);

        printf("Code compte d'arrivée : ");
        scanf("%d", &code2);

        for (int i = 0; i < 20; i++)
        {
            if (comptes[i].code_cpt == code1)
            {
                do
                {
                    printf("\n Montant : ");
                    scanf("%d", &m);
                    if (m > 1000)
                        printf("\n Le montant ne doit pas dépasser 1000 DT");
                    solde = comptes[i].somme - m;
                    if (solde < 10)
                        printf("\n Le solde ne doit pas être inférieur à 10 DT");
                } while (m > 1000 || solde < 10);

                comptes[i].somme -= m;

                printf(" Compte de départ : ");
                printf("\n Code compte %d", comptes[i].code_cpt);
                printf("\n Code client %d", comptes[i].Code_cli);
                printf("\n Nouveau solde : %d", comptes[i].somme);
                printf("\n Date creation %d / %d / %d", comptes[i].d_compte.Jour, comptes[i].d_compte.Mois, comptes[i].d_compte.Annee);
                printf("\n-----------------------------------------");
            }
            else if (comptes[i].code_cpt == code2)
            {
                comptes[i].somme += m;

                printf(" Compte d'arrivée :");
                printf("\n Code compte %d", comptes[i].code_cpt);
                printf("\n Code client %d", comptes[i].Code_cli);
                printf("\n Nouveau solde : %d", comptes[i].somme);
                printf("\n Date creation %d / %d / %d", comptes[i].d_compte.Jour, comptes[i].d_compte.Mois, comptes[i].d_compte.Annee);
                printf("\n-----------------------------------------");
            }
        }

        saveComptesToFile();
    }
}

int main()
{
    menu();
    return 0;
}
