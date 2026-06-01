#include "Plataforma.hpp"

Entidades::Obstaculos::Plataforma::Plataforma(const sf::Vector2f pos, const sf::Vector2f tam)
    : Entidades::Obstaculos::Obstaculo(pos, tam, IDs::IDs::plataforma)
{
    corpo.setFillColor(sf::Color::Green);
}

Entidades::Obstaculos::Plataforma::~Plataforma() {}

void Entidades::Obstaculos::Plataforma::resolverColisao(Personagens::Personagem* p, sf::Vector2f ds)
{
    sf::Vector2f posOutra = p->getCorpo().getPosition();
    sf::Vector2f tamOutra = p->getCorpo().getSize();
    sf::Vector2f posEsta = getCorpo().getPosition();
    sf::Vector2f tamEsta = getCorpo().getSize();

    sf::Vector2f centroOutra(posOutra.x + tamOutra.x / 2.0f, posOutra.y + tamOutra.y / 2.0f);
    sf::Vector2f centroEsta(posEsta.x + tamEsta.x / 2.0f, posEsta.y + tamEsta.y / 2.0f);

    // empurra pelo eixo de MENOR penetração
    if (ds.x < ds.y) {
        if (centroOutra.x < centroEsta.x)
            p->mover(sf::Vector2f(-ds.x, 0.0f)); // está à esquerda -> empurra p/ esquerda
        else
            p->mover(sf::Vector2f(ds.x, 0.0f)); // à direita -> empurra p/ direita
    }
    else {
        if (centroOutra.y < centroEsta.y)
        {
            p->mover(sf::Vector2f(0.0f, -ds.y)); // está acima -> empurra p/ cima
            p->aterrissar();
        }            
        else
            p->mover(sf::Vector2f(0.0f, ds.y)); // abaixo -> empurra p/ baixo
    }
}