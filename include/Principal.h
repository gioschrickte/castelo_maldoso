#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
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
    void carregarFase(int numFase);   // recria a fase salva a partir de save.txt

	Entidades::Personagens::Jogadores::Jogador* jogador1;
	Entidades::Personagens::Jogadores::Jogador* jogador2;
	int numJogadores;   // 1 ou 2, escolhido no menu

	std::string nomeJogador;   // nome do usuario (para save e ranking)
	int pontuacaoJogador;      // pontuacao acumulada entre fases sequenciais
public:
    Principal();
    ~Principal();
    void executar();
};
