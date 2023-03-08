
add_executable(reflection_base
    main.cpp
)

target_link_libraries(reflection_base
)
target_include_directories(reflection_base
PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
