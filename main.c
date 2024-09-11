#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int jour;
    int mois;
    int annee;
}Date;

typedef struct{
    int numero;
    char nom[100];
    char prenom[100];
    Date birthday;
    char departement[100];
    float note;
}Student;

typedef struct{
    char departement[100];
    float moyenne;
}Group;

typedef struct{
    char departement[100];
    int nombre;
}Group1;

Student students[500] = {
    { 1, "test1", "test1", { 1, 1, 2001 }, "informatique", 14 },
    { 2, "test2", "test2", { 3, 2, 2000 }, "informatique", 9 },
    { 3, "test3", "test3", { 3, 10, 1999 }, "pc", 9 },
    { 4, "test4", "test4", { 6, 11, 2005 }, "svt", 10 },
    { 5, "test5", "test5", { 9, 8, 2003 }, "pc", 19 },
    { 6, "test6", "test6", { 20, 5, 2000 }, "math", 14 },
    { 7, "test7", "test7", { 16, 6, 2002 }, "math", 13 },
    { 8, "test8", "test8", { 3, 2, 2000 }, "math", 6 },
    { 9, "test9", "test9", { 4, 2, 2000 }, "informatique", 11 },
    { 10, "test10", "test10", { 3, 2, 2000 }, "informatique", 20 }
};

int counter = 10;

int findByNumero(int numero){
    for(int i=0; i<counter; i++){
        if(students[i].numero == numero)
            return i;
    }
    return -1;
}


void ajouter(){
    Student student;
    while(1){
        printf("Entrer le numero de l'etudiant :\n-");
        scanf("%d", &student.numero);
        int index = findByNumero(student.numero);
        if(index == -1){
            break;
        }else{
            printf("Il y a deja un etudiant avec le meme numero !\n");
        }
    }

    printf("Entrer le nom de l'etudiant :\n-");
    scanf("%s", student.nom);
    printf("Entrer le prenom de l'etudiant :\n-");
    scanf("%s", student.prenom);
    printf("Entrer le jour de naissance :\n-");
    scanf("%d", &student.birthday.jour);
    printf("Entrer le mois de naissance :\n-");
    scanf("%d", &student.birthday.mois);
    printf("Entrer l'annee de naissance :\n-");
    scanf("%d", &student.birthday.annee);
    printf("Entrez le departement :\n-");
    scanf("%s", student.departement);
    printf("Entrez la Note generale :\n-");
    scanf("%f", &student.note);

    students[counter++] = student;
    printf("L'etudiant est ajouté avec succes !\n");
    system("pause");
    system("cls");
}

//get item before update delete
int getItemBeforeUD(){
    int numero;
    printf("Entrez le numero de l'etudiant recherche : \n-");
    scanf("%d", &numero);
    int index = findByNumero(numero);

    if(index == -1){
        printf("L'etudiant n'existe pas !\n");
        return -1;
    }
    return index;
}

//Supprimer les informations d'un étudiant en fonction de son numéro unique
void supprimer(){
    int index = getItemBeforeUD();
    if(index != -1){
        char confirm;
        printf("Confirmez que vous souhaitez supprimer en tapant 'o' et annulez 'n'\n-");
        scanf(" %c", &confirm);
        if(confirm == 'o'){
            for(int i=index; i<counter-1; i++){
                students[i] = students[i+1];
            }

            counter--;
            printf("L'etudiant a ete supprimer avec succes !\n");
        }
    }
}

//Modifier les informations d'un étudiant en fonction de son numéro unique
void modifier(){
    int index = getItemBeforeUD();
    if(index != -1){
        Student student;
        student.numero = students[index].numero;
        printf("Entrer le nom de l'etudiant :\n-");
        scanf("%s", student.nom);
        printf("Entrer le prenom de l'etudiant :\n-");
        scanf("%s", student.prenom);
        printf("Entrer le jour de naissance :\n-");
        scanf("%d", &student.birthday.jour);
        printf("Entrer le mois de naissance :\n-");
        scanf("%d", &student.birthday.mois);
        printf("Entrer l'annee de naissance :\n-");
        scanf("%d", &student.birthday.annee);
        printf("Entrez le departement :\n-");
        scanf("%s", student.departement);
        printf("Entrez la Note generale :\n-");
        scanf("%f", &student.note);

        students[index] = student;
        printf("L'eleve est modifie avec succes !\n");
    }
}

//Consulter les informations complètes des étudiants, y compris la note générale et les détails personnels.
void afficher(Student list[], int seuil){
    for(int i=0; i<counter; i++){
        if(list[i].note >= seuil){
            printf("Numero : %d\nNom : %s\nPrenom : %s\nDate de naissance : %d/%d/%d\nDepartement : %s\nNote generale : %.2f\n", list[i].numero, list[i].nom, list[i].prenom, list[i].birthday.jour, list[i].birthday.mois, list[i].birthday.annee, list[i].departement, list[i].note);
            if(i != counter-1)
                printf("-----------------------------------------------------------------\n");
        }
    }
}

int findInGroupDepartment(Group list[], int size, char department[]){
    for(int i=0; i<size; i++){
        if(strcmp(list[i].departement, department) == 0){
            return i;
        }
    }
    return -1;
}

int findInGroupDepartment1(Group1 list[], int size, char department[]){
    for(int i=0; i<size; i++){
        if(strcmp(list[i].departement, department) == 0){
            return i;
        }
    }
    return -1;
}

//moyenne generale de chaque departement et de l’université entière
void moyennegenerale(){
    Group group[500];
    int count = 0;
    float univmoyenne = 0;
    for(int i=0; i<counter; i++){
        if(findInGroupDepartment(group, count, students[i].departement) != -1){
            continue;
        }

        strcpy(group[count].departement, students[i].departement);
        group[count].moyenne = students[i].note;
        int countDepartment = 1;
        for(int j=0; j<counter; j++){
            if(students[i].numero != students[j].numero && strcmp(students[i].departement, students[j].departement) == 0){
                group[count].moyenne += students[j].note;
                countDepartment++;
            }    
        }
        group[count].moyenne /= countDepartment;
        univmoyenne +=  group[count++].moyenne;
    }

    univmoyenne /= count;
    for(int i=0; i<count; i++){
        printf("Department : %s | Moyenne generale : %.2f\n", group[i].departement, group[i].moyenne);
    }
    printf("Moyenne generale de l'universite entiere : %.2f\n", univmoyenne);
}

//Rechercher un étudiant par son nom.
void findByName(){
    char nom[50], prenom[50];
    printf("Entrer le nom : ");
    scanf("%s", nom);
    printf("Entrer le prenom : ");
    scanf("%s", prenom);
    int found = 0;
    for(int i=0; i<counter; i++){
        
        if(strcmp(students[i].prenom, prenom) == 0 && strcmp(students[i].nom, nom) == 0){
            printf("Numero : %d\nNom : %s\nPrenom : %s\nDate de naissance : %d/%d/%d\nDepartement : %s\nNote generale : %.2f\n", students[i].numero, students[i].nom, students[i].prenom, students[i].birthday.jour, students[i].birthday.mois, students[i].birthday.annee, students[i].departement, students[i].note);
            found = 1;
        }
    }
    if(found == 0)
        printf("L'etudiant n'existe pas !\n");
}

//Afficher la liste des étudiants inscrits dans un département spécifique
void findByDepartment(){
    char departement[100];
    printf("Entrer le departement : ");
    scanf("%s", departement);

    int found = 0;
    for(int i=0; i<counter; i++){
        if(strcmp(students[i].departement, departement) == 0){
            printf("Numero : %d\nNom : %s\nPrenom : %s\nDate de naissance : %d/%d/%d\nDepartement : %s\nNote generale : %.2f\n", students[i].numero, students[i].nom, students[i].prenom, students[i].birthday.jour, students[i].birthday.mois, students[i].birthday.annee, students[i].departement, students[i].note);
            if(i != counter-1)
                printf("-----------------------------------------------------------------\n");
            found = 1;
        }
    }

    if(found == 0)
        printf("Il n'y a aucun etudiant dans ce departement !\n");
}

//sooooooooooooooooooorting

//alpha

//top3
void top3(Student list[]){
    for(int i=0; i<counter; i++){
        printf("Numero : %d\nNom : %s\nPrenom : %s\nDate de naissance : %d/%d/%d\nDepartement : %s\nNote generale : %.2f\n", list[i].numero, list[i].nom, list[i].prenom, list[i].birthday.jour, list[i].birthday.mois, list[i].birthday.annee, list[i].departement, list[i].note);
        if(i == 2)
            break;
        else
            printf("-----------------------------------------------------------------\n");
    }
}
void sortBy(char by[]){
    Student sorted[500];
    //copy
    for(int i=0; i<counter; i++){
        sorted[i] = students[i];
    }

    for(int i=0; i<counter; i++){
        for(int j=0; j<counter-i-1; j++){
            if(strcmp(by, "alpha") == 0){
                if(strcmp(sorted[j].nom, sorted[j+1].nom) > 0){
                    Student tmp = sorted[j];
                    sorted[j] = sorted[j+1];
                    sorted[j+1] = tmp;
                }
            }else{
                //moyenne
                if(sorted[j].note < sorted[j+1].note){
                    Student tmp = sorted[j];
                    sorted[j] = sorted[j+1];
                    sorted[j+1] = tmp;
                }
            }
        }
    }
    if(strcmp(by, "alpha") == 0 || strcmp(by, "moyenne") == 0){
        afficher(sorted, 0);
    }else if(strcmp(by, "top3") == 0){
        top3(sorted);
    }else{
        afficher(sorted, 10);
    }
}

