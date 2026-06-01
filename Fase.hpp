#pragma once
#include "ListaEntidade.hpp"
#include "Inimigo.hpp"
#include "Jogador.hpp"
#include "Plataforma.hpp"
#include "chao.hpp"
#include "GerenciadorEventos.hpp"


namespace Gerenciador {
	class GerenciadorColisoes;
}

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
			Entidades::Chao* chao; 
		public:
			Fase(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2 = nullptr);
			~Fase();
			virtual void executar(); // loop principal da fase, usará a lista de entidades para chamar o método executar de cada entidade, e depois pedirá para o gerenciador gráfico desenhá-las
			virtual void criarCenario(); // cria o cenário da fase, ou seja, os obstáculos e inimigos. Será chamada no construtor da fase, e depois poderá ser chamada para criar um novo cenário, caso a fase seja reiniciada
			void criarInimigosFaceis(); // cria em posições aleatórias inimigos
			void criarPlataformas(); // cria em posições aleatórias plataformas
			void criarChao();
			Entidades::Chao* getChao() { return chao; }

			// virtual void criarInimigos() = 0;
			//virtual void criarObstaculos() = 0;
		};
	}
}