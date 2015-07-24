#include "Bullets.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <list>
#include <cmath>

std::list<BulletManager::LinearProjectile> projs;

void BulletManager::fixed_update(float dt)
{
	for (auto it = projs.begin(); it != projs.end();)
	{
		it->Position += sf::Vector2f(std::cos(it->Angle), std::sin(it->Angle)) * it->Speed * dt;

		if (it->Position.y < -2500)
			it = projs.erase(it);
		else
			++it;

		// TODO: Collision check
	}
}
void BulletManager::variadic_update(float dt)
{
}
void BulletManager::draw(sf::RenderTarget& target)
{
	sf::VertexArray arr(sf::Quads);

	for (auto& p : projs)
	{
		sf::Vector2f xcoord(std::cos(p.Angle - M_PI/2.f), std::sin(p.Angle - M_PI/2.f));
		sf::Vector2f ycoord(std::cos(p.Angle - M_PI), std::sin(p.Angle - M_PI));
		sf::Vector2f pos = p.Position;
		sf::Color col = p.Color;

		for (int i = 0; i < 6; ++i)
		{
			arr.append(sf::Vertex(pos - xcoord * p.Rect.width/2.f - ycoord * p.Rect.height/2.f, col,
					   sf::Vector2f(p.Rect.left, p.Rect.top)));
			arr.append(sf::Vertex(pos + xcoord * p.Rect.width/2.f - ycoord * p.Rect.height/2.f, col,
					   sf::Vector2f(p.Rect.left + p.Rect.width, p.Rect.top)));
			arr.append(sf::Vertex(pos + xcoord * p.Rect.width/2.f + ycoord * p.Rect.height/2.f, col,
					   sf::Vector2f(p.Rect.left + p.Rect.width, p.Rect.top + p.Rect.height)));
			arr.append(sf::Vertex(pos - xcoord * p.Rect.width/2.f + ycoord * p.Rect.height/2.f, col,
					   sf::Vector2f(p.Rect.left, p.Rect.top + p.Rect.height)));

			col.a = col.a - 50;
			pos += ycoord * (p.Rect.height + 5);
		}
	}

	target.draw(arr);
}
void BulletManager::linearProjectile(LinearProjectile&& proj)
{
	projs.push_back(proj);
}
void BulletManager::seekingProjectile(SeekingProjectile&& proj)
{
}
void BulletManager::linearBeam(LinearBeam&& beam)
{
}

