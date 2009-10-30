include_directories(${EMBODIED_SRC_DIR}/include)
link_directories(${EMBODIED_SRC_DIR}/lib)

ADD_EXECUTABLE(embody main.cpp embodied.cpp)
target_link_libraries(embody boost_program_options point points cell)
