cmake_minimum_required(VERSION 4.0)
project(SnT)

set(CMAKE_CXX_STANDARD 20)

add_executable(SnT main.cpp
        StaffMember.h
        StaffMember.cpp
        StaffManager.cpp
        StaffManager.h
        StaffGardener.cpp
        StaffGardener.h
        StaffSalesman.cpp
        StaffSalesman.h
        ObserverMediator.cpp
        ObserverMediator.h
        SubjectColleague.cpp
        SubjectColleague.h
        Customer.cpp
        Customer.h
        StaffCommand.cpp
        StaffCommand.h
        StaffReaction.cpp
        StaffReaction.h
        StaffAction.cpp
        StaffAction.h)
