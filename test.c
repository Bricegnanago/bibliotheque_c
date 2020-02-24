#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include "biblio.h"

// void finish_with_error(MYSQL *con)
// {
//   fprintf(stderr, "%s\n", mysql_error(con));
//   mysql_close(con);
//   exit(1);        
// }

int main(int argc, char **argv)
{
    Client client;
    Client modif_client;
    Book book;
    User user;
    // MYSQL *con = mysql_init(NULL);
    printf("\n*** Creer maintenant un nouvelle client ***\n\n");



    // printf("Nom : ");
    // scanf("%s", client.lastname);
    
    // printf("Prenom : ");
    // scanf("%s", client.firstname);
  
    // printf("numero carte etudiant : ");
    // scanf("%s", client.numcart);
    
    // // 193939393
    // printf("Age : ");
    // scanf("%d", &client.age);

    // printf("Classe : ");
    // scanf("%s", client.classroom);

    // printf("Titre du livre : ");
    // scanf("%s", book.title);
    
    // printf("Description : ");
    // scanf("%s", book.description);

    // printf("Nombre de page : ");
    // scanf("%d", &book.nb_page);

    // printf("Auteur du livre : ");
    // scanf("%s", book.author);

    // printf("Categorie du livre : ");
    // scanf("%s", book.category);
    
    // insertBook(book);
    User user_session;
    int flag_auth=1;
    do
    {
        /* Authentification */
        printf("Login : ");
        scanf("%s", user_session.username);

        printf("Mode de passe : ");
        scanf("%s", user_session.password);
        flag_auth =  checkIfUserExist(user_session);        
    } while (flag_auth == 1);
    //Authentification réussi
    
    // printf("\n\n");
    // if(flag == 0)
    //     printf("existe\n\n");
    // else
    //     printf("n'existe pas\n");    
    return 0;
}