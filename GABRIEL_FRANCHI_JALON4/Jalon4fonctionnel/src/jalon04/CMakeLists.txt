cmake_minimum_required(VERSION 2.8.3)

project(RE216_JALON04)

#add here source files you need to compile and link to the client app
SET(SRC_CLIENT
	client.c
	user.c
	fonction.c
	user.h
	fonction.h
	salon.c
	salon.h
	)


add_executable(RE216_JALON04_CLIENT ${SRC_CLIENT})


#add here source files you need to compile and link to the server app
SET(SRC_SERVER
        server.c
	user.c
	fonction.c
	user.h
	fonction.h
	salon.c
	salon.h
	)


add_executable(RE216_JALON04_SERVER  ${SRC_SERVER})


