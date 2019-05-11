# CMakeList.txt: proyecto de CMake para GraphGenerator, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Agregue un origen al ejecutable de este proyecto.
add_executable (GraphGenerator "GraphGenerator.cpp" "GraphGenerator.h" "Graph.cpp" "Graph.h")

# TODO: Agregue pruebas y destinos de instalación si es necesario.

# This does nothing, apparently
set_target_properties(
    GraphGenerator PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${currentDir}")