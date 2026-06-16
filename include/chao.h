#pragma once

#include "Entidade.h"

namespace Entidades {
		class Chao : public Entidade {
		private:
			sf::Color cor = sf::Color::Cyan; // cor do chao
		public:
			Chao(const sf::Vector2f pos, const sf::Vector2f tam) :
				Entidade(pos, tam, IDs::IDs::chao)
			{
                corpo.setFillColor(sf::Color::Cyan);
			}

            void obstaculizar(Personagens::Personagem* p, sf::Vector2f ds)
            {
                sf::Vector2f posOutra = p->getCorpo().getPosition();
                sf::Vector2f tamOutra = p->getCorpo().getSize();
                sf::Vector2f posEsta = getCorpo().getPosition();
                sf::Vector2f tamEsta = getCorpo().getSize();

                sf::Vector2f centroOutra(posOutra.x + tamOutra.x / 2.0f, posOutra.y + tamOutra.y / 2.0f);
                sf::Vector2f centroEsta(posEsta.x + tamEsta.x / 2.0f, posEsta.y + tamEsta.y / 2.0f);

                // empurra pelo eixo de MENOR penetraÃ§Ã£o
                if (ds.x < ds.y) {
                    if (centroOutra.x < centroEsta.x)
                        p->mover(sf::Vector2f(-ds.x, 0.0f)); // estÃ¡ Ã  esquerda -> empurra p/ esquerda
                    else
                        p->mover(sf::Vector2f(ds.x, 0.0f)); // Ã  direita -> empurra p/ direita
                }
                else {
                    if (centroOutra.y < centroEsta.y)
                    {
                        p->mover(sf::Vector2f(0.0f, -ds.y)); // estÃ¡ acima -> empurra p/ cima
                        p->aterrissar();
                    }
                    else
                    {
                        p->mover(sf::Vector2f(0.0f, ds.y)); // abaixo -> empurra p/ baixo
                        p->baterCabeca();
                    }                        
            }
        }

        void executar() {}
        void salvar() {}
	};
}
