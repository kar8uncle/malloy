include(FetchContent)

########################################################################################################################
# Boost
########################################################################################################################
find_package(
    Boost
    1.73.0
    REQUIRED
)

########################################################################################################################
# spdlog
########################################################################################################################
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG        v1.8.3
)
FetchContent_MakeAvailable(spdlog)
