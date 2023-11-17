cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(reflection)

add_executable(generator "src/ceta.c")

add_custom_target(run_generator
    COMMAND generator
    DEPENDS "src/ceta.c"
    COMMENT "Running code generator"
    VERBATIM
)

add_executable(test "src/main.c")

add_dependencies(test run_generator)


# cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE="Release" -G "Ninja"