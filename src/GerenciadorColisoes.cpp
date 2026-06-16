#include "GerenciadorColisoes.h"
#include <cmath>

#define ALCANCE_ATAQUE_H 80.0f  // alcance horizontal da espada
#define ALCANCE_ATAQUE_V 60.0f  // tolerÃ¢ncia vertical


Gerenciador::GerenciadorColisoes* Gerenciador::GerenciadorColisoes::pGC(nullptr);

Gerenciador::GerenciadorColisoes::GerenciadorColisoes() :
	LIs(), LOs(), projeteis(), pJog1(nullptr), pJog2(nullptr), fase(nullptr)
{
	// Aqui, o gerenciador de colisoes estÃ¡ com as listas vazias, e o ponteiro para o jogador Ã© nulo
}

Gerenciador::GerenciadorColisoes::~GerenciadorColisoes()
{
}

Gerenciador::GerenciadorColisoes* Gerenciador::GerenciadorColisoes::getGerenciadorColisoes()
{
	if (pGC == nullptr)
	{
		pGC = new Gerenciador::GerenciadorColisoes();
		return pGC;
	}
	return pGC;
}

void Gerenciador::GerenciadorColisoes::setJogador1(Entidades::Personagens::Jogadores::Jogador* p)
{
	pJog1 = p;
}

void Gerenciador::GerenciadorColisoes::setJogador2(Entidades::Personagens::Jogadores::Jogador* p)
{
	// p pode ser nullptr (modo 1 jogador) -> limpa ponteiro obsoleto
	pJog2 = p;
}

void Gerenciador::GerenciadorColisoes::setFase(Jogo::Fases::Fase* f)
{
	fase = f;
}

void Gerenciador::GerenciadorColisoes::incluirInimigo(Entidades::Personagens::Inimigos::Inimigo* pInim)
{
	if (pInim)
	{
		LIs.push_back(pInim);
	}
	else
		printf("Erro, pInim Nulo");
}

void Gerenciador::GerenciadorColisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* pObst)
{
	if (pObst)
	{
		LOs.push_back(pObst);
	}
	else
	{
		printf("Erro, pObst nulo");
	}
}

void Gerenciador::GerenciadorColisoes::incluirProjetil(Entidades::Projetil* pProj)
{
	if (pProj)
	{
		projeteis.insert(pProj);
	}
	else
	{
		printf("Erro, pProj nulo");
	}
}

const sf::Vector2f Gerenciador::GerenciadorColisoes::calculaColisao(Entidades::Entidade* ent1, Entidades::Entidade* ent2)
{
	sf::Vector2f pos1 = ent1->getCorpo().getPosition();
	sf::Vector2f pos2 = ent2->getCorpo().getPosition();
	sf::Vector2f tam1 = ent1->getCorpo().getSize();
	sf::Vector2f tam2 = ent2->getCorpo().getSize();

	sf::Vector2f centro1(pos1.x + tam1.x / 2.0f, pos1.y + tam1.y / 2.0f);
	sf::Vector2f centro2(pos2.x + tam2.x / 2.0f, pos2.y + tam2.y / 2.0f);

	float overlapX = (tam1.x / 2.0f + tam2.x / 2.0f) - fabs(centro1.x - centro2.x);
	float overlapY = (tam1.y / 2.0f + tam2.y / 2.0f) - fabs(centro1.y - centro2.y);

	// ambos > 0  =>  hÃ¡ colisÃ£o. Valores sÃ£o as profundidades de penetraÃ§Ã£o.
	return sf::Vector2f(overlapX, overlapY);
}

// Agora considera colisÃ£o quando penetraÃ§Ã£o em X e Y for positiva
const bool Gerenciador::GerenciadorColisoes::verificarColisao(Entidades::Entidade* ent1, Entidades::Entidade* ent2)
{
	sf::Vector2f ds = calculaColisao(ent1, ent2);
	if (ds.x > 0.0f && ds.y > 0.0f && ent1->getAtiva() && ent2->getAtiva())
		return true;
	return false;
}

