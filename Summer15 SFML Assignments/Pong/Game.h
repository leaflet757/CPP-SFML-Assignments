#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <cstdio>
#include <thread>
#include <mutex>
#include <iostream>

#include <MathFuncsDll.h> // test

#include "Ball.h"

using namespace std;


namespace OpenSFMLEngine
{
	class Game
	{
	private:
		sf::Window* window;

		thread* renderingThread;
		thread* updateThread;

		vector<Actor2D*> actors;

		std::mutex _lock;

		sf::Clock* clock;

		bool running = true;
		float r = 0, g = 0.3, b = 0.6;

		Game(Game const&) = delete;
		void operator=(Game const&) = delete;

	public:
		Game();
		~Game(); // TODO: would this be private too?

		static Game& getInstance();

		void start();

		virtual void initActors();

		void renderingFunction();
		void updateFunction();

	};
}
