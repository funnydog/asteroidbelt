#pragma once

enum class ViewID
{
	None,
	Title,
	Playing,
	PlayerDead,
	GameOver,
};

enum class FontID
{
};

enum class TextureID
{
	TitleScreen,
	SpriteSheet,
};

template<typename Resource, typename Identifier>
class ResourceHolder;

class Font;
typedef ResourceHolder<Font, FontID> FontHolder;

class Texture;
typedef ResourceHolder<Texture, TextureID> TextureHolder;
