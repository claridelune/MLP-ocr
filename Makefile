# Nombre del ejecutable
TARGET = main

# Compilador
CXX = g++

# Flags de compilación
CXXFLAGS = -std=c++11 -Wall

# Librerías adicionales
LIBS = -lGL -lGLU -lglut

# Archivos fuente
SRCS = main.cpp DataVisualizer.cpp Neuron.cpp Perceptron.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	rm -f $(OBJS) $(TARGET)
