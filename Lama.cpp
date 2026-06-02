#include "Lama.hpp"

Entidades::Obstaculos::Lama::Lama(const sf::Vector2f pos, const sf::Vector2f tam)
	: Entidades::Obstaculos::Obstaculo(pos, tam, IDs::IDs::lama)
{
	corpo.setFillColor(sf::Color(100, 70, 30)); // marrom
	multiplicadorVelocidade = 0.4f; // anda a 40% da velocidade normal
	multiplicadorPulo = 0.5f; // pula com metade da forca
	danoso = false; 
}

Entidades::Obstaculos::Lama::~Lama() {}

void Entidades::Obstaculos::Lama::resolverColisao(Personagens::Personagem* p, sf::Vector2f ds)
{
	p->aplicarLentidao(multiplicadorVelocidade, multiplicadorPulo);

	// poderia ter algum efeito visual 
}