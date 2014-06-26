
CFLAGS  := -I../modules -Wall -Wextra
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

bitmapfont: bitmapfont.cpp ../modules/BitmapFont/BitmapFont.cpp ../modules/BitmapFont/BitmapText.cpp
	g++ $^ $(CFLAGS) $(LDFLAGS) -o $@
