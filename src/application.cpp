#include <cstdint>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "application.hpp"

#include "titleview.hpp"
#include "gameview.hpp"
#include "gameoverview.hpp"

namespace
{
const std::uint64_t targetFPS = 60;
const float SecondsPerFrame = 1.f / targetFPS;
const int MaxStepsPerFrame = 5;

const unsigned SCREEN_WIDTH = 800;
const unsigned SCREEN_HEIGHT = 600;
}

Application::Application()
	: mAudioDevice()
	, mSoundPlayer(mAudioDevice)
	, mEventQueue()
	, mWindow()
	, mTarget()
	, mFonts()
	, mTextures()
	, mViewStack({ &mAudioDevice, &mSoundPlayer, &mWindow, &mTarget, &mFonts, &mTextures, })
{
	if (!glfwInit())
	{
		const char *error;
		glfwGetError(&error);
		throw std::runtime_error(error);
	}

	mWindow.open("AsteroidBelt", SCREEN_WIDTH, SCREEN_HEIGHT);

	// track the window events
	mEventQueue.track(mWindow);

	// tell the target to render on the window
	mTarget.use(mWindow);

	// with a context in use we load the assets
	loadAssets();

	// register the views
	registerViews();

	// push the first view
	mViewStack.pushView(ViewID::Title);
	mViewStack.update(0.f);
}

Application::~Application()
{
	glfwTerminate();
}

void
Application::loadAssets()
{
	mSoundPlayer.load(SoundID::Shot1, "assets/sounds/Shot1.wav");
	mSoundPlayer.load(SoundID::Shot2, "assets/sounds/Shot2.wav");
	mSoundPlayer.load(SoundID::Explosion1, "assets/sounds/Explosion1.wav");
	mSoundPlayer.load(SoundID::Explosion2, "assets/sounds/Explosion2.wav");
	mSoundPlayer.load(SoundID::Explosion3, "assets/sounds/Explosion3.wav");
	mSoundPlayer.load(SoundID::Explosion4, "assets/sounds/Explosion4.wav");

	mFonts.load(FontID::Pericles14, "assets/fonts/Peric.ttf", 14);

	mTextures.load(TextureID::TitleScreen, "assets/textures/TitleScreen.png");
	mTextures.load(TextureID::SpriteSheet, "assets/textures/SpriteSheet.png");
}

void
Application::registerViews()
{
	mViewStack.registerView<TitleView>(ViewID::Title);
	mViewStack.registerView<GameView>(ViewID::Playing);
	mViewStack.registerView<GameOverView>(ViewID::GameOver);
}

void
Application::run()
{
	// game loop
	const std::uint64_t deltaTicks = glfwGetTimerFrequency() / targetFPS;
	std::uint64_t currentTicks = glfwGetTimerValue();
	std::uint64_t accumulator = 0;
	while (!mWindow.isClosed() && !mViewStack.empty())
	{
		// update at constant frameTicks intervals
		auto newTicks = glfwGetTimerValue();
		accumulator += newTicks - currentTicks;
		currentTicks = newTicks;

		for (int steps = MaxStepsPerFrame;
		     steps > 0 && accumulator >= deltaTicks;
		     --steps, accumulator -= deltaTicks)
		{
			processInput();

			// update the view
			mViewStack.update(SecondsPerFrame);

			// remove the stopped sounds
			mSoundPlayer.removeStoppedSounds();
		}

		// render
		mViewStack.render(mTarget);
		mWindow.display();
	}
}

void
Application::processInput()
{
	mEventQueue.poll();
	Event event;
	while (mEventQueue.pop(event))
	{
		if (mViewStack.handleEvent(event))
		{
			// event handled by a view in the stack
		}
		else if (const auto ep(std::get_if<KeyPressed>(&event)); ep
			 && ep->key == GLFW_KEY_ESCAPE)
		{
			mWindow.close();
		}
	}
}