bool Gerenciador::GerenciadorColisoes::haInimigosVivos() const
{
	for (size_t i = 0; i < LIs.size(); i++)
		if (LIs[i]->getAtiva())
			return true;
	return false;
}

void Gerenciador::GerenciadorColisoes::executar() {
	tratarColisoesJogsInimgs();
	tratarColisoesInimgsObstacs();
	tratarColisoesJogsObstacs();
	tratarColisoesChao();
	tratarColisoesJogsProjeteis();
	tratarAtaqueJogador();
}

void Gerenciador::GerenciadorColisoes::tratarColisoesJogsInimgs()
{
	// Checar se cada jogador estÃ¡ colidindo com algum inimigo
	Entidades::Personagens::Jogadores::Jogador* jogs[2] = { pJog1, pJog2 };
	for (int j = 0; j < 2; j++)
	{
		Entidades::Personagens::Jogadores::Jogador* jog = jogs[j];
		if (!jog) continue; // verificarColisao ja ignora jogador morto

		for (int i = 0; i < LIs.size(); i++)
		{
			bool col = verificarColisao(static_cast<Entidades::Entidade*>(jog), static_cast<Entidades::Entidade*>(LIs[i]));
			if (col) // se colidiu
			{
				jog->colidir(LIs[i]); // chama a funÃ§Ã£o de colidir do jogador, passando o inimigo
			}
		}
	}
}

void Gerenciador::GerenciadorColisoes::tratarColisoesJogsObstacs()
{
	// Checar se cada jogador estÃ¡ colidindo com algum obstÃ¡culo
	Entidades::Personagens::Jogadores::Jogador* jogs[2] = { pJog1, pJog2 };
	for (int j = 0; j < 2; j++)
	{
		Entidades::Personagens::Jogadores::Jogador* jog = jogs[j];
		if (!jog || !jog->getAtiva()) continue;

		for (list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin(); it != LOs.end(); ++it)
		{
			// calcula uma vez e reutiliza
			sf::Vector2f ds = calculaColisao(static_cast<Entidades::Entidade*>(jog), static_cast<Entidades::Entidade*>(*it));
			if (ds.x > 0.0f && ds.y > 0.0f) // se colidiu
			{
				// passa a penetraÃ§Ã£o assinada para a rotina de resoluÃ§Ã£o do jogador
				(*it)->obstaculizar(jog, ds);
			}
		}
	}
}


void Gerenciador::GerenciadorColisoes::tratarColisoesInimgsObstacs() {
	for (list<Entidades::Obstaculos::Obstaculo*>::iterator itO = LOs.begin(); itO != LOs.end(); ++itO) {
		if ((*itO)->afetaInimigos()) { // se o obstÃ¡culo afeta inimigos, ou seja, eles colidem com ele e sÃ£o empurrados para fora
			for (int i = 0; i < LIs.size(); i++) {
				if (!LIs[i]->getAtiva()) continue; // nao empurra inimigo morto

				sf::Vector2f ds = calculaColisao(static_cast<Entidades::Entidade*>(LIs[i]), static_cast<Entidades::Entidade*>(*itO));
				if (ds.x > 0.0f && ds.y > 0.0f) { // se colidiu
					(*itO)->obstaculizar(LIs[i], ds); // passa a penetraÃ§Ã£o assinada para a rotina de resoluÃ§Ã£o do inimigo
				}
			}
		}
	}
}

void Gerenciador::GerenciadorColisoes::tratarColisoesChao()
{
	Entidades::Chao* chao = fase->getChao();

	// Checar se cada jogador estÃ¡ colidindo com o chÃ£o
	Entidades::Personagens::Jogadores::Jogador* jogs[2] = { pJog1, pJog2 };
	for (int j = 0; j < 2; j++)
	{
		Entidades::Personagens::Jogadores::Jogador* jog = jogs[j];
		if (!jog || !jog->getAtiva()) continue;

		sf::Vector2f ds = calculaColisao(static_cast<Entidades::Entidade*>(jog), static_cast<Entidades::Entidade*>(chao));
		if (ds.x > 0.0f && ds.y > 0.0f) // se colidiu
		{
			chao->obstaculizar(jog, ds);
		}
	}

	//Checar se os inimigos estÃ£o colidindo com o chao
	for (int i = 0; i < LIs.size(); i++)
	{
		if (!LIs[i]->getAtiva()) continue; // nao empurra inimigo morto

		sf::Vector2f ds = calculaColisao(static_cast<Entidades::Entidade*>(LIs[i]), static_cast<Entidades::Entidade*>(chao));
		if (ds.x > 0.0f && ds.y > 0.0f) // se colidiu
		{
			chao->obstaculizar(LIs[i], ds);
		}
	}
}

void Gerenciador::GerenciadorColisoes::tratarColisoesJogsProjeteis()
{
	Entidades::Personagens::Jogadores::Jogador* jogs[2] = { pJog1, pJog2 };

	// So projeteis ATIVOS colidem; os inativos estao escondidos fora da tela.
	for (set<Entidades::Projetil*>::iterator it = projeteis.begin(); it != projeteis.end(); ++it)
	{
		Entidades::Projetil* proj = *it;
		if (!proj->estaAtivo()) continue;

		for (int j = 0; j < 2; j++)
		{
			Entidades::Personagens::Jogadores::Jogador* jog = jogs[j];
			if (!jog || !jog->getAtiva()) continue;

			sf::Vector2f ds = calculaColisao(static_cast<Entidades::Entidade*>(jog),
				static_cast<Entidades::Entidade*>(proj));
			if (ds.x > 0.0f && ds.y > 0.0f) // acertou um jogador
			{
				proj->atingir(); // exibe o dano no terminal e se desativa
				jog->tomarDano(proj->getDano()); // o jogador toma dano
				break; // o projetil ja se desativou; nao acerta os dois
			}
		}
	}
}


void Gerenciador::GerenciadorColisoes::tratarAtaqueJogador()
{
	Entidades::Personagens::Jogadores::Jogador* jogs[2] = { pJog1, pJog2 };
	for (int j = 0; j < 2; j++)
	{
		Entidades::Personagens::Jogadores::Jogador* jog = jogs[j];
		if (!jog || !jog->estaAtacando()) continue;

		sf::Vector2f posJog = jog->getCorpo().getPosition();
		bool paraEsquerda = jog->olhandoParaEsquerda();

		for (int i = 0; i < (int)LIs.size(); i++)
		{
			if (!LIs[i]->getAtiva()) continue; // nao acerta inimigo morto

			sf::Vector2f posInim = LIs[i]->getCorpo().getPosition();
			float dx = posInim.x - posJog.x;
			bool naFrente = paraEsquerda ? (dx < 0.0f) : (dx >= 0.0f);
			if (!naFrente) continue;
			if (fabs(dx) <= ALCANCE_ATAQUE_H && fabs(posInim.y - posJog.y) <= ALCANCE_ATAQUE_V)
			{
				LIs[i]->tomarDano(jog->getDanoAtaque());
				std::cout << "Jogador acertou inimigo! (dano=" << jog->getDanoAtaque() << ")\n";
				std::cout << "Vida do inimigo: " << LIs[i]->getVida() << " / " << LIs[i]->getVidaMax() << std::endl;

				// Pontua quando o jogador do usuario (pJog1) da o golpe final no inimigo.
				// O inimigo ainda esta ativo aqui; sera desativado no proximo frame (atualizaVida),
				// entao o ponto e contado uma unica vez.
				if (jog == pJog1 && LIs[i]->getAtiva() && LIs[i]->getVida() <= 0.0f)
					pJog1->addPonto();
			}
		}
	}
}

void Gerenciador::GerenciadorColisoes::limpar()
{
	LIs.clear();
	LOs.clear();
	projeteis.clear();
	pJog1 = nullptr;
	pJog2 = nullptr;
	fase = nullptr;
}
