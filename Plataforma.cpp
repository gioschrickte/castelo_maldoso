#include "Plataforma.hpp"

Entidades::Obstaculos::Plataforma::Plataforma(const sf::Vector2f pos, const sf::Vector2f tam)
    : Entidades::Obstaculos::Obstaculo(pos, tam, IDs::IDs::plataforma)
{
    corpo.setFillColor(sf::Color::Green);
}

Entidades::Obstaculos::Plataforma::~Plataforma() {}

void Entidades::Obstaculos::Plataforma::colidir(Entidades::Entidade* outraEntidade, sf::Vector2f overlap)
{
    sf::Vector2f posOutra = outraEntidade->getCorpo().getPosition();
    sf::Vector2f tamOutra = outraEntidade->getCorpo().getSize();
    sf::Vector2f posEsta = getCorpo().getPosition();
    sf::Vector2f tamEsta = getCorpo().getSize();

    sf::Vector2f centroOutra(posOutra.x + tamOutra.x / 2.0f, posOutra.y + tamOutra.y / 2.0f);
    sf::Vector2f centroEsta(posEsta.x + tamEsta.x / 2.0f, posEsta.y + tamEsta.y / 2.0f);

    // empurra pelo eixo de MENOR penetração
    if (overlap.x < overlap.y) {
        if (centroOutra.x < centroEsta.x)
            outraEntidade->mover(sf::Vector2f(-overlap.x, 0.0f)); // está à esquerda -> empurra p/ esquerda
        else
            outraEntidade->mover(sf::Vector2f(overlap.x, 0.0f)); // à direita -> empurra p/ direita
    }
    else {
        if (centroOutra.y < centroEsta.y)
            outraEntidade->mover(sf::Vector2f(0.0f, -overlap.y)); // está acima -> empurra p/ cima
        else
            outraEntidade->mover(sf::Vector2f(0.0f, overlap.y)); // abaixo -> empurra p/ baixo
    }
}