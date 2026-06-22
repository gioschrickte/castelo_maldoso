#pragma once

#include "Ente.h"

namespace Entidades {
		class Chao : public Jogo::Ente {
		private:
			sf::Color cor = sf::Color::Cyan; // cor do chao
		public:
			Chao(const sf::Vector2f pos, const sf::Vector2f tam) :
				Jogo::Ente(pos, tam, IDs::IDs::chao)
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

                // empurra pelo eixo de MENOR penetracao
                if (ds.x < ds.y) {
                    if (centroOutra.x < centroEsta.x)
                        p->mover(sf::Vector2f(-ds.x, 0.0f)); 
                    else
                        p->mover(sf::Vector2f(ds.x, 0.0f)); 
                }
                else {
                    if (centroOutra.y < centroEsta.y)
                    {
                        p->mover(sf::Vector2f(0.0f, -ds.y)); 
                        p->aterrissar();
                    }
                    else
                    {
                        p->mover(sf::Vector2f(0.0f, ds.y)); 
                        p->baterCabeca();
                    }                        
            }
        }

        void executar() {}
	};
}
