# glob_target_files(
#     <BASE> output variables name base
#     TARGET_ROOT <TARGET_ROOT_VALUE> <TARGET root>
#     TARGET_NAME <TARGET_NAME_VALUE> <project name, used to search for main_*.*>
#
# Build lists of library source and include files.
# As result function will set following variables with corresponding values:
#
# <BASE>_SOURCE - list of TARGET source files, excluding main_*.*
# <BASE>_HEADER - list of TARGET include files in 'include'
#
function(glob_target_files BASE)
    set(options "")
    set(oneValueArgs TARGET_ROOT TARGET_NAME)
    set(multiValueArgs "")

    cmake_parse_arguments(glob_target_files "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

     # Find all files in src folder
    file(GLOB_RECURSE ALL_SRC_FOLDER_FILES "${glob_target_files_TARGET_ROOT}/src/?*.*")

    if (ALL_SRC_FOLDER_FILES)
        # Remove all non-source files start with '.'
        file(GLOB_RECURSE FOLDER_DOT_FILES "${glob_target_files_TARGET_ROOT}/src/._?*.*")
        if (FOLDER_DOT_FILES)
            message(STATUS "Ignore files: ${FOLDER_DOT_FILES}")
            list(REMOVE_ITEM ALL_SRC_FOLDER_FILES ${FOLDER_DOT_FILES})
        endif()
    endif()

    # Find all files in include folder
    file(GLOB_RECURSE ALL_INCLUDE_FOLDER_FILES "${glob_target_files_TARGET_ROOT}/include/?*.*")

    # Return TARGET files
    set(${BASE}_SOURCE ${ALL_SRC_FOLDER_FILES} PARENT_SCOPE)
    set(${BASE}_HEADER ${ALL_INCLUDE_FOLDER_FILES} PARENT_SCOPE)
endfunction()