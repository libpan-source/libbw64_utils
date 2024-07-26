set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES
        main.cpp
    )

if(WIN32)
    add_executable(axml_utils
        WIN32
        ${SOURCE_FILES}
    )
elseif(APPLE)
    add_executable(axml_utils
        ${SOURCE_FILES}
    )
	set_target_properties(axml_utils PROPERTIES
		MACOSX_BUNDLE TRUE
		MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
	)
else()
    add_executable(axml_utils
        ${SOURCE_FILES}
    )
endif()

# set_target_properties(axml_utils PROPERTIES
# 	LINK_FLAGS /SUBSYSTEM:CONSOLE
# )

target_include_directories(axml_utils
    PUBLIC
        #$<TARGET_PROPERTY:IRT::bw64,INCLUDE_DIRECTORIES>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../thrid_party/libbw64/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<TARGET_PROPERTY:adm,INCLUDE_DIRECTORIES>
)

target_link_libraries(axml_utils
    PUBLIC
      IRT::bw64
      adm
)

target_compile_features(axml_utils
    PRIVATE
        cxx_std_17)