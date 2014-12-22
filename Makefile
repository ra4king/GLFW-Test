FILES = main.cpp utils.cpp
OUTPUT = glfw-test

all:
	mkdir -p build
	cd src; g++ -std=c++11 $(FILES) -o ../build/$(OUTPUT) -lepoxy -lglfw3 -lm -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi
	cp -r res/* build/
	cd build; ./$(OUTPUT)

run:
	cd build; ./$(OUTPUT)

clean:
	rm -rf build/
