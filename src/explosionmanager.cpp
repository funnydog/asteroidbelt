#include "explosionmanager.hpp"

#include "audiodevice.hpp"
#include "resources.hpp"
#include "rendertarget.hpp"
#include "utility.hpp"

namespace
{
const int MinPieceCount = 3;
const int MaxPieceCount = 6;
const int MinPointCount = 20;
const int MaxPointCount = 30;
const float Duration = 90.f / 60.f;
const float ExplosionMaxSpeed = 30.f;
const float PieceSpeedScale = 6.f;
const float PointSpeedMin = 15.f;
const float PointSpeedMax = 30.f;

const Color InitialColor(127, 38, 0);
const Color FinalColor = Color::Transparent;
}

ExplosionManager::ExplosionManager(
	const FloatRect &pointRectangle,
	const Texture &texture, const FloatRect &textureRect, unsigned frameCount,
	AudioDevice &audioDevice)
	: mTexture(texture)
	, mFrameSize(textureRect.size)
	, mPointSize(pointRectangle.size)
	, mPointUV(pointRectangle / texture.getSize())
	, mAudioDevice(audioDevice)
{
	FloatRect uv = textureRect / texture.getSize();
	while (frameCount-->0)
	{
		mExpUV.push_back(uv);
		uv.pos.x += uv.size.x;
	}
}

glm::vec2
ExplosionManager::getRandomDirection(float scale)
{
	glm::vec2 direction;
	do
	{
		direction.x = Utility::randomFloat(100.f) - 50.f;
		direction.y = Utility::randomFloat(100.f) - 50.f;
	} while (direction.x == 0.f && direction.y == 0.f);

	return glm::normalize(direction) * scale;
}

void
ExplosionManager::addExplosion(glm::vec2 location, glm::vec2 momentum)
{
	glm::vec2 pieceLocation = location - mFrameSize * 0.5f;
	int pieces = MinPieceCount + Utility::randomInt(MaxPieceCount-MinPieceCount);
	while (pieces-->0)
	{
		auto pPtr = std::make_unique<Particle>(
			mFrameSize,
			pieceLocation,
			getRandomDirection(PieceSpeedScale) + momentum,
			glm::vec2(0.f),
			ExplosionMaxSpeed,
			Duration,
			InitialColor, FinalColor);

		auto pos = mExpUV.begin() + Utility::randomInt(mExpUV.size());
		pPtr->frames = std::span(pos, pos+1);
		mParticles.push_back(std::move(pPtr));
	}

	// high speed point particles
	int points = MinPointCount + Utility::randomInt(MaxPointCount-MinPointCount);
	while (points-->0)
	{
		auto pPtr = std::make_unique<Particle>(
			mPointSize,
			location,
			momentum + getRandomDirection(
				PointSpeedMin
				+ Utility::randomFloat(PointSpeedMax - PointSpeedMin)),
			glm::vec2(0.f),
			ExplosionMaxSpeed,
			Duration,
			InitialColor, FinalColor);
		auto *pos = &mPointUV;
		pPtr->frames = std::span(pos, pos+1);
		mParticles.push_back(std::move(pPtr));
	}

	mAudioDevice.play(static_cast<SoundID>(Utility::randomInt(4) + static_cast<int>(SoundID::Explosion1)));
}

void
ExplosionManager::update(float dt)
{
	for (auto it = mParticles.begin(); it != mParticles.end();)
	{
		(*it)->update(dt);
		if (!(*it)->isActive())
		{
			it = mParticles.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void
ExplosionManager::draw(RenderTarget &target)
{
	for (auto &pPtr: mParticles)
	{
		if (pPtr->isActive())
		{
			target.draw(*pPtr, mTexture);
		}
	}
}
