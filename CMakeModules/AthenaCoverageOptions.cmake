function(enable_coverage)
    if (ENABLE_CODE_COVERAGE)
        set(FLAGS "${CMAKE_CXX_FLAGS} ")
        if(UNIX)
            set(FLAGS "${FLAGS} -Wall -fprofile-arcs -ftest-coverage")
            if (NOT APPLE)
                set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov")
            endif()
        endif()
        set(CMAKE_CXX_FLAGS "${FLAGS}" PARENT_SCOPE)
        set(CMAKE_C_FLAGS "${FLAGS}" PARENT_SCOPE)
    endif()
endfunction()