#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <algorithm> // For transform function

using namespace std;

struct Course {
    string courseName;
    bool isAvailable;

    Course(string name, bool available) : courseName(name), isAvailable(available) {}
};

struct Student {
    string name;
    int age;
    vector<string> courses;
    Student* next;

    Student(string studentName, int studentAge) : name(studentName), age(studentAge), next(nullptr) {}
};

Student* head = nullptr;

void addStudent(string name, int age, vector<string> courses) {
    Student* newStudent = new Student(name, age);
    newStudent->courses = courses;
    newStudent->next = head;
    head = newStudent;
}

void displayStudentsFromCSV(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, ageStr, course;
            vector<string> courses;

            getline(ss, name, ',');
            getline(ss, ageStr, ',');
            int age = stoi(ageStr);

            while (getline(ss, course, ',')) {
                courses.push_back(course);
            }

            cout << "Name: " << name << ", Age: " << age << ", Courses: ";
            for (const auto& course : courses) {
                cout << course << " ";
            }
            cout << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

void saveToCSV(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        Student* temp = head;
        while (temp != nullptr) {
            file << temp->name << "," << temp->age;
            for (const auto& course : temp->courses) {
                file << "," << course;
            }
            file << endl;
            temp = temp->next;
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

bool isCourseAvailable(const vector<Course>& courses, const string& courseName) {
    string lowerCourseName = toLowerCase(courseName);
    for (const auto& course : courses) {
        if (toLowerCase(course.courseName) == lowerCourseName && course.isAvailable) {
            return true;
        }
    }
    return false;
}

void enrollStudent(const vector<Course>& courses, const string& name, int age, const vector<string>& studentCourses) {
    vector<string> validCourses;
    for (const auto& course : studentCourses) {
        if (isCourseAvailable(courses, course)) {
            validCourses.push_back(course);
        } else {
            cout << "Course " << course << " is not available." << endl;
        }
    }
    addStudent(name, age, validCourses);
}

void addNewStudent(const vector<Course>& courses) {
    string name;
    int age;
    vector<string> studentCourses;
    string course;

    cout << "Enter student name: ";
    cin >> ws; // To ignore leading whitespace
    getline(cin, name);

    cout << "Enter student age: ";
    while (!(cin >> age) || age <= 0) {
        cout << "Invalid input. Please enter a valid age: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter courses (type 'done' to finish): ";
    while (true) {
        cin >> course;
        if (course == "done") break;
        studentCourses.push_back(course);
    }

    enrollStudent(courses, name, age, studentCourses);
    cout << "Student enrolled successfully!" << endl;
}

void displayMenu() {
    cout << "\n=== Student Enrollment System ===" << endl;
    cout << "1. Add a new student" << endl;
    cout << "2. Display students from CSV file" << endl;
    cout << "3. Save students to CSV file" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    vector<Course> courses = {
        Course("Math", true),
        Course("Science", true),
        Course("History", false),
        Course("Art", true)
    };

    char choice;
    bool exitProgram = false;

    while (!exitProgram) {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case '1':
                addNewStudent(courses);
                break;
            case '2':
                cout << "Displaying students from CSV file:" << endl;
                displayStudentsFromCSV("students.csv");
                break;
            case '3':
                exitProgram = true;
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
