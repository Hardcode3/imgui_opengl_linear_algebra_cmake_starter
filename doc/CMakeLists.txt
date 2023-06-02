include(${PROJECT_SOURCE_DIR}/cmake/build_doc.cmake)

build_docs(
    "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile" 
    "${PROJECT_SOURCE_DIR}"
    "${CMAKE_PROJECT_SOURCE_DIR}/doc"
)