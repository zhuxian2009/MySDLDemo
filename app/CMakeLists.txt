cmake_minimum_required(VERSION 3.4.1)

set(lib_src_DIR ${CMAKE_SOURCE_DIR}/libs/armeabi-v7a)
include_directories(
     ${CMAKE_SOURCE_DIR}/src/main/cpp/include
)
add_library(sdl2_lib SHARED IMPORTED)
set_target_properties(sdl2_lib PROPERTIES IMPORTED_LOCATION
    ${lib_src_DIR}/libSDL2.so)

#add_library(sdlmain_lib SHARED IMPORTED)
#set_target_properties(sdlmain_lib PROPERTIES IMPORTED_LOCATION
#    ${lib_src_DIR}/libmain.so)

add_library( native-lib  SHARED
             src/main/cpp/native-lib.cpp
             src/main/cpp/SDL_android_main.c
             )

find_library(log-lib    log )
find_library(GLESv1_CM-lib    GLESv1_CM )
find_library(GLESv2-lib    GLESv2 )

target_link_libraries(  native-lib
                       ${log-lib}
                       ${GLESv1_CM-lib}
                       ${GLESv2-lib}
                       sdl2_lib
 #                      sdlmain_lib
                       )