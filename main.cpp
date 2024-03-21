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
    vector<Courses*> courseEnrolled;

public:
    Student() {}; // Default constructor
    Student(string studentId, string name, string email) : studentId(studentId), name(name), email(email) {}

    string getID() { return studentId; }
    string getName() { return name; }
    string getEmail() { return email; }

    void enrollCourse( Courses* course);
     void dropCourse(Courses* course);
     void viewCourse();
};
class Teacher
{
private:
    string Teacher_Id;
    string Teacher_name, Teacher_email;
    vector<Courses*> Teacher_course;

public:
    Teacher(string Teacher_Id, string Teacher_name, string Teacher_email) : Teacher_Id(Teacher_Id), Teacher_name(Teacher_name), Teacher_email(Teacher_email) {}

    string getID() { return Teacher_Id; }
    string getName() { return Teacher_name; }
    string getEmail() { return Teacher_email; }
    void assignCourse(Courses* course)
    {
        Teacher_course.push_back(course);
    }
    void removeCourse(Courses* course)
    {
        auto it = find(Teacher_course.begin(), Teacher_course.end(), course);
        if (it != Teacher_course.end())
        {
            Teacher_course.erase(it);
        }
    }
    vector<Courses*> viewCourse() const
    {
        return Teacher_course;
    }
};
class Courses 
{
private:
     string courseCode;
    string courseName;
    Student* student;
    Teacher* teacher;

public:
	Courses() {}; // Default constructor
    Courses(string courseCode, string courseName, Teacher* teacher) : courseCode(courseCode), courseName(courseName), teacher(teacher) {}
    string getCode() { return courseCode; }
    string getName() { return courseName; }
    Teacher* getTeacher() { return teacher; }
    string getCourseName();
    void addStudent(vector<Student*>& students);
    void removeStudent(Student* student);
    void viewStudent();
};

void Student::enrollCourse(Courses* course)
{
    courseEnrolled.push_back( course);
}

void Student::dropCourse( Courses* course)
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

string Courses::getCourseName()
{
    return courseName;
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
void loadDataFromFile(vector<Student*>& students, vector<Teacher*>& teachers, vector<Courses*>& courses)
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
        Teacher* teacherPtr = nullptr;
        for (Teacher* teacher : teachers)
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
void addStudent(vector<Student*> & students)
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

void addTeacher(vector<Teacher*>& teachers)
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
void addCourse(vector<Courses*>& courses, const vector<Teacher*>& teachers)
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

    Teacher* teacherPtr = nullptr;
    for (Teacher* teacher : teachers)
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
void saveDataToFile(vector<Student*>& students, vector<Teacher*>& teachers, vector<Courses*>& courses)
{
    ofstream studentFile("students.txt");
    ofstream teacherFile("teachers.txt");
    ofstream courseFile("courses.txt");

    for (const auto& student : students)
    {
        studentFile << student->getID() << " " << student->getName() << " " << student->getEmail() << endl;
    }
    studentFile.close();

    for (const auto& teacher : teachers)
    {
        teacherFile << teacher->getID() << " " << teacher->getName() << " " << teacher->getEmail() << endl;
    }
    teacherFile.close();

    for (const auto& course : courses)
    {
        courseFile << course->getCode() << " " << course->getName() << " " << course->getTeacher()->getID() << " "
            << endl;
    }
    courseFile.close();
}
int main()
{

    vector<Student*> students;
    vector<Teacher*> teachers;
    vector<Courses*> courses;
   
    Student student1("014", "Jasmine", "Jasmin@example.com");   
    Student student2("078", "Arfa", "arfa@example.com");   
	Teacher teachers1("T001", "DR Arham", "Arham@example.com");
	Teacher teachers2("T002", "DR hashir", "Hashir@example.com");
    Courses course1("CSC001", "CP", &teachers1);
    Courses course2("CSC002","Introduction To SE", &teachers2);
	

	student1.enrollCourse(&course1);
	student2.dropCourse(&course1);
	student1.viewCourse();

	teachers1.assignCourse(&course1);
	teachers2.removeCourse(&course1);
	teachers1.viewCourse();

	course1.addStudent(students);
	course2.removeStudent(students[1]);
	course1.viewStudent();

	
	
	
	saveDataToFile(students, teachers, courses);


		// Load data from files
    loadDataFromFile(students, teachers, courses);

    char main_choice;
    char choice;
    do
    {
        cout << "Want to add Data About Student, Teacher or Courses in Database File (Y / N )";
        cin >> main_choice;
        cout << endl;

    } while (main_choice == 'y');
    do
    {
        cout << "---------- MENU ----------" << endl;
        cout << "1. Student" << endl;
        cout << "2. Teacher" << endl;
        cout << "3. Course" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case'1':
			cout << "--- For adding students to Students Database File --- " << endl;
            addStudent(students);
            break;

        case'2':
            cout << "--- For adding Teachers to Teachers Database File --- " << endl;
            addTeacher(teachers);
			break;

		case'3':
			cout << "--- For adding Courses to Courses Database File --- " << endl;
			addCourse(courses, teachers);

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
