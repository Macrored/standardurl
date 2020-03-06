cmake_minimum_required (VERSION 2.8)

# add_definitions(-std=c++11)

project(main)

aux_source_directory(. MAIN_SRCS)
aux_source_directory(src ONEURL_SRCS)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/icu4c/include
)

# 指定库文件链接路径
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/icu4c/lib
)

# 指定生成目标
add_executable(main ${MAIN_SRCS} ${ONEURL_SRCS})

# 指定目标文件链接的库名
target_link_libraries(main icudt.lib)
target_link_libraries(main icuin.lib)
target_link_libraries(main icuio.lib)
target_link_libraries(main icutu.lib)
target_link_libraries(main icuuc.lib)
