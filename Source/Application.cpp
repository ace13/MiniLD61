#include "Application.hpp"
#include "State/IntroState.hpp"
#include "Util/Font.hpp"
#include "Util/Profiling.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#ifndef NDEBUG
#include "State/MenuState.hpp"
#include "Menu/MainMenu.hpp"
#endif

#include <sstream>

const float TICK_LENGTH = 1.f / 60.f;

namespace
{
	Application* sApplication = nullptr;
}

Application::Application(int argc, char** argv) :
	mWindow()
{
	if (!sApplication)
		sApplication = this;
}

Application::~Application()
{
}

void Application::run()
{
	mWindow.create(sf::VideoMode(800, 600), "MiniLD 61");
#ifdef NDEBUG
	mWindow.setFramerateLimit(200);
#endif

	mGameView = sf::View(sf::Vector2f(), sf::Vector2f(2048, 2500));
	mUIView = mWindow.getDefaultView();
	{
		sf::Vector2f size = (sf::Vector2f)mWindow.getSize();
		mUIView.setSize(size);
		mUIView.setCenter(size / 2.f);

		mGameView.setSize(mGameView.getSize().y * (size.x / size.y), mGameView.getSize().y);
	}

#ifdef NDEBUG
	mState.changeState<IntroState>();
#else
	mState.changeState<MenuState>();
	static_cast<MenuState*>(mState.getCurrentState())->pushPane(new MainMenuPane);
#endif

	sf::Clock frameTimer;
	sf::Event ev;
	sf::Text profilingText("", sf::getDefaultFont(), 10U);

	float dt, extraDT = 0;
	float totalTime = 0;

	{ // Prime the profiling tree
		PROFILE_NAMED("Frame");
		{ PROFILE_NAMED("Tick"); }
		{ PROFILE_NAMED("Update"); }
		{ PROFILE_NAMED("Draw"); }
	} Profiler::resetBlocks();

	auto root = Profiler::getRoot()->getChild("Frame");

	while (mWindow.isOpen())
	{ Profiler::startBlock("Frame");
		dt = frameTimer.restart().asSeconds();
		extraDT += dt;

		while (mWindow.pollEvent(ev))
		{ PROFILE_NAMED("Events");
			mState.handle_event(ev);

			if (ev.type == sf::Event::Resized)
			{
				sf::Vector2f size(ev.size.width, ev.size.height);

				mUIView.setSize(size);
				mUIView.setCenter(size / 2.f);

				mGameView.setSize(mGameView.getSize().y * (size.x / size.y), mGameView.getSize().y);
			}
			else if (ev.type == sf::Event::Closed)
				mWindow.close();
		}

		while (extraDT >= TICK_LENGTH)
		{ PROFILE_NAMED("Tick");
			mState.fixed_update(TICK_LENGTH);

			extraDT -= TICK_LENGTH;
		}

		PROFILE_CALL("Update", mState.variadic_update(dt));

		mWindow.clear();

		mWindow.setView(mGameView);

		PROFILE_CALL("Draw", mState.draw(mWindow));

		mWindow.setView(mUIView);
		
		PROFILE_CALL("DrawUI", mState.drawUI(mWindow));
		mWindow.draw(profilingText);

		mWindow.display();

		Profiler::endBlock(); // Frame

		if (root->getTotalTime() >= std::chrono::seconds(1))
		{
			std::ostringstream oss;
			oss << *root << std::endl;
			profilingText.setString(oss.str());

			Profiler::resetBlocks();
		}

		// State manager is without state, might as well die nicely
		if (mState.getCurrentState() == nullptr)
			mWindow.close();
	}
}

Application& Application::Singleton()
{
	return *sApplication;
}

