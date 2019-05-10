# CMakeList.txt: archivo del proyecto de CMake de nivel superior, establezca la configuración global
# e incluya los subproyectos aquí.
#
cmake_minimum_required (VERSION 3.8)

project ("GraphGenerator")

# Incluya los subproyectos.
add_subdirectory ("GraphGenerator")

# This does nothing, apparently
set_target_properties(
    GraphGenerator PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${currentDir}")
