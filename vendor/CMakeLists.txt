include(FetchContent)

# fmt
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.1.1
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
message("Fetching `fmt`")
FetchContent_MakeAvailable(fmt)