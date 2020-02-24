typedef struct Client Client;
typedef struct Book Book;
typedef struct User User;
typedef struct Category Category;

struct User
{
    char username[20];
    char password[20];
};



struct Client
{
    int client_id;
    char firstname[50];
    char lastname[50];
    char numcart[15];
    int age;
    char classroom[20];
    char created_cli[15];
    char last_update_cli[15];
    
};

struct Book
{
    int livre_id;
    char title[100];
    char description[200];
    char author[50];
    char saved[15];
    char category[50];
    int nb_page;
    char last_update[15];
};



void insertClient(Client dataClientHost); //ok
void insertBook(Book dataBookHost); //ok
void insertCategory(Category data); //ok
void readAll(char table_name[10]); //ok
void updateClient(Client dataClientHost, Client DataClientOfUpdate); //ok
void updateBook(Book dataBookHost, Book DataBookOfUpdate); //ok
void removeClient(Client dataClientHost); //ok
void removeBook(Book dataBookHost); //ok
int checkIfClientExist(Client data);
int checkIfBookExist(Book data);
int checkIfUserExist(User data);
int authentification(User user);
void borrowOneBook(Book book, Client client, User borrower);
int getIdOfClient(Client client);
int getIdOfBook(Book book);

// bool authentification(User user);