cmake_minimum_required(VERSION 3.28)
project(Http-Server LANGUAGES C)

add_executable(Http-Server)

set_property(TARGET Http-Server PROPERTY C_STANDARD 99)

target_sources(Http-Server
    PRIVATE src/http_server.c
    PRIVATE src/http_parser.c
)

target_include_directories(Http-Server PRIVATE include)