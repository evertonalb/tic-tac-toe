find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

function (add_with_sdl3 lib)
	add_library(${lib} STATIC ${lib}.cpp)
	target_link_libraries(${lib} PUBLIC SDL3::SDL3)
	target_include_directories(${lib} PUBLIC ${CMAKE_SOURCE_DIR}/include)
endfunction()

add_with_sdl3(game)
target_link_libraries(game PUBLIC SDL3_image::SDL3_image)
target_link_libraries(game PUBLIC SDL3_ttf::SDL3_ttf)

add_with_sdl3(mark)