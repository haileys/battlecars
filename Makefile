CXXFLAGS=-g -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual -Wextra -Werror -Wno-unused-parameter -Wno-unused-function -iquote inc/ \
			-I deps/sfml/mac/include -I deps/gwen/include/ -fno-rtti

LDFLAGS=-framework SFML -framework sfml-graphics -framework sfml-window -framework sfml-system -framework sfml-network \
		-framework OpenGL -Ldeps/gwen/lib/macosx/ -lgwen_static -lunittest -lGWEN-Renderer-SFML

all: client server

clean:
	rm -f src/client/*.o src/client/**/*.o src/server/*.o src/server/**/*.o client server

client: src/client/main.o src/client/game.o src/client/scene.o src/client/single_player.o \
		src/client/main_menu.o src/client/asset_cache.o src/client/ui/main_menu.o
	g++ $(CXXFLAGS) $(LDFLAGS) -o client src/client/*.o src/client/**/*.o

server: src/server/main.o src/server/player.o src/server/server.o
	g++ $(CXXFLAGS) $(LDFLAGS) -o server src/server/*.o #src/server/**/*.o

src/%.o: src/%.cc inc/*.hh