# Compilador
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Archivos fuente y objetos
SRC = main.cpp cpu.cpp instructions.cpp
OBJ = $(SRC:.cpp=.o)

# Nombre del ejecutable
TARGET = cpu

# Regla principal (compilar todo)
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar los archivos fuente en objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -f $(OBJ) $(TARGET)

# Limpiar todo (incluye dependencias generadas)
dist-clean: clean
	rm -f *.d

# Generar dependencias automáticamente
-include $(SRC:.cpp=.d)

