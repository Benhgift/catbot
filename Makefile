OBJS = obj/main.o

robosim.out: $(OBJS)
	g++ -std=c++11 -o robosim.out $(OBJS) -pthread -ldrawstuff `pkg-config --libs glu ode` -lX11 -lXext

obj/main.o: src/main.cpp
	g++ -c -std=c++11 -o $@ $< `pkg-config --cflags ode`
