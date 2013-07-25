EXECUTABLE = evolution

COMPILER = g++

LIBDIRS= -L/opt/local/lib -L/usr/local/lib
LIBS = -lBulletDynamics -lBulletCollision -lLinearMath -framework Cocoa -framework OpenGL -lSDL2 -lSDL2main -lboost_thread-mt -lboost_system-mt
INCLUDES = -I/usr/local/include/bullet -I/opt/local/include -I/usr/local/include

LDFLAGS= $(LIBDIRS) $(LIBS)

SRC = *.cpp

all: $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(COMPILER) -o $(EXECUTABLE) $(SRC) $(INCLUDES) $(LDFLAGS)

clean: 
	-@rm $(EXECUTABLE) 2>/dev/null || true
	-@rm *.o 2>/dev/null || true
