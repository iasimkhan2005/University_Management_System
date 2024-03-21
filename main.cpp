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
    Student() {
        cout << "Enter Student ID: ";
        cin >> studentId;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Email Address: ";
        cin >> email;

    }

    string getID() const { return studentId; }
    string getName() const { return name; }
    string getEmail() const { return email; }

  
    string getID() const { return studentId; }
    string getName() const { return name; }
    string getEmail() const { return email; }

    void enrollCourse(Courses *course);
    void dropCourse(Courses *course);
    string getName() const;

    void viewCourse();
};
class Teacher
{
private:
    string Teacher_Id;
    string Teacher_name, Teacher_email;


    vector<Courses *> Teacher_course;


public:
    Teacher(string id, string n, string e) : Teacher_Id(id), Teacher_name(n), Teacher_email(e) {}

    string getID() const { return Teacher_Id; }
    string getName() const { return Teacher_name; }
    string getEmail() const { return Teacher_email; }

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
    Courses();
    string getCode() const { return courseCode; }
    string getName() const { return courseName; }


    Teacher *getTeacher() const { return teacher; }

    string getCourseName() const;
    void addStudent(Student *student);
    void removeStudent(Student *student);
    void viewStudent();
};

// Implementations for Student methods


void Student::enrollCourse(Courses *course)
{
    courseEnrolled.push_back(course);
}

void Student::dropCourse(Courses *course)
{
    courseEnrolled.erase(find(courseEnrolled.begin(), courseEnrolled.end(), course));
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

void Courses::addStudent(Student *student)
{
    this->student = student;
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


void saveDataToFile(vector<const Student *> &students, const vector<Teacher *> &teachers, const vector<Courses *> &courses)

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

    Student student1();


    system("pause");
    return 0;
}
