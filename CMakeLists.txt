cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

project(reflection)


add_executable(generator "src/yeta.c" "src/yt_vector.c" "src/yt_string.c" "src/yt_file.c" "src/yt_lexer.c"
                            "src/yt_generator.c" "src/yt_interpreter.c" "src/yt_parser.c")

add_custom_target(run_generator
    COMMAND generator
    COMMENT "Running code generator"
    VERBATIM
)

add_executable(test "sandbox/main.c")

#add_dependencies(test run_generator)

# cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE="Release" -G "Ninja"