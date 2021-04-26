#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define LGNLE 6
#define NS 6
#define LGUE 7
#define TAILLE_MAX 1000

/* Modèle représentant l'utilsateur */
struct User
{
    int Nle; //Numéro matricule de l'étudiant
    char Nom[30];
    char Prenom[40];
    int Semestre; //1,2,..,6
};

/* Modèle des notes */
struct Note
{
    char ue[LGUE];
    float devoir;
    float examen;
    float moyenne;
    char valide[4]; //OUI ou NON
};

void PremiereConnexion(void)
{
    FILE *fichier=NULL;
    int i,verif,numero,sem;
    char nom[30],prenom[40],saisie[50];
    puts("C'EST VOTRE PREMIERE EXPERIENCE");
    puts("VEUILLEZ FOURNIR QLQ INFIRMATIONS");
    do
    {
        printf("Votre nom : ");
        scanf("%s", nom);
        //gets(nom);
    }while(strlen(nom)==0);
    for(i=0;i<strlen(nom);i++)
    nom[i]=toupper(nom[i]);
    do
    {
        printf("Votre prenom : ");
        scanf("%s", prenom);
        //gets(prenom);
    }while(strlen(prenom)==0);
    for(i=0;i<strlen(prenom);i++)
    prenom[i]=toupper(prenom[i]);
    do
    {
        do
        {
            printf("Votre numero matricule : ");
            scanf("%s", saisie);
            //gets(saisie);
        }while(strlen(saisie)!=LGNLE);
        verif=sscanf(saisie,"%d",&numero);
    }while(verif<1);
    for(i=0;i<NS;i++)
    printf("%d- SEMESTRE %d\n",i+1,i+1);
    do
    {
        do
        {
            printf("Semestre : ");
            scanf("%s", saisie);
            //gets(saisie);
            verif=sscanf(saisie,"%d",&sem);
        }while(verif<1);
    }while(sem<1 || sem>NS);
    fichier=fopen("user_datas.txt","w");
    if(fichier!=NULL)
    {
        fprintf(fichier,"%s\n%s\n%d\n%d\n",nom,prenom,numero,sem);
        fclose(fichier);
        puts("\nMERCI POUR CES INFORMATIONS");
        puts("ELLES ONT ETE ENREGISTREES");
    }
    else
    {
        puts("ERREUR : INFORMATIONS NON ENREGISTREES");
    }
}
void Intro(void)
{
    puts("===============================================");
    puts("====  SOYEZ LA BIENVENUE DANS \"MES NOTES\"  ====");
    puts("===============================================");
    puts("===================    ===========92296692(W)==");
    puts("===  MES NOTES  ===    ==CONTACTS 96273390(W)==");
    puts("===================    ========================");
    puts("==  CODE_WARS_C  ==    ==UNIVERSITE  DE  LOME==");
    puts("KAKONE TECHNOLOGIES    DEPART. DE MATHEMATIQUES");
    puts("===============================================");
    puts("= AUTEURS: C. BIDJADA && J. KONKA (ETUDIANTS) =");
    puts("===============================================");

}
int OldUser(FILE *fichier)
{
    struct User U;
    fscanf(fichier,"%s\n%s\n%d\n%d\n",U.Nom,U.Prenom,&U.Nle,&U.Semestre);
        fclose(fichier);
        printf("\tSALUT MR/MME %s %s\n",U.Prenom,U.Nom);
        printf("======  UL/FDS/MATHEMATIQUES/S%d/%d  =======\n",U.Semestre,U.Nle);
        puts("===============================================");
    return U.Semestre;
}
int OuiNon(void)
{
    char saisie[10];
    int verif,choix;
    do
    {
        puts("1- OUI\t0- NON");
        do
        {
            printf("Reponse : ");
            scanf("%s", saisie);
            //gets(saisie);
            verif=sscanf(saisie,"%d",&choix);
        }while(verif<1);
    }while(choix!=1 && choix!=0);
    return choix;
}
void ModifierSemestre(FILE *fichier)
{
    int i,verif;
    char saisie[20];
    struct User U;
    fichier=fopen("user_datas.txt","r");
    fscanf(fichier,"%s\n%s\n%d\n%d\n",U.Nom,U.Prenom,&U.Nle,&U.Semestre);
    fclose(fichier);
    remove("user_datas.txt");
    fichier=fopen("user_datas.txt","w");
    for(i=0;i<NS;i++)
    if(U.Semestre<i+1)
    printf("%d- SEMESTRE %d\n",i+1,i+1);
    i=U.Semestre;
    do
    {
        do
        {
            printf("Semestre : ");
            scanf("%s", saisie);
            //gets(saisie);
            verif=sscanf(saisie,"%d",&U.Semestre);
        }while(verif<1);
    }while(U.Semestre>NS || i>=U.Semestre);
    fprintf(fichier,"%s\n%s\n%d\n%d\n",U.Nom,U.Prenom,U.Nle,U.Semestre);
    fclose(fichier);
    puts("\nMODIFICATIONS PRISES EN COMPTE");

}

