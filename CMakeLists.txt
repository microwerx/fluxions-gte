cmake_minimum_required(VERSION 3.16)
project(fluxions-gte)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

if (APPLE)
   include_directories(/usr/local/include)
   link_directories(/usr/local/lib)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/hatchetfish/include)

add_library(${PROJECT_NAME}
    STATIC
    src/fluxions_gte.cpp
    src/fluxions_gte_bounding_box.cpp
    src/fluxions_gte_color3.cpp
    src/fluxions_gte_color4.cpp
    src/fluxions_gte_color_tests.cpp
    src/fluxions_gte_geometric_algebra.cpp
    src/fluxions_gte_image.cpp
    src/fluxions_gte_image_operations.cpp
    src/fluxions_gte_iostream.cpp
    src/fluxions_gte_math.cpp
    src/fluxions_gte_matrix2.cpp
    src/fluxions_gte_matrix3.cpp
    src/fluxions_gte_matrix4.cpp
    src/fluxions_gte_matrix_extra.cpp
    src/fluxions_gte_matrix_stack.cpp
    src/fluxions_gte_quaternion.cpp
    src/fluxions_gte_ray.cpp
    src/fluxions_gte_rect.cpp
    src/fluxions_gte_scalar.cpp
    src/fluxions_gte_spherical_harmonic.cpp
    src/fluxions_gte_superquadric.cpp
    src/fluxions_gte_transformation.cpp
    src/fluxions_gte_vector2.cpp
    src/fluxions_gte_vector3.cpp
    src/fluxions_gte_vector4.cpp
    )

if(${CMAKE_VERSION} VERSION_GREATER "3.16.0")
    message("Fluxions GTE using precompiled headers")
    target_precompile_headers(${PROJECT_NAME} PRIVATE src/fluxions_gte_pch.cpp)
endif()
