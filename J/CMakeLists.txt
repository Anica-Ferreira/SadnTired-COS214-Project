cmake_minimum_required(VERSION 4.0)
project(J)

set(CMAKE_CXX_STANDARD 20)

add_executable(J main.cpp
        IMediator.h
        IColleague.h
        IObserver.h
        ISubject.h
        Customer.h
        Plant.h
        StaffMember.h
        StaffManager.h
        StaffSalesman.h
        StaffGardener.h
        StaffCommand.h
        StaffReaction.h
        StaffAction.h
        Customer.cpp
        StaffMember.cpp
        StaffManager.cpp
        StaffSalesman.cpp
        StaffGardener.cpp
        StaffReaction.cpp
        WaterCommand.cpp
        WaterCommand.h
        StaffAction.cpp
        Plant.cpp
)
