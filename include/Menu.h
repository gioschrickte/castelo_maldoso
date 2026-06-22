// Menu.hpp
#pragma once
#include "Ente.h"
#include "GerenciadorGrafico.h"
#include <SFML/Graphics.hpp>
#include <string>

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

        sf::RectangleShape botaoModo;   // alterna 1 / 2 jogadores
        sf::Text textoBotaoModo;
        int numJogadores;               // 1 (default) ou 2

        sf::Text textoRanking;          // lista de pontuacoes exibida no menu

        sf::RectangleShape caixaNome;   // campo onde o usuario digita o nome
        sf::Text textoLabelNome;        // rotulo "Nome:" acima da caixa
        sf::Text textoNome;             // texto digitado exibido dentro da caixa
        std::string nomeJogador;        // nome digitado (uma palavra, sem espacos)

        //Jogo* pjog;

        bool fontCarregada;

        bool carregarFonte();
        void carregarRanking();         // le ranking.txt e monta o texto do ranking
        bool clicouEm(const sf::RectangleShape& botao, sf::Vector2i posMouse) const;
        void atualizarHover(sf::Vector2i posMouse);
        void atualizarTextoModo();      // sincroniza o texto do botao com numJogadores
        void atualizarTextoNome();      // sincroniza o texto exibido com nomeJogador

    public:
        Menu();
        ~Menu();

        
        void executar() override {}

        // Chamado pela Principal. Retorna 1, 2 ou -1 (janela fechada)
        int rodar();

        // Quantidade de jogadores escolhida no menu (1 ou 2)
        int getNumJogadores() const { return numJogadores; }

        // Nome digitado no menu; "Jogador" caso o campo tenha ficado vazio
        std::string getNomeJogador() const { return nomeJogador.empty() ? "Jogador" : nomeJogador; }
    };
}
