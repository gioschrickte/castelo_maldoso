#include "Plataforma.h"
#include <fstream>


Entidades::Obstaculos::Plataforma::Plataforma(const sf::Vector2f pos, const sf::Vector2f tam)
    : Entidades::Obstaculos::Obstaculo(pos, tam, IDs::IDs::plataforma)
{
    corpo.setFillColor(sf::Color::Green);


    textura = pGG->carregarTextura("assets/plataforma.png");
    sprite.setTexture(textura);

    // Ajusta a escala do sprite para cobrir exatamente o corpo (50x50)
    sf::Vector2u tSz = textura.getSize();
    if (tSz.x > 0 && tSz.y > 0)
    {
        sprite.setScale(200.0f / tSz.x, 20.0f / tSz.y);
    }

    sprite.setPosition(pos);
    temSprite = true;
    //Os sprites foram criados com a IA Sprite-AI.
    //link:https://www.sprite-ai.art/

    // Parametros do "ceder com o peso".
    yInicial       = pos.y;
    afundamentoMax = 200.0f;
    velocidade     = 1.5f;
    alguemEmCima   = false;
}

Entidades::Obstaculos::Plataforma::~Plataforma() {}

void Entidades::Obstaculos::Plataforma::executar()
{
    // O afundamento acontece em obstaculizar (la temos o personagem em
    // contato para descer junto). Aqui so tratamos o RETORNO: se ninguem
    // estava apoiado no frame anterior, a plataforma sobe de volta a origem.
    if (!alguemEmCima)
    {
        float deslocamento = getPosicao().y - yInicial; // >0 = abaixo da origem
        if (deslocamento > 0.0f)
            mover(sf::Vector2f(0.0f, -velocidade));
    }

    // As colisoes deste frame remarcam a flag se ainda houver alguem em cima;
    // zera aqui para detectar quando todos sairem.
    alguemEmCima = false;
}

void Entidades::Obstaculos::Plataforma::obstaculizar(Personagens::Personagem* p, sf::Vector2f ds)
{
    sf::Vector2f posOutra = p->getCorpo().getPosition();
    sf::Vector2f tamOutra = p->getCorpo().getSize();
    sf::Vector2f posEsta = getCorpo().getPosition();
    sf::Vector2f tamEsta = getCorpo().getSize();

    sf::Vector2f centroOutra(posOutra.x + tamOutra.x / 2.0f, posOutra.y + tamOutra.y / 2.0f);
    sf::Vector2f centroEsta(posEsta.x + tamEsta.x / 2.0f, posEsta.y + tamEsta.y / 2.0f);

    // empurra pelo eixo de MENOR penetraÃ§Ã£o
    if (ds.x < ds.y) {
        if (centroOutra.x < centroEsta.x)
            p->mover(sf::Vector2f(-ds.x, 0.0f)); // esta a esquerda -> empurra p/ esquerda
        else
            p->mover(sf::Vector2f(ds.x, 0.0f)); //   direita -> empurra p/ direita
    }
    else {
        if (centroOutra.y < centroEsta.y)
        {
            p->mover(sf::Vector2f(0.0f, -ds.y)); // esta acima -> empurra p/ cima (encosta no topo)
            p->aterrissar();
            alguemEmCima = true; // ha um personagem apoiado em cima -> plataforma cede

            // A plataforma cede com o peso: afunda um passo levando o personagem
            // junto, ate o limite. Descer os dois juntos mantem o contato e evita
            // a folga que causava a trepidacao.
            float deslocamento = getPosicao().y - yInicial;
            if (deslocamento < afundamentoMax)
            {
                mover(sf::Vector2f(0.0f, velocidade));    // plataforma desce
                p->mover(sf::Vector2f(0.0f, velocidade)); // personagem desce junto
            }
        }
        else
        {
            p->mover(sf::Vector2f(0.0f, ds.y)); // abaixo -> empurra p/ baixo
            p->baterCabeca();
        }
    }
}

void Entidades::Obstaculos::Plataforma::salvar()
{
    buffer.str("");
	buffer.clear();
	salvarDataBuffer();
	cout << "[SALVAR] " << buffer.str() << endl;//debug
	ofstream arquivo("plataforma.txt", ios::app);
	
	if (!arquivo.is_open())//debug
    {
        cout << "[ERRO] nao foi possivel abrir o arquivo!" << endl;
        return;
    }

	arquivo << buffer.str() << "\n";
	arquivo.close();
	 
	cout << "[SALVAR] gravado com sucesso!" << endl;//debug
}

void Entidades::Obstaculos::Plataforma::salvarDataBuffer()
{
	Entidades::Obstaculos::Obstaculo::salvarDataBuffer();
	//mais nada pra salvar, so posiçao e Idd
}


