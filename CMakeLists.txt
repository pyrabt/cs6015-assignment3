cmake_minimum_required(VERSION 3.13)

#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
# Now build our tools
ADD_EXECUTABLE(quadClassifier main.cpp qdShape.cpp shapeClassifier.cpp)

# Link against LLVM libraries
#target_link_libraries(quadClassifier ${llvm_libs})
