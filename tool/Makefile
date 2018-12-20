all: clean image_qrc_generator
	rm -rf *.o

image_qrc_generator:
	g++ -c image_qrc_generator.cpp -std=c++0x
	g++ -o image_qrc_generator image_qrc_generator.o

clean:
	rm -rf *.o image_qrc_generator
