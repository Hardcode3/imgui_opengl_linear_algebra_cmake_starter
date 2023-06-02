
function(build_docs DOXYFILE_PATH INPUT_DIR OUTPUT_DIR)

    # tests if Dopxygen is installed locally
    find_package(Doxygen REQUIRED)
    if (NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "> Doxygen not found, install it of disbale the build or the documentation")
        return()
    endif()

    # Configure Doxygen with the specified Doxyfile path
    set(DOXYFILE ${DOXYFILE_PATH})
    set(DOXYGEN_EXECUTABLE ${DOXYGEN_EXECUTABLE})
    
    # launch the command
    execute_process(
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
        WORKING_DIRECTORY ${INPUT_DIR}
        RESULT_VARIABLE DOXYGEN_RESULT
        TIMEOUT 600
        OUTPUT_QUIET
    )

    # Check if Doxygen was successful
    if(DOXYGEN_RESULT)
        message(FATAL_ERROR "Doxygen failed with error code ${DOXYGEN_RESULT}")
    endif()

    # Install the documentation
    # install(DIRECTORY ${DOC_OUTPUT_DIR} DESTINATION share/doc)

endfunction()
