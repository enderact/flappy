#include "Cloud.hpp"
#include <chrono>
#include <random>
#include "global.hpp"

Cloud::Cloud(sf::Texture* texture)
{
	cloud.setTexture(texture);
	cloud.setSize(sf::Vector2f(40, 26.667));
	cloud.setPosition(sf::Vector2f(rand_gen(sf::Vector2i(window_width - 400, window_width + 100), sf::Vector2i(100, window_height - 100))));
}

Cloud::~Cloud()
{
}

sf::Vector2f Cloud::rand_gen(sf::Vector2i x, sf::Vector2i y)
{
	unsigned seed_cloud = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generate(seed_cloud);
	std::uniform_int_distribution<int> distribution_x(x.x, x.y);
	std::uniform_int_distribution<int> distribution_y(y.x, y.y);
	return sf::Vector2f(distribution_x(generate), distribution_y(generate));
}

void Cloud::cloud_reset()
{
	cloud.setPosition(sf::Vector2f(rand_gen(sf::Vector2i(window_width - 400, window_width + 100), sf::Vector2i(100, window_height - 100))));
}

void Cloud::check()
{
	if (cloud.getPosition().x + cloud.getSize().x < 0)
	{
		cloud.setPosition(rand_gen(sf::Vector2i(window_width + 100, window_width + 300), sf::Vector2i(100, window_height - 100)));
	}
	
}

void Cloud::update(float delta_time)
{
	check();
	sf::Vector2f movement(0.0f, 0.0f);
	movement.x -= cloud_speed * delta_time;

	cloud.move(movement);
}

void Cloud::draw(sf::RenderWindow& window)
{
	window.draw(cloud);
}
