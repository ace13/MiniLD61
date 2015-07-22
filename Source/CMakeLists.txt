set( HEADERS
	Application.hpp	
	FX/Particles.hpp
	Menu/MainMenu.hpp
	Menu/MenuPane.hpp
	Menu/Options.hpp
	State/GameState.hpp
	State/IntroState.hpp
	State/MenuState.hpp
	State/ScoreState.hpp
	State/StateManager.hpp
	Util/Easing.hpp
	Util/Font.hpp
	Util/Profiling.hpp
)

set( SOURCES
	Application.cpp
	FX/Particles.cpp
	Menu/MainMenu.cpp
	Menu/MenuPane.cpp
	Menu/Options.cpp
	State/GameState.cpp
	State/IntroState.cpp
	State/MenuState.cpp
	State/ScoreState.cpp
	State/StateManager.cpp
	Util/Easing.cpp
	Util/Font.cpp
	Util/Profiling.cpp

	main.cpp
)

if (NOT WIN32 AND NOT APPLE)
	find_package( FontConfig )
	if ( FONTCONFIG_FOUND )
		add_definitions( -DFONTCONFIG )
	endif()
	include_directories( ${FONTCONFIG_INCLUDE_DIR} )
endif()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
add_executable( MiniLD61 ${HEADERS} ${SOURCES} )
target_link_libraries( MiniLD61 ${SFML_LIBRARIES} )

if (NOT WIN32 AND NOT APPLE)
	target_link_libraries( MiniLD61 ${FONTCONFIG_LIBRARIES} )
endif()

