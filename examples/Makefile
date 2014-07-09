
CFLAGS  := -I../modules -Wall -Wextra
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

all: bitmapfont particles

bitmapfont: bitmapfont.cpp ../modules/BitmapFont/BitmapFont.cpp ../modules/BitmapFont/BitmapText.cpp
	g++ $^ $(CFLAGS) $(LDFLAGS) -o $@

particles: particles.cpp ../modules/ParticleSystem/ParticleSystem.cpp ../modules/ParticleSystem/Utils/Math.cpp
	g++ $^ $(CFLAGS) -std=c++11 $(LDFLAGS) -o $@

clean:
	-@rm bitmapfont
	-@rm particles
