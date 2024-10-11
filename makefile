# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -I./headers # Добавляем -I./headers для указания директории с заголовочными файлами
  
# Директории
SRCDIR = src
BINDIR = bin

# Имя исполняемого файла
TARGET = $(BINDIR)/coursework

# Исходные файлы
SRC = $(SRCDIR)/main.cpp $(SRCDIR)/func.cpp

# Объектные файлы
OBJ = $(SRC:.cpp=.o)

# Правило для сборки всех файлов
all: $(TARGET)

# Правило для создания исполняемого файла
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Правило для компиляции .cpp файлов в .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка всех сгенерированных файлов
# rm -f $(OBJ) $(TARGET)
# del /Q src\*.o bin\coffee_machine.exe
clean:
	del /Q src\*.o bin\coursework.exe
	
# Запуск программы после сборки
run: $(TARGET)
	./$(TARGET)