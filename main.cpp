#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Complete class definitions for Student and Teacher
class Student
{
private:
    int studentID;
    string name;
    string email;
    vector<string> coursesEnrolled;

public:
    Student(int id, const string &n, const string &e) : studentID(id), name(n), email(e) {}

    void enrollCourse(const string &courseCode)
    {
        coursesEnrolled.push_back(courseCode);
    }

    void dropCourse(const string &courseCode)
    {
        coursesEnrolled.erase(remove(coursesEnrolled.begin(), coursesEnrolled.end(), courseCode), coursesEnrolled.end());
    }

    void viewCourses() const
    {
        cout << "Courses enrolled by " << name << ":" << endl;
        for (const string &course : coursesEnrolled)
        {
            cout << course << endl;
        }
    }

    int getStudentID() const
    {
        return studentID;
    }

    const string &getName() const
    {
        return name;
    }

    const string &getEmail() const
    {
        return email;
    }

    void saveToFile(ofstream &file) const
    {
        file << studentID << "," << name << "," << email << "\n";
    }
};

class Teacher
{
private:
    int teacherID;
    string name;
    string email;
    vector<string> coursesTaught;

public:
    Teacher(int id, const string &n, const string &e) : teacherID(id), name(n), email(e) {}

    void assignCourse(const string &courseCode)
    {
        coursesTaught.push_back(courseCode);
    }

    void removeCourse(const string &courseCode)
    {
        coursesTaught.erase(remove(coursesTaught.begin(), coursesTaught.end(), courseCode), coursesTaught.end());
    }

    void viewCourses() const
    {
        cout << "Courses taught by " << name << ":" << endl;
        for (const string &course : coursesTaught)
        {
            cout << course << endl;
        }
    }

    int getTeacherID() const
    {
        return teacherID;
    }

    const string &getName() const
    {
        return name;
    }

    const string &getEmail() const
    {
        return email;
    }

    void saveToFile(ofstream &file) const
    {
        file << teacherID << "," << name << "," << email << "\n";
    }
};

// Forward declaration for Course
class Course;

// Forward declaration for functions to save and load data
void saveStudentData(const vector<Student *> &students);
vector<Student *> loadStudentData();
void saveTeacherData(const vector<Teacher *> &teachers);
vector<Teacher *> loadTeacherData();
void saveCourseData(const vector<Course *> &courses);
vector<Course *> loadCourseData(vector<Teacher *> &teachers);

class Course
{
private:
    string courseCode;
    string courseName;
    Teacher *teacher;
    vector<Student *> studentsEnrolled;
    int maxCapacity;

public:
    Course(const string &code, const string &name, Teacher *t, int capacity) : courseCode(code), courseName(name), teacher(t), maxCapacity(capacity) {}

    void addStudent(Student *student)
    {
        if (studentsEnrolled.size() < maxCapacity)
        {
            studentsEnrolled.push_back(student);
            student->enrollCourse(courseCode);
        }
        else
        {
            cout << "Course " << courseCode << " is full. Cannot enroll more students." << endl;
        }
    }

    void removeStudent(Student *student)
    {
        studentsEnrolled.erase(remove(studentsEnrolled.begin(), studentsEnrolled.end(), student), studentsEnrolled.end());
        student->dropCourse(courseCode);
    }

    void viewStudents() const
    {
        cout << "Students enrolled in " << courseName << ":" << endl;
        for (const Student *student : studentsEnrolled)
        {
            cout << student->getName() << endl;
        }
    }

    const string &getCourseCode() const
    {
        return courseCode;
    }

    const string &getCourseName() const
    {
        return courseName;
    }

    const Teacher *getTeacher() const
    {
        return teacher;
    }

    int getMaxCapacity() const
    {
        return maxCapacity;
    }

    void saveToFile(ofstream &file) const
    {
        file << courseCode << "," << courseName << "," << teacher->getTeacherID() << "," << maxCapacity << "\n";
    }

    void assignTeacher(Teacher *t)
    {
        teacher = t;
        t->assignCourse(courseCode);
    }

    void removeTeacher()
    {
        if (teacher != nullptr)
        {
            teacher->removeCourse(courseCode);
            teacher = nullptr;
        }
    }
};

// Function to save student data to a text file
void saveStudentData(const vector<Student *> &students)
{
    ofstream file("students.txt");
    if (file.is_open())
    {
        for (const auto &student : students)
        {
            student->saveToFile(file);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file for saving student data." << endl;
    }
}

// Function to load student data from a text file
vector<Student *> loadStudentData()
{
    vector<Student *> students;
    ifstream file("students.txt");
    if (file.is_open())
    {
        int id;
        string name, email;
        while (file >> id >> name >> email)
        {
            students.push_back(new Student(id, name, email));
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file for loading student data." << endl;
    }
    return students;
}

// Function to save teacher data to a text file
void saveTeacherData(const vector<Teacher *> &teachers)
{
    ofstream file("teachers.txt");
    if (file.is_open())
    {
        for (const auto &teacher : teachers)
        {
            teacher->saveToFile(file);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file for saving teacher data." << endl;
    }
}

// Function to load teacher data from a text file
vector<Teacher *> loadTeacherData()
{
    vector<Teacher *> teachers;
    ifstream file("teachers.txt");
    if (file.is_open())
    {
        int id;
        string name, email;
        while (file >> id >> name >> email)
        {
            teachers.push_back(new Teacher(id, name, email));
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file for loading teacher data." << endl;
    }
    return teachers;
}

// Function to save course data to a text file
void saveCourseData(const vector<Course *> &courses)
{
    ofstream file("courses.txt");
    if (file.is_open())
    {
        for (const auto &course : courses)
        {
            course->saveToFile(file);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file for saving course data." << endl;
    }
}

// Function to load course data from a text file
vector<Course *> loadCourseData(vector<Teacher *> &teachers)
{
    vector<Course *> courses;
    ifstream file("courses.txt");
    if (file.is_open())
    {
        string code, name;
        int teacherID, capacity;
        while (file >> code >> name >> teacherID >> capacity)
        {
            Teacher *teacher = nullptr;
            for (const auto &t : teachers)
            {
                if (t->getTeacherID() == teacherID)
                {
                    teacher = t;
                    break;
                }
            }
            if (teacher != nullptr)
            {
                courses.push_back(new Course(code, name, teacher, capacity));
            }
            else
            {
                cout << "Teacher with ID " << teacherID << " not found in the system." << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file for loading course data." << endl;
    }
    return courses;
}

// Function to display the menu options for teachers
void displayTeacherMenu()
{
    cout << "Teacher Menu:" << endl;
    cout << "1. Add Teacher" << endl;
    cout << "2. Remove Teacher" << endl;
    cout << "3. View Courses Taught" << endl;
    cout << "Enter your choice: ";
}

// Function to display the menu options for courses
void displayCourseMenu()
{
    cout << "Courses Menu:" << endl;
    cout << "1. View Courses" << endl;
    cout << "2. Add Course" << endl;
    cout << "3. Remove Course" << endl;
    cout << "4. Assign Teacher to Course" << endl;
    cout << "5. View Students Enrolled in Course" << endl;
    cout << "Enter your choice: ";
}

int main()
{
    // Load student, teacher, and course data from files
    vector<Student *> students = loadStudentData();
    vector<Teacher *> teachers = loadTeacherData();
    vector<Course *> courses = loadCourseData(teachers);

    int choice;
    do
    {
        cout << "Main Menu:" << endl;
        cout << "1. Student Menu" << endl;
        cout << "2. Teacher Menu" << endl;
        cout << "3. Courses Menu" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice)
        {
        case 1:
        {
            // Student Menu
            cout << "Student Menu:" << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Remove Student" << endl;
            cout << "3. Enroll Course" << endl;
            cout << "4. Drop Course" << endl;
            cout << "5. View Enrolled Courses" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Clear input buffer

            switch (choice)
            {
            case 1:
            {
                int id;
                string name, email;
                cout << "Enter student ID: ";
                cin >> id;
                cin.ignore(); // Clear input buffer
                cout << "Enter student name: ";
                getline(cin, name);
                cout << "Enter student email: ";
                getline(cin, email);
                students.push_back(new Student(id, name, email));
                saveStudentData(students);
                break;
            }
            case 2:
            {
                int id;
                cout << "Enter student ID to remove: ";
                cin >> id;
                auto it = find_if(students.begin(), students.end(), [id](const Student *s)
                                  { return s->getStudentID() == id; });
                if (it != students.end())
                {
                    delete *it;
                    students.erase(it);
                    saveStudentData(students);
                }
                else
                {
                    cout << "Student not found." << endl;
                }
                break;
            }
            case 3:
            {
                int studentID;
                string courseCode;
                cout << "Enter student ID: ";
                cin >> studentID;
                cout << "Enter course code to enroll: ";
                cin >> courseCode;
                auto studentIt = find_if(students.begin(), students.end(), [studentID](const Student *s)
                                         { return s->getStudentID() == studentID; });
                auto courseIt = find_if(courses.begin(), courses.end(), [courseCode](const Course *c)
                                        { return c->getCourseCode() == courseCode; });
                if (studentIt != students.end() && courseIt != courses.end())
                {
                    (*courseIt)->addStudent(*studentIt);
                    saveCourseData(courses);
                }
                else
                {
                    cout << "Student or course not found." << endl;
                }
                break;
            }
            case 4:
            {
                int studentID;
                string courseCode;
                cout << "Enter student ID: ";
                cin >> studentID;
                cout << "Enter course code to drop: ";
                cin >> courseCode;
                auto studentIt = find_if(students.begin(), students.end(), [studentID](const Student *s)
                                         { return s->getStudentID() == studentID; });
                auto courseIt = find_if(courses.begin(), courses.end(), [courseCode](const Course *c)
                                        { return c->getCourseCode() == courseCode; });
                if (studentIt != students.end() && courseIt != courses.end())
                {
                    (*courseIt)->removeStudent(*studentIt);
                    saveCourseData(courses);
                }
                else
                {
                    cout << "Student or course not found." << endl;
                }
                break;
            }
            case 5:
            {
                int studentID;
                cout << "Enter student ID: ";
                cin >> studentID;
                auto studentIt = find_if(students.begin(), students.end(), [studentID](const Student *s)
                                         { return s->getStudentID() == studentID; });
                if (studentIt != students.end())
                {
                    (*studentIt)->viewCourses();
                }
                else
                {
                    cout << "Student not found." << endl;
                }
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
            break;
        }
        case 2:
        {
            // Teacher Menu
            displayTeacherMenu();
            cin >> choice;
            cin.ignore(); // Clear input buffer

            switch (choice)
            {
            case 1:
            {
                int id;
                string name, email;
                cout << "Enter teacher ID: ";
                cin >> id;
                cin.ignore(); // Clear input buffer
                cout << "Enter teacher name: ";
                getline(cin, name);
                cout << "Enter teacher email: ";
                getline(cin, email);
                teachers.push_back(new Teacher(id, name, email));
                saveTeacherData(teachers);
                break;
            }
            case 2:
            {
                int id;
                cout << "Enter teacher ID to remove: ";
                cin >> id;
                auto it = find_if(teachers.begin(), teachers.end(), [id](const Teacher *t)
                                  { return t->getTeacherID() == id; });
                if (it != teachers.end())
                {
                    delete *it;
                    teachers.erase(it);
                    saveTeacherData(teachers);
                }
                else
                {
                    cout << "Teacher not found." << endl;
                }
                break;
            }
            case 3:
            {
                int teacherID;
                cout << "Enter teacher ID: ";
                cin >> teacherID;
                auto teacherIt = find_if(teachers.begin(), teachers.end(), [teacherID](const Teacher *t)
                                         { return t->getTeacherID() == teacherID; });
                if (teacherIt != teachers.end())
                {
                    (*teacherIt)->viewCourses();
                }
                else
                {
                    cout << "Teacher not found." << endl;
                }
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
            break;
        }
        case 3:
        {
            // Courses Menu
            displayCourseMenu();
            cin >> choice;
            cin.ignore(); // Clear input buffer

            switch (choice)
            {
            case 1:
            {
                cout << "Courses available:" << endl;
                for (const auto &course : courses)
                {
                    cout << course->getCourseCode() << " - " << course->getCourseName() << endl;
                }
                break;
            }
            case 2:
            {
                string code, name;
                int capacity;
                cout << "Enter course code: ";
                cin >> code;
                cin.ignore(); // Clear input buffer
                cout << "Enter course name: ";
                getline(cin, name);
                cout << "Enter maximum capacity: ";
                cin >> capacity;
                cout << "Debug: Input received - Code: " << code << ", Name: " << name << ", Capacity: " << capacity << endl;

                // Check if the course already exists
                auto courseExists = find_if(courses.begin(), courses.end(), [code](const Course *c)
                                            { return c->getCourseCode() == code; });
                if (courseExists != courses.end())
                {
                    cout << "Course with code " << code << " already exists." << endl;
                }
                else
                {
                    courses.push_back(new Course(code, name, nullptr, capacity));
                    saveCourseData(courses);
                }
                break;
            }

            case 3:
            {
                string code;
                cout << "Enter course code to remove: ";
                cin >> code;
                auto it = find_if(courses.begin(), courses.end(), [code](const Course *c)
                                  { return c->getCourseCode() == code; });
                if (it != courses.end())
                {
                    delete *it;
                    courses.erase(it);
                    saveCourseData(courses);
                }
                else
                {
                    cout << "Course not found." << endl;
                }
                break;
            }
            case 4:
            {
                string code;
                int teacherID;
                cout << "Enter course code: ";
                cin >> code;
                cout << "Enter teacher ID to assign: ";
                cin >> teacherID;
                auto courseIt = find_if(courses.begin(), courses.end(), [code](const Course *c)
                                        { return c->getCourseCode() == code; });
                auto teacherIt = find_if(teachers.begin(), teachers.end(), [teacherID](const Teacher *t)
                                         { return t->getTeacherID() == teacherID; });
                if (courseIt != courses.end() && teacherIt != teachers.end())
                {
                    (*courseIt)->assignTeacher(*teacherIt);
                    saveCourseData(courses);
                }
                else
                {
                    cout << "Course or teacher not found." << endl;
                }
                break;
            }
            case 5:
            {
                string code;
                cout << "Enter course code to view students: ";
                cin >> code;
                auto it = find_if(courses.begin(), courses.end(), [code](const Course *c)
                                  { return c->getCourseCode() == code; });
                if (it != courses.end())
                {
                    (*it)->viewStudents();
                }
                else
                {
                    cout << "Course not found." << endl;
                }
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
            break;
        }
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    // Clean up memory
    for (auto &student : students)
    {
        delete student;
    }
    for (auto &teacher : teachers)
    {
        delete teacher;
    }
    for (auto &course : courses)
    {
        delete course;
    }

    return 0;
}
