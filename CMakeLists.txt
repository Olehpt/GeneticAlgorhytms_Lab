cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GA_lab")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(gapp_DIR
    "C:/Users/User/libs/gapp/lib/cmake/gapp"
)

find_package(gapp CONFIG REQUIRED)

add_executable (GA_lab "GA_lab.cpp" "GA_lab.h" "src/Task1.cpp" "src/Task1.h" "src/Task2.h" "src/Task2.cpp" "src/Schedule.cpp" "src/Schedule.h" "src/ScheduleData.h" "other/Gradient.h" "other/Gradient.cpp" "other/GreedySchedule.h" "other/GreedySchedule.cpp")

target_link_libraries(GA_lab PRIVATE gapp::gapp)



