#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include "Fase.h"

class Principal
{
private:
    Gerenciador::GerenciadorGrafico* pGrafico;
    Gerenciador::GerenciadorEvento* pEvento;
    Gerenciador::GerenciadorColisoes* pColisoes;
    Lista::ListaEntidade listaEntidade;
    Lista::ListaEntidade listaObstaculo;

	Jogo::Fases::Fase* faseAtual;
    void criarFase(int numFase);

	Entidades::Personagens::Jogadores::Jogador* jogador1;
	Entidades::Personagens::Jogadores::Jogador* jogador2;
	int numJogadores;   // 1 ou 2, escolhido no menu
public:
    Principal();
    ~Principal();
    void executar();
};
