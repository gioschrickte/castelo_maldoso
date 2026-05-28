#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include "Fase.hpp"

class Principal
{
private:
    Gerenciador::GerenciadorGrafico* pGrafico;
    Gerenciador::GerenciadorEvento* pEvento;
    Gerenciador::GerenciadorColisoes* pColisoes;
    Lista::ListaEntidade listaEntidade;
    Lista::ListaEntidade listaObstaculo;

	Jogo::Fases::Fase* faseAtual;

	Entidades::Personagens::Jogadores::Jogador* jogador1;
public:
    Principal();
    ~Principal();
    void executar();
};