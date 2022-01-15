cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

option(STEREYE_PC "PC mode, debug workstation, normal viewer" ON)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "amd64.*|x86_64.*|AMD64.*")
    if (STEREYE_PC)
        add_definitions(-DSTEREYE_PC)
    endif()
else()
    # system platform not match pc, set to OFF
    set(STEREYE_PC OFF)
endif()

if(STEREYE_PC)
    set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -gencode arch=compute_61,code=sm_61;-gencode arch=compute_75,code=compute_75")
    find_package(CUDA)

    include_directories(
        /usr/local/cuda/include
    )

    link_directories(
        /usr/local/cuda/lib64/
    )

    add_library(decoder_lib SHARED
        JPEGDecoder.cpp
    )

    target_link_libraries(decoder_lib
        PRIVATE
        ${CUDA_LIBRARIES}
        ${CUDA_npp_LIBRARY}
        nvjpeg
    )

else()
    link_directories(
        /usr/lib/aarch64-linux-gnu/tegra
    )

    include_directories(
        /usr/src/jetson_multimedia_api/include/libjpeg-8b
    )

    add_library(decoder_lib SHARED
        JPEGDecoder.cpp
    )

    target_link_libraries(decoder_lib
	PRIVATE
        nvjpeg
    )
endif()

# find_package(OpenCV REQUIRED)
# include_directories(
#     ${OpenCV_INCLUDE_DIRS}
# )
# add_executable(decoder
#     JPEGDecoderTest.cpp
# )
# 
# target_link_libraries(decoder
#     decoder_lib
#     ${OpenCV_LIBS}
# )

