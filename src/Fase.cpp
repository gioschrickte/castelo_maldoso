// Fase.cpp
#include "Fase.h"
#include "Entidade.h"
#include "GerenciadorColisoes.h"
#include "GerenciadorGrafico.h"
#include "Zumbi.h"
#include "Plataforma.h"
#include "Projetil.h"
#include "Ork.h"
#include "Mago.h"
#include "Espinho.h"
#include "Lama.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#define MAX_INIMIGOS_FACEIS 4
#define MAX_PLATAFORMAS 5

Jogo::Fases::Fase::Fase(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2)
    : Ente(), jog1(jogador), jog2(j2), listaEntidade(),
    gerColisoes(Gerenciador::GerenciadorColisoes::getGerenciadorColisoes()),
    gerEventos(Gerenciador::GerenciadorEvento::getGerenciadorEvento()),
    chao(nullptr),
    pausado(false),
    resultado(ResultadoFase::JanelaFechada)
{
    inicializar();
}

Jogo::Fases::Fase::Fase(Entidades::Personagens::Jogadores::Jogador* jogador, Entidades::Personagens::Jogadores::Jogador* j2, bool /*carregando*/)
    : Ente(), jog1(jogador), jog2(j2), listaEntidade(),
    gerColisoes(Gerenciador::GerenciadorColisoes::getGerenciadorColisoes()),
    gerEventos(Gerenciador::GerenciadorEvento::getGerenciadorEvento()),
    chao(nullptr),
    pausado(false),
    resultado(ResultadoFase::JanelaFechada)
{
    inicializar();
    // As entidades (inimigos/obstaculos) sao recriadas pela classe derivada,
    // que chama carregarEntidades() apos definir o fundo e o numFase.
}

void Jogo::Fases::Fase::inicializar()
{
    criarChao();

    listaEntidade.addEntidade(jog1);
    if (jog2) listaEntidade.addEntidade(jog2);

    gerColisoes->setFase(this);
    gerColisoes->setJogador1(jog1);
    gerColisoes->setJogador2(jog2);   // jog2 pode ser nullptr (limpa ponteiro obsoleto)
    gerEventos->setJogador(jog1);
    gerEventos->setJogador2(jog2);     // idem
    gerEventos->setFase(this);
}

Jogo::Fases::Fase::~Fase()
{
    for (int i = 0; i < listaEntidade.getTam(); i++)
        delete listaEntidade[i];
    if (chao) delete chao;   // chao fora da lista, liberado aqui
    gerColisoes->limpar();
}

void Jogo::Fases::Fase::criarChao()
{
    // O chao deriva de Ente (nao de Entidade), entao nao entra na listaEntidade;
    // a Fase o guarda, desenha e libera diretamente.
    chao = new Entidades::Chao(sf::Vector2f(0.0f, 750.0f), sf::Vector2f(pGG->getWindow()->getSize().x, 20.0f));
}

void Jogo::Fases::Fase::adicionarInimigo(Entidades::Personagens::Inimigos::Inimigo* i)
{
    i->setJogador2(jog2);   // segundo alvo para a IA (nullptr em 1 jogador)
    listaEntidade.addEntidade(i);
    gerColisoes->incluirInimigo(i);
}

void Jogo::Fases::Fase::adicionarObstaculo(Entidades::Obstaculos::Obstaculo* o)
{
    listaEntidade.addEntidade(o);
    gerColisoes->incluirObstaculo(o);
}

void Jogo::Fases::Fase::adicionarProjetil(Entidades::Projetil* p)
{
    listaEntidade.addEntidade(p);     // entra no loop de executar()/desenhar()
    gerColisoes->incluirProjetil(p);  // entra no set de projeteis (colisao com o jogador)
}

int Jogo::Fases::Fase::aleatorio(int minimo, int maximo)
{
    if (maximo <= minimo) return minimo;
    return minimo + rand() % (maximo - minimo + 1);
}

