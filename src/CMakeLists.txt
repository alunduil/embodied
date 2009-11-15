ADD_EXECUTABLE(embody main.cpp embodied.cpp)
target_link_libraries(embody boost_program_options boost_regex)
target_link_libraries(embody octtree)
