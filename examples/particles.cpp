#include "ParticleSystem/ParticleSystem.hpp"
#include "ParticleSystem/Utils/Math.hpp"

/**
 * Example of custom emitter for a scrolling-star background
 */
class StarsEmitter: public ParticleSystem::Emitter
{
public:
	void onParticleUpdated(ParticleSystem::Particle& particle, float) const override
	{
		if (particle.position.x < 0)
		{
			resetParticle(particle);
			particle.position.x = 800;
		}
	}

	void onParticleCreated(ParticleSystem::Particle& particle) const override
	{
		particle.position.x = math::rand(0, 800);
		particle.position.y = math::rand(0, 600);
	}
};


int main()
{
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");
    app.setFramerateLimit(60);

	ParticleSystem& particles = ParticleSystem::getInstance();
	sf::Texture texture;
	texture.loadFromFile("resources/particles.png");
	texture.setSmooth(true);
	particles.setTexture(&texture);

	// Stars
	StarsEmitter stars;
	stars.setLifetime(0);
	stars.setParticleColor(sf::Color(255, 255, 255, 192));
	stars.setSpeed(150.f, 140.f);
	stars.setAngle(-math::PI, 0.1);
	stars.setTextureRect(sf::IntRect(16, 16, 3, 3));
	stars.createParticles(200);

	// Smoke
	ParticleSystem::Emitter smoke;
	smoke.setTextureRect(sf::IntRect(0, 0, 16, 16));
	smoke.setLooping(true);
	smoke.setSpeed(50, 25);
	smoke.setLifetime(1.5);
	smoke.setScale(0.5, 2);

	// Green
	ParticleSystem::Emitter green;
	green.setLooping(true);
	green.setScale(1.5, 0.5);
	green.setSpeed(30.f, 10.f);
	green.setLifetime(5);
	green.setTextureRect(sf::IntRect(0, 0, 16, 16));
	green.setParticleColor(sf::Color::Green);

	// Explosion
	ParticleSystem::Emitter explosion;
	explosion.setTextureRect(sf::IntRect(24, 31, 8, 1));
	explosion.setScale(2.f, 0.5f);
	explosion.setSpeed(150, 50);

	sf::Font font;
	font.loadFromFile("resources/goldfish_9px.ttf");
	sf::Text text("E: Explosion\nS: Smoke\nT: Stars\nG: Green\n----\nA: BlendAlpha (default)\nD: BlendAdd\nC: Clear", font, 9);

	sf::Clock clock;
	sf::BlendMode blendMode = sf::BlendAlpha;
	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			switch (event.type)
            {
				case sf::Event::Closed:
					app.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::Escape:
							app.close();
							break;
						case sf::Keyboard::S:
							smoke.createParticles(200);
							break;
						case sf::Keyboard::T:
							stars.createParticles(50);
							break;
						case sf::Keyboard::G:
							green.createParticles(200);
							break;
						case sf::Keyboard::E:
							explosion.setPosition(math::rand(100, 700), math::rand(100, 500));
							explosion.createParticles(50);
							break;
						case sf::Keyboard::C:
							particles.clear();
							break;
						case sf::Keyboard::A:
							blendMode = sf::BlendAlpha;
							break;
						case sf::Keyboard::D:
							blendMode = sf::BlendAdd;
							break;
						default:
							break;
					}
					break;
				case sf::Event::MouseMoved:
				{
					sf::Vector2f pos = app.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
					smoke.setPosition(pos);
					green.setPosition(pos);
					break;
				}
				default:
					break;
            }

        }

		float frametime = clock.restart().asSeconds();
		particles.update(frametime);

		app.clear();
		app.draw(text);
		sf::RenderStates states;
		states.blendMode = blendMode;
		app.draw(particles, states);
		app.display();
	}
	return 0;
}