sf::Vector2f Jogo::Fases::Fase::posicaoAleatoria(float xMin, float xMax, float yMin, float yMax)
{
    float x = static_cast<float>(aleatorio(static_cast<int>(xMin), static_cast<int>(xMax)));
    float y = static_cast<float>(aleatorio(static_cast<int>(yMin), static_cast<int>(yMax)));
    return sf::Vector2f(x, y);
}

sf::Vector2f Jogo::Fases::Fase::posicaoInimigoAleatoria() const
{
    const float largura = static_cast<float>(pGG->getWindow()->getSize().x);
    const float chaoTopo = chao->getPosicao().y;   // y real do chÃ£o

    const float margem = 50.0f;
    const float xMin = margem;
    const float xMax = largura - margem;
    const float yMin = margem;
    const float yMax = chaoTopo - 100.0f;          // folga acima do chÃ£o
    return posicaoAleatoria(xMin, xMax, yMin, yMax);
}

sf::Vector2f Jogo::Fases::Fase::posicaoPlataformaAleatoria() const
{
    const float largura = static_cast<float>(pGG->getWindow()->getSize().x);
    const float chaoTopo = chao->getPosicao().y;

    const float margem = 100.0f;
    const float xMin = margem;
    const float xMax = largura - margem;

    const float plataformaYMin = 1500.0f;
    const float plataformaYMax = chaoTopo - 150.0f;
    return posicaoAleatoria(xMin, xMax, plataformaYMin, plataformaYMax);
}

void Jogo::Fases::Fase::criarInimigosFaceis()
{
    using namespace Entidades::Personagens::Inimigos;
    int n = aleatorio(3, MAX_INIMIGOS_FACEIS);
    for (int i = 0; i < n; i++)
        adicionarInimigo(new Zumbi(jog1, posicaoInimigoAleatoria()));
}

void Jogo::Fases::Fase::criarPlataformas()
{
    using namespace Entidades::Obstaculos;

    const sf::Vector2f tam(200.0f, 20.0f);
    const float folga = 40.0f;              
    const int  MAX_TENTATIVAS = 30;

    const float largura = static_cast<float>(pGG->getWindow()->getSize().x);
    const float chaoTopo = chao->getPosicao().y;
    const float xMin = 0.0f;
    const float xMax = largura - tam.x;
    const float yMin = 250.0f;
    const float yMax = chaoTopo - 150.0f;

    std::vector<sf::FloatRect> colocadas;    

    int n = aleatorio(3, MAX_PLATAFORMAS);
    for (int i = 0; i < n; i++)
    {
        for (int t = 0; t < MAX_TENTATIVAS; t++)
        {
            sf::Vector2f pos = posicaoAleatoria(xMin, xMax, yMin, yMax);

            sf::FloatRect cand(pos.x - folga, pos.y - folga,
                tam.x + 2 * folga, tam.y + 2 * folga);

            bool livre = true;
            for (size_t k = 0; k < colocadas.size(); k++)
                if (cand.intersects(colocadas[k])) { livre = false; break; }

            if (livre)
            {
                colocadas.push_back(sf::FloatRect(pos.x, pos.y, tam.x, tam.y));
                adicionarObstaculo(new Plataforma(pos, tam));
                break;
            }
        }
        // se esgotar as tentativas sem achar lugar, simplesmente pula esta plataforma
    }
}

void Jogo::Fases::Fase::executar()
{

    cout << "LOOP DE EXECUTAR" << endl;
    while (pGG->verificaJanelaAberta()) {
        gerEventos->executar();                                   // 1. entrada
        
        
        if(!pausado)
        {
            for (int i = 0; i < listaEntidade.getTam(); i++)
            {
                if (!listaEntidade[i]->getAtiva()) continue; // 
                cout << "Executando entidade: " << i << endl;
                listaEntidade[i]->executar();
            }
                      
        }                                  
        
        gerColisoes->executar();                                 
        pGG->limpaJanela();


        pGG->desenhaSprite(spriteFundo);
        chao->desenhar();                                          // chao fora da lista
        for (int i = 0; i < listaEntidade.getTam(); i++)
        {
            if(listaEntidade[i]->getAtiva())
                listaEntidade[i]->desenhar();                          // 4. desenha tudo
        }
        pGG->mostraElementos();

        // Fim de fase: a Principal le getResultado() para decidir o proximo passo.
        if (!haJogadorVivo())
        {
            resultado = ResultadoFase::JogadorMorreu;   // ambos mortos -> menu
            return;
        }
        if (!gerColisoes->haInimigosVivos())
        {
            resultado = ResultadoFase::FaseConcluida;    // fase limpa -> proxima fase
            return;
        }
    }
    resultado = ResultadoFase::JanelaFechada;            // saiu pelo fechamento da janela
}

