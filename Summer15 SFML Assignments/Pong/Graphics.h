#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <atomic>
#include <mutex>

namespace OpenSFMLEngine
{
	class Graphics
	{
	private:
		Graphics();
		static std::atomic<Graphics*> pInstance;
		static std::mutex m_;

		void initialize();
	public:
		~Graphics();

		static Graphics* getInstance();

		void update();
	};
}

