#include "GerenciadorColisoes.hpp"

void Gerenciador::GerenciadorColisoes::tratarColisoesJogsInimgs()
{
	for (int i = 0; i < LIs.size(); i++)
	{
		bool col = verificarColisao(static_cast<Entidade::Entidade*> (pJog1), static_cast<Entidade::Entidade*> (LIs[i]));
		if (col) // se colidiu
		{
			pJog1->colidir(LIs[i]);
		}
	}
}


Gerenciador::GerenciadorColisoes::GerenciadorColisoes(Entidade::Personagem::Jogador::Jogador* p) :
	LIs(), LOs(), pJog1(p)
{

}

Gerenciador::GerenciadorColisoes::~GerenciadorColisoes()
{
	// DELETAR TODAS AS INSTANCIAS EM LI E LO
}

const sf::Vector2f Gerenciador::GerenciadorColisoes::calculaColisao(Entidade::Entidade* ent1, Entidade::Entidade* ent2)
{
	sf::Vector2f pos1 = ent1->getCorpo().getPosition();
	sf::Vector2f pos2 = ent2->getCorpo().getPosition();

	sf::Vector2f tam1 = ent1->getCorpo().getSize();
	sf::Vector2f tam2 = ent2->getCorpo().getSize();

	sf::Vector2f distanciaEntreCentros(
		fabs((pos1.x + tam1.x / 2.0f) - (pos2.x + tam2.x / 2.0f)),
		fabs((pos1.y + tam1.y / 2.0f) - (pos2.y + tam2.y / 2.0f))
	);
	sf::Vector2f somaMetadeRectangulo(tam1.x / 2.0f + tam2.x / 2.0f, tam1.y / 2.0f + tam2.y / 2.0f);
	return sf::Vector2f(distanciaEntreCentros.x - somaMetadeRectangulo.x, distanciaEntreCentros.y - somaMetadeRectangulo.y);
}

const bool Gerenciador::GerenciadorColisoes::verificarColisao(Entidade::Entidade* ent1, Entidade::Entidade* ent2)
{
	sf::Vector2f ds = calculaColisao(ent1, ent2);
	if (ds.x < 0.0f && ds.y < 0.0f)
		return true;
	return false;
}

void Gerenciador::GerenciadorColisoes::executar() {
	tratarColisoesJogsInimgs();
	// tratarColisoesEntsObstacs();
	tratarColisoesJogsObstacs();
	
}


void Gerenciador::GerenciadorColisoes::incluirInimigo(Entidade::Personagem::Inimigo::Inimigo* pInim)
{
	if (pInim)
	{
		LIs.push_back(pInim);
	}
	else
		printf("Erro, pInim Nulo");
}

void Gerenciador::GerenciadorColisoes::incluirObstaculo(Entidade::Obstaculo::Obstaculo* pObst)
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