void Jogo::Fases::Fase::SalvarTudo()
{
    // save.txt agora guarda SO o cabecalho da partida (qual fase, quantos jogadores, nome e
    // pontuacao). A Principal le essa linha na opcao "Continuar".
    std::ofstream arquivo("save.txt", std::ios::trunc);
    if (arquivo.is_open())
    {
        arquivo << numFase << " " << (jog2 ? 2 : 1) << " "
                << jog1->getNome() << " " << jog1->getPontuacao() << "\n";
        arquivo.close();
    }

    // Zera o .txt de cada tipo antes de regravar: como cada salvar() abre em append, sem isto
    // os saves antigos se acumulariam (e ate ressuscitariam entidades de outra fase).
    limparArquivosEntidades();

    listaEntidade.salvarEntidades();   // cada entidade da append no .txt do seu proprio tipo
}

void Jogo::Fases::Fase::carregarEntidades()
{
    // Um metodo por tipo: cada um le o seu proprio .txt. Sem switch e sem cabecalho aqui
    // (o cabecalho fica em save.txt e ja foi lido pela Principal).
    carregarJogadores();
    carregarZumbis();
    carregarOrks();
    carregarMagos();
    carregarProjeteis();   // depois dos magos: associa cada projetil salvo a um mago
    carregarPlataformas();
    carregarEspinhos();
    carregarLamas();
}

void Jogo::Fases::Fase::carregarJogadores()
{
    std::ifstream in("jogador.txt");
    if (!in.is_open()) return;

    int id; float x, y, vx, vy, vida; bool ativa;
    int jogLidos = 0;
    while (in >> id >> x >> y >> vx >> vy >> ativa >> vida)
    {
        // Os jogadores ja existem (jog1/jog2); aqui so aplicamos o estado salvo.
        Entidades::Personagens::Jogadores::Jogador* alvo = (jogLidos == 0) ? jog1 : jog2;
        jogLidos++;
        if (alvo)
        {
            alvo->setPosicao(sf::Vector2f(x, y));
            alvo->setVelFinal(sf::Vector2f(vx, vy));
            alvo->setVida(vida);
            alvo->setAtiva(ativa);
        }
    }
}

void Jogo::Fases::Fase::carregarZumbis()
{
    using namespace Entidades::Personagens::Inimigos;
    std::ifstream in("zumbi.txt");
    if (!in.is_open()) return;

    int id; float x, y, vx, vy, vida; bool ativa;
    while (in >> id >> x >> y >> vx >> vy >> ativa >> vida)
    {
        Zumbi* z = new Zumbi(jog1, sf::Vector2f(x, y));
        z->setVelFinal(sf::Vector2f(vx, vy));
        z->setVida(vida);
        z->setAtiva(ativa);
        adicionarInimigo(z);
    }
}

void Jogo::Fases::Fase::carregarOrks()
{
    using namespace Entidades::Personagens::Inimigos;
    std::ifstream in("ork.txt");
    if (!in.is_open()) return;

    int id; float x, y, vx, vy, vida; bool ativa;
    while (in >> id >> x >> y >> vx >> vy >> ativa >> vida)
    {
        Ork* o = new Ork(jog1, sf::Vector2f(x, y));
        o->setVelFinal(sf::Vector2f(vx, vy));
        o->setVida(vida);
        o->setAtiva(ativa);
        adicionarInimigo(o);
    }
}

