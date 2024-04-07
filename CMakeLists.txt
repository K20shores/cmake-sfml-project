cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

include(FetchContent)
FetchContent_Declare(sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)

set(CPACK_SOURCE_IGNORE_FILES ${sfml_SOURCE_DIR})
if (NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(CMakeSFMLProject src/main.cpp)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

set(OS_NAME "MacOS")
set(CPACK_GENERATOR "ZIP;DragNDrop")

set_target_properties(CMakeSFMLProject 
    PROPERTIES 
        MACOSX_BUNDLE TRUE
        INSTALL_RPATH "$ORIGIN"
)

if(APPLE)
    # Set the install name directory for shared libraries to be relative to the executable
    set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")

    # Copy SFML shared libraries into the app bundle
    install(DIRECTORY ${SFML_BINARY_DIR}/lib/ DESTINATION ${CMAKE_BINARY_DIR}/bin/${CMAKE_PROJECT_NAME}.app/Contents/Frameworks
            FILES_MATCHING PATTERN "*.dylib")

    # Create a macOS app bundle
    set(MACOS_BUNDLE_BUNDLE_NAME ${CMAKE_PROJECT_NAME})
    set(MACOS_BUNDLE_GUI_IDENTIFIER "com.example.${CMAKE_PROJECT_NAME}")
    set(MACOS_BUNDLE_ICON_FILE "")
    set(MACOS_BUNDLE_BUNDLE_VERSION "1.0.0")
    set(MACOS_BUNDLE_SHORT_VERSION_STRING "1.0.0")

    install(TARGETS CMakeSFMLProject
            BUNDLE DESTINATION . COMPONENT Runtime)
endif()

# Set the CPack properties
set(CPACK_BUNDLE_NAME "Example")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-${OS_NAME}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Example")
set(CPACK_PACKAGE_VENDOR "SFML")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)