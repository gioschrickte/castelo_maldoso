#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "GerenciadorGrafico.hpp"
#include "GerenciadorEventos.hpp"
#include "ListaEntidade.hpp"

class Principal
{
private:
	Gerenciador::GerenciadorGrafico* pGrafico;
	Gerenciador::GerenciadorEvento* pEvento;
	Lista::ListaEntidade listaEntidade;
public:
	Principal();
	~Principal();
	void executar();
	void instanciaEntidades();
};