void Jogo::Fases::Fase::carregarMagos()
{
    using namespace Entidades::Personagens::Inimigos;
    std::ifstream in("mago.txt");
    if (!in.is_open()) return;

    int id; float x, y, vx, vy, vida; bool ativa;
    while (in >> id >> x >> y >> vx >> vy >> ativa >> vida)
    {
        Mago* m = new Mago(jog1, sf::Vector2f(x, y));
        m->setVelFinal(sf::Vector2f(vx, vy));
        m->setVida(vida);
        m->setAtiva(ativa);
        adicionarInimigo(m);   // o projetil sera associado por carregarProjeteis()
    }
}

void Jogo::Fases::Fase::carregarProjeteis()
{
    using namespace Entidades;
    using namespace Entidades::Personagens::Inimigos;
    std::ifstream in("projetil.txt");
    if (!in.is_open()) return;

    // carregarMagos() ja rodou: junta os magos da fase para receberem um projetil cada
    // (a ordem nao importa, basta cada mago ficar com o seu).
    std::vector<Mago*> magos;
    for (int i = 0; i < listaEntidade.getTam(); i++)
        if (listaEntidade[i]->getId() == IDs::IDs::mago)
            magos.push_back(static_cast<Mago*>(listaEntidade[i]));

    size_t idx = 0;
    int id; float x, y, vx, vy; bool ativo; int dano;
    while (in >> id >> x >> y >> vx >> vy >> ativo >> dano)
    {
        Projetil* p = new Projetil(dano);
        p->setPosicao(sf::Vector2f(x, y));
        p->setVelocidade(sf::Vector2f(vx, vy));
        p->setAtivo(ativo);

        if (idx < magos.size())
            magos[idx]->setProjetil(p);   // associa ao mago (so' precisa de um por mago)

        adicionarProjetil(p);
        idx++;
    }
}

void Jogo::Fases::Fase::carregarPlataformas()
{
    using namespace Entidades::Obstaculos;
    std::ifstream in("plataforma.txt");
    if (!in.is_open()) return;

    // Obstaculos so usam posicao + ativa; vx vy vida vem como placeholders e sao ignorados.
    int id; float x, y, vx, vy, vida; bool ativa;
    while (in >> id >> x >> y >> vx >> vy >> ativa >> vida)
    {
        Plataforma* o = new Plataforma(sf::Vector2f(x, y));
        o->setAtiva(ativa);
        adicionarObstaculo(o);
    }
}

void Jogo::Fases::Fase::carregarEspinhos()
{
    using namespace Entidades::Obstaculos;
    std::ifstream in("espinho.txt");
    if (!in.is_open()) return;

    int id; float x, y, vx, vy, vida; bool ativa;
    while (in >> id >> x >> y >> vx >> vy >> ativa >> vida)
    {
        Espinho* o = new Espinho(sf::Vector2f(x, y));
        o->setAtiva(ativa);
        adicionarObstaculo(o);
    }
}

void Jogo::Fases::Fase::carregarLamas()
{
    using namespace Entidades::Obstaculos;
    std::ifstream in("lama.txt");
    if (!in.is_open()) return;

    int id; float x, y, vx, vy, vida; bool ativa;
    while (in >> id >> x >> y >> vx >> vy >> ativa >> vida)
    {
        Lama* o = new Lama(sf::Vector2f(x, y));
        o->setAtiva(ativa);
        adicionarObstaculo(o);
    }
}

void Jogo::Fases::Fase::limparArquivosEntidades()
{
    // Esvazia (trunca) o .txt de cada tipo, para que o save atual nao herde linhas de saves
    // anteriores nem de outra fase.
    const char* arquivos[] = {
        "jogador.txt", "zumbi.txt", "ork.txt", "mago.txt", "projetil.txt",
        "plataforma.txt", "espinho.txt", "lama.txt"
    };
    for (const char* nome : arquivos)
        std::ofstream(nome, std::ios::trunc);   // abre em modo trunc e fecha: esvazia o arquivo
}
