#pragma once

#include "Personagem.h"
#include <string>
// nÃ£o incluir Inimigo.hpp aqui; forward declare:
namespace Entidades {
	namespace Personagens {
		namespace Inimigos { class Inimigo; }

		namespace Jogadores {
			class Jogador : public Personagem {
			private:
				bool ataqueAtivo;
				sf::Clock relogioAtaque;
				float danoAtaque;
				std::string nome = "Jogador"; // nome do usuario (para o ranking)
				int pontuacao = 0;            // incrementada ao neutralizar inimigos
			public:
				Jogador(const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f), const sf::Vector2f tam = sf::Vector2f(50.0f, 50.0f));
				~Jogador();
				void executar();
				void colidir(Entidades::Personagens::Inimigos::Inimigo* inimigo);
				void setChao(bool noChao) { this->noChao = noChao; }
				void atacar();
				bool estaAtacando() const;
				float getDanoAtaque() const;
				void salvar();
				void salvarDataBuffer();

				// Nome e pontuacao do usuario (usados no save e no ranking)
				void addPonto() { pontuacao++; }
				int getPontuacao() const { return pontuacao; }
				void setPontuacao(int p) { pontuacao = p; }
				const std::string& getNome() const { return nome; }
				void setNome(const std::string& n) { nome = n; }
			};
		}
	}
}
