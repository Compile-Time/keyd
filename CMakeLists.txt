cmake_minimum_required(VERSION 3.13)
project(keyd)

set(CMAKE_C_STANDARD 99)

set(HEADERS
        src/config.h
        src/keyd.h
        src/error.h
        src/ini.h
        src/vkbd.h
        src/layer.h
        src/keyboard.h
        src/descriptor.h
        )

set(SOURCES
        src/config.c
        src/keyd.c
        src/error.c
        src/ini.c
        src/layer.c
        src/keyboard.c
        src/descriptor.c
        "src/vkbd/${VKBD}.c"
        )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
        -ludev \
        -I/usr/local/include \
        -L/usr/local/lib"
        )

# Get the latest git hash.
execute_process(
        COMMAND bash -c "git describe --no-match --always --abbrev=40 --dirty | tr -d '\n'"
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_VARIABLE GIT_HASH
)

# Define variables used in source code
add_definitions(
        -DCONFIG_DIR="/etc/keyd"
        -DLOCK_FILE="/var/lock/keyd.lock"
        -DLOG_FILE="/var/log/keyd.log"
        -DVERSION="2.1.0-beta"
        -DGIT_COMMIT_HASH="${GIT_HASH}"
)

add_executable(keyd "${HEADERS}" "${SOURCES}")