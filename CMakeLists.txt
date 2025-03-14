cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(GEODE_DISABLE_PRECOMPILED_HEADERS ON)

project(AnimatedProfiles VERSION 1.0.1)

add_library(${PROJECT_NAME} SHARED
    src/hooks/AchievementCell.cpp
    src/hooks/CCAnimatedSprite.cpp
    src/hooks/CCTouchDispatcher.cpp
    src/hooks/CommentCell.cpp
    src/hooks/CommunityCreditsPage.cpp
    src/hooks/GJGarageLayer.cpp
    src/hooks/GJItemIcon.cpp
    src/hooks/GJLevelScoreCell.cpp
    src/hooks/GJRequestCell.cpp
    src/hooks/GJScoreCell.cpp
    src/hooks/GJUserCell.cpp
    src/hooks/ItemInfoPopup.cpp
    src/hooks/ProfilePage.cpp
    src/hooks/PurchaseItemPopup.cpp
    src/AnimatedIcons.cpp
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
