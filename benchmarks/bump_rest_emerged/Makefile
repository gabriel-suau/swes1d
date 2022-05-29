INCLUDE_DIR  = /usr/local/include
LIBRARY_PATH = /usr/local/lib
CXX          = g++ -std=c++20
CXX_OPTIONS  = -Wall -Wextra -O3
MAIN_FILE  = main.cpp

bump_rest_emerged:
	$(CXX) -I$(INCLUDE_DIR) -L$(LIBRARY_PATH) $(CXX_OPTIONS) $(MAIN_FILE) -lSWES1D -o bump_rest_emerged

clean:
	rm -f bump_rest_emerged
