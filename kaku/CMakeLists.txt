include_directories(${DRENTDOMO_SOURCE_DIR}/src)
include_directories(${DRENTDOMO_SOURCE_DIR}/gpio)
link_directories(${DRENTDOMO_BINARY_DIR}/src)
link_directories(${DRENTDOMO_BINARY_DIR}/gpio)

set(PROGRAMS kaku-send)

add_library(kaku-tx KakuTransmitter.cpp)

foreach(program ${PROGRAMS})
	add_executable(${program} ${program}.cpp)
	target_link_libraries(${program} gpio kaku-tx)
endforeach(program)