INCLUDE_DIR  = /home/gabriel/Documents/Informatique/swes1d/src/
LIBRARY_PATH = /home/gabriel/Documents/Informatique/swes1d/install/lib
CXX          = g++ -std=c++20
CXX_OPTIONS  = -Wall -Wextra -O3
MAIN_FILE  = main.cpp

bump_fluvial:
	$(CXX) -I$(INCLUDE_DIR) -L$(LIBRARY_PATH) $(CXX_OPTIONS) $(MAIN_FILE) -lSWES1D -o bump_fluvial

clean:
	rm -f bump_fluvial
