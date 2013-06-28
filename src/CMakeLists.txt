include_directories(${DRENTDOMO_SOURCE_DIR}/src)
link_directories(${DRENTDOMO_BINARY_DIR}/src)

set(PROGRAMS test)

add_library(gpio GpioPin.cpp)
add_library(tx KakuTransmitter.cpp)

foreach(program ${PROGRAMS})
	add_executable(${program} ${program}.cpp)
	target_link_libraries(${program} gpio tx)
endforeach(program)