int ChoisirAction(FILE *fichier)
{
    int choice,verif;
    char saisie[50];

    puts("CHOISSISEZ L'ACTION A FAIRE");
    puts("1- EDITER LES NOTES");
    puts("2- RECHERCHER UNE NOTE");
    puts("3- AJOUTER UNE NOTE");
    puts("4- AJOUTER PLUSIEURS NOTES");
    puts("5- METTRE A JOUR UNE NOTE");
    puts("6- SUPPRIMER UNE NOTE");
    puts("7- QUITTER");
    do
    {
        do
        {
            printf("Choix : ");
            scanf("%s", saisie);
            //gets(saisie);
            verif=sscanf(saisie,"%d",&choice);
        }while(verif<1);

    }while(choice>7||choice<1);
    return choice;
}
/* 1 */
void EditerNotes(FILE *fichier,int S)
{
    struct Note N;
    int verif,choice,n=0,i;
    char saisie[50],chaine[1000];

    printf("\n");
    while(fgets(chaine,TAILLE_MAX,fichier)!=NULL)
    {
        n++;
        if(n==1)
        puts("CODE DE L'UE\tNOTE DE DEVOIR\tNOTE D'EXAMEN \t\tMOYENNE\tVALIDE");
        verif=sscanf(chaine,"%s %f %f %f %s\n",N.ue,&N.devoir,&N.examen,&N.moyenne,N.valide);
        printf("%s\t%0.2f\t%0.2f\t%0.2f\t%s\n",N.ue,N.devoir,N.examen,N.moyenne,N.valide);
    }
}
/*2*/
void RechercherNote(FILE *fichier)
{
    void AfficherNote(struct Note);

    struct Note N;
    char Ue[LGUE],chaine[1000];
    int ok,i,verif;
    do
    {
        do
        {
            printf("Code de l'UE : ");
            scanf("%s", Ue);
            //gets(Ue);
        }while(strlen(Ue)!=NS);
        for(i=0;i<NS;i++)
        Ue[i]=toupper(Ue[i]);
        ok=0;
        for(i=0;i<NS/2;i++)
        if(Ue[i]<'A' || Ue[i]>'Z')
        ok=1;
        for(i=NS/2;i<NS;i++)
        if(Ue[i]<'0' || Ue[i]>'9')
        ok=1;
    }while(ok);
    ok=1;
    while(fgets(chaine,TAILLE_MAX,fichier)!=NULL && ok)
    {
        verif=sscanf(chaine,"%s %f %f %f %s\n",N.ue,&N.devoir,&N.examen,&N.moyenne,N.valide);
        if(strcmp(N.ue,Ue)==0)
        ok=0;

    }
    if(strcmp(N.ue,Ue)==0)
    {
        AfficherNote(N);
    }
}
void AfficherNote(struct Note N)
{
    printf("======================\n");
    printf("=UE : %s    ==========\n",N.ue);
    printf("======================\n");
    printf("=NOTE DS : %0.2f",N.devoir);
    if(N.devoir<10)
    printf(" ");
    printf("=NOTE EX : %0.2f",N.examen);
    if(N.examen<10)
    printf(" ");
    printf("=\n");
    printf("==================================\n");
    printf("== MOYENNE : %0.2f",N.moyenne);
    if(N.moyenne<10)
    printf(" ");
                      printf("= VALIDE : %s==",N.valide);
    printf("==================================\n");
}
/*    ------    */
struct Note SaisirNote(void)
{
    char saisie[40];
    int verif;
    struct Note N;
    do
    {
        printf("NOTE DE DEVOIR : ");
        scanf("%s", saisie);
        //gets(saisie);
        verif=sscanf(saisie,"%f",&N.devoir);
    }while(verif<1 || N.devoir<0 || N.devoir>20);
    do
    {
        printf("NOTE D'EXAMEN : ");
        scanf("%s", saisie);
        //gets(saisie);
        verif=sscanf(saisie,"%f",&N.examen);
    }while(verif<1 || N.examen<0 || N.examen>20);
    N.moyenne=0.4*N.devoir+0.6*N.examen;
    if(N.moyenne<10)
    strcat(N.valide,"NON");
    else
    strcat(N.valide,"OUI");
}
/*3*/
void AjouterNote(FILE *fichier)
{
    struct Note N;;
    char saisie[50];
    int reponse,verif;
    N=SaisirNote();
    puts("\nCONFIRMEZ-VOUS CES INFORMATIONS?");
    do
    {
        puts("1- OUI\t0- NON");
        do
        {
            printf("Reponse : ");
            scanf("%s", saisie);
            //gets(saisie);
            verif=sscanf(saisie,"%d",&reponse);
        }while(verif<1);
    }while(reponse!=0 && reponse!=1);
    if(reponse)
    {
        fprintf(fichier,"%s %f %f %f %s\n",N.ue,N.devoir,N.examen,N.moyenne,N.valide);
        puts("\nCLIENT ENREGISTRE AVEC SUCCES\n");
    }
    else
    puts("\nENREGISTREMENT ANNULE AVEC SUCCES\n");
}
/*4*/
void AjouterNNotes(FILE *fichier)
{

}
/*5*/
void ModifierNote(FILE *fichier)
{

}
/*5*/
void SupprimerNote(FILE *fichier)
{

}

