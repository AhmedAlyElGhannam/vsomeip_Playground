# Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

set(EXAMPLE_CONFIG_FILES
    "../config/vsomeip.json"
    "../config/vsomeip-local.json"
    "../config/vsomeip-tcp-client.json"
    "../config/vsomeip-tcp-service.json"
    "../config/vsomeip-udp-client.json"
    "../config/vsomeip-udp-service.json"
)

find_package(Boost)

# set (VSOMEIP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../interface/vsomeip/")

include_directories(
    #"${CMAKE_CURRENT_SOURCE_DIR}/../interface/compat/vsomeip"
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
    ${VSOMEIP_INCLUDE_DIRS}/../
)

link_directories(
    "/home/nemesis/Playground/vsomeip/vsomeip-3.5.5/build"
)

# Examples
add_executable(server server_main.cpp ${EXAMPLE_CONFIG_FILES})
target_link_libraries(server vsomeip3 ${VSOMEIP_NAME} ${Boost_LIBRARIES} ${DL_LIBRARY})

add_executable(client client_main.cpp ${EXAMPLE_CONFIG_FILES})
target_link_libraries(client vsomeip3 ${VSOMEIP_NAME} ${Boost_LIBRARIES} ${DL_LIBRARY})

# add_dependencies(examples request-sample response-sample subscribe-sample notify-sample)

###################################################################################################
