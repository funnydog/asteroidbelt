#pragma once

#include <fstream>

#include <vorbis/vorbisfile.h>

#include "soundfile.hpp"

class SoundFileOgg: public SoundFile
{
public:
	~SoundFileOgg() override;

	bool open(const std::string &filename, Info &info) override;
	void seek(std::uint64_t sampleOffset) override;
	std::size_t read(std::int16_t *samples, std::size_t size) override;

private:
	std::ifstream  mStream;
	OggVorbis_File mVorbis{};
	unsigned       mChannelCount{};
};
