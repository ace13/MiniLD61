set( HEADERS
	Application.hpp	
	FX/Particles.hpp
	State/GameState.hpp
	State/IntroState.hpp
	State/MenuState.hpp
	State/ScoreState.hpp
	State/StateManager.hpp
	Util/Font.hpp
	Util/Profiling.hpp
)

set( SOURCES
	Application.cpp
	FX/Particles.cpp
	State/GameState.cpp
	State/IntroState.cpp
	State/MenuState.cpp
	State/ScoreState.cpp
	State/StateManager.cpp
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

add_executable( MiniLD61 ${HEADERS} ${SOURCES} )
target_link_libraries( MiniLD61 ${SFML_LIBRARIES} )

if (NOT WIN32 AND NOT APPLE)
	target_link_libraries( MiniLD61 ${FONTCONFIG_LIBRARIES} )
endif()

