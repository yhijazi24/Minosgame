cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(Minosgames C)

# Définit le standard C
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Recherche de SDL2
find_package(SDL2 REQUIRED)

# Dossiers d'inclusion
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# Ajout des chemins pour SDL2_ttf et SDL2_mixer
include_directories(/usr/include/SDL2)

# Recherche des fichiers sources principaux
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/*.c
    ${CMAKE_SOURCE_DIR}/dominos/*.c
    ${CMAKE_SOURCE_DIR}/triominos/*.c
)

# Création de l'exécutable
add_executable(Minosgames ${SOURCES})

# Lien avec les bibliothèques nécessaires
target_link_libraries(Minosgames
    ${SDL2_LIBRARIES}
    SDL2_ttf
    SDL2_mixer
)
