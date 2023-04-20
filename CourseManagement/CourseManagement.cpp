// simple console application that implements Course Managament

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <regex>

class Person {
protected:
    std::string firstName;
    std::string surname;
    std::string email;
    int personID; // univoque ID, generated automatically on Person creation
public:
    // constructor only used to create "empty" people
    Person();

    // the data members are either assigned with this method, by propmting the user
    void insertData(std::string em);

    // or with this one silently, after passing them
    void insertData(std::string em, std::string fn, std::string sn);

    // email getter
    std::string getEmail();

    // STATIC MEMBERS

    // max persons that can be saved in the system, used to dimensionate the collection
    static const int MAX_PERSONS = 100;
    // number of people currently saved in the system, used to generate personID
    static int personCount;
    // collection of registered users emails
    static std::string emailsCollection[];


    // method that search for a person with the given email
    static bool personExists(std::string email);
};

// static members initializations
int Person::personCount = 0;
std::string Person::emailsCollection[MAX_PERSONS];

class Lecturer : Person {
private:
    std::string academicTitle;
public:
    //empty constructor, necessary for the Course class to initialize the lecturer attribute
    Lecturer() {};

    // construtor with parameters
    Lecturer(std::string em, std::string fn, std::string sn, std::string at);
};


class Student : Person {
    // object storge is implemented within the class and its accomplished using arrays
private:
    std::string matrNumber; // matriculation number
    std::string uniName; // in case student is an extern, specifies uni name
    int coursesCount; // numbers of courses the student is currently enrolled in
    bool own_university; // false = student is an extern
public:
    // constructor only used to create "empty" students
    Student();

    // method that prompts the user for data and fill the attributes
    void insertData(std::string em);

    bool canJoinNewCourse(); // returns true if the student is eligible to join a new course

    void showStudent(); // show student details

    void incrementCoursesCount(); // setter for coursesCount, called after course enrolment

    std::string getEmail(); // getter for email

    // STATIC MEMBERS

    static const int MAX_STUDENTS = 100; // maximum number of students that can be saved in the system, used to dimensionate the static storage
    static Student students[]; // static storage containing MAX_STUDENTS students,
    static int registeredStudents; // of which registeredStudents are "actual" Students and the rest are empty ones

    // "fills" an empty student in the students array using the insertData() method and returns the ID
    static int registerNewStudent(std::string em);

    // returns the ID of the student with the given email, in case it does not exists -1 is returned
    static int getStudent(std::string email);

    // performs a check on the value of studentID and if it's valid,
    // the method shows data of the student with the given email, using the non-static showStudent() method
    static void showStudent(int studentID);
};

// static members initializations
int Student::registeredStudents = 0;
Student Student::students[Student::MAX_STUDENTS];

class Course {
private:
    // Static constants
    static const int MAX_PARTICIPANTS = 10; // course maximum capacity
    static const int MIN_PARTICIPANTS = 3; // minimum participants for the course to take place

    Lecturer lecturer; // course lecturer
    std::string name; // course name
    int numParticipants; // number of participants
    std::string participantsEmails[MAX_PARTICIPANTS]; // array with partitipants email
    // booleans indicating the course state, updated when a student enrol
    bool is_fully_booked;
    bool will_take_place;

public:
    // empty constructor, used to initalize the coursesArchive array
    Course();

    Course(std::string n, Lecturer l);
    // search for a student with the given email among the course participants
    bool isParticipant(std::string email);

    // enrol the given student object in the course
    bool enrol(Student student);

    // getter for the is_fully_booked attribute
    bool isFullyBooked();

    // getter for the name attribute
    std::string getName();

    // show course details
    void showCourse();

    // STATIC MEMBERS

    static const int MAX_COURSES = 3; // maximum courses that can be saved in the system, used to dimensionate array coursesArchive


    static int coursesCount; // number of offered courses
    static Course coursesArchive[]; // static storage of Courses object

    // method used to insert a new course into the archive
    static void insertCourseData(std::string n, Lecturer l);

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
};

// static variables initializazion
Course Course::coursesArchive[MAX_COURSES];
int Course::coursesCount = 0;

class Utils {
// class of general purpose re-usable methods
public:
    // integer input in given boundaries
    static int inputInteger(int min, int max);

    // email input
    static std::string inputEmail();

    // email validation
    static bool ValidateEmail(std::string email);

    // method to pause execution and clear the screen (platform-dependent)
    static void pauseExec();
};

void printMenu();

int main(int argc, char *argv[]) {
    // create lecturers
    Lecturer progLecturer = Lecturer("john.white@uni.us", "John", "White", "CS Bachelor");
    Lecturer DBLecturer = Lecturer("walt.obama@uni.de", "Walter", "Obama", "Computer Engineering Bachelor");
    Lecturer SELecturer = Lecturer("luke.wellington@uni.it", "Luke", "Wellington", "PhD in Software engineering");

    // create courses & populate courses array
    Course::insertCourseData("Programming", progLecturer);
    Course::insertCourseData("Databases", DBLecturer);
    Course::insertCourseData("Software Engineering", SELecturer);

    int choice;
    do {
        // Print the menu and collect user choice in choice variable
        printMenu();
        choice = Utils::inputInteger(1, 4);
        switch (choice) {
            case 1: {
                // prompt the user to choose a course and store the index in a variable
                int courseID = Course::chooseCourse();
                // input user email
                std::string email = Utils::inputEmail();
                // search for existing user (could be a lecturer) with the given email
                bool personExists = Person::personExists(email);
                // search for existing student with that email
                int studentID = Student::getStudent(email);
                if (personExists) {
                    // user exists
                    if (studentID != -1) {
                        // user already registered as a student, the ID of it is stored in the studentID variable
                        std::cout << "User already registered" << std::endl;
                        Student::showStudent(studentID);
                    } else {
                        // user exists but its a lecturer, aborting the enrolment procedure
                        std::cout << "Lecturer cannot join courses!" << std::endl;
                        break;
                    }
                } else {
                    // user does not exists, create new
                    studentID = Student::registerNewStudent(email);
                }

                // enrol the chosen student in the chosen course
                Course::enrol(courseID, studentID);
                break;
            }
            case 2: {
                Course::showCourses();
                break;
            }
            case 3: {
                Course::showFreeToJoinCourses();
                break;
            }
        }
        Utils::pauseExec();
    } while (choice != 4);


}


void printMenu() {
    std::cout << "Welcome to the Main Menu, at the moment there are " << std::endl << std::endl << "Commands:"
              << std::endl <<
              "1. Registration for a course (including querying student data). " << std::endl <<
              "    Each student has a unique email, meaning there can't be two or more students with the same email in the same course."
              << std::endl <<
              "2. Output of all courses with data of the participants." << std::endl <<
              "    Please note that if there are fewer than 3 participants in a course, an additional message must be displayed - \"Course will not take place\"."
              << std::endl <<
              "3. Output of all courses that are not fully booked yet. " << std::endl <<
              "The output must include the number of free places, the name of the course and the academic name of the lecturer with its academic title."
              << std::endl
              << "4. End of program: A message will be displayed stating which participants (=all data members of the class PERSON) have to be notified because your course is not taking place."
              << std::endl << std::endl
              << "Input: ";
}

// constructor, assigns personID
Person::Person() {
    if (personCount >= MAX_PERSONS) { personCount = 0; }
    personID = personCount++;
}

// method for data insertion with user prompt, 
// user email is added to the static emailsCollection[] member
void Person::insertData(std::string em) {
    email = em;
    std::cout << "Name: ";
    std::cin >> firstName;
    std::cout << "Surname: ";
    std::cin >> surname;
    emailsCollection[personID] = em;
}

// method for silent data insertion 
// user email is added to the static emailsCollection[] member
void Person::insertData(std::string em, std::string fn, std::string sn) {
    email = em;
    firstName = fn;
    surname = sn;
    emailsCollection[personID] = em;
}

// getter for email member
std::string Person::getEmail() { return email; }

// performs search in the emailsCollection array
bool Person::personExists(std::string email) {
    for (int i = 0; i < personCount; i++)
        if (emailsCollection[i] == email)
            return true;
    return false;
}

// lecturer constructor with all data members and silent insertion
Lecturer::Lecturer(std::string em, std::string fn, std::string sn, std::string at) : academicTitle(at) {
    Person::insertData(em, fn, sn);
}

// constructor being called when instantiating the students array
// takes care of assigning ID 
// and populating the students array with the freshly created object
Student::Student() : Person() {}

void Student::insertData(std::string em) {
    Person::insertData(em);
    std::cout << "Matriculation number: ";
    std::cin >> matrNumber;
    std::cout << "Do you study in this university? (1) Or you are an extern (0): ";
    own_university = Utils::inputInteger(0, 1);
    if (!own_university) {
        std::cout << "University name: ";
        std::cin >> uniName;
    }
}

bool Student::canJoinNewCourse() { return own_university || coursesCount < 1; }

std::string Student::getEmail() { return Person::getEmail(); }

void Student::incrementCoursesCount() { coursesCount++; }

void Student::showStudent() {
    std::cout << "Email: " << email << "; " <<
              "Name: " << firstName << "; " <<
              "Surname: " << surname << "; " <<
              "Matriculation number: " << matrNumber << "; " <<
              "own_student: " << own_university << "; ";
    if (!own_university)
        std::cout << "University: " << uniName << "; ";
    std::cout << "Courses count: " << coursesCount << ".";
    std::cout << std::endl;
}

int Student::getStudent(std::string email) {
    for (int i = 0; i < registeredStudents; i++) { if (students[i].getEmail() == email) return i; }
    return -1;
}

int Student::registerNewStudent(std::string em) {
    students[registeredStudents].insertData(em);
    return registeredStudents++;
}

void Student::showStudent(int studentID) {
    if (studentID >= 0 && studentID < registeredStudents)
        students[studentID].showStudent();
}


void Course::insertCourseData(std::string n, Lecturer l) {
    coursesArchive[coursesCount++] = Course(n,l);
    if (coursesCount > MAX_COURSES) coursesCount = 0;
}

std::string Course::getName() { return name; }

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
                std::cout << "Successfully enrolled!" << std::endl;
                return true;
            } else std::cout << "This course is fully booked!" << std::endl;
        else std::cout << "You cannot enrol in a new course at the moment!" << std::endl;
    else std::cout << "You are already enrolled in this course!" << std::endl;
    return false;
}

bool Course::isParticipant(std::string email) {
    for (int i = 0; i < numParticipants; i++) { if (participantsEmails[i] == email) { return true; }}
    return false;
}

bool Course::isFullyBooked() { return is_fully_booked; }


void Course::showCourse() {
    std::cout << "Name: " << name << "; Participants: " << numParticipants << "/" << MAX_PARTICIPANTS << std::endl;
    for (int i = 0; i < numParticipants; i++) {
        if (!participantsEmails[i].empty()) {
            int studentIndex = Student::getStudent(participantsEmails[i]);
            std::cout << "          " << i + 1 << ". ";
            Student::students[studentIndex].showStudent();
        }
    }
    if (!will_take_place) {
        std::cout << std::endl << "     Warning! This course will not take place" << std::endl;
    }
}

void Course::showCourses() {
    std::cout << "Courses list:" << std::endl << std::endl;
    for (int i = 0; i < coursesCount; i++) {
        std::cout << "Course " << i + 1 << std::endl << "     ";
        coursesArchive[i].showCourse();
        std::cout << std::endl;
    }
}

int Course::chooseCourse() {
    std::cout << "Please choose a course from the list:" << std::endl;
    for (int i = 0; i < coursesCount; i++) {
        std::cout << i + 1 << ". Course Name: " << coursesArchive[i].getName() << std::endl;
    }
    int choice = Utils::inputInteger(1, coursesCount);

    return choice - 1;
}

bool Course::enrol(int courseID, int studentID) {
    if (courseID >= 0 && courseID < coursesCount)
        if (studentID >= 0 && studentID < Student::registeredStudents) {
            if (coursesArchive[courseID].enrol(Student::students[studentID])) {
                Student::students[studentID].incrementCoursesCount();
                return true;
            }
        }
    return false;
}

void Course::showFreeToJoinCourses() {
    std::cout << "Free to join courses list:" << std::endl << std::endl;
    for (int i = 0; i < coursesCount; i++) {
        if (!coursesArchive[i].is_fully_booked) {
            std::cout << "Course " << i + 1 << std::endl << "     ";
            coursesArchive[i].showCourse();
        }
        std::cout << std::endl;
    }
}

Course::Course() : is_fully_booked(false), will_take_place(false),
                   numParticipants(0) {}


Course::Course(std::string n, Lecturer l) : name(n), lecturer(l), is_fully_booked(false), will_take_place(false),
                                            numParticipants(0) {}
// method for interger input
int Utils::inputInteger(int min, int max) {
    // reading an int in a range from cin, the cin.fail() method return false when an alphanumeric string is inputted instead of a numeric value
    // inspiration taken from https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
    int x;
    std::cin >> x;
    while (std::cin.fail()) {
        std::cout << "Error, please input an integer!" << std::endl << "Input: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    while (x < min || x > max) {
        std::cout << "Value out of range!" << std::endl << "Input: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    return x;

}


// method for email validation using regex
bool Utils::ValidateEmail(std::string email) {
    // code taken from https://stackoverflow.com/questions/36903985/email-validation-in-c/51007772
    return regex_match(email, std::regex("([a-z]+)([_.a-z0-9]*)([a-z0-9]+)(@)([a-z]+)([.a-z]+)([a-z]+)"));
}


// method for email input with user prompt
std::string Utils::inputEmail() {
    std::cout << "Please enter your email:" << std::endl;
    std::cout << "Email: ";
    std::string result;
    do {
        std::cin >> result;
        if (!ValidateEmail(result))
            std::cout << "Not a valid email! Please enter again: ";
    } while (!ValidateEmail(result));
    return result;
}

// method for execution pause and console cleanup (platform dependent)
void Utils::pauseExec() {
    system("pause");
    system("cls");
}