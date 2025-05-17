/********************************************************************************************************
 * Fichier : ProjeDeClsse.C                                                                            *
                                                                                                       *
 * Auteur : ADAMAH Kouevi Joseph (LF - IS) et MAZA Kossivi Renaud                                      *
                                                                                                       *
 * Encadrant : Dr AKAKPO                                                                               *
                                                                                                       *
 * Date de création : Lundi le 12 Mai 2025                                                             *
                                                                                                       *
 *                                                                                                     *
 *                                                                                                     *                                                                                                     *
 * Fonctionnalités :                                                                                   *
 *   - Saisie du nombre du nombres des points et tous ces informations                                 *
 *   - Calcul automatique de la distance entre deux points
     -Calcul automatique du Barycentre entre deux points                                               *
     -Les autres fonctionnalités se retrouve au menu                                                   *
 *   - Possibilité de recalcul sans quitter le programme                                               *
 *                                                                                                     *
 *                                                                                                     *
 ********************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <locale>
#include <math.h>
#include <string.h>


/*
NB: Dans notre code il existe des scanf("%*c") ce qui est du au fais que fgets prend des \n et ignore ce qu'il doit prendre
*/

typedef struct Point pt;
struct Point
{
    char nom[3] ;
    float abs, ord;
    int coef;

};


int GenereCoefficient(pt *infoPoint, int nbPoint, pt *p) //Fonction qui génere les coefficients
{
    p->coef = ceil(fmax(fabs(p->abs), fabs(p->ord)) / floor(fmin(fabs(p->abs), fabs(p->ord))));

    return p->coef;
}


void saisiInfo(pt *infopoint, int nbPoint) //
{

    pt *p;
    float controle; // sera utiliser pour controler l'entrée des abscisses et des oordonnées

    for (p = infopoint; p< infopoint + nbPoint; p++ )
    {



        printf("\nEntrez le nom du point %d : ", (int)(p-infopoint+1));
        while (getchar() != '\n');

        fgets(p->nom, sizeof(p->nom), stdin);
        do
        {
            printf("\nEntrez l'abscisse du point %d : ", (int)(p-infopoint+1));

            while (getchar() != '\n');

            controle = scanf("%f", &p->abs);

            if(controle != 1)
            {
                system("cls");
            }
        }
        while(controle != 1);

        do
        {
            printf("\nEntrez l'ordonnée du point %d : ", (int)(p-infopoint+1));

            while (getchar() != '\n');

            controle = scanf("%f", &p->ord);

            if(controle != 1)
            {
                system("cls");
            }
        }
        while(controle != 1);

        GenereCoefficient(infopoint, nbPoint, p);

        system("pause");

    }


}

void AfficherInfoPoint(pt *infopoint, int nbPoint)
{
    pt *p;

    printf("\nNOM----------Cordonnées----------Coefficient\n");

    for (p = infopoint; p< infopoint + nbPoint; p++ )
    {

        printf("\n%s          (%.2f, %.2f)          %d", p->nom, p->abs, p->ord, p->coef);
    }
}




float Maxabs(pt *infoPoint, int nbPoint) // Fonction qui recherche et retourne le Maximum des abscisses
{
    float max;

    pt *p;

    max = 0;

    for (p = infoPoint; p< infoPoint + nbPoint; p++ )
    {

        if(fabs(p->abs) > fabs(max))
        {
            max = fabs(p->abs);
        }

    }

    printf("\nLe maximum des abscisses est : %.2f\n",max);

    return max;

}

float Maxord(pt *infoPoint, int nbPoint) // Fonction qui recherche et retourne le Maximum des ordonées
{
    float max;

    pt *p;

    max = infoPoint->ord;

    for (p = infoPoint; p< infoPoint + nbPoint; p++ )
    {
        if(fabs(p->ord) > fabs(max))
        {
            max = fabs(p->ord);
        }
    }

    printf("\nLe maximum des ordonnée est : %.2f\n",max);

    return max;
}

float MinAbs(pt *infoPoint, int nbPoint) // Fonction qui recherche et retourne le Minimum des abscisses
{
    float min;

    pt *p;

    min = infoPoint->abs;

    for (p = infoPoint; p< infoPoint + nbPoint; p++ )
    {
        if(fabs(p->abs) < fabs(min))
        {
            min = fabs(p->abs);
        }
    }

    printf("\nLe minimum des abscisses est : %.2f\n",min);

    return min;
}

float MinOrd(pt *infoPoint, int nbPoint) // Fonction qui recherche et retourne le Minimum des ordonnées
{
    float min;

    pt *p;

    min = infoPoint->ord;

    for (p = infoPoint; p< infoPoint + nbPoint; p++ )
    {
        if(fabs(p->ord) < fabs(min))
        {
            min = fabs(p->ord);
        }
    }

    printf("\nLe minimum des ordonnée est : %.2f\n",min);

    return min;
}

/*
La fonction suivante sera utiliser dans les fonctions comme Barycentre , Calculde distance de deux points
pour rechercher le nom des point et returne le pointeur (L'adresse) du point
*/

pt *RecherchePt(pt *infoPoint, int nbPoint, char *nom, pt **pointp   )
{

    pt *n = NULL,*p;
    // printf("\nVeuillez entrer le nom du point recherché");
    //scanf("%*c");
    //fgets(nom, sizeof(nom), stdin);
    for (p = infoPoint; p< infoPoint + nbPoint; p++ )
    {

        if(strcmp(nom, p->nom) == 0 ) // La fonction strcmp permet de comparer les chaine de caractère
        {
            printf("Le point %s (%.2f, %.2f)", p->nom, p->abs, p->ord);

            *pointp = p;

            n=p;

            break;

        }
    }
    if ( n == NULL)
    {
        printf("\nDésolé mais ce point n'existe pas dans la liste des points ");
    }


    return n;

}


/*
La fonction suivante sera utiliser au menu du programme pour rechercher le nom des points
Et returne le pointeur (L'adresse) de ce point
*/

pt *RechercherPointeur(pt *infoPoint, int nbPoint, char *nom)
{
    pt *n = NULL,*p;

    for (p = infoPoint; p< infoPoint + nbPoint; p++ )
    {

        if(strcmp(nom, p->nom) == 0 )
        {
            printf("C'est le point %s (%.2f, %.2f)", p->nom, p->abs, p->ord);

            n=p; // Passage de l'adresse du point à n qui va le retourner

            printf("\nEt son pointeurs est %p : \n", n);
            break;

        }
    }
    if ( n == NULL)
    {
        printf("\n\nDésolé mais ce point n'existe pas dans la liste des points ");
    }

    return n;


}

void Barycentre(pt *infoPoint, int nbPoint) // Fonction qui calcule le barycentre
{
    char x[3]  ;// Variable pour prendre le nom des point pour calculer le barycentre
    char y[3] ; // Pareil ici
    float xG, yG; // cordonnéés du barycentre
    pt *PtxG = NULL;
    pt *ptyG = NULL;

    printf("\nVeuillez entrer le nom du premier point : \n");



    fgets(x, sizeof(x), stdin);

    while (getchar() != '\n');
    RecherchePt(infoPoint, nbPoint, x, &PtxG);

    if( PtxG != NULL ) // Si le premier point n'existe pas alors on ne demande plus le deuxieme
    {

        printf("\nVeuillez entrer le nom du deuxiéme point : ");

        while (getchar() != '\n');

        fgets(y, sizeof(y), stdin);

        RecherchePt(infoPoint, nbPoint, y, &ptyG);
    }

    if(ptyG != NULL)  // Si le deuxieme point n'existe pas alors on ne calcul plus le barycentre

    {
        xG = (PtxG->abs*PtxG->coef + ptyG->abs*ptyG->coef)/(PtxG->coef+ptyG->coef);

        yG = (PtxG->ord*PtxG->coef + ptyG->ord*ptyG->coef)/(PtxG->coef+ptyG->coef);

        printf("\n\nLe Barycentre est le point G(%.2f,%.2f ) ",xG, yG);
    }

}

float CalculDistance(pt *infoPoint, int nbPoint)
{
    char x[3] ; // Pour demander le nom des points
    pt *Ptx, *pty; // Pour prendre les pointeurs des coordonnées des point si ils existent
    float distance;

    printf("\nVeuillez entrer le nom du premier point : \n");

    while (getchar() != '\n');

    fgets(x, sizeof(x), stdin);

    RecherchePt(infoPoint, nbPoint, x, &Ptx);

    if(Ptx != NULL) // Si le premier point n'existe pas alors on ne demande plus le deuxieme
    {
        printf("\nVeuillez entrer le nom du deuxiéme point : ");

        while (getchar() != '\n');

        fgets(x, sizeof(x), stdin);

        RecherchePt(infoPoint, nbPoint, x, &pty);
    }

    if(pty!= NULL) // Si le deuxieme point n'existe pas alors on ne calcul plus la distance
    {
        distance = sqrt(pow((Ptx->abs - pty->abs),2) + pow((Ptx->ord - pty->ord),2));

        printf("\nLa distance %s%s = %.2f", Ptx->nom, pty->nom, distance);
    }

    return distance;


}

void Menu(int *choix)
{
    // printf("\n1 Réservation de mémoire");
    printf("\n1 Saisi des infots d'un point");
    printf("\n\n");

    printf("\n2 Afficher la liste des points ");
    printf("\n\n");

    printf("\n3 Calcul de distance de deux points");
    printf("\n\n");

    printf("\n4 Calcul de   Barycentre ");
    printf("\n\n");

    printf("\n5 Minimum des abscisses ");
    printf("\n\n");

    printf("\n6 Minimum des ordonnées");
    printf("\n\n");

    printf("\n7 Maximum des abscisses ");
    printf("\n\n");

    printf("\n8 Maximum des ordonnées ");
    printf("\n\n");

    printf("\n9 Recherche d'un point et retour de son pointeur");
    printf("\n\n");

    printf("\n10 Quitter\n");

    printf("\tVotre choix:  ");
    scanf("%d",choix);


}


int main()
{
    //system("color 6");
    setlocale(LC_ALL,"");
    int nbPoint,choix;
    pt *infoPoint;
    char nomPoint[3];
    printf("\nCombien de point vous voulez manipuler ? : ");
    scanf("%d",&nbPoint);
    infoPoint = (pt*)malloc(nbPoint*sizeof(pt));
    if(!infoPoint)
    {
        printf("\nEureur d'allocation");
    }

    system("cls");
    do
    {

        Menu(&choix);

        switch (choix)
        {
        case 1:
            system("cls");
            printf("\n=============Saisi des informations des points=============\n\n");

            saisiInfo(infoPoint, nbPoint);

            printf("\n\n");
            system("cls");
            break;
        case 2:
            system("cls");
            printf("\n=============Infos points===========\n\n");

            AfficherInfoPoint(infoPoint, nbPoint);

            printf("\n\n");
            system("\npause");
            system("cls");
            break;
        case 3:
            system("cls");
            printf("\n=============Calcul de distance de deux points=============\n\n");

            CalculDistance(infoPoint, nbPoint);

            printf("\n\n");
            system("pause");
            system("cls");
            break;
        case 4:
            system("cls");
            printf("\n=============Calcul de Barycentre===========\n\n");

            Barycentre(infoPoint, nbPoint);

            printf("\n\n");
            system("pause");
            system("cls");
            break;
        case 5:
            system("cls");
            printf("+++++++++++++Le minimum+++++++++++++++\n\n");

            MinAbs(infoPoint, nbPoint);

            printf("\n\n");
            system("pause");
            system("cls");
            break;
        case 6:
            system("cls");
            printf("+++++++++++++Le Minimum+++++++++++++++\n\n");

            MinOrd(infoPoint, nbPoint);

            printf("\n\n");
            system("pause");
            system("cls");
            break;
        case 7:
            system("cls");
            printf("+++++++++++++Le maximum+++++++++++++++\n\n");

            Maxabs(infoPoint, nbPoint);

            printf("\n\n");
            system("pause");
            system("cls");
            break;
        case 8:
            system("cls");
            printf("+++++++++++++Le maximum+++++++++++++++\n\n");

            Maxord(infoPoint, nbPoint);

            printf("\n\n");
            system("pause");
            system("cls");
            break;

        case 9 :
            system("cls");
            printf("+++++++++++++Recherche des adresses des points+++++++++++++++\n\n");

            printf("\nVeuillez entrer le nom du point que vous voulez rechercher l'adresse: ");

            while (getchar() != '\n');

            fgets(nomPoint, sizeof(nomPoint), stdin);

            RechercherPointeur(infoPoint, nbPoint, nomPoint);

            printf("\n");
            system("pause");
            system("cls");

            Menu(&choix);
            break;
        case 10:
            system("cls");
            printf("\nDommage de vous voir partir \n");
            break;
        default:
            printf("\nErreur\n");
            printf("\n\n");
            system("pause");
            system("cls");

        }
    }
    while(choix!=10);

    free(infoPoint);

    infoPoint = NULL;

    return 0;
}