//statistique



//Afficher le nombre d'étudiants dans chaque département.
void nombreEtudiantParDepartement(int seuil){
    Group1 group[500];
    int count = 0;
    for(int i=0; i<counter; i++){
        if(findInGroupDepartment1(group, count, students[i].departement) != -1){
            continue;
        }

        strcpy(group[count].departement, students[i].departement);
        group[count].nombre = students[i].note >= seuil ? 1 : 0;
        for(int j=0; j<counter; j++){
            if(students[i].numero != students[j].numero && strcmp(students[i].departement, students[j].departement) == 0){
                if(students[j].note >= seuil)
                    group[count].nombre++;
            }    
        }
        count++;
    }

    for(int i=0; i< count; i++){
        printf("Departement : %s, nombre d'etudiants : %d\n", group[i].departement, group[i].nombre);
    }
}

void main(){
    system("cls");
    system("color 3");
    int choix = 0;  
    char souschoix;
    
    do{
        printf("#####################################################################################\n");
        printf("#                                                                                   #\n");
        printf("#                     Gestion des etudiants dans une universite                     #\n");
        printf("#                                                                                   #\n");
        printf("#####################################################################################\n\n");
        printf("0- Exit\n");
        printf("1- Ajouter un etudiant\n");
        printf("2- Afficher la liste des etudiants\n");
        printf("3- Modifier un etudiant\n");
        printf("4- Supprimer un etudiant\n");
        printf("5- Calculer la moyenne generale de chaque departement et de l'universite entiere\n");
        printf("6- Rechercher un etudiant :\n");
        printf("  a- Rechercher un etudiant par son nom\n");
        printf("  b- La liste des etudiants inscrits dans un departement specifique\n");
        printf("7- Trier un etudiant :\n");
        printf("  a- Tri alphabetique des etudiants par nom\n");
        printf("  b- Tri des etudiants par moyenne, du plus haut au plus bas\n");
        printf("  c- Tri des etudiants selon leur statut de reussite\n");
        printf("8- Statistiques :\n\n");
        printf("Entrez votre choix :\n-");
        scanf("%d", &choix);

        switch(choix){
            case 1:
                ajouter();
            break;
            case 2:
                afficher(students, 0);
            break;
            case 3:
                modifier();
            break;
            case 4:
                supprimer();
            break;
            case 5:
                moyennegenerale();
            break;
            case 6:                
                while(1){
                    int isValid = 1;
                    printf("Entrer votre sous choix (a ou b) :\n-");
                    scanf(" %c", &souschoix);
                    switch(souschoix){
                        case 'a':
                            findByName();
                        break;
                        case 'b':
                            findByDepartment();
                        break;
                        default:
                            printf("Sous-choix non valide, saisissez 'a' ou 'b' !\n");
                            isValid = 0;
                        break;
                    }

                    if(isValid == 1)
                        break;
                }
            break;
            case 7:
                while(1){
                    int isValid = 1;
                    printf("Entrer votre sous choix (a ou b ou c) :\n-");
                    scanf(" %c", &souschoix);
                    switch(souschoix){
                        case 'a':
                            sortBy("alpha");
                        break;
                        case 'b':
                            sortBy("moyenne");
                        break;
                        case 'c':
                            sortBy("reussite");
                        break;
                        default:
                            printf("Sous-choix non valide, saisissez 'a' ou 'b' ou 'c' !\n");
                            isValid = 0;
                        break;
                    }

                    if(isValid == 1)
                        break;
                }
            break;
            case 8:
                printf("--------------------------------- Le nombre total d'etudiants inscrits ---------------------------------\n\n");
                printf("=========> %d\n\n", counter);

                printf("--------------------------------- Le nombre d'etudiants dans chaque departement ---------------------------------\n\n");
                nombreEtudiantParDepartement(0);

                printf("\n--------------------------------- Les etudiants ayant une moyenne generale superieure a un certain seuil ---------------------------------\n\n");

                int seuil = 0;
                printf("Entrer le seuil : \n-");
                scanf("%d", &seuil);
                afficher(students, seuil);

                printf("\n--------------------------------- Les 3 etudiants ayant les meilleures notes ---------------------------------\n\n");
                sortBy("top3");

                printf("\n--------------------------------- Afficher le nombre d'etudiants ayant reussi dans chaque departement ---------------------------------\n\n");
                nombreEtudiantParDepartement(10);

            break;
            default:
                if(choix != 0){
                    printf("choisir un valid nombre !\n");
                }
            break;
        }
        

        system("pause");
        system("cls");
    }while(choix);
}