# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.6.0)

#set(CMAKE_SYSTEM_NAME Android)
#set(CMAKE_SYSTEM_VERSION ) # API level


#src/main/cpp/
# was -Wa,-I${PROJECT_SOURCE_DIR}/common -Wa,-I${PROJECT_SOURCE_DIR}/modules/math

#Tell CMake these files need to go to the C compiler
function(set_file_to_c files)
  set(FLAGS
    "-x assembler-with-cpp -mfpu=neon-vfpv4 -mfloat-abi=softfp  -Wa,-I/src/main/cpp " )  #-mfpu=vfpv3-d16  -mfpu=neon
  foreach(file ${${files}})
    set_property (SOURCE ${file} PROPERTY LANGUAGE C)
    set_source_files_properties(
      ${file} PROPERTIES COMPILE_FLAGS
      ${FLAGS}
      )
  endforeach(file)
endfunction()

#Cortex-A5 -mfpu=vfpv3-fp16
##-mfpu=vfpv3-d16-fp16
#-mfpu=neon-fp16
##Cortex-A7 -mfpu=vfpv4
#-mfpu=vfpv4-d16    -mfpu=neon-vfpv4
#-mfpu=neon-vfpv4

if( ${ANDROID_ABI} STREQUAL "armeabi-v7a" )

 set(los_neon src/main/cpp/native-lib.cpp
              src/main/cpp/matrix.cpp
              src/main/cpp/ArmSimd.cpp)

               set_property(SOURCE ${los_neon} APPEND_STRING PROPERTY COMPILE_FLAGS " -mfpu=neon -ftree-vectorize")  #was  -mfpu=neon
              add_definitions("-DHAVE_NEON=1")

 set (realNeon src/main/cpp/losN.neon.s
               )
 set_file_to_c(realNeon)


 elseif( ${ANDROID_ABI} STREQUAL "arm64-v8a")

set(los_neon src/main/cpp/native-lib.cpp
             src/main/cpp/matrix.cpp
             src/main/cpp/ArmSimd.cpp)

              set_property(SOURCE ${los_neon} APPEND_STRING PROPERTY COMPILE_FLAGS " -mfpu=neon -ftree-vectorize")
             add_definitions("-DHAVE_NEON=1")

set (realNeon src/main/cpp/NeonarmSFour.cpp)
#set_file_to_c(realNeon)

elseif (${ANDROID_ABI} STREQUAL "x86")
set(los_neon  src/main/cpp/native-lib.cpp
                src/main/cpp/matrix.cpp
              src/main/cpp/x_86Simd.cpp)

set_property(SOURCE ${los_neon} APPEND_STRING PROPERTY COMPILE_FLAGS " -mssse3 -Who-unknown-attributes")
add_definitions(-DHAVE_NEON_X86=1 -DHAVE_NEON=1)


#enable_language(ASM_NASM)
#add_library(test-yasm SHARED jni/test-yasm.c jni/print_hello.asm)

else()
set (los_neon src/main/cpp/native-lib.cpp
              src/main/cpp/SimpleMat.cpp
              src/main/cpp/EmptySimd.cpp)
endif()



#add_library( native-lib
#
#             SHARED
#
  #            src/main/cpp/native-lib.cpp
  #            src/main/cpp/matrix.cpp
  #            src/main/cpp/texture.cpp
  #            )
 #                              was src/main/cpp/native-lib.cpp

add_library(andHelp STATIC /Users/SergeyLoscutnikov/Desktop/SDK/android-sdk-macosx/ndk-bundle/sources/android/cpufeatures/cpu-features.c)
add_library(native-lib SHARED  src/main/cpp/texture.cpp ${los_neon} ${realNeon})

target_include_directories(native-lib PRIVATE
                           /Users/SergeyLoscutnikov/Desktop/SDK/android-sdk-macosx/ndk-bundle/sources/android/cpufeatures
                           )

find_library( log-lib
              log )

target_link_libraries( native-lib
                        GLESv3
                        andHelp
                       ${log-lib} )