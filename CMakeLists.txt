cmake_minimum_required(VERSION 3.11)
project(test)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)
aux_source_directory(. ALL_SRCS)
#add_executable(DeepCV ${ALL_SRCS})
add_executable(test test.c image_core.c image_engine.c image_math.c image_filter.c image_proc.c image_io.c evector.c arm_malloc.c image_draw.c usr_api.c)
target_link_libraries(test libjpeg.a)
