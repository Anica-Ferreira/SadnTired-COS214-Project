cmake_minimum_required(VERSION 4.0)
project(Sad_Tired)

set(CMAKE_CXX_STANDARD 20)

add_executable(Sad_Tired main.cpp
        Strategies.h
        Factory.h
        Decorator.h
        Composite.h
        State.h
        ObserverMediator.h
        Commands.h
        Builder.h
        "Chain of Responsibility.h"
        Facade.h
        TemplateMethod.h)
