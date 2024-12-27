#include <stdio.h>
#include <stdlib.h>
typedef struct { int id; char name[20]; float salary; } Employee;
void manageEmployee(FILE *f, int action) {
    Employee e;
    if (action == 1) {
        printf("Enter ID, Name, Salary: ");
        scanf("%d %19s %f", &e.id, e.name, &e.salary);
    } else {
        printf("Enter ID to view: ");
        scanf("%d", &e.id);
        fseek(f, (e.id - 1) * sizeof(Employee), SEEK_SET);
        if (fread(&e, sizeof(Employee), 1, f) && e.id)
            printf("ID: %d, Name: %s, Salary: %.2f\n", e.id, e.name, e.salary);
        else
            printf("Not found.\n");
        return;
    }
    fseek(f, (e.id - 1) * sizeof(Employee), SEEK_SET);
    fwrite(&e, sizeof(Employee), 1, f);
}
int main() {
    FILE *f = fopen("employees.dat", "rb+");
    if (!f) f = fopen("employees.dat", "wb+");
    if (!f) return perror("File error"), 1;
    int choice;
    do {
        printf("1.Add 2.View 3.Exit: ");
        scanf("%d", &choice);
        if (choice == 1 || choice == 2) manageEmployee(f, choice);
    } while (choice != 3);
    fclose(f);
    return 0;
}
