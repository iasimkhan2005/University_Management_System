#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

// Forward declaration of Courses class
class Courses;

class Student
{
private:
    string studentId;
    string name, email;
    vector<Courses *> courseEnrolled;

public:
    Student(){}; // Default constructor
    Student(string studentId, string name, string email) : studentId(studentId), name(name), email(email) {}

    string getID() { return studentId; }
    string getName() { return name; }
    string getEmail() { return email; }

    friend void enrollCourse(Student &student, Courses *course);
    friend void dropCourse(Student &student, Courses *course);
    friend void viewCourse(Student &student);
};
class Teacher
{
private:
    string Teacher_Id;
    string Teacher_name, Teacher_email;
    vector<Courses *> Teacher_course;

public:
    Teacher(string Teacher_Id, string Teacher_name, string Teacher_email) : Teacher_Id(Teacher_Id), Teacher_name(Teacher_name), Teacher_email(Teacher_email) {}

    string getID() { return Teacher_Id; }
    string getName() { return Teacher_name; }
    string getEmail() { return Teacher_email; }
    void assignCourse(Courses *course)
    {
        Teacher_course.push_back(course);
    }
    void removeCourse(Courses *course)
    {
        auto it = find(Teacher_course.begin(), Teacher_course.end(), course);
        if (it != Teacher_course.end())
        {
            Teacher_course.erase(it);
        }
    }
    vector<Courses *> viewCourse() const
    {
        return Teacher_course;
    }
};
class Courses
{
private:
    string courseCode;
    string courseName;
    Student *student;
    Teacher *teacher;

public:
    Courses(string courseCode, string courseName, Teacher *teacher) : courseCode(courseCode), courseName(courseName), teacher(teacher) {}
    string getCode() { return courseCode; }
    string getName() { return courseName; }
    Teacher *getTeacher() { return teacher; }
    string getCourseName();
    void addStudent(vector<Student *> &students);
    void removeStudent(Student *student);
    void viewStudent();
};

void enrollCourse(Student &student, Courses *course)
{
    student.courseEnrolled.push_back(course);
}

void dropCourse(Student &student, Courses *course)
{
    student.courseEnrolled.erase(find(student.courseEnrolled.begin(), student.courseEnrolled.end(), course));
}

void viewCourse(Student &student)
{
    for (int i = 0; i < student.courseEnrolled.size(); i++)
    {
        cout << student.courseEnrolled[i]->getCourseName() << endl;
    }
}

// Implementations for Courses methods

string Courses::getCourseName()
{
    return courseName;
}

void Courses::removeStudent(Student *student)
{
    if (this->student == student)
    {
        delete this->student;
        this->student = nullptr;
    }
    else
    {
        cout << "Student not found" << endl;
    }
}

void Courses::viewStudent()
{
    if (this->student == nullptr)
    {
        cout << "No student enrolled" << endl;
    }
    else
    {
        cout << this->student->getName() << endl;
    }
}
void loadDataFromFile(vector<Student *> &students, vector<Teacher *> &teachers, vector<Courses *> &courses)
{
    ifstream studentFile("students.txt");
    ifstream teacherFile("teachers.txt");
    ifstream courseFile("courses.txt");

    // Load students
    string studentID, studentName, studentEmail;
    while (studentFile >> studentID >> studentName >> studentEmail)
    {
        students.push_back(new Student(studentID, studentName, studentEmail));
    }
    studentFile.close();

    // Load teachers
    string teacherID, teacherName, teacherEmail;
    while (teacherFile >> teacherID >> teacherName >> teacherEmail)
    {
        teachers.push_back(new Teacher(teacherID, teacherName, teacherEmail));
    }
    teacherFile.close();

    // Load courses
    string courseCode, courseName, teacher_ID;

    while (courseFile >> courseCode >> courseName >> teacher_ID)
    {
        Teacher *teacherPtr = nullptr;
        for (Teacher *teacher : teachers)
        {
            if (teacher->getID() == teacher_ID)
            {
                teacherPtr = teacher;
                break;
            }
        }
        if (teacherPtr != nullptr)
        {
            courses.push_back(new Courses(courseCode, courseName, teacherPtr));
            teacherPtr->assignCourse(courses.back());
        }
    }
    courseFile.close();
}
void addStudent(vector<Student *> &students)
{
    string studentID, studentName, studentEmail;
    cout << "Enter student ID: ";
    cin >> studentID;
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, studentName);
    cout << "Enter student email: ";
    cin >> studentEmail;
    students.push_back(new Student(studentID, studentName, studentEmail));
}