int main()
{
    //LES PROTOTYPES
    void PremiereConnexion(void);

    //Les variables
    FILE *fichierUser=NULL,*fichierNotes=NULL;
    int Sem,Rep,Choix;

    Intro();

    fichierUser=fopen("user_datas.txt","r");
    if(fichierUser==NULL)
    PremiereConnexion();
    else
    {
        Sem=OldUser(fichierUser);

        if(Sem<6)
        {
            puts("ETES-VOUS PASSE EN SEMESTRE SUPERIEUR?");
            Rep=OuiNon();
            if(Rep)
            ModifierSemestre(fichierUser);
        }
    }
    do
    {
        Choix=ChoisirAction(fichierNotes);
        switch(Choix)
        {
            case 1://Édition
            fichierNotes=fopen("user_notes.txt","r");
            EditerNotes(fichierNotes,Sem);
            fclose(fichierNotes);
            break;
            case 2://Recherche
            fichierNotes=fopen("user_notes.txt","r");
            RechercherNote(fichierNotes);
            fclose(fichierNotes);
            break;
            case 3://Ajout
            fichierNotes=fopen("user_notes.txt","a");
            AjouterNote(fichierNotes);
            fclose(fichierNotes);
            break;
            case 4://Ajout++
            fichierNotes=fopen("user_notes.txt","a");
            AjouterNNotes(fichierNotes);
            fclose(fichierNotes);
            break;
            case 5://Modification
            fichierNotes=fopen("user_notes.txt","r+");
            ModifierNote(fichierNotes);
            fclose(fichierNotes);
            break;
            case 6://Suppression
            fichierNotes=fopen("user_notes.txt","r+");
            SupprimerNote(fichierNotes);
            fclose(fichierNotes);
            break;
            case 7://Fin
            printf("\nACTION ANNULEE\n");
            break;
        }
        printf("\n");
    }while(Choix!=7);

    return 0;
}
