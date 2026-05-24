#include "Obstaculo.hpp"

Entidade::Obstaculo::Obstaculo::Obstaculo(const sf::Vector2f pos, const sf::Vector2f tam, IDs::IDs id)
    : Entidade(pos, tam, id)
{
}

Entidade::Obstaculo::Obstaculo::~Obstaculo() {}

void Entidade::Obstaculo::Obstaculo::atualizar() {}