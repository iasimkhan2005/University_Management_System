#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Forward declaration of Courses class
class Courses;

class Student
{
private:
    int studentId;
    string name, email;
    vector<Courses*> courseEnrolled;

public:
    Student();

    void enrollCourse(Courses* course);
    void dropCourse(Courses* course);
    string getName() const;
    void viewCourse();
};

class Courses
{
private:
    int courseCode;
    string courseName;
    Student* student;

public:
    Courses();
    string getCourseName() const;
    void addStudent(Student* student);
    void removeStudent(Student* student);
    void viewStudent();
};

// Implementations for Student methods
Student::Student()
{
    cout << "Enter Student ID: ";
    cin >> studentId;
    cin.ignore();
    cout << "Enter Student Name: ";
    getline(cin, name);
    cout << "Enter Email Address: ";
    cin >> email;
}

void Student::enrollCourse(Courses* course)
{
    courseEnrolled.push_back(course);
}

void Student::dropCourse(Courses* course)
{
    courseEnrolled.erase(find(courseEnrolled.begin(), courseEnrolled.end(), course));
}

string Student::getName() const
{
    return name;
}

void Student::viewCourse()
{
    for (int i = 0; i < courseEnrolled.size(); i++)
    {
        cout << courseEnrolled[i]->getCourseName() << endl;
    }
}

// Implementations for Courses methods
Courses::Courses()
{
    cout << "Enter Course Code: ";
    cin >> courseCode;
    cin.ignore();
    cout << "Enter Course Name: ";
    getline(cin, courseName);
}

string Courses::getCourseName() const
{
    return courseName;
}

void Courses::addStudent(Student* student)
{
    this->student = student;
}

void Courses::removeStudent(Student* student)
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

int main()
{
    cout << "Hello World!\n";

    system("pause");
    return 0;
}