void addTeacher(vector<Teacher *> &teachers)
{
    string teacherID, teacherName, teacherEmail;
    cout << "Enter teacher ID: ";
    cin >> teacherID;
    cout << "Enter teacher name: ";
    cin.ignore();
    getline(cin, teacherName);
    cout << "Enter teacher email: ";
    cin >> teacherEmail;
    teachers.push_back(new Teacher(teacherID, teacherName, teacherEmail));
}
void addCourse(vector<Courses *> &courses, const vector<Teacher *> &teachers)
{
    string courseCode, courseName, teacherID;
    int maxCapacity;
    cout << "Enter course code: ";
    cin >> courseCode;
    cout << "Enter course name: ";
    cin.ignore();
    getline(cin, courseName);
    cout << "Enter teacher ID: ";
    cin >> teacherID;

    Teacher *teacherPtr = nullptr;
    for (Teacher *teacher : teachers)
    {
        if (teacher->getID() == teacherID)
        {
            teacherPtr = teacher;
            break;
        }
    }
    if (teacherPtr != nullptr)
    {
        courses.push_back(new Courses(courseCode, courseName, teacherPtr));
        teacherPtr->assignCourse(courses.back());
    }
    else
    {
        cout << "Teacher with ID " << teacherID << " not found." << endl;
    }
}
void saveDataToFile(vector<Student *> &students, vector<Teacher *> &teachers, vector<Courses *> &courses)
{
    ofstream studentFile("students.txt");
    ofstream teacherFile("teachers.txt");
    ofstream courseFile("courses.txt");

    for (const auto &student : students)
    {
        studentFile << student->getID() << " " << student->getName() << " " << student->getEmail() << endl;
    }
    studentFile.close();

    for (const auto &teacher : teachers)
    {
        teacherFile << teacher->getID() << " " << teacher->getName() << " " << teacher->getEmail() << endl;
    }
    teacherFile.close();

    for (const auto &course : courses)
    {
        courseFile << course->getCode() << " " << course->getName() << " " << course->getTeacher()->getID() << " "
                   << endl;
    }
    courseFile.close();
}
int main()
{
    Student stu_obj;

    vector<Student *> students;
    vector<Teacher *> teachers;
    vector<Courses *> courses;

    // Load data from files
    loadDataFromFile(students, teachers, courses);

    char choice;
    do
    {
        cout << "---------- MENU ----------" << endl;
        cout << "1. Student" << endl;
        cout << "2. Teacher" << endl;
        cout << "3. Course" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        char option;
        switch (choice)
        {
        case '1':
            Courses *course_obj;
            cout << "---------- STUDENT ----------\n";
            cout << "a. Add Student\n";
            cout << "b. Enroll Course\n";
            cout << "c. Drop Course\n";
            cout << "d. View Courses\n";
            cout << "e. Exit\n";
            cin >> option;

            switch (option)
            {
            case 'a':
                addStudent(students);
                break;

            case 'b':
                enrollCourse(stu_obj, course_obj);
                break;

            case 'c':
                dropCourse(stu_obj, course_obj);
                break;

            case 'd':
                viewCourse(stu_obj);
                break;

            case 'e':
                return 0;

            default:
                cout << "Invalid Option! Try Again.\n";
                break;
            }
            break;
        case '2':
            cout << "---------- TEACHER ----------\n";
            cout << "a. Add Teacher\n";
            cout << "b. Assign Course\n";
            cout << "c. Remove Course\n";
            cout << "d. View Courses\n";
            cout << "e. Exit\n";
            cin >> option;

            // switch (option)
            // {
            // case 'a':
            //     addTeacher(teachers);
            //     break;

            // case 'b':
            //     assignCourse(courses, teachers);
            //     break;

            // case 'c':
            //     removeCourse(teachers, courses);
            //     break;

            // case 'd':
            //     viewCourse();
            //     break;

            // case 'e':
            //     return 1; // Return to main menu

            // default:
            //     cout << "Unknown option\n";
            //     break;
            // }
            break;
        case '3':
            cout << "---------- COURSES ----------" << endl;
            cout << "a. Add Course\n";
            cout << "b. Remove Course\n";
            cout << "c. View Students\n";
            cout << "d. Exit\n";
            cin >> option;

            // switch (option)
            // {
            // case 'a':
            //     addCourse(courses, teachers);
            //     break;

            // case 'b':
            //     removeCourse(courses, students);
            //     break;

            // case 'c':
            //     viewStudent();
            //     break;

            // case 'd':
            //     return 2; // Return to main menu

            // default:
            //     cout << "Unknown option\n";
            //     break;
            // }
            break;

        case '4':
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != '4');

    // Save data back to files
    saveDataToFile(students, teachers, courses);

    system("pause");
    return 0;
}
