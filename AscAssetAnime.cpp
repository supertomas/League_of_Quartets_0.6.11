#include"Asc/Anime/AssetAnime.hpp"

using namespace asc;

AssetAnime::AssetAnime() = default;

AssetAnime::AssetAnime(const TextureAssetName & name, size_t size, int32 duration, StartImmediately startImmediately) :
	m_name(name),
	m_size(size),
	m_duration(size, duration),
	m_index(0),
	m_stopwatch(startImmediately) {}

AssetAnime::AssetAnime(const TextureAssetName & name, size_t size, const Array<int32> & duration, StartImmediately startImmediately) :
	m_name(name),
	m_size(size),
	m_duration(duration),
	m_index(0),
	m_stopwatch(startImmediately) {}

AssetAnime::~AssetAnime() = default;

void AssetAnime::reset() noexcept
{
	m_index = 0;
	m_stopwatch.reset();
}

void AssetAnime::restart()
{
	m_index = 0;
	m_stopwatch.restart();
}

void AssetAnime::setDuration(int32 duration)
{
	m_duration = Array<int32>(m_size, duration);
}

void AssetAnime::setDuration(const Array<int32> & duration)
{
	m_duration = duration;
}

void AssetAnime::jump(int index, const MillisecondsF & time)
{
	m_index = index;
	m_stopwatch.set(time);
}

void AssetAnime::update()
{
	auto ms = m_stopwatch.ms();

	while (ms > m_duration[m_index])
	{
		ms -= m_duration[m_index];
		m_index >= m_size - 1 ? m_index = 0 : m_index++;
	}

	m_stopwatch.set(MicrosecondsF(ms * 1000));
}

const TextureRegion AssetAnime::get() const
{
	return TextureAsset(m_name).uv(static_cast<double>(m_index) / m_size, 0.0, 1.0 / m_size, 1.0);
}
