option(POLAR_GENERIC_SYCL_RT "" OFF)
option(POLAR_GENERIC_CUDA_RT "" ON)
option(POLAR_GENERIC_HIP_RT "" OFF)
option(POLAR_GENERIC_VULKAN_RT "" ON)
option(POLAR_GENERIC_OPENCL_RT "" OFF)
option(POLAR_GENERIC_METAL_RT "" ON)

add_subdirectory(support)

if (POLAR_GENERIC_SYCL_RT)
    set(POLAR_HAS_SYCL "true" CACHE STRING "" FORCE)
    add_subdirectory(sycl)
else()
    set(POLAR_HAS_SYCL "false" CACHE STRING "" FORCE)
endif()

find_package(CUDAToolkit)
if (POLAR_GENERIC_CUDA_RT AND CUDAToolkit_FOUND)
    add_subdirectory(cuda)
else()
    set(POLAR_HAS_CUDA "false" CACHE STRING "" FORCE)
endif()

if (NOT DEFINED ROCM_PATH)
    if (NOT DEFINED ENV{ROCM_PATH})
        set(ROCM_PATH "/opt/rocm" CACHE PATH "Path to which ROCm has been installed")
    else()
        set(ROCM_PATH $ENV{ROCM_PATH} CACHE PATH "Path to which ROCm has been installed")
    endif()
    set(HIP_PATH "${ROCM_PATH}/hip" CACHE PATH " Path to which HIP has been installed")
endif()
set(CMAKE_MODULE_PATH "${HIP_PATH}/cmake" ${CMAKE_MODULE_PATH})
find_package(HIP)
if (POLAR_GENERIC_HIP_RT AND HIP_FOUND)
  add_subdirectory(hip)
else()
  set(POLAR_HAS_HIP "false" CACHE STRING "" FORCE)
endif()

find_package(Vulkan)
if (POLAR_GENERIC_VULKAN_RT AND Vulkan_FOUND)
    add_subdirectory(vulkan)
else()
    set(POLAR_HAS_VULKAN "false" CACHE STRING "" FORCE)
endif()

if (POLAR_GENERIC_METAL_RT AND APPLE)
    add_subdirectory(metal)
else()
    set(POLAR_HAS_METAL "false" CACHE STRING "" FORCE)
endif()

set(POLAR_HAS_OPENCL "false" CACHE STRING "" FORCE)

# Runtime driver
add_subdirectory(driver)
