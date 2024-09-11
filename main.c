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
    printf("Entrer le numero de l'etudiant : \n-");
    scanf("%d", &numero);
    int index = findByNumero(numero);

    if(index == -1){
        printf("L'etudiant n'existe pas !\n");
        return -1;
    }
    return numero;
}

//Supprimer les informations d'un étudiant en fonction de son numéro unique
void supprimer(){
    int index = getItemBeforeUD();
    if(index != -1){
        char confirm;
        printf("Confirmez que vous souhaitez supprimer en tapant « o » et annulez « n »\n-");
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
        scanf("%f", student.note);

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
    char nom[50], prenom[50], full[100];
    printf("Entrer le nom : ");
    scanf("%s", nom);
    printf("Entrer le prenom : ");
    scanf("%s", prenom);
    int found = 0;
    for(int i=0; i<counter; i++){
        strcpy(full, students[i].nom);
        if(strcmp(strcat(full, students[i].prenom), strcat(nom, prenom)) == 0){
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
            found = 1;
        }
    }

    if(found == 0)
        printf("Il n'y a aucun étudiant dans ce département !\n");
}

//sooooooooooooooooooorting

//alpha

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
    if(strcmp(by, "moyenne") != 0){
        afficher(sorted, 0);
    }else if(strcmp(by, "top3") != 0){
        afficher(sorted, 3);
    }else{
        afficher(sorted, 10);
    }
}

//statistique

//top3
void top3(Student list[], int seuil){
    for(int i=0; i<counter; i++){
        printf("Numero : %d\nNom : %s\nPrenom : %s\nDate de naissance : %d/%d/%d\nDepartement : %s\nNote generale : %.2f\n", list[i].numero, list[i].nom, list[i].prenom, list[i].birthday.jour, list[i].birthday.mois, list[i].birthday.annee, list[i].departement, list[i].note);
        if(i == 2)
            break;
    }
}


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
nombreEtudiantParDepartement(10);
}