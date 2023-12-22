#pragma once

#include "slt.hpp"
#include "sltconfig.hpp"

#include <raylib.h>

#include <memory>
#include <sstream>

namespace solitaire {
    class GraphicalGame {
        GraphicalGame();

        void renderCard(const Card& card, Vector2 position);
        void renderCardFaceDown(Vector2 position);
        void renderStock();
        void renderCardPileFaceUp(const CardPile& pile, Vector2 position);
        void renderCardPileFaceDown(std::size_t pileSize, Vector2& position);

        int cardWidth();
        int cardHeight();

        Vector2 stockPosition;
        Vector2 wasteStart;
        Vector2 tableauStart;

        Game *game;
        Vector2 actualResolution;
        float cardScale = 1.0f;

        std::unique_ptr<CardPile> heldCards;

        std::map<std::pair<Suit, Face>, Texture> cardTextures;
        Texture cardBackTexture;

    public:
        GraphicalGame(std::minstd_rand::result_type seed);

        ~GraphicalGame();

        void calculateBounds();

        template<typename URNG>
        static std::unique_ptr<GraphicalGame> create(URNG& rand) {
            GraphicalGame *ggame = new GraphicalGame();
            ggame->game = Game::createAndDealGame(rand);
            return std::unique_ptr<GraphicalGame>(ggame);
        }

        void render();
        void detectClick(Vector2 mousePosition);

        std::size_t windowWidth();
        std::size_t windowHeight();

        friend std::unique_ptr<GraphicalGame> debugScript(std::unique_ptr<GraphicalGame> game);
    };
}