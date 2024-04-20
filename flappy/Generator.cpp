#include "Generator.hpp"
#include <chrono>
#include <random>

Generator::Generator(sf::Texture* texture, bool hardmode = false)
{
	this->hardmode = hardmode;
	for (int i = 0; i < 3; i++)
	{
		Pipe p(forward_speed, rand_gen(), hardmode);
		p.set_pipe_texture(texture);
		p.set_x(900 + distance_between_pipes * i);
		pipe_container.push_back(p);
	}
}

Generator::~Generator()
{
}

int Generator::rand_gen()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generate(seed);
	std::uniform_int_distribution<int> distribution(-(pipe_axis-100), window_height - pipe_axis - distance_between_pipes - 100);
	return distribution(generate);
}

void Generator::add_pipe(sf::Texture* texture)
{
	Pipe p(forward_speed, rand_gen(), hardmode);
	p.set_pipe_texture(texture);
	p.set_x(450 + distance_between_pipes);
	pipe_container.push_back(p);
}

bool Generator::check_collision(sf::RectangleShape& bird)
{
	for (Pipe& p : pipe_container)
	{
		if (bird.getPosition().x + bird_width >= p.get_position_upper().x + 5 && bird.getPosition().x <= p.get_position_upper().x + pipe_width - 5
			&& (bird.getPosition().y <= p.get_position_upper().y + window_height || bird.getPosition().y + bird_height >= p.get_position_lower().y))
		{
			return true;
		}
	}
	return false;
}

void Generator::mode_distance(float distance)
{
	for (Pipe& p : pipe_container)
	{
		p.set_distance_inbetween(distance);
	}
}

void Generator::update(float delta_time, sf::Texture* texture)
{
	for (Pipe& p : pipe_container)
	{
		p.update(delta_time);
	}
	for (std::vector<Pipe>::iterator p = pipe_container.begin(); p != pipe_container.end(); p++)
	{
		if (p->check() == 0)
		{
			pipe_container.erase(p);
			add_pipe(texture);
			break;
		}
	}
}

void Generator::draw(sf::RenderWindow& window)
{
	for (Pipe& p : pipe_container)
	{
		p.draw(window);
	}
}

void Generator::generator_restart(sf::Texture* texture)
{
	pipe_container.clear();
	for (int i = 0; i < 3; i++)
	{
		Pipe p(forward_speed, rand_gen(), hardmode);
		p.set_pipe_texture(texture);
		p.set_x(900 + distance_between_pipes * i);
		pipe_container.push_back(p);
	}
}
