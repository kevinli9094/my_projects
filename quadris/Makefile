CXX = g++ 
CXXFLAGS = -g -Wall -MMD
OBJECTS = quadris.o grid.o textdisplay.o window.o cell.o level.o block.o iblock.o jblock.o lblock.o oblock.o sblock.o tblock.o zblock.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11
-include ${DEPENDS}
