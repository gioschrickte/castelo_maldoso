#pragma once
#include "ListaEntidade.hpp"
#include "Inimigo.hpp"
#include "Jogador.hpp"
#include "Plataforma.hpp"
#include "GerenciadorColisoes.hpp"
#include "GerenciadorEventos.hpp"


/*
Classe Fase, que é a classe base para as fases do jogo.
É responsável por criar as entidades, e por executar o loop de jogo, chamando os métodos de cada entidade, e depois pedindo para o gerenciador gráfico desenhá-las.
Observação: O chão é uma plataforma, pois é apenas um bloco de colisão onde as entidades interagem. 

Os obstaculos e os inimigos estarão agregados na fase. Assim como um gerenciador de colisão
*/

namespace Jogo
{
	namespace Fases
	{
		class Fase : public Jogo::Ente
		{
		protected:
			Entidades::Personagens::Jogadores::Jogador* jog1;
			Entidades::Personagens::Jogadores::Jogador* jog2;
			Lista::ListaEntidade listaEntidade;
			Gerenciador::GerenciadorColisoes* GerenciadorColisoes;
			Gerenciador::GerenciadorEvento* GerenciadorEventos;
			Entidades::Entidade* chao;
		public:
			Fase(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2 = nullptr);
			~Fase();
			virtual void executar(); // loop principal da fase, usará a lista de entidades para chamar o método executar de cada entidade, e depois pedirá para o gerenciador gráfico desenhá-las
			virtual void criarCenario(); // cria o cenário da fase, ou seja, os obstáculos e inimigos. Será chamada no construtor da fase, e depois poderá ser chamada para criar um novo cenário, caso a fase seja reiniciada
			void criarInimigosFaceis(); // cria em posições aleatórias inimigos
			void criarPlataformas(); // cria em posições aleatórias plataformas
			void criarChao();
			Entidades::Entidade* getChao() { return chao; }

			// virtual void criarInimigos() = 0;
			//virtual void criarObstaculos() = 0;
		};
	}
}