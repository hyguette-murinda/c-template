#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
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

void toLowerCase(string& str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void addStudent(string name, int age, vector<string> courses) {
    Student* newStudent = new Student(name, age);
    newStudent->courses = courses;
    newStudent->next = head;
    head = newStudent;

    ofstream file("students.csv", ios::app);
    if (file.is_open()) {
        file << newStudent->name << "," << newStudent->age;
        for (const auto& course : newStudent->courses) {
            file << "," << course;
        }
        file << endl;
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
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

bool isCourseNameExists(const vector<Course>& courses, const string& courseName) {
    string lowerCaseCourseName = courseName;
    toLowerCase(lowerCaseCourseName);
    for (const auto& course : courses) {
        string existingCourseName = course.courseName;
        toLowerCase(existingCourseName);
        if (existingCourseName == lowerCaseCourseName) {
            return true;
        }
    }
    return false;
}

void addCourse(vector<Course>& courses, const string& courseName, bool isAvailable) {
    if (isCourseNameExists(courses, courseName)) {
        cout << "Course " << courseName << " already exists." << endl;
        return;
    }

    string lowerCaseCourseName = courseName;
    toLowerCase(lowerCaseCourseName);
    courses.push_back(Course(lowerCaseCourseName, isAvailable));

    ofstream file("courses.csv", ios::app);
    if (file.is_open()) {
        file << lowerCaseCourseName << "," << isAvailable << endl;
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

void loadCourses(vector<Course>& courses, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string courseName, availableStr;
            bool isAvailable;

            getline(ss, courseName, ',');
            getline(ss, availableStr, ',');
            isAvailable = (availableStr == "1");

            courses.push_back(Course(courseName, isAvailable));
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

bool isCourseAvailable(const vector<Course>& courses, const string& courseName) {
    string lowerCaseCourseName = courseName;
    toLowerCase(lowerCaseCourseName);
    for (const auto& course : courses) {
        if (course.courseName == lowerCaseCourseName) {
            return course.isAvailable;
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

void searchStudentByName(const string& filename, const string& studentName) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        bool found = false;
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

            if (name == studentName) {
                cout << "Name: " << name << ", Age: " << age << ", Courses: ";
                for (const auto& course : courses) {
                    cout << course << " ";
                }
                cout << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student not found." << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

void displayAvailableCourses(const vector<Course>& courses) {
    cout << "Available courses:" << endl;
    for (const auto& course : courses) {
        if (course.isAvailable) {
            cout << course.courseName << endl;
        }
    }
}

int main() {
    vector<Course> courses;
    loadCourses(courses, "courses.csv");

    char choice;
    do {
        cout << "Menu:\n1. Add new course\n2. Add new student\n3. Display saved students\n4. Search student by name\n5. Display available courses\n6. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == '1') {
            string courseName;
            char availability;
            bool isAvailable;
            cout << "Enter course name: ";
            cin >> ws;
            getline(cin, courseName);
            cout << "Is the course available? (y/n): ";
            cin >> availability;
            isAvailable = (availability == 'y');
            addCourse(courses, courseName, isAvailable);

        } else if (choice == '2') {
            string name;
            int age;
            vector<string> studentCourses;
            string course;

            cout << "Enter student name: ";
            cin >> ws;
            getline(cin, name);

            cout << "Enter student age: ";
            cin >> age;

            cout << "Enter courses (type 'done' to finish): ";
            while (true) {
                cin >> course;
                if (course == "done") break;
                studentCourses.push_back(course);
            }

            enrollStudent(courses, name, age, studentCourses);

        } else if (choice == '3') {
            cout << "Displaying students from CSV file:" << endl;
            displayStudentsFromCSV("students.csv");

        } else if (choice == '4') {
            string studentName;
            cout << "Enter student name to search: ";
            cin >> ws;
            getline(cin, studentName);
            searchStudentByName("students.csv", studentName);

        } else if (choice == '5') {
            displayAvailableCourses(courses);
        }

    } while (choice != '6');

    return 0;
}








