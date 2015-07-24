#include "Particles.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>

static ParticleManager& getSingleton()
{
	static ParticleManager* sParticleManager = new ParticleManager;

	return *sParticleManager;
}

void ParticleManager::addParticle(Particle&& p)
{
	auto it = std::lower_bound(mParticles.begin(), mParticles.end(), p);

	mParticles.insert(it, std::move(p));
}
void ParticleManager::clearParticles()
{
	mParticles.clear();
}
void ParticleManager::variadic_update(float dt)
{
	for (auto it = mParticles.begin(); it != mParticles.end();)
	{
		it->Life -= dt;
		it->Position += it->Velocity * dt;
		it->Angle += it->Rotation * dt;

		if (it->Life <= 0)
			it = mParticles.erase(it);
		else
			++it;
	}

}
void ParticleManager::draw(sf::RenderTarget& target, Level l)
{
	sf::VertexArray arr(sf::Quads);

	for (auto& p : mParticles)
	{
		if (p.Height < l)
			continue;
		else if (p.Height > l)
			break;

		sf::Vector2f xcoord(std::cos(p.Angle) * 5, std::sin(p.Angle) * 5);
		sf::Vector2f ycoord(std::cos(p.Angle - M_PI/2.f) * 5, std::sin(p.Angle - M_PI/2.f) * 5);

		arr.append(sf::Vertex(p.Position - xcoord - ycoord, p.Color,
		           sf::Vector2f(p.Rect.left, p.Rect.top)));
		arr.append(sf::Vertex(p.Position + xcoord - ycoord, p.Color,
		           sf::Vector2f(p.Rect.left + p.Rect.width, p.Rect.top)));
		arr.append(sf::Vertex(p.Position - xcoord + ycoord, p.Color,
		           sf::Vector2f(p.Rect.left, p.Rect.top + p.Rect.height)));
		arr.append(sf::Vertex(p.Position + xcoord + ycoord, p.Color,
		           sf::Vector2f(p.Rect.left + p.Rect.width, p.Rect.top + p.Rect.height)));
	}

	target.draw(arr);
}
