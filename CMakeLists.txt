cmake_minimum_required(VERSION 3.10)
project(TutorAutostradale)

# Specifica lo standard C++ richiesto (Libreria standard C++ [cite: 103])
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Attiva le opzioni di ottimizzazione -O2 come richiesto 
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_BUILD_TYPE Release)

add_executable(Simulatore 
    src/simulatore_main.cpp 
    src/highway_load.cpp
    src/vehicle_generator.cpp
    # Aggiungere altri file .cpp del simulatore
)

add_executable(Tutor 
    src/tutor_main.cpp 
    src/highway_load.cpp
    src/traffic_analyzer.cpp
    # Aggiungere altri file .cpp del tutor
)

# Nota: highway_loader.cpp è incluso in entrambi se entrambi devono leggere Highway.txt [cite: 19, 96]