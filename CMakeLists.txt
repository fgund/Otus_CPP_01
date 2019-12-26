cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
  message("TRAVIS_BUILD_NUMBER not defined. Setting its value to 1.")
  set(ENV{TRAVIS_BUILD_NUMBER} 1)
endif(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})

project(Otus_CPP_01 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file(version.h.in version.h)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) 
conan_basic_setup()

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
#add_executable(boost_test_version boost_test_version.cpp)
add_executable(g_test_version g_test_version.cpp)

set_target_properties(helloworld_cli helloworld g_test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    helloworld
)
#target_link_libraries(boost_test_version
#    helloworld
#    ${CONAN_LIBS}
#)
target_link_libraries(g_test_version
    helloworld
    ${CONAN_LIBS}
)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld PRIVATE
        /W4
    )
#    target_compile_options(boost_test_version PRIVATE
#       /W4 /MD
#    )
    target_compile_options(g_test_version PRIVATE
        /W4 /MD
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
#    target_compile_options(boost_test_version PRIVATE
#        -Wall -Wextra -pedantic -Werror
#    )
    target_compile_options(g_test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

if (MSVC)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/)
endif()
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

if (MSVC)
    set(CPACK_GENERATOR NSIS)
else ()
    set(CPACK_GENERATOR DEB)
endif()

set(CPACK_PACKAGE_NAME "HelloWorld")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_SOURCE_DIR}/README.md)

include(CPack)

enable_testing()

add_test(g_test_version "bin/g_test_version")