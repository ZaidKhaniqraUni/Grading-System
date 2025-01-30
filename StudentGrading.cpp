#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int rollNumber;
    float marks;

public:
    Student(string name, int rollNumber, float marks) {
        this->name = name;
        this->rollNumber = rollNumber;
        this->marks = marks;
    }

    void displayStudent() {
        cout << "Name: " << name << "\nRoll Number: " << rollNumber << "\nMarks: " << marks << "\nGrade: " << calculateGrade() << endl;
    }

    string calculateGrade() {
        if (marks >= 90) return "A";
        else if (marks >= 75) return "B";
        else if (marks >= 50) return "C";
        else return "F";
    }

    void saveToFile(fstream& outFile) {
        outFile << name << "\n" << rollNumber << "\n" << marks << endl;
    }

    static Student loadFromFile(fstream& inFile) {
        string name;
        int rollNumber;
        float marks;
        getline(inFile, name);
        inFile >> rollNumber >> marks;
        inFile.ignore();
        return Student(name, rollNumber, marks);
    }
};

void addStudent() {
    string name;
    int rollNumber;
    float marks;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Roll Number: ";
    cin >> rollNumber;
    cout << "Enter Marks: ";
    cin >> marks;

    Student student(name, rollNumber, marks);
    fstream outFile("students.txt", ios::app);
    if (outFile.is_open()) {
        student.saveToFile(outFile);
        cout << "Student record added successfully!\n";
    } else {
        cout << "Error opening file!\n";
    }
    outFile.close();
}

void displayStudents() {
    fstream inFile("students.txt", ios::in);
    if (inFile.is_open()) {
        while (!inFile.eof()) {
            Student student = Student::loadFromFile(inFile);
            student.displayStudent();
            cout << "----------------------------------\n";
        }
    } else {
        cout << "Error opening file!\n";
    }
    inFile.close();
}

int main() {
    int choice;
    while (true) {
        cout << "1. Add Student\n2. Display All Students\n3. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            addStudent();
        } else if (choice == 2) {
            displayStudents();
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}
