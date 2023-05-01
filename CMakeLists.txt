cmake_minimum_required(VERSION 3.25)
project(C__)

set(CMAKE_CXX_STANDARD 17)

add_executable(C__ AccountManagement/main.cpp AccountManagement/Account.cpp AccountManagement/Account.h AccountManagement/CurrentAccount.cpp AccountManagement/CurrentAccount.h AccountManagement/SavingsAccount.cpp AccountManagement/SavingsAccount.h AccountManagement/CashAccount.cpp AccountManagement/CashAccount.h ShoppingList/main.cpp CourseManagement/CourseManagement.cpp main.cpp Files/textFile.cpp Files/textFile.h CourseManagement/CourseManagement.h Files/division.cpp Files/Employee.cpp Pointers/Exercises.cpp Pointers/Pointers.h)
