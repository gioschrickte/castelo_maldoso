#include "Obstaculo.hpp"

Entidades::Obstaculos::Obstaculo::Obstaculo(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id)
    : Entidade(pos, tam, id)
{
	corpo.setTexture(&textura);
}

Entidades::Obstaculos::Obstaculo::~Obstaculo() {}

void Entidades::Obstaculos::Obstaculo::executar() {
	// Obstáculos podem ter comportamentos específicos, como se moverem ou mudarem de estado.
	// Por exemplo, um obstáculo danoso poderia piscar ou se mover para dificultar a passagem do jogador.
}

