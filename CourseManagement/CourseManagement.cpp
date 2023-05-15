// simple console application that implements Course Management
// Classes definitions are here before the main() and implementations are on the bottom.
// Comments on the definitions should be enough to understand the program. But if you are curious you can find more comments in the methods' body
// "Archive" classes are used in order to obtain a common static global storage for objects (E.G. see class StudentArchive line 84)
//

#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

class Person { // person class, with a static collection of emails of registered people
protected:
    string firstName;
    string surname;
    string email;
    int personID; // univoque ID, generated automatically on Person creation
public:
    // constructor only used to create "empty" people
    Person();

    // the data members are either assigned with this method, by propmting the user
    void insertData(string em);

    // or with this one silently, after passing them
    void insertData(string em, string fn, string sn);

    // email getter
    string getEmail();

    // STATIC MEMBERS

    // max people that can be saved in the system, used to dimensionate the email collection
    static const int MAX_PERSONS = 150;
    // number of people currently saved in the system, used to generate personID
    static int personCount;
    // collection of registered users emails
    static string emailsCollection[];


    // method that search for a person with the given email inside the collection
    static bool personExists(string email);
};

// static members initializations
int Person::personCount = 0;
string Person::emailsCollection[MAX_PERSONS];

class Lecturer : public Person {
private:
    string academicTitle;
public:

    Lecturer() {}; //empty constructor, necessary for the Course class to initialize the lecturer attribute


    Lecturer(string em, string fn, string sn, string at); // construtor with parameters

    void showLecturer(); // show lecturer details
};


class Student : public Person {
private:
    string matrNumber; // matriculation number
    string uniName; // in case student is an extern, specifies uni name
    int coursesCount; // numbers of courses the student is currently enrolled in
    bool own_university; // false = student is an extern
public:
    // constructor only used to create "empty" students
    Student();

    // method that prompts the user for data and fill the attributes
    void insertData(string em);

    bool canJoinNewCourse(); // returns true if the student is eligible to join a new course

    void showStudent(); // show student details

    void incrementCoursesCount(); // setter for coursesCount, called after course enrolment
};

class StudentArchive { // static storage of students, used to make the main() function more understandable
public:
    static const int MAX_STUDENTS = 100; // maximum number of students that can be saved in the system, used to dimensionate the static storage
    static Student students[]; // static storage containing MAX_STUDENTS students,
    static int registeredStudents; // of which only registeredStudents are "actual" Students and the rest are empty ones

    // "fills" an empty student in the students array using the insertData() method and returns the ID
    static int registerNewStudent(string em);

    // returns the ID of the student with the given email, in case it does not exists -1 is returned
    static int getStudent(string email);

    // performs a check on the value of studentID and if it's valid,
    // the method shows data of the student with the given email, using the non-static showStudent() method
    static void showStudent(int studentID);
};

// static members initializations
int StudentArchive::registeredStudents = 0;
Student StudentArchive::students[StudentArchive::MAX_STUDENTS];

class Course {
    friend class CoursesArchive;

private:
    // Static constants
    static const int MAX_PARTICIPANTS = 10; // course maximum capacity
    static const int MIN_PARTICIPANTS = 3; // minimum participants for the course to take place

    Lecturer lecturer; // course lecturer
    string name; // course name
    int numParticipants; // number of participants
    string participantsEmails[MAX_PARTICIPANTS]; // array with partitipants email
    // booleans indicating the course state, updated when a student enrol
    bool is_fully_booked;
    bool will_take_place;
public:
    // empty constructor, used to initalize the coursesArchive array
    Course();

    Course(string n, Lecturer l);

    // search for a student with the given email among the course participants
    bool isParticipant(string email);

    // enrol the given student object in the course
    bool enrol(Student student);

    // getter for the is_fully_booked attribute
    bool isFullyBooked();

    // getter for the name attribute
    string getName();

    // getter for the will_take_place attrbiute
    bool willTakePlace();

    // show course details
    void showCourse();


};

class CoursesArchive { // static storage of Courses
public:
    static const int MAX_COURSES = 3; // maximum courses that can be saved in the system, used to dimensionate array coursesArchive


    static int coursesCount; // number of offered courses
    static Course coursesArchive[]; // static storage of Courses object

    // method used to insert a new course into the archive
    static void insertCourse(string n, Lecturer l);

    // shows details about every course in the coursesArchive array
    static void showCourses();

    // same as above but only for not fully booked courses
    static void showFreeToJoinCourses();

    // method used to prompt the user for a course choosing from the courses list, and return the value
    static int chooseCourse();

    // performs check on the value of the passed IDs, retrieves the desired student object,
    // call the non-static enrol() method for the specified Course object passing the student as a parameter
    // and lastly, increment the students courseCount
    static bool enrol(int courseID, int studentID);


    // display for each course that will not take place, the names of the people to be notified
    static void notifyCoursesNotTakingPlace();
};

// static variables initializazion
Course CoursesArchive::coursesArchive[MAX_COURSES];
int CoursesArchive::coursesCount = 0;

class Utils {
// class of general purpose re-usable methods
public:
    // integer input in given boundaries
    static int inputInteger(int min, int max);

    // email input
    static string inputEmail();

    // email validation
    static bool ValidateEmail(string email);

    // method to pause execution and clear the screen (platform-dependent)
    static void pauseExec();

    // method to determine if a given string is in a string array
    static bool stringInArray(string stringToSearch, string stringArray[], int arrayLength);
};

void printMenu(); //method to print the Menu (app-depentent)


// the main() is very light because most of the application logic is inside classes.
int courseManagement() {
    // create lecturers
    Lecturer progLecturer = Lecturer("john.white@uni.us", "John", "White", "CS Bachelor");
    Lecturer DBLecturer = Lecturer("walt.obama@uni.de", "Walter", "Obama", "Computer Engineering Bachelor");
    Lecturer SELecturer = Lecturer("luke.wellington@uni.it", "Luke", "Wellington", "PhD in Software engineering");

    // create courses & populate courses array
    CoursesArchive::insertCourse("Programming", progLecturer);
    CoursesArchive::insertCourse("Databases", DBLecturer);
    CoursesArchive::insertCourse("Software Engineering", SELecturer);

    int choice;
    do {
        // Print the menu and collect user choice in choice variable
        printMenu();
        choice = Utils::inputInteger(1, 4);
        switch (choice) {
            case 1: {
                // prompt the user to choose a course and store the index in a variable
                int courseID = CoursesArchive::chooseCourse();
                // input user email
                string email = Utils::inputEmail();
                // search for existing user (could be a lecturer) with the given email
                bool personExists = Person::personExists(email);
                // search for existing student with that email
                int studentID = StudentArchive::getStudent(email);
                if (personExists) {
                    // user exists
                    if (studentID != -1) {
                        // user already registered as a student, the ID of it is stored in the studentID variable
                        cout << "User already registered" << endl;
                        StudentArchive::showStudent(studentID);
                    } else {
                        // user exists but its a lecturer, aborting the enrolment procedure
                        cout << "Lecturer cannot join courses!" << endl;
                        break;
                    }
                } else {
                    // user does not exists, create new
                    if (StudentArchive::registeredStudents >= StudentArchive::MAX_STUDENTS) {
                        cout << "Error! Max numbers of people reached! Please contact the system admin."
                             << endl;
                        break;
                    }
                    studentID = StudentArchive::registerNewStudent(email);
                }

                // enrol the chosen student in the chosen course
                CoursesArchive::enrol(courseID, studentID);
                Utils::pauseExec();
                break;
            }
            case 2: {
                CoursesArchive::showCourses();
                Utils::pauseExec();
                break;
            }
            case 3: {
                CoursesArchive::showFreeToJoinCourses();
                Utils::pauseExec();
                break;
            }
        }

    } while (choice != 4);

    cout << endl;
    CoursesArchive::notifyCoursesNotTakingPlace();

    Utils::pauseExec();

    return 0;

}


void printMenu() {
    cout << "Welcome to the Main Menu, options: " << endl << endl << "Commands:"
         << endl <<
         "1. Registration for a course (including querying student data). " << endl <<
         "    Each student has a unique email, meaning there can't be two or more students with the same email in the same course."
         << endl <<
         "2. Output of all courses with data of the participants." << endl <<
         "    Please note that if there are fewer than 3 participants in a course, an additional message must be displayed - \"Course will not take place\"."
         << endl <<
         "3. Output of all courses that are not fully booked yet. " << endl <<
         "The output must include the number of free places, the name of the course and the academic name of the lecturer with its academic title."
         << endl
         << "4. End of program: A message will be displayed stating which participants (=all data members of the class PERSON) have to be notified because your course is not taking place."
         << endl << endl
         << "Input: ";
}

// constructor, assigns personID
Person::Person() {
    if (personCount >= MAX_PERSONS) { personCount = 0; }
    personID = personCount++;
}

// method for data insertion with user prompt,
// user email is added to the static emailsCollection[] member
void Person::insertData(string em) {
    email = em;
    cout << "Name: ";
    cin >> firstName;
    cout << "Surname: ";
    cin >> surname;
    emailsCollection[personID] = em;
}

// method for silent data insertion
// user email is added to the static emailsCollection[] member
void Person::insertData(string em, string fn, string sn) {
    email = em;
    firstName = fn;
    surname = sn;
    emailsCollection[personID] = em;
}

// getter for email member
string Person::getEmail() { return email; }

// performs search in the emailsCollection array
bool Person::personExists(string email) {
    for (int i = 0; i < personCount; i++)
        if (emailsCollection[i] == email)
            return true;
    return false;
}

// lecturer constructor with all data members and silent insertion
Lecturer::Lecturer(string em, string fn, string sn, string at) : academicTitle(at) {
    Person::insertData(em, fn, sn);
}

void Lecturer::showLecturer() {
    cout << "Email: " << email << "; " <<
         "Name: " << firstName << "; " <<
         "Surname: " << surname << "; " <<
         "Academic title: " << academicTitle << "; " << endl;
}

// constructor being called when instantiating the students array
Student::Student() : Person() {}

// input wizard for popupating student data
void Student::insertData(string em) {
    Person::insertData(em);
    cout << "Matriculation number: ";
    cin >> matrNumber;
    cout << "Do you study in this university? (1) Or you are an extern (0): ";
    own_university = Utils::inputInteger(0, 1);
    if (!own_university) {
        cout << "University name: ";
        cin >> uniName;
    }
}

// returns true if the student can join a new course
bool Student::canJoinNewCourse() { return own_university || coursesCount < 1; }

// increments courseCount
void Student::incrementCoursesCount() { coursesCount++; }

// display student's data
void Student::showStudent() {
    cout << "Email: " << email << "; " <<
         "Name: " << firstName << "; " <<
         "Surname: " << surname << "; " <<
         "Matriculation number: " << matrNumber << "; " <<
         "own_student: " << own_university << "; ";
    if (!own_university)
        cout << "University: " << uniName << "; ";
    cout << "Courses count: " << coursesCount << ".";
    cout << endl;
}

// retrieves student from student archive given email
int StudentArchive::getStudent(string email) {
    for (int i = 0; i < registeredStudents; i++) { if (students[i].getEmail() == email) return i; }
    return -1;
}

// insert a new student in the archive
// (input wizard is called on the pre-existing Student object)
int StudentArchive::registerNewStudent(string em) {
    students[registeredStudents].insertData(em);
    return registeredStudents++;
}

// retrieves given student and shows it
void StudentArchive::showStudent(int studentID) {
    if (studentID >= 0 && studentID < registeredStudents)
        students[studentID].showStudent();
}

//getter for name attribute
string Course::getName() { return name; }

// Enrol the given student in the course
bool Course::enrol(Student student) {
    if (!isParticipant(student.getEmail()))
        // if the user is not already enrolled in this course
        if (student.canJoinNewCourse())
            // and can join a new course (E.G. not possible for extern with courseCount>1)
            if (!isFullyBooked()) {
                // and its not fully booked
                participantsEmails[numParticipants++] = student.getEmail();
                will_take_place = numParticipants >= MIN_PARTICIPANTS;
                is_fully_booked = (numParticipants == MAX_PARTICIPANTS);
                cout << "Successfully enrolled!" << endl;
                return true;
            } else cout << "This course is fully booked!" << endl;
        else cout << "You cannot enrol in a new course at the moment!" << endl;
    else cout << "You are already enrolled in this course!" << endl;
    return false;
}

// returns true if the student with the given email is a participant in the current course
bool Course::isParticipant(string email) {
    for (int i = 0; i < numParticipants; i++) { if (participantsEmails[i] == email) { return true; }}
    return false;
}

// getter for fullyBooked attribute
bool Course::isFullyBooked() { return is_fully_booked; }

// shows course details and gives warning in case the course won't take place
void Course::showCourse() {
    cout << "Name: " << name << "; Participants: " << numParticipants << "/" << MAX_PARTICIPANTS << endl;
    for (int i = 0; i < numParticipants; i++) {
        if (!participantsEmails[i].empty()) {
            int studentIndex = StudentArchive::getStudent(participantsEmails[i]);
            cout << "          " << i + 1 << ". ";
            StudentArchive::students[studentIndex].showStudent();
        }
    }
    if (!will_take_place) {
        cout << endl << "     Warning! This course will not take place" << endl;
    }
}

// insert new course into coursesArchive array
void CoursesArchive::insertCourse(string n, Lecturer l) {
    coursesArchive[coursesCount++] = Course(n, l);
    if (coursesCount > MAX_COURSES) coursesCount = 0;
}

// for every course, call the showCourse() method
void CoursesArchive::showCourses() {
    cout << "Courses list:" << endl << endl;
    for (int i = 0; i < coursesCount; i++) {
        cout << "Course " << i + 1 << endl << "     ";
        coursesArchive[i].showCourse();
        cout << endl;
    }
}

// print the available courses and prompt the user to choose one
int CoursesArchive::chooseCourse() {
    cout << "Please choose a course from the list:" << endl;
    for (int i = 0; i < coursesCount; i++) {
        cout << i + 1 << ". Course Name: " << coursesArchive[i].getName() << endl;
    }
    int choice = Utils::inputInteger(1, coursesCount);

    return choice - 1;
}

// enrol the given student in the given course
bool CoursesArchive::enrol(int courseID, int studentID) {
    if (courseID >= 0 && courseID < coursesCount)
        if (studentID >= 0 && studentID < StudentArchive::registeredStudents) {
            if (coursesArchive[courseID].enrol(StudentArchive::students[studentID])) {
                StudentArchive::students[studentID].incrementCoursesCount();
                return true;
            }
        }
    return false;
}

// show courses that are not fully booked
void CoursesArchive::showFreeToJoinCourses() {
    cout << "Free to join courses list:" << endl << endl;
    for (int i = 0; i < coursesCount; i++) {
        if (!coursesArchive[i].isFullyBooked()) {
            cout << "Course " << i + 1 << endl << "     ";
            coursesArchive[i].showCourse();
        }
        cout << endl;
    }
}

// notify People that their course won't take place
// nested iterations over courses and students
// an array with the emails of the already notified people is used to ensure not to notify someone twice
void CoursesArchive::notifyCoursesNotTakingPlace() {
    cout
            << "WARNING - notify these people that the courses they signed up for, or that they will hold won't take place:"
            << endl
            << endl;

    string emailsToNotify[Person::MAX_PERSONS]; // stores the email of already notified people
    int numberToNotify = 0;

    for (int i = 0; i < coursesCount; i++) { // iterate over courses
        if (!coursesArchive[i].willTakePlace()) {
            if (!Utils::stringInArray(
                    coursesArchive[i].lecturer.getEmail(), emailsToNotify, numberToNotify)
                || numberToNotify == 0) {
                // if the given lecturer is not already notified, add him to the emailsToNotify array and print the details
                emailsToNotify[numberToNotify++] = coursesArchive[i].lecturer.getEmail();
                coursesArchive[i].lecturer.showLecturer();
            }
            for (int j = 0; j < coursesArchive[i].numParticipants; j++) { // iterate over course participants
                if (!Utils::stringInArray(coursesArchive[i].participantsEmails[j], emailsToNotify, numberToNotify)) {
                    // if the student is not already notified, add him to the emailsToNotify array and print the details
                    emailsToNotify[numberToNotify++] = coursesArchive[i].participantsEmails[j];
                    StudentArchive::showStudent(
                            StudentArchive::getStudent(coursesArchive[i].participantsEmails[j])
                    );
                }
            }

        }
    }
}

// empty constructor
Course::Course() : is_fully_booked(false), will_take_place(false),
                   numParticipants(0) {}

// constructor with parameters
Course::Course(string n, Lecturer l) : name(n), lecturer(l), is_fully_booked(false), will_take_place(false),
                                       numParticipants(0) {}

// getter for the will_take_place attribute
bool Course::willTakePlace() { return will_take_place; }

// method for interger input
int Utils::inputInteger(int min, int max) {
    // reading an int in a range from cin, the cin.fail() method return false when an alphanumeric string is inputted instead of a numeric value
    // inspiration taken from https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
    int x;
    cin >> x;
    while (cin.fail()) {
        cout << "Error, please input an integer!" << endl << "Input: ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> x;
    }
    while (x < min || x > max) {
        cout << "Value out of range!" << endl << "Input: ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> x;
    }
    return x;

}


// method for email validation using regex
bool Utils::ValidateEmail(string email) {
    // code taken from https://stackoverflow.com/questions/36903985/email-validation-in-c/51007772
    return regex_match(email, regex("([a-z]+)([_.a-z0-9]*)([a-z0-9]+)(@)([a-z]+)([.a-z]+)([a-z]+)"));
}


// method for email input with user prompt
string Utils::inputEmail() {
    cout << "Please enter your email:" << endl;
    cout << "Email: ";
    string result;
    do {
        cin >> result;
        if (!ValidateEmail(result))
            cout << "Not a valid email! Please enter again: ";
    } while (!ValidateEmail(result));
    return result;
}

// method for execution pause and console cleanup (platform dependent)
void Utils::pauseExec() {
    // this code is for windows
    system("pause");
    system("cls");
}

// search for string in array
bool Utils::stringInArray(string stringToSearch, string stringArray[], int arrayLength) {
    for (int i = 0; i < arrayLength; i++) {
        if (stringArray[i] == stringToSearch)
            return true;
    }
    return false;
}
