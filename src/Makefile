# Include OpenCV library and build main.cpp
all: main.cpp
	g++ -o rt_object_tracking main.cpp Image_Processor.cpp Object_Tracker.cpp `pkg-config --cflags --libs opencv`

clean: 
	$(RM) rt_object_tracking

