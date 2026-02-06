cmake_minimum_required(VERSION 3.11)

project(hello)

add_executable(${PROJECT_NAME} 
    main.c
    
)




# 👇 Tell compiler where matrix2.h is
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)



target_link_libraries(${PROJECT_NAME} PRIVATE
    pspdebug
    pspdisplay
    pspge
)

create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH NULL
    BACKGROUND_PATH NULL
    PREVIEW_PATH NULL
    TITLE ${PROJECT_NAME}
    VERSION 01.00
)
