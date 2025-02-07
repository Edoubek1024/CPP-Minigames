list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

include(CMakeFindDependencyMacro)

# When installing, save whether SFML was built using system dependencies.
set(SFML_BUILT_USING_SYSTEM_DEPS OFF)

# start with an empty list
set(FIND_SFML_DEPENDENCIES_NOTFOUND)

if(SFML_BUILT_USING_SYSTEM_DEPS)
    find_dependency(Freetype)
else()
    find_dependency(Freetype CONFIG PATHS "${CMAKE_CURRENT_LIST_DIR}/../../../")
endif()

if(FIND_SFML_DEPENDENCIES_NOTFOUND)
    set(FIND_SFML_ERROR "SFML found but some of its dependencies are missing (${FIND_SFML_DEPENDENCIES_NOTFOUND})")
    set(SFML_FOUND OFF)
endif()
