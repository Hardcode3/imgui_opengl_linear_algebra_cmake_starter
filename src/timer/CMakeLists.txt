message(STATUS "> Found sources/timer directory")

set(target_name timer)

add_library(${target_name} STATIC "")

target_sources(${target_name}
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src/timer/timer.cpp"

    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/timer/timer.h"

)

target_include_directories (${target_name}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include/timer"
        "${PROJECT_BINARY_DIR}"
)


set_property(TARGET ${target_name} PROPERTY FOLDER "Sources/Timer")
