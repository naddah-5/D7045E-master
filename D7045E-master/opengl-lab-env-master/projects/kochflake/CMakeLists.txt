#--------------------------------------------------------------------------
# kochflake project
#--------------------------------------------------------------------------

FILE(GLOB kochflake_headers code/*.h)
FILE(GLOB kochflake_sources code/*.cc)

SET(files_kochflake ${kochflake_headers} ${kochflake_sources})
SOURCE_GROUP("kochflake" FILES ${files_kochflake})

ADD_EXECUTABLE(kochflake ${files_kochflake})
TARGET_LINK_LIBRARIES(kochflake core render glm_static)
ADD_DEPENDENCIES(kochflake core render glm_static)