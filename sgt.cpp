#include <iostream>
#include <vector>
#include <algorithm> // for sorting
#include <iomanip>   // for setprecision
#include <cmath>     // for floor

using namespace std;

// Define a structure for student information
struct Student {
    string name;
    int id;
    double testGrade;       // out of 80
    double assignmentGrade; // out of 20

    // Constructor to initialize name, id, and grades
    Student(string n, int i, double t = 0.0, double a = 0.0) : name(n), id(i), testGrade(t), assignmentGrade(a) {}

    // Function to calculate the total grade (sum of test and assignment grades)
    double calculateTotalGrade() const {
        return testGrade + assignmentGrade;
    }
};

// Function to check if a student with given ID already exists
bool studentExists(const vector<Student>& students, int id) {
    auto it = find_if(students.begin(), students.end(),
                      [id](const Student& student) { return student.id == id; });
    return it != students.end();
}

// Function to calculate class average of total grades
double calculateClassAverage(const vector<Student>& students) {
    double sum = 0.0;
    int count = 0;
    for (const auto& student : students) {
        sum += student.calculateTotalGrade();
        count++;
    }
    if (count > 0) {
        return sum / count;
    }
    return 0.0;
}

// Function to display top 3 students by total grades
void displayTopThree(const vector<Student>& students) {
    vector<Student> sortedStudents = students; // make a copy
    sort(sortedStudents.begin(), sortedStudents.end(),
         [](const Student& a, const Student& b) {
             return a.calculateTotalGrade() > b.calculateTotalGrade();
         });

    cout << "Top 3 Students:\n";
    cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Test Grade" << setw(15) << "Assignment Grade" << setw(15) << "Total Grade\n";
    cout << setw(5) << "------------------------------------------------------------------\n";
    for (int i = 0; i < min(3, static_cast<int>(sortedStudents.size())); ++i) {
        cout << setw(5) << sortedStudents[i].id << setw(15) << sortedStudents[i].name << setw(15) << fixed << setprecision(2) << sortedStudents[i].testGrade
             << setw(15) << fixed << setprecision(2) << sortedStudents[i].assignmentGrade << setw(15) << fixed << setprecision(2) << sortedStudents[i].calculateTotalGrade() << "\n";
    }
}

// Function to display ranges of total grades and number of students in each range
void displayGradeRanges(const vector<Student>& students) {
    const int numRanges = 10;
    vector<int> rangeCount(numRanges, 0);

    // Count grades in each range
    for (const auto& student : students) {
        int rangeIndex = static_cast<int>(floor(student.calculateTotalGrade() / 10));
        if (rangeIndex < numRanges) {
            rangeCount[rangeIndex]++;
        }
    }

    // Display ranges and number of students in each range
    cout << "Total Grade Ranges:\n";
    for (int i = 0; i < numRanges; ++i) {
        int rangeStart = i * 10;
        int rangeEnd = rangeStart + 9;
        if (i == numRanges - 1) {
            rangeEnd = 100;
        }
        cout << setw(5) << rangeStart << "-" << setw(5) << rangeEnd << ": " << rangeCount[i] << " students\n";
    }
}

// Function to add a new student with initial test and assignment grades
void addStudent(vector<Student>& students) {
    string name;
    int id;
    double testGrade, assignmentGrade;

    // Prompt for student information
    cout << "Enter student name: ";
    cin >> name;

    // Validate and prompt for unique student ID
    bool idExists;
    do {
        idExists = false;
        cout << "Enter student ID (must be unique): ";
        cin >> id;
        if (studentExists(students, id)) {
            cout << "Error: Student with ID " << id << " already exists. Please choose another ID.\n";
            idExists = true;
        }
    } while (idExists);

    cout << "Enter test grade (out of 80) for " << name << ": ";
    cin >> testGrade;
    cout << "Enter assignment grade (out of 20) for " << name << ": ";
    cin >> assignmentGrade;

    // Create new student with test and assignment grades
    students.emplace_back(name, id, testGrade, assignmentGrade);
}

// Function to display specific student info with grades
void showStudentInfo(const vector<Student>& students, int id) {
    // Find the student by ID
    auto it = find_if(students.begin(), students.end(),
                      [id](const Student& student) { return student.id == id; });

    if (it != students.end()) {
        cout << "Student ID: " << it->id << ", Name: " << it->name << "\n";
        cout << "Test Grade: " << fixed << setprecision(2) << it->testGrade << "\n";
        cout << "Assignment Grade: " << fixed << setprecision(2) << it->assignmentGrade << "\n";
        cout << "Total Grade: " << fixed << setprecision(2) << it->calculateTotalGrade() << "\n";
    } else {
        cout << "Student with ID " << id << " not found.\n";
    }
}

// Function to show all students with their info and grades
void showAllStudents(const vector<Student>& students) {
    cout << "All Students:\n";
    cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Test Grade" << setw(15) << "Assignment Grade" << setw(15) << "Total Grade\n";
    cout << setw(5) << "------------------------------------------------------------------\n";
    for (const auto& student : students) {
        cout << setw(5) << student.id << setw(15) << student.name << setw(15) << fixed << setprecision(2) << student.testGrade
             << setw(15) << fixed << setprecision(2) << student.assignmentGrade << setw(15) << fixed << setprecision(2) << student.calculateTotalGrade() << "\n";
    }
}

int main() {
    vector<Student> students;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add a student\n";
        cout << "2. Show specific student info\n";
        cout << "3. Show all student info\n";
        cout << "4. Show class average\n";
        cout << "5. Show top 3 students\n";
        cout << "6. Show grade ranges of total grades\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                int id;
                cout << "Enter student ID: ";
                cin >> id;
                showStudentInfo(students, id);
                break;
            case 3:
                showAllStudents(students);
                break;
            case 4:
                cout << "Class Average of Total Grades: " << fixed << setprecision(2) << calculateClassAverage(students) << "\n";
                break;
            case 5:
                displayTopThree(students);
                break;
            case 6:
                displayGradeRanges(students);
                break;
            case 7:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}
