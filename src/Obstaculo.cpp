#include "Obstaculo.h"

Entidades::Obstaculos::Obstaculo::Obstaculo(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs id)
    : Entidade(pos, tam, id)
{
	corpo.setTexture(&textura);
}

Entidades::Obstaculos::Obstaculo::~Obstaculo() {}

void Entidades::Obstaculos::Obstaculo::executar() {
	// ObstÃ¡culos podem ter comportamentos especÃ­ficos, como se moverem ou mudarem de estado.
	// Por exemplo, um obstÃ¡culo danoso poderia piscar ou se mover para dificultar a passagem do jogador.
}

void Entidades::Obstaculos::Obstaculo::salvarDataBuffer()
{
	Entidades::Entidade::salvarDataBuffer();
	// Obstaculo nao tem velocidade nem vida: grava placeholders para manter
	// o schema uniforme (id x y velX velY ativa vida).
	buffer << "0 0 " << ativa << " 0";
}

