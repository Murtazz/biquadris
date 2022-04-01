CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD -L/usr/X11/lib -I/usr/X11/include
EXEC = biquadris
OBJECTS = main.o Board.o BiqBoard.o Cell.o Block.o LBlock.o IBlock.o OBlock.o SBlock.o TBlock.o JBlock.o ZBlock.o Level.o Window.o Draw.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}  -lX11 

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
