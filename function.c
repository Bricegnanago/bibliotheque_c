#include <my_global.h>
#include <mysql.h>
#include "biblio.h"
#include <string.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}


void insertClient(Client client){

    // Debut verfication d'existence
    int flag = checkIfClientExist(client);
    //Fin verification existence
    if (flag == 1){ //ok 
        MYSQL *con = mysql_init(NULL);
        if (con == NULL){
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }  
        
        if (mysql_real_connect(con, "localhost", "root", "root","testdb", 0, NULL, 0) == NULL){
            finish_with_error(con);
        }   
        char buf[1024] = {};

        char query_string[] = { 
            "INSERT INTO Client VALUES(null, '%s', '%s', '%s', '%d', '%s', NOW(), null)"
        };
        sprintf(buf, query_string,client.firstname, client.lastname, client.numcart, client.age, client.classroom);

        if (mysql_query(con,buf)){
            finish_with_error(con);
        }
    
        mysql_close(con);

        printf("\nDonnée insérée avec succès\n\n");
    }else{
        printf("\nCe Client existe déja dans la base de données\n\n");
        exit(1);
    }
    
}

void insertBook(Book book){
    
    // Debut verfication d'existence
    int flag = checkIfBookExist(book);
    //Fin verification existence
    if (flag == 1){ //ok 
        MYSQL *con = mysql_init(NULL);
        if (con == NULL)
        {
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }  
        
        if (mysql_real_connect(con, "localhost", "root", "root", "testdb", 0, NULL, 0) == NULL){
            finish_with_error(con);
        }   
        char buf[1024] = {};
        char query_string[] = { 
            "INSERT INTO Book VALUES(null, '%d', '%s', '%s', '%s', '%s', NOW(), null, 0)"
        };
        sprintf(buf, query_string, book.nb_page, book.author, book.description, book.title, book.category);    
        
        if (mysql_query(con,buf)){
            finish_with_error(con);
        }
    
        mysql_close(con);  
    }else{
        printf("\nCe Livre existe déja dans la base de données\n\n");
        exit(1);
    }  
}



// Supprimer un client
void removeClient(Client data){
    
    // Debut verfication d'existence
    int flag = checkIfClientExist(data);
    //Fin verification existence
    
    if (flag == 0){ //ok 
        MYSQL *con = mysql_init(NULL);
        if (con == NULL){
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }  
        
        // Connexion à la base de données
        if (mysql_real_connect(con, "localhost", "root", "root","testdb", 0, NULL, 0) == NULL){
            finish_with_error(con);
        }   
        char buf[1024] = {};

        // Requete sql 
        char query_string[] = { 
            "DELETE FROM Client WHERE firstname='%s' OR lastname='%s' OR numcart='%s'"
        };
        sprintf(buf, query_string, data.firstname, data.lastname, data.numcart);
        if (mysql_query(con,buf)){
            finish_with_error(con);
        }
    
        mysql_close(con);
    }else {
        printf("\nClient introuvable\n");
    }
}

void removeBook(Book book){
    // Debut verfication d'existence
    int flag = checkIfBookExist(book);
    //Fin verification existence
    
    if (flag == 0){ //ok 
        MYSQL *con = mysql_init(NULL);
        if (con == NULL){
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }  
        
        if (mysql_real_connect(con, "localhost", "root", "root","testdb", 0, NULL, 0) == NULL){
            finish_with_error(con);
        }   
        char buf[1024] = {};
        
        char query_string[] = { 
            "DELETE FROM Book WHERE title='%s'"
        };
        sprintf(buf, query_string, book.title);
        if (mysql_query(con,buf)){
            finish_with_error(con);
        }
    
        mysql_close(con);
    }else{
        printf("\nSuppression impossible ! Client enexistant \n");
    }
}

void updateClient(Client dataClientHost, Client dataClientToUpdate){
    // Debut verfication d'existence
    int flag = checkIfClientExist(dataClientHost);
    //Fin verification existence
    
    if (flag == 0){ //ok 
        MYSQL *con = mysql_init(NULL);
        if (con == NULL){
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }  
        
        if (mysql_real_connect(con, "localhost", "root", "root","testdb", 0, NULL, 0) == NULL){
            finish_with_error(con);
        }   
        char buf[1024] = {};
        
        char query_string[] = { 
            "UPDATE Client SET firstname='%s', lastname='%s', numcart='%s', age='%d', classroom='%s', last_update=NOW() WHERE firstname='%s'"
        };
        sprintf(buf, query_string, dataClientToUpdate.firstname, dataClientToUpdate.lastname, dataClientToUpdate.numcart, dataClientToUpdate.age, dataClientToUpdate.classroom, dataClientHost.firstname);
        if (mysql_query(con,buf)){
            finish_with_error(con);
        }
    
        mysql_close(con);
    }else
        printf("\nMise à jour impossible Client inexistant\n");
}


void updateBook(Book dataBookHost, Book dataBookToUpdate){
    // Debut verfication d'existence
    int flag = checkIfBookExist(dataBookHost);
    //Fin verification existence
    
    if (flag == 0){ //ok 
        MYSQL *con = mysql_init(NULL);
        if (con == NULL){
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }  
        
        if (mysql_real_connect(con, "localhost", "root", "root","testdb", 0, NULL, 0) == NULL){
            finish_with_error(con);
        }   
        char buf[1024] = {};
        
        char query_string[] = { 
            "UPDATE Book SET nb_page='%d', author='%s', description='%s', title='%s', category='%s', last_update=NOW() WHERE title='%s'"
        };
        sprintf(buf, query_string, dataBookToUpdate.nb_page, dataBookToUpdate.author, dataBookToUpdate.description, dataBookToUpdate.title, dataBookToUpdate.category, dataBookHost.title);
        if (mysql_query(con,buf)){
            finish_with_error(con);
        }
    
        mysql_close(con);
    }else{
        printf("\n Mise à jour impossible ! Données inexistante \n");
    }
}

void readAll(char table_name[10]){

    MYSQL *con = mysql_init(NULL);
    if (con == NULL){
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }  
    
    if (mysql_real_connect(con, "localhost", "root", "root","testdb", 0, NULL, 0) == NULL){
        finish_with_error(con);
    }   
    char buf[1024] = {};
    
    char query_string[] = { 
        "SELECT * FROM %s"
    };
    sprintf(buf, query_string, table_name);

    printf("%s", buf);
    if (mysql_query(con,buf)){
        finish_with_error(con);
    }    
        
    MYSQL_RES * result = mysql_store_result(con);
    
    if (result == NULL){
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);   
    MYSQL_ROW row;         
    
    while ((row = mysql_fetch_row(result))){ 
        for(int i = 0; i < num_fields; i++){ 
            printf("%s ", row[i] ? row[i] : "NULL"); 
        } 
            printf("\n"); 
    }

    //Fin affichage client
    mysql_free_result(result);
    mysql_close(con);
}

int checkIfClientExist(Client data){
    int flag;

    MYSQL *con = mysql_init(NULL);
    if (con == NULL){
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }  
    
    if (mysql_real_connect(con, "localhost", "root", "root","testdb", 0, NULL, 0) == NULL){
        finish_with_error(con);
    }   
    char buf[1024] = {};
    
    char query_string[] = { 
        "SELECT count(client_id) FROM Client WHERE numcart='%s'"
    };
    
    sprintf(buf, query_string, data.numcart);
    if (mysql_query(con,buf)){
        finish_with_error(con);
    }

    MYSQL_RES * result = mysql_store_result(con);  
    int num_fields = mysql_num_fields(result);
    
    MYSQL_ROW row;    
    while ((row = mysql_fetch_row(result))) 
    { 
        for(int i = 0; i < num_fields; i++) 
        { 
            // printf("%s", row[i] ? row[i] : "NULL");
            num_fields = atoi(row[i]);
        } 
            printf("\n"); 
    }
    if(num_fields > 0)
        flag = 0; //ok
    else
        flag = 1; //nok    
    mysql_free_result(result);
    mysql_close(con);
    return flag;
}


// int getIdOfClient(Client client){
//     int flacheckIfClientExist(client);
// }



int checkIfBookExist(Book data){
    int flag;

    MYSQL *con = mysql_init(NULL);
    if (con == NULL){
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }  
    
    if (mysql_real_connect(con, "localhost", "root", "root","testdb", 0, NULL, 0) == NULL){
        finish_with_error(con);
    }   
    char buf[1024] = {};
    
    char query_string[] = { 
        "SELECT count(*) FROM Book WHERE title='%s'"
    };
    
    sprintf(buf, query_string, data.title);
    if (mysql_query(con,buf)){
        finish_with_error(con);
    }

    MYSQL_RES * result = mysql_store_result(con);  
    int num_fields = mysql_num_fields(result);
    // printf("\nnum == %d\n\n", num_fields);
    MYSQL_ROW row;      
    while ((row = mysql_fetch_row(result))) 
    { 
        for(int i = 0; i < num_fields; i++) 
        { 
            // printf("%s", row[i] ? row[i] : "NULL");
            num_fields = atoi(row[i]);
        } 
            printf("\n");        
    }

    // printf("\nj === %d\n\n", j);
    if(num_fields > 0)
        flag = 0; //ok
    else
        flag = 1; //nok    
    mysql_free_result(result);
    mysql_close(con);
    return flag;
}

int checkIfUserExist(User data){
    int flag;

    MYSQL *con = mysql_init(NULL);
    if (con == NULL){
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }  
    
    if (mysql_real_connect(con, "localhost", "root", "root","testdb", 0, NULL, 0) == NULL)
        finish_with_error(con);

    char buf[1024] = {};
    
    char query_string[] = { 
        "SELECT count(*) FROM superuser WHERE username='%s'AND password=sha1('%s')"
    };
    
    sprintf(buf, query_string, data.username,data.password);
    if (mysql_query(con,buf)){
        finish_with_error(con);
    }

    MYSQL_RES * result = mysql_store_result(con);  
    int num_fields = mysql_num_fields(result);    
    MYSQL_ROW row;      
    while ((row = mysql_fetch_row(result))) 
    { 
        for(int i = 0; i < num_fields; i++)            
            num_fields = atoi(row[i]);
            printf("\n");        
    }
    
    if(num_fields > 0)
        flag = 0; //ok
    else
        flag = 1; //nok    
    mysql_free_result(result);
    mysql_close(con);
    return flag;
}

// int authentification(User user){

//     // 

//     return flag;
// }

void borrowOneBook(Book book, Client client, User borrower){

    // Debut verfication d'existence
    int flag_client = checkIfClientExist(client);
    int flag_book = checkIfBookExist(book);
    int flag = flag_book + flag_client;
    //Fin verification existence
    if (flag == 0){ //ok 
        MYSQL *con = mysql_init(NULL);
        if (con == NULL){
            fprintf(stderr, "mysql_init() failed\n");
            exit(1);
        }

        if (mysql_real_connect(con, "localhost", "root", "root","testdb", 0, NULL, 0) == NULL){
            finish_with_error(con);
        }   
        char buf[1024] = {};
        /***************** Recuperer l'identifiant du livre ********************/ 
        char query_string_Client[] = {
            "SELECT client_id from Client WHERE firstname='%s' OR numcart='%s'"
        };
        sprintf(buf, query_string_Client, client.firstname, client.numcart);
        printf("req client_id = %s\n", buf);
        if (mysql_query(con,buf)){
            finish_with_error(con);
        }
        

        MYSQL_RES * result_cli = mysql_store_result(con);  
        int num_fields_cli = mysql_num_fields(result_cli);    
        MYSQL_ROW row_cli;    
        while ((row_cli = mysql_fetch_row(result_cli))) 
        { 
            // for(int i = 0; i < num_fields_cli; i++)            
            //     num_fields_cli = atoi(row_cli[i]);
            //     printf("\n");        
            num_fields_cli = atoi(row_cli[0]);
        }
        printf("client id : %d\n", num_fields_cli);
        mysql_free_result(result_cli);           
        
        /***************** Fin Recuperer l'identifiant du livre ********************/ 


        /***************** Debut Recuperer l'identifiant du livre ********************/
         char query_string_Book[] = {
            "SELECT livre_id from Book WHERE title='%s'"
        };
        sprintf(buf, query_string_Book, book.title);
        printf("req livre_id = %s\n", buf);
        if (mysql_query(con,buf )){
            finish_with_error(con);
        }
        MYSQL_RES * result_book = mysql_store_result(con);  
        int num_fields_book = mysql_num_fields(result_book);    

        MYSQL_ROW row_book;      
        while ((row_book = mysql_fetch_row(result_book))) 
        { 
            // for(int i = 0; i < num_fields_book; i++)            
            //     num_fields_book = atoi(row_book[i]);
            //     printf("\n");
            num_fields_book = atoi(row_book[0]);
            // printf(" livre id 00000 : %d\n\n", atoi(row_book[0]));
                
        }
        printf("livre id : %d\n", num_fields_book);
        mysql_free_result(result_book);        

       /***************** Fin Recuperer l'identifiant du livre ********************/ 
        /***************** Recuperer l'identifiant de l'emprunteur ********************/ 
        char query_string_Borrower[] = {
            "SELECT user_id from superuser WHERE username='%s'"
        };        
        sprintf(buf, query_string_Borrower, borrower.username);
        printf("req user_id = %s\n", buf);
        if (mysql_query(con,buf)){
            finish_with_error(con);
        }
        
        MYSQL_RES * result_borrower = mysql_store_result(con);
        int num_fields_borrower = mysql_num_fields(result_borrower);    

        MYSQL_ROW row_borrower;
        while ((row_borrower = mysql_fetch_row(result_borrower))) 
        { 
            // for(int i = 0; i < num_fields_borrower; i++)            
            //     num_fields_borrower = atoi(row_borrower[i]);
            //     printf("\n");
            num_fields_borrower = atoi(row_borrower[0]);
        }
        printf("user id : %d\n", num_fields_borrower);
        mysql_free_result(result_borrower);         
        /***************** Fin Recuperer l'identifiant de l'emprunteur ********************/ 
        

        char query_string[] = { 
            "INSERT INTO Borrow VALUES(null, '%d', '%d', NOW(), '%d')"
        };
        sprintf(buf, query_string, num_fields_cli, num_fields_book, num_fields_borrower);

        if (mysql_query(con,buf)){
            finish_with_error(con);
        }

        /****** Modification du status de disponibilié du livre emprunté ***********/

        int status = 1;
        char query_status_book[] = { 
            "UPDATE Book SET statusBook='%d' WHERE livre_id='%d'"
        };
        sprintf(buf, query_status_book, status, num_fields_book);
        printf("query status : %s", buf);
        if (mysql_query(con,buf)){
            finish_with_error(con);
        }
        mysql_close(con);

        printf("\nDonnée insérée avec succès\n\n");
    }else{
        printf("\nCe Client existe déja dans la base de données\n\n");
        exit(1);
    }
    
}