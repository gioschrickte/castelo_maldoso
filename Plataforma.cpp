#include "Plataforma.hpp"

Entidades::Obstaculos::Plataforma::Plataforma(const sf::Vector2f pos, const sf::Vector2f tam)
    : Entidades::Obstaculos::Obstaculo(pos, tam)
{
    corpo.setFillColor(sf::Color::Green);
}

Entidades::Obstaculos::Plataforma::~Plataforma() {}

void Entidades::Obstaculos::Plataforma::colisao(Entidades::Entidade* outraEntidade, sf::Vector2f ds)
{
    sf::Vector2f posOutra = outraEntidade->getCorpo().getPosition();
    sf::Vector2f posEsta = getCorpo().getPosition();

    // empurra pelo eixo de menor sobreposição
    if (fabs(ds.x) < fabs(ds.y)) {
        float dirX = (posOutra.x < posEsta.x) ? ds.x : -ds.x;
        outraEntidade->mover(sf::Vector2f(dirX, 0.0f));
    }
    else {
        float dirY = (posOutra.y < posEsta.y) ? ds.y : -ds.y;
        outraEntidade->mover(sf::Vector2f(0.0f, dirY));
    }
}