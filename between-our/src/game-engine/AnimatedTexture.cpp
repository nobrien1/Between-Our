#include "AnimatedTexture.h"

namespace gameEngine {
	void AnimatedTexture::drawNormal(Pointf origin, Dimensionf scaleSize)
	{
		Texture* frame = frames[currentFrame];
		frame->setFlipped(false);
		frame->draw(origin, scaleSize);
	}
	void AnimatedTexture::drawFlipped(Pointf origin, Dimensionf scaleSize)
	{
		Texture* frame = frames[currentFrame];
		frame->setFlipped(true);
		frame->draw(origin, scaleSize);
	}
	void AnimatedTexture::addFrame(Texture* frame)
	{
		Texture** newList = new Texture * [frameCount + 1];
		for (int i = 0; i < frameCount; i++)
			newList[i] = frames[i];
		newList[frameCount] = frame;
		frames = newList;
		frameCount++;
	}
	float AnimatedTexture::getFps()
	{
		return fps;
	}
	void AnimatedTexture::setFps(float fps)
	{
		this->fps = fps;
	}
	void AnimatedTexture::update(double delta)
	{
		currentTime += delta;
		if (currentTime < 1 / fps) return;

		currentTime -= 1 / fps;
		currentFrame++;
		currentFrame %= frameCount;
	}
}