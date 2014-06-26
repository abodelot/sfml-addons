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
	 * @param image_path: path to the bitmap font's image
	 * @param width: number of glyphs on each line
	 * @param height: number of glyphs on each column
	 * @return true if loading succeeded, false if it failed
	 */
	bool loadFromFile(const std::string& image_path, int width=16, int height=6);

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

	int getGlyphHeight() const;
	int getGlyphWidth() const;

private:
	sf::Texture m_texture;
	int         m_width;
	int         m_height;
	int         m_glyph_width;
	int         m_glyph_height;
};


#endif // BITMAP_FONT_HPP
