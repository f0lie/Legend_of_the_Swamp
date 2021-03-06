#include "include/Tile.h"

Tile::Tile(unsigned int tileSize,
           unsigned int height,
           sf::Texture &texture,
           const std::vector<Animation> &animations,
           TileType tileType) : m_tileType(tileType),
                                m_tileVariant(0)
{
    m_sprite.setTexture(texture);

    m_animHandler.m_frameSize = sf::IntRect(0, 0, tileSize, tileSize * height);
    for (auto animation : animations)
    {
        m_animHandler.addAnim(animation);
    }
    m_animHandler.update(0.0f);
}

void Tile::draw(sf::RenderWindow &window, const float dt)
{
    // Change the m_sprite to reflect the tile variant
    m_animHandler.changeAnim(m_tileVariant);

    // Update the animation
    m_animHandler.update(dt);

    // Update the m_sprite
    m_sprite.setTextureRect(m_animHandler.m_bounds);

    // Draw the tile
    window.draw(m_sprite);
}

void Tile::update()
{

}

TileType pixelToTileType(unsigned char red, unsigned char green, unsigned char blue)
{
    if (blue == 255) { return TileType::WATER; }
    if (green == 255) { return TileType::GRASS; }
    if (green == 219) { return TileType::FOREST; }
    return TileType::VOID;
}
