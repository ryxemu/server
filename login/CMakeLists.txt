CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

SET(eqlogin_sources
	client.cpp
	client_manager.cpp
	config.cpp
	database.cpp
	eq_crypto.cpp
	main.cpp
	server_manager.cpp
	world_server.cpp
)

SET(eqlogin_headers
	client.h
	client_manager.h
	config.h
	database.h
	eq_crypto.h
	login_server.h
	login_structures.h
	options.h
	server_manager.h
	world_server.h
)

ADD_EXECUTABLE(login ${eqlogin_sources} ${eqlogin_headers})

INSTALL(TARGETS login RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

TARGET_LINK_LIBRARIES(login ${SERVER_LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)