#ifndef BITMAP_FONT_HPP
#define BITMAP_FONT_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

/**
 * Class for loading and manipulating bitmap fonts
 */
class BitmapFont
{
public:
	BitmapFont();

	/**
	 * Load a bitmap font from an image file
	 * @param imagePath: path to the bitmap font's image
	 * @param width: number of glyphs on each line
	 * @param height: number of glyphs on each column
	 * @return true if loading succeeded, false if it failed
	 */
	bool loadFromFile(const std::string& imagePath, size_t width=16, size_t height=6);

	/**
	 * Get the font's texture
	 */
	const sf::Texture& getTexture() const;

	/**
	 * Retrieve the texture rect of a font's glyph
	 * @param character: the character to get
	 * @return texture sub rect
	 */
	sf::IntRect getGlyphRect(char character) const;

	const sf::Vector2u& getGlyphSize() const;

private:
	sf::Texture  m_texture;
	size_t       m_width;
	size_t       m_height;
	sf::Vector2u m_glyphSize;
};


#endif // BITMAP_FONT_HPP
