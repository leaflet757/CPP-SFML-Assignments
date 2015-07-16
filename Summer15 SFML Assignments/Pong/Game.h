#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <cstdio>
#include <thread>
#include <mutex>
#include <iostream>

#include <MathFuncsDll.h> // test

using namespace std;


namespace OpenSFMLEngine
{
	class Game
	{
	private:
		sf::Window* window;

		std::mutex _lock;

		bool running = true;
		float r = 0, g = 0.3, b = 0.6;

	public:
		Game();
		~Game();

		void Start();

		void renderingFunction();
		void updateFunction();

	};
}
