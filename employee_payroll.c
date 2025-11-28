#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee {
    int id;
    char name[50];
    char designation[30];
    float basicSalary;
    int hoursWorked;
};

int count = 0;
struct Employee emp[100]; // max 100 employees

// Function prototypes
void loadFromFile();
void saveToFile();
void addEmployee();
void displayEmployees();
void calculateSalary();
void searchEmployee();
void updateEmployee();
void deleteEmployee();
void sortEmployeesBySalary();

int main() {
    int choice;
    loadFromFile();  // Load employees from file at start

    do {
        printf("\n--- Employee Payroll System ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Calculate Salary\n");
        printf("4. Search Employee\n");
        printf("5. Update Employee\n");
        printf("6. Delete Employee\n");
        printf("7. Sort Employees by Salary\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: calculateSalary(); break;
            case 4: searchEmployee(); break;
            case 5: updateEmployee(); break;
            case 6: deleteEmployee(); break;
            case 7: sortEmployeesBySalary(); break;
            case 8: 
                printf("Exiting...\n");
                saveToFile();  // Save employees to file before exit
                break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 8);

    return 0;
}

// --- File Handling Functions ---

void loadFromFile() {
    FILE *fp = fopen("employees.dat", "rb");
    if(fp != NULL) {
        while(fread(&emp[count], sizeof(struct Employee), 1, fp)) {
            count++;
        }
        fclose(fp);
    }
}

void saveToFile() {
    FILE *fp = fopen("employees.dat", "wb");
    if(fp != NULL) {
        fwrite(emp, sizeof(struct Employee), count, fp);
        fclose(fp);
    } else {
        printf("Error saving to file!\n");
    }
}

// --- Function definitions ---

void addEmployee() {
    printf("Enter Employee ID: ");
    scanf("%d", &emp[count].id);
    printf("Enter Name: ");
    scanf(" %[^\n]", emp[count].name);
    printf("Enter Designation: ");
    scanf(" %[^\n]", emp[count].designation);
    printf("Enter Basic Salary: ");
    scanf("%f", &emp[count].basicSalary);
    printf("Enter Hours Worked: ");
    scanf("%d", &emp[count].hoursWorked);
    count++;
    saveToFile(); // save after adding
    printf("Employee added successfully!\n");
}

void displayEmployees() {
    if(count == 0) {
        printf("No employees to display.\n");
        return;
    }
    printf("\n--- Employee List ---\n");
    for(int i=0; i<count; i++) {
        printf("ID: %d | Name: %s | Designation: %s | Basic Salary: %.2f | Hours Worked: %d\n",
               emp[i].id, emp[i].name, emp[i].designation, emp[i].basicSalary, emp[i].hoursWorked);
    }
}

void calculateSalary() {
    int id;
    printf("Enter Employee ID to calculate salary: ");
    scanf("%d", &id);
    for(int i=0; i<count; i++) {
        if(emp[i].id == id) {
            float overtime = 0;
            if(emp[i].hoursWorked > 40)
                overtime = (emp[i].hoursWorked - 40) * 100; // 100 per extra hour
            float totalSalary = emp[i].basicSalary + overtime;
            float tax = 0;
            if(totalSalary > 50000)
                tax = totalSalary * 0.10; // 10% tax
            totalSalary -= tax;
            printf("Total Salary for %s: %.2f (Overtime: %.2f, Tax: %.2f)\n",
                   emp[i].name, totalSalary, overtime, tax);
            return;
        }
    }
    printf("Employee not found!\n");
}

void searchEmployee() {
    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);
    for(int i=0; i<count; i++) {
        if(emp[i].id == id) {
            printf("ID: %d | Name: %s | Designation: %s | Basic Salary: %.2f | Hours Worked: %d\n",
                   emp[i].id, emp[i].name, emp[i].designation, emp[i].basicSalary, emp[i].hoursWorked);
            return;
        }
    }
    printf("Employee not found!\n");
}

void updateEmployee() {
    int id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);
    for(int i=0; i<count; i++) {
        if(emp[i].id == id) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", emp[i].name);
            printf("Enter new Designation: ");
            scanf(" %[^\n]", emp[i].designation);
            printf("Enter new Basic Salary: ");
            scanf("%f", &emp[i].basicSalary);
            printf("Enter new Hours Worked: ");
            scanf("%d", &emp[i].hoursWorked);
            saveToFile(); // save after updating
            printf("Employee updated successfully!\n");
            return;
        }
    }
    printf("Employee not found!\n");
}

void deleteEmployee() {
    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);
    for(int i=0; i<count; i++) {
        if(emp[i].id == id) {
            for(int j=i; j<count-1; j++)
                emp[j] = emp[j+1];
            count--;
            saveToFile(); // save after deletion
            printf("Employee deleted successfully!\n");
            return;
        }
    }
    printf("Employee not found!\n");
}

void sortEmployeesBySalary() {
    if(count == 0) {
        printf("No employees to sort.\n");
        return;
    }
    for(int i=0; i<count-1; i++) {
        for(int j=i+1; j<count; j++) {
            float salary_i = emp[i].basicSalary + (emp[i].hoursWorked > 40 ? (emp[i].hoursWorked-40)*100 : 0);
            float salary_j = emp[j].basicSalary + (emp[j].hoursWorked > 40 ? (emp[j].hoursWorked-40)*100 : 0);
            if(salary_i < salary_j) {
                struct Employee temp = emp[i];
                emp[i] = emp[j];
                emp[j] = temp;
            }
        }
    }
    printf("Employees sorted by total salary (descending):\n");
    displayEmployees();
}
