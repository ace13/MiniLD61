#include "Particles.hpp"

#include <Util/Easing.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>

namespace
{
	Easers::Cubic sAlphaEaser;
	sf::Texture sParticleTexture;
}

std::list<ParticleManager::Particle> ParticleManager::mParticles;

void ParticleManager::init()
{
	sParticleTexture.loadFromFile("Resources/Particles.png");
}

void ParticleManager::addParticle(Particle&& p)
{
	p.StartLife = p.Life;

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
		it->Velocity.y = std::min(700.f, it->Velocity.y + 400.f*dt);
		it->Position += it->Velocity * dt;
		it->Angle += it->Rotation * dt;

		it->Color.a = 255 * sAlphaEaser.Out(it->Life / it->StartLife);

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

		sf::Vector2f xcoord(std::cos(p.Angle), std::sin(p.Angle));
		sf::Vector2f ycoord(std::cos(p.Angle - M_PI/2.f), std::sin(p.Angle - M_PI/2.f));

		arr.append(sf::Vertex(p.Position - xcoord * p.Rect.width/2.f * p.Scale - ycoord * p.Rect.height/2.f * p.Scale, p.Color,
		           sf::Vector2f(p.Rect.left, p.Rect.top)));
		arr.append(sf::Vertex(p.Position + xcoord * p.Rect.width/2.f * p.Scale - ycoord * p.Rect.height/2.f * p.Scale, p.Color,
		           sf::Vector2f(p.Rect.left + p.Rect.width, p.Rect.top)));
		arr.append(sf::Vertex(p.Position + xcoord * p.Rect.width/2.f * p.Scale + ycoord * p.Rect.height/2.f * p.Scale, p.Color,
		           sf::Vector2f(p.Rect.left + p.Rect.width, p.Rect.top + p.Rect.height)));
		arr.append(sf::Vertex(p.Position - xcoord * p.Rect.width/2.f * p.Scale + ycoord * p.Rect.height/2.f * p.Scale, p.Color,
		           sf::Vector2f(p.Rect.left, p.Rect.top + p.Rect.height)));
	}

	sf::RenderStates states;
	states.texture = &sParticleTexture;

	target.draw(arr, states);
}

