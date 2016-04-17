#include "Game.h"
#include "GameState.h"

constexpr unsigned int winWidth{800}, winHeight{600};

Game::Game() : m_window({winWidth, winHeight}, "Legend of the Swamp"),
               m_texmgr(),
               m_background()
{
    loadTextures();
    loadTiles();
    loadFonts();
    loadStylesheets();

    m_window.setFramerateLimit(60);

    m_background.setTexture(m_texmgr.getRef("background"));
}

void Game::run()
{
    sf::Clock clock;

    while (m_window.isOpen())
    {
        sf::Time elapsed{clock.restart()};
        float dt{elapsed.asSeconds()};

        if (peekState() == nullptr)
        {
            continue;
        }

        peekState()->handleInput();
        peekState()->update(dt);

        m_window.clear(sf::Color::Black);

        peekState()->draw(dt);

        m_window.display();
    }
}


void Game::pushState(std::unique_ptr<GameState> state)
{
    // http://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function
    // m_states owns the states so move is required
    m_states.push(std::move(state));
}

void Game::popState()
{
    m_states.pop();
}

void Game::changeState(std::unique_ptr<GameState> state)
{
    if (!m_states.empty())
    {
        popState();
    }

    pushState(std::move(state));
}

GameState *Game::peekState()
{
    if (m_states.empty())
    {
        return nullptr;
    }

    return m_states.top().get();
}

void Game::loadTiles()
{
    // TODO: Change the atlas to load RPG tiles with appropriate members
    Animation staticAnim(0, 0, 1.0f);
    m_tileAtlas["grass"] =
            Tile(m_tileSize, 1, m_texmgr.getRef("grass"),
                 { staticAnim },
                 TileType::GRASS, 50, 0, 1);
    m_tileAtlas["forest"] =
            Tile(m_tileSize, 1, m_texmgr.getRef("forest"),
                 { staticAnim },
                 TileType::FOREST, 100, 0, 1);
    m_tileAtlas["water"] =
            Tile(m_tileSize, 1, m_texmgr.getRef("water"),
                 { staticAnim,
                   staticAnim,
                   staticAnim },
                 TileType::WATER, 0, 0, 1);
    m_tileAtlas["residential"] =
            Tile(m_tileSize, 2, m_texmgr.getRef("residential"),
                 { staticAnim, staticAnim, staticAnim,
                   staticAnim, staticAnim, staticAnim },
                 TileType::RESIDENTIAL, 300, 50, 6);
    m_tileAtlas["commercial"] =
            Tile(m_tileSize, 2, m_texmgr.getRef("commercial"),
                 { staticAnim, staticAnim, staticAnim, staticAnim},
                 TileType::COMMERCIAL, 300, 50, 4);
    m_tileAtlas["industrial"] =
            Tile(m_tileSize, 2, m_texmgr.getRef("industrial"),
                 { staticAnim, staticAnim, staticAnim,
                   staticAnim },
                 TileType::INDUSTRIAL, 300, 50, 4);
    m_tileAtlas["road"] =
            Tile(m_tileSize, 1, m_texmgr.getRef("road"),
                 { staticAnim, staticAnim, staticAnim,
                   staticAnim, staticAnim, staticAnim,
                   staticAnim, staticAnim, staticAnim,
                   staticAnim, staticAnim },
                 TileType::ROAD, 100, 0, 1);
}

void Game::loadTextures()
{
    // TODO: Change to load RPG texture, assuming we made them...
    m_texmgr.loadTexture("grass",         "media/grass.png");
    m_texmgr.loadTexture("forest",        "media/forest.png");
    m_texmgr.loadTexture("water",         "media/water.png");
    m_texmgr.loadTexture("residential",   "media/residential.png");
    m_texmgr.loadTexture("commercial",    "media/commercial.png");
    m_texmgr.loadTexture("industrial",    "media/industrial.png");
    m_texmgr.loadTexture("road",          "media/road.png");

    m_texmgr.loadTexture("background",    "media/background.png");
}

void Game::loadFonts()
{
    sf::Font font;
    font.loadFromFile("media/font.ttf");
    m_fonts["main_font"] = font;
}

void Game::loadStylesheets()
{
    m_stylesheets["button"] = GuiStyle(&m_fonts.at("main_font"), 1,
                                       sf::Color(0xc6,0xc6,0xc6), sf::Color(0x94,0x94,0x94), sf::Color(0x00,0x00,0x00),
                                       sf::Color(0x61,0x61,0x61), sf::Color(0x94,0x94,0x94), sf::Color(0x00,0x00,0x00));
    m_stylesheets["text"] = GuiStyle(&m_fonts.at("main_font"), 0,
                                     sf::Color(0x00,0x00,0x00,0x00), sf::Color(0x00,0x00,0x00), sf::Color(0xff,0xff,0xff),
                                     sf::Color(0x00,0x00,0x00,0x00), sf::Color(0x00,0x00,0x00), sf::Color(0xff,0x00,0x00));
}