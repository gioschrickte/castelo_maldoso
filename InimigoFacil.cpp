// InimigoFacil.cpp
#include "InimigoFacil.hpp"

Entidades::Personagens::Inimigos::InimigoFacil::InimigoFacil(
    Jogadores::Jogador* j, const sf::Vector2f pos)
    : Inimigo(j, pos, sf::Vector2f(50.0f, 50.0f), 90.0f)
{
    corpo.setFillColor(sf::Color::Red); 

    textura = pGG->carregarTextura("assets/zombie.png");
    sprite.setTexture(textura);

    // Ajusta a escala do sprite para cobrir exatamente o corpo (50x50)
    sf::Vector2u tSz = textura.getSize();
    if (tSz.x > 0 && tSz.y > 0)
    {
        sprite.setScale(50.0f / tSz.x, 50.0f / tSz.y);
    }

    sprite.setPosition(pos);
    temSprite = true;
}

void Entidades::Personagens::Inimigos::InimigoFacil::danificar(
    Jogadores::Jogador* pJog)
{
    std::cout << "InimigoFacil causou dano leve!\n";
    // quando houver vida: pJog->receberDano(1);
}