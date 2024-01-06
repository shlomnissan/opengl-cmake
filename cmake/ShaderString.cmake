# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)
#
# ShaderString.cmake
# This function looks for *.glsl files and converts them into C-style strings

function(ShaderString)

file(GLOB_RECURSE SHADERS "**/*.glsl" "**/*.vert" "**/*.frag")
foreach(SHADER IN LISTS SHADERS)
    get_filename_component(FILENAME ${SHADER} NAME)
    get_filename_component(DIRECTORY ${SHADER} DIRECTORY)

    string(REGEX REPLACE "\\.[^.]*$" "" FILENAME_NO_EXT ${FILENAME})
    set(HEADER_FILE ${DIRECTORY}/headers/${FILENAME_NO_EXT}.h)

    message("🎨 Writing shader ${FILENAME_NO_EXT}.h")

    file(READ ${SHADER} CONTENTS)
    file(WRITE ${HEADER_FILE} "static const char* _SHADER_${FILENAME_NO_EXT} = R\"(")
    file(APPEND ${HEADER_FILE} "${CONTENTS}")
    file(APPEND ${HEADER_FILE} ")\";")
endforeach()

endfunction()