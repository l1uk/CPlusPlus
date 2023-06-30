#cmake_minimum_required(VERSION 3.25)
project(C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(C__ AccountManagement/main.cpp AccountManagement/Account.cpp AccountManagement/Account.h AccountManagement/CurrentAccount.cpp AccountManagement/CurrentAccount.h AccountManagement/SavingsAccount.cpp AccountManagement/SavingsAccount.h AccountManagement/CashAccount.cpp AccountManagement/CashAccount.h ShoppingListSimple/main.cpp CourseManagement/CourseManagement.cpp main.cpp Files/textFile.cpp Files/textFile.h CourseManagement/CourseManagement.h Files/division.cpp Files/Employee.cpp Pointers/Exercises.cpp Pointers/Pointers.h dynamicMemory/dynamicArray.h dynamicMemory/dynamicArray.cpp Utils/Utils.h Utils/Utils.cpp dynamicMemory/game.cpp SingleLinkedLists/Person.cpp SingleLinkedLists/Person.h SingleLinkedLists/ListOfPeople.cpp SingleLinkedLists/ListOfPeople.h SingleLinkedLists/PeopleHandling.cpp SingleLinkedLists/peopleHandling.h ShoppingList/ListItem.cpp ShoppingList/ListItem.h ShoppingList/ShoppingList.cpp ShoppingList/ShoppingList.h Polymorphism/Polygon.cpp Polymorphism/Polygon.h OperatorOverloading/Euro.cpp OperatorOverloading/Overloading.h OperatorOverloading/Veichle.cpp OperatorOverloading/Date.cpp OperatorOverloading/Date.h OperatorOverloading/dateExcercise.cpp OperatorOverloading/RockPaperScrissors.cpp Templates/Templates.cpp Templates/Templates.h CombatGame/combatGame.cpp CombatGame/combatGame.h AdvancedCPP/Part1/TypeDeduction.cpp AdvancedCPP/AdvancedCPP.h AdvancedCPP/Part1/Lambda.cpp AdvancedCPP/Part1/UniformInitialization.cpp AdvancedCPP/Part2/pointers.cpp AdvancedCPP/Part2/copyControl.cpp OperatorOverloading/Overloading.h OperatorOverloading/Complex.cpp Exam2406/task1.cpp Exam2406/exam.h Exam2406/task2.cpp Exam2406/task3.cpp Exam2406/task4.cpp Exam2406/task5.cpp AdvancedCPP/Part5/Allocators.cpp AdvancedCPP/Part5/cycle.cpp AdvancedCPP/Part5/cycleBreak.cpp AdvancedCPP/Part5/useCount.cpp AdvancedCPP/AdvancedCPP.h AdvancedCPP/Part6/Regex.cpp AdvancedCPP/Part6/Random.cpp AdvancedCPP/Part6/Chrono.cpp AdvancedCPP/Part7/VariadicTemplates.cpp AdvancedCPP/Part7/typeTraits.cpp AdvancedCPP/Part8/CoRoutines.cpp)


cmake_minimum_required(VERSION 3.9)
#project(VectorExercise)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pedantic -g")

add_compile_options(-DVECTOR_DEBUG)
#add_executable(C__ AdvancedCPP/Exercise2/code/main.cpp AdvancedCPP/Part8/CoRoutines.cpp)

