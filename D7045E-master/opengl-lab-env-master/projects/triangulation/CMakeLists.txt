#--------------------------------------------------------------------------
# triangulation project
#--------------------------------------------------------------------------

FILE(GLOB triangulation_headers code/*.h)
FILE(GLOB triangulation_sources code/*.cc)

SET(files_triangulation ${triangulation_headers} ${triangulation_sources})
SOURCE_GROUP("triangulation" FILES ${files_triangulation})

ADD_EXECUTABLE(triangulation ${files_triangulation})
TARGET_LINK_LIBRARIES(triangulation core render glm_static)
ADD_DEPENDENCIES(triangulation core render glm_static)