cmake_minimum_required(VERSION 3.10)
project(TutorAutostradale)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_BUILD_TYPE Release)

add_executable(Simulatore
    src/datatime.cpp
    src/file_error.cpp
    src/Highway.cpp
    src/profiloVelocita.cpp
    src/svincolo.cpp
    src/varco.cpp
    src/vehicle_generator.cpp
    src/vehicle.cpp
    
    src/Simulatore.cpp

    # Aggiungere altri file .cpp del simulatore
)

add_executable(Tutor
    
    src/file_error.cpp
    src/Highway.cpp
    src/svincolo.cpp
    src/varco.cpp
    src/Tutor.cpp
    src/datatime.cpp
    src/tutor_main.cpp
    # Aggiungere altri file .cpp del tutor
)
