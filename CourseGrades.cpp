/*
Course Grades program:

What it does: Reads users file and stores information inside struct object. Displays sudents name, id, and calculates avarage score 
&& letter grade for each student.


How it works: struct Student - creats a struct of students info: name, id, scores, avarage, grade.

              Student *getData() - stores the information for struct from the file provided by user.

              calcAverage() - calculates avarage grade for student scores.

              getLetterGrade() - turns the avarage score into a letter grade.

             print() - prints the table with all calculated info.

             void cleanup() - Frees dynamically allocated arrays for each student

*/

#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <iomanip>
/**/
struct Student {
    string name;
    int id;
    double* scores;   // dynamically allocated array for test scores
    double average;
    char grade;
};

Student *getData(ifstream& file, int& studentCnt, int& testsCnt);

void calcAverage(Student students[], int studentCnt, int testsCnt);

char getLetterGrade(double average);

void print(const Student students[], int studentCnt);

void cleanup(Student students[], int studentCnt);


int main()
{
    ifstream inFile("student_data.txt");  

    if (!inFile) {
        cout << "Error: Could not open student_data.txt\n";
        return 1;
    }

    int studentCnt;
    int testsCnt;

    Student *students = getData(inFile, studentCnt, testsCnt);
    inFile.close();

    calcAverage(students, studentCnt, testsCnt);
    print(students, studentCnt);
    cleanup(students, studentCnt);

    return 0;
}


Student* getData(ifstream& file, int& studentCnt, int& testsCnt) {
    file >> studentCnt >> testsCnt;
    Student* students = new Student[studentCnt];

    for (int i = 0; i < studentCnt; i++) {
        file >> students[i].name >> students[i].id;
        students[i].scores = new double[testsCnt];

        for (int j = 0; j < testsCnt; j++) {
            file >> students[i].scores[j];
        }
    
    }

    return students;
}

void calcAverage(Student students[], int studentCnt, int testsCnt) {
    for (int i = 0; i < studentCnt; i++) {
        double total = 0.0;
        for (int j = 0; j < testsCnt; j++) {
            total += students[i].scores[j];
        }
        students[i].average = total / testsCnt;
        students[i].grade = getLetterGrade(students[i].average);
    }
}

char getLetterGrade(double average) {
    if (average >= 90) return 'A';
    else if (average >= 80) return 'B';
    else if (average >= 70) return 'C';
    else if (average >= 60) return 'D';
    else return 'F';
}

void print(const Student students[], int studentCnt) {
    cout << left << setw(12) << "Student"
        << setw(8) << "ID"
        << setw(10) << "Average"
        << "Grade" << endl;

    cout << "--------------------------------\n";

    for (int i = 0; i < studentCnt; i++) {
        cout << left << setw(12) << students[i].name
            << setw(8) << students[i].id
            << setw(10) << fixed << setprecision(1) << students[i].average
            << students[i].grade << endl;
    }
}

void cleanup(Student students[], int studentCnt) {
    for (int i = 0; i < studentCnt; i++) {
        delete[] students[i].scores;
    }
    delete[] students;
}