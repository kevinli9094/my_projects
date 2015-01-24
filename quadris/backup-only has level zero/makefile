CXX = g++ 
CXXFLAGS = -g -Wall -MMD
OBJECTS = quadris.o grid.o textdisplay.o cell.o level.o block.o iblock.o jblock.o lblock.o oblock.o sblock.o tblock.o zblock.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}

.PHONY : clean # not a file name
clean : # remove files that can be regenerated
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC} # alternative *.d *.o
