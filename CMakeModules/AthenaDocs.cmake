function(enable_docs)
    find_package(Doxygen)
    if (${DOXYGEN_FOUND})
        set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR})
        configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        add_custom_target(docs COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    else ()
        message(WARNING "Doxygen not found. Docs will not be generated")
    endif ()
endfunction()