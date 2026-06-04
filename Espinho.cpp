// Espinho.cpp
#include "Espinho.hpp"

Entidades::Obstaculos::Espinho::Espinho(const sf::Vector2f pos, const sf::Vector2f tam)
    : Entidades::Obstaculos::Obstaculo(pos, tam, IDs::IDs::plataforma) // reaproveita o id; crie IDs::espinho se quiser distinguir
{
    corpo.setFillColor(sf::Color(150, 30, 30)); // vermelho escuro
    danoso = true; // indica que o espinho é dano
   
    textura = pGG->carregarTextura("assets/espinho.png");
    sprite.setTexture(textura);

    // Ajusta a escala do sprite para cobrir exatamente o corpo (50x50)
    sf::Vector2u tSz = textura.getSize();
    if (tSz.x > 0 && tSz.y > 0)
    {
        sprite.setScale(40.0f / tSz.x, 40.0f / tSz.y);
    }

    sprite.setPosition(pos);
    temSprite = true;
}

Entidades::Obstaculos::Espinho::~Espinho() {}

void Entidades::Obstaculos::Espinho::resolverColisao(Personagens::Personagem* p, sf::Vector2f ds)
{
    sf::Vector2f posOutra = p->getCorpo().getPosition();
    sf::Vector2f tamOutra = p->getCorpo().getSize();
    sf::Vector2f posEsta = getCorpo().getPosition();
    sf::Vector2f tamEsta = getCorpo().getSize();

    sf::Vector2f centroOutra(posOutra.x + tamOutra.x / 2.0f, posOutra.y + tamOutra.y / 2.0f);
    sf::Vector2f centroEsta(posEsta.x + tamEsta.x / 2.0f, posEsta.y + tamEsta.y / 2.0f);

    // sólido: empurra para fora pelo eixo de menor penetração (igual à plataforma)
    if (ds.x < ds.y) {
        if (centroOutra.x < centroEsta.x) p->mover(sf::Vector2f(-ds.x, 0.0f));
        else                              p->mover(sf::Vector2f(ds.x, 0.0f));
    }
    else {
        if (centroOutra.y < centroEsta.y) { p->mover(sf::Vector2f(0.0f, -ds.y)); p->aterrissar(); }
        else                                p->mover(sf::Vector2f(0.0f, ds.y));
    }
    // AQUI vai o dano quando houver sistema de vida (só o jogador chega aqui, pois afetaInimigos()==false)
}