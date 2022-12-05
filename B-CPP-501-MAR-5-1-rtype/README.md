# R-TYPE DOCUMENTATION
\
by Samuel Parayre.
You can generate this documentation in PDF format using ```Markdown PDF``` visual extension. (CTRL + SHIFT + P , "export" and choose "PDF")
<p>&nbsp;</p>

## Summary
1. [Remotes](#REMOTES)
2. [Create Conan build folder](#create-conan-build-folder)
3. [Cmake](#cmake)
4. [.gitignore](#.gitignore)
5. [Use the project](#use-the-project)
6. [RFC Protocol](#RFC-Protocol)
    1. [TCP](#TCP)
    2. [UDP](#UDP)
<p>&nbsp;</p>

## REMOTES

to add remotes to conan you need to do :
conan remote add <NAME> <URL>

and the only remote to add is :
https://api.bintray.com/conan/conan-community/conan
https://api.bintray.com/conan/conan-center
https://api.bintray.com/conan/bincrafters/public-conan

name it randomly ;)
<p>&nbsp;</p>

## CREATE CONAN BUILD FOLDER

In order to create conan build architecture, you may need this command:

>mkdir build && cd build && conan install .. --build missing && cmake .. -G “UnixMakefiles” && cmake –build

This command will download and install all the libs contain in "conanfile.txt".
Three files will be created "conanbuildinfo.cmake", "conaninfo.txt" and "conanbuildinfo.txt" and they are necessary to compile so copy them to the root of the repo.

In build folder, run:
>cp conanbuildinfo.cmake  conanbuildinfo.txt conaninfo.txt ..
<p>&nbsp;</p>

## CMAKE

Then you are ready to compile !

>cmake CMakeLists.txt

>make
<p>&nbsp;</p>

## .gitignore

Some files are undesirable on github ! Don't forget to add all of these files to your ```.gitignore``` file.

- r-type_server
- r-type_client
- a.out
- .vscode
- CMakeCache.txt
- cmake_install.cmake
- conanbuildinfo.cmake
- conanbuildinfo.txt
- conaninfo.txt
- CMakeFiles
- README.pdf
- build
- Makefile
- *.so
<p>&nbsp;</p>

## Use the project

The project works as follow:

For the server, you need to specify two ports for client management. The first one is the TCP port for the client connexion, the second one is the UDP port used in the game. 

>./r-type_server TCP_PORT UDP_PORT

For clients, you don't need anything. The IP and port specification is done in the graphic interface. 

>./r-type_client
<p>&nbsp;</p>

## RFC Protocol

### TCP

R-TYPE TCP Protocol

Command-Reply Sequences

The server reply is defined to contain the 3-digit code, followed by one line of text, and terminated by end-of-line code <LF>.

-> : Request command from client to server
<- : Reply from server to client


        Connection Establishment
            <- 220

        Login
            LOGIN user ->
              <- 104
              <- 501 (No username)

        Exit
            EXIT ->
              <- 103

        Rooms
            CREATEROOM ->
              <- 101 <- xxxxx (Room code)
              <- 500 (Not logged in)
              <- 502 (Already in room)
            JOINROOM ->
              <- 100
              <- 500 (Not logged in)
              <- 502 (Already in room)
              <- 503 (Room full)
              <- 504 (Room not found)
              <- 505 (No rooms)
            LEAVEROOM ->
              <- 102
              <- 500 (Not logged in)
              <- 506 (Not in room)

        Game
            STARTGAME
              <<- 200 xxxx (port)
            GETMEMBERROOM
              <- 105 <- user1;user2...
              <- 507

### UDP

<p>&nbsp;</p>