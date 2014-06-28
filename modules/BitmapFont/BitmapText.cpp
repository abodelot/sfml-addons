#include "BitmapText.hpp"


BitmapText::BitmapText():
	m_font(NULL),
	m_vertices(sf::Quads),
	m_color(255, 255, 255)
{
}


BitmapText::BitmapText(const sf::String &string, const BitmapFont &font):
	m_font(&font),
	m_vertices(sf::Quads),
	m_string(string),
	m_color(255, 255, 255)
{
	updateGeometry();
}


void BitmapText::setString(const sf::String& string)
{
	m_string = string;
	updateGeometry();
}


const sf::String& BitmapText::getString() const
{
	return m_string;
}


void BitmapText::setFont(const BitmapFont& font)
{
	if (m_font != &font)
	{
		m_font = &font;
		updateGeometry();
	}
}


const BitmapFont* BitmapText::getFont() const
{
	return m_font;
}


void BitmapText::setColor(const sf::Color& color)
{
	if (color != m_color)
	{
		m_color = color;
		for (unsigned int i = 0; i < m_vertices.getVertexCount(); ++i)
			m_vertices[i].color = m_color;
	}
}


const sf::Color& BitmapText::getColor() const
{
	return m_color;
}


sf::Vector2f BitmapText::findCharacterPos(size_t index)
{
	// Make sure that we have a valid font
	if (!m_font)
		return sf::Vector2f();

	// Adjust the index if it's out of range
	if (index > m_string.getSize())
		index = m_string.getSize();

	// Compute the position
	sf::Vector2f position;
	sf::Vector2u glyphSize = m_font->getGlyphSize();
	for (size_t i = 0; i < index; ++i)
	{
		sf::Uint32 current = m_string[i];
		switch (current)
		{
			case L'\n': // New line
				position.y += glyphSize.y;
				position.x = 0;
				break;
			case L'\t': // Horizontal tab
				position.x += glyphSize.x * 4;
				break;
			case L'\v': // Vertical tab
				position.y += glyphSize.y * 4;
				break;
			default:
				position.x += glyphSize.x;
				break;
		}
	}

	// Transform the position to global coordinates
	position = getTransform().transformPoint(position);
	return position;
}


sf::FloatRect BitmapText::getLocalBounds() const
{
	return m_bounds;
}


sf::Vector2f BitmapText::getSize() const
{
	return sf::Vector2f(m_bounds.width * getScale().x, m_bounds.height * getScale().y);
}


void BitmapText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_font->getTexture();
	target.draw(m_vertices, states);
}


void BitmapText::updateGeometry()
{
	// Clear the previous geometry
	m_vertices.clear();

	// No text: nothing to draw
	if (m_string.isEmpty())
		return;

	float x = 0.f;
	float y = 0.f;

	// Create one quad for each character
	for (size_t i = 0; i < m_string.getSize(); ++i)
	{
		sf::Uint32 current = m_string[i];

		// Handle special characters
		sf::Vector2u glyphSize = m_font->getGlyphSize();
		switch (current)
		{
			case L'\t': x += glyphSize.x * 4;    continue;
			case L'\n': y += glyphSize.y; x = 0; continue;
			case L'\v': y += glyphSize.y * 4;    continue;
		}

		// Extract the current glyph's description
		const sf::IntRect& glyph = m_font->getGlyphRect(current);

		int right  = glyph.width;
		int bottom = glyph.height;

		float u1 = static_cast<float>(glyph.left);
		float v1 = static_cast<float>(glyph.top);
		float u2 = static_cast<float>(glyph.left + glyph.width);
		float v2 = static_cast<float>(glyph.top  + glyph.height);

		// Add a quad for the current character
		m_vertices.append(sf::Vertex(sf::Vector2f(x, y),                  m_color, sf::Vector2f(u1, v1)));
		m_vertices.append(sf::Vertex(sf::Vector2f(x + right, y),          m_color, sf::Vector2f(u2, v1)));
		m_vertices.append(sf::Vertex(sf::Vector2f(x + right, y + bottom), m_color, sf::Vector2f(u2, v2)));
		m_vertices.append(sf::Vertex(sf::Vector2f(x, y + bottom),         m_color, sf::Vector2f(u1, v2)));

		// Advance to the next character
		x += glyph.width;
	}
	// Recompute the bounding rectangle
	m_bounds = m_vertices.getBounds();
}
