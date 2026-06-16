#pragma once
#include "Obstaculo.h"

namespace Entidades {
    namespace Obstaculos {
        class Plataforma : public Obstaculos::Obstaculo {
        private:
            // A plataforma cede com o peso: afunda enquanto houver personagem
            // em cima e volta para a origem quando todos saem.
            float yInicial;        // posicao Y original (plataforma "em repouso")
            float afundamentoMax;  // quanto pode afundar a partir da origem, em pixels
            float velocidade;      // deslocamento vertical por frame, em pixels
            bool  alguemEmCima;    // marcado pela obstaculizar a cada frame
        public:
			bool afetaInimigos() const override { return true; } // Plataformas afetam inimigos, ou seja, eles tambÃ©m colidem com elas e sÃ£o empurrados para fora
            Plataforma(const sf::Vector2f pos, const sf::Vector2f tam = sf::Vector2f(200.0f, 20.0f));
            ~Plataforma();
            void executar() override;   // faz a plataforma oscilar verticalmente, todo frame
			void obstaculizar(Personagens::Personagem* p, sf::Vector2f ds) override;
            void salvar();
            void salvarDataBuffer();
        };
    }
}
