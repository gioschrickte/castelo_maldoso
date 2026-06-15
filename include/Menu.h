// Menu.hpp
#pragma once
#include "Ente.h"
#include "GerenciadorGrafico.h"
#include <SFML/Graphics.hpp>

namespace Jogo {

    class Menu : public Ente {
    private:
        sf::Font fonte;
        sf::RectangleShape botaoFase1;
        sf::RectangleShape botaoFase2;
        sf::Text textoBotao1;
        sf::Text textoBotao2;
        sf::Text textoTitulo;
        sf::RectangleShape botaoSave;
        sf::Text textoBotaoSave;

        //Jogo* pjog;

        bool fontCarregada;

        bool carregarFonte();
        bool clicouEm(const sf::RectangleShape& botao, sf::Vector2i posMouse) const;
        void atualizarHover(sf::Vector2i posMouse);

    public:
        Menu();
        ~Menu();

        // Satisfaz Ente::executar() â€” nÃ£o usado diretamente
        void executar() override {}

        // Chamado pela Principal. Retorna 1, 2 ou -1 (janela fechada)
        int rodar();
    };
}
