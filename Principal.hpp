#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Plataforma.hpp"
#include "GerenciadorGrafico.hpp"
#include "GerenciadorEventos.hpp"
#include "GerenciadorColisoes.hpp"
#include "ListaEntidade.hpp"

class Principal
{
private:
    Gerenciador::GerenciadorGrafico* pGrafico;
    Gerenciador::GerenciadorEvento* pEvento;
    Gerenciador::GerenciadorColisoes* pColisoes;
    Lista::ListaEntidade listaEntidade;
    Lista::ListaEntidade listaObstaculo;
public:
    Principal();
    ~Principal();
    void executar();
    void instanciaEntidades();
};