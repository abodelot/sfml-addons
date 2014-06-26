#ifndef BITMAP_TEXT_HPP
#define BITMAP_TEXT_HPP

#include <SFML/Graphics.hpp>

#include "BitmapFont.hpp"


/**
 * Drawable class for displaying a bitmap text on a render target
 * Works in combination with BitmapFont class
 * Since bitmap fonts don't support character size, use setScale(factor, factor)
 * on the bitmap text to change its size.
 */
class BitmapText: public sf::Drawable, public sf::Transformable
{
public:
	/**
	 * Default constructor
	 */
	BitmapText();

	/**
	 * Construct the text from a string and bitmap font
	 */
	BitmapText(const sf::String &string, const BitmapFont &font);

	/**
	 * Set the text's string
	 */
	void setString(const sf::String& string);

	/**
	 * Get the text's string
	 */
	const sf::String& getString() const;

	/**
	 * Set the text's bitmap font
	 */
	void setFont(const BitmapFont& font);

	/**
	 * Get the text's bitmap font
	 */
	const BitmapFont* getFont() const;

	/**
	 * Set the color of the text
	 */
	void setColor(const sf::Color& color);

	/**
	 * Get the color of the text
	 */
	const sf::Color& getColor() const;

	/**
	 * Return the position of a given charater
	 * @param index: index of the character in the text
	 * @return visual position
	 */
	sf::Vector2f findCharacterPos(size_t index);

	/**
	 * Get the local bounding rectangle of the entity
	 */
	sf::FloatRect getLocalBounds() const;

	/**
	 * Get the text width and height
	 */
	sf::Vector2f getSize() const;

private:
	/**
	 * Draw the bitmap text to a render target
	 */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/**
	 * Update the vertices used for rendering
	 */
	void updateGeometry();

	const BitmapFont* m_font;
	sf::VertexArray   m_vertices;
	sf::String        m_string;
	sf::Color         m_color;
	sf::FloatRect     m_bounds;
};


#endif // BITMAP_TEXT_HPP
