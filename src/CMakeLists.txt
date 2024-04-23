file(GLOB SOURCE_FILES CONFIGURE_DEPENDS *.cpp)
add_executable(graphs ${SOURCE_FILES})
target_compile_definitions(graphs PRIVATE CLIENT)
target_link_libraries(graphs sfml-graphics sfml-window sfml-audio sfml-network sfml-system)
target_compile_features(graphs PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET graphs
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<BOOL:${ARCH_64BITS}>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:graphs>
        VERBATIM)
endif()

# Installing instructions
install(TARGETS graphs DESTINATION ${CMAKE_SOURCE_DIR}/bin)