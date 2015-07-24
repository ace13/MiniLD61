#include "Cloud.hpp"

#include <FX/Particles.hpp>

#include <random>
#include <cmath>

float CloudGenerator::mCooldown = 0;

void CloudGenerator::fixed_update(float dt)
{
	const float CLOUD_RATE = 1.9f;
	const float CLOUD_RANDOM = 1.2f;

	mCooldown -= dt;

	if (mCooldown <= 0)
	{
		std::random_device rd;
		std::uniform_real_distribution<float> dist(-1, 1);
		std::uniform_int_distribution<int> type(0, 3);
		std::uniform_int_distribution<int> puffs(6, 24);
		std::uniform_int_distribution<int> color(97, 192);

		float baseXCoord = dist(rd) * 1500.f;

		int j = puffs(rd);
		for (int i = 0; i < j; ++i)
		{
			auto p = Particles::Cloud_Puff;
			p.Angle = dist(rd) * M_PI;
			p.Position = sf::Vector2f(baseXCoord, -2048) + sf::Vector2f(dist(rd) * 360, dist(rd) * 120);
			p.Rotation = dist(rd) * 0.05f;

			int t = type(rd);
			p.Rect.top = 100 + (t / 2) * 200;
			p.Rect.left = 100 + (t % 2) * 200;

			uint8_t col = color(rd);
			p.Color = sf::Color(col,col,col,179);

			ParticleManager::addParticle(std::move(p));
		}

		mCooldown = CLOUD_RATE + CLOUD_RANDOM * dist(rd);
	}
}

