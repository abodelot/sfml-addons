#include <cstdio>
#include "BitmapFont.hpp"

// ASCII Printable characters range
const char FIRST_PRINTABLE_CHAR = 32;
const char LAST_PRINTABLE_CHAR = 126;


BitmapFont::BitmapFont():
	m_width(0),
	m_height(0)
{
}


bool BitmapFont::loadFromFile(const std::string& imagePath, size_t width, size_t height)
{
	if (width > 0 && height > 0 && m_texture.loadFromFile(imagePath))
	{
		m_width = width;
		m_height = height;

		// Compute the size of a glyph from image dimensions
		m_glyphSize.x = m_texture.getSize().x / m_width;
		m_glyphSize.y = m_texture.getSize().y / m_height;
		return true;
	}
	return false;
}


const sf::Texture& BitmapFont::getTexture() const
{
	return m_texture;
}


sf::IntRect BitmapFont::getGlyphRect(char character) const
{
	if (character < FIRST_PRINTABLE_CHAR || character > LAST_PRINTABLE_CHAR)
	{
		fprintf(stderr, "BitmapFont: non printable character encoutered (ASCII %d\n)", character);
		// Replace non printable characters with '?'
		character = '?';
	}
	character -= FIRST_PRINTABLE_CHAR;

	sf::IntRect subrect;
	subrect.left = (character % m_width) * m_glyphSize.x;
	subrect.width = m_glyphSize.x;
	subrect.top = (character / m_width) * m_glyphSize.y;
	subrect.height = m_glyphSize.y;
	return subrect;
}


const sf::Vector2u& BitmapFont::getGlyphSize() const
{
	return m_glyphSize;
}
