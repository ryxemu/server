CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

SET(world_sources
	client.cpp
	cliententry.cpp
	clientlist.cpp
	console.cpp
	login_server.cpp
	login_server_list.cpp
	main.cpp
	queryserv.cpp
	ucs.cpp
	wguild_mgr.cpp
	worlddb.cpp
	zonelist.cpp
	zoneserver.cpp
)

SET(world_headers
	client.h
	cliententry.h
	clientlist.h
	console.h
	login_server.h
	login_server_list.h
	main.h
	queryserv.h
	char_create_data.h
	ucs.h
	wguild_mgr.h
	world_tcp_connection.h
	worlddb.h
	zonelist.h
	zoneserver.h
)

ADD_EXECUTABLE(world ${world_sources} ${world_headers})

INSTALL(TARGETS world RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

ADD_DEFINITIONS(-DWORLD)

TARGET_LINK_LIBRARIES(world ${SERVER_LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
