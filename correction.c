#include<stdio.h>
#include <my_global.h>
#include <mysql.h>
#include "biblio.h"
#include "enregistrement.h"
#define RC printf("\n")



void retraitope();


int main(){
    int resultat = 0;
    Utilisateur utilisateur; // c'est petit u pour le 
    do{
        printf(" entrer votre login \n");
        scanf("%s",utilisateur.login);
        printf(" entrer votre mot de passe\n");
        scanf("%s",utilisateur.mdp);
        resultat = checkIfUserExists(utilisateur);
    }while (resultat == 0);

    return 0;
}