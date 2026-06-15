#include "Menu.h"

// Cores dos botÃµes
static const sf::Color COR_FASE1_NORMAL(70, 130, 180);
static const sf::Color COR_FASE1_HOVER(100, 160, 210);
static const sf::Color COR_FASE2_NORMAL(178, 34, 34);
static const sf::Color COR_FASE2_HOVER(210, 60, 60);
static const sf::Color COR_FUNDO(30, 30, 30);
static const sf::Color COR_SAVE_NORMAL(46, 139, 87);  // Verde
static const sf::Color COR_SAVE_HOVER(60, 179, 113);  // Verde Claro

Jogo::Menu::Menu()
    : Ente(), fontCarregada(false)
{
    const float W = static_cast<float>(pGG->getWindow()->getSize().x);
    const float H = static_cast<float>(pGG->getWindow()->getSize().y);

    // BotÃµes centralizados horizontalmente, na metade inferior da tela
    const sf::Vector2f tamBotao(260.0f, 90.0f);
    const float espacamento = 60.0f;
    const float totalLarg = tamBotao.x * 2.0f + espacamento;
    const float xInicio = (W - totalLarg) / 2.0f;
    const float yBotao = H * 0.55f;

    botaoFase1.setSize(tamBotao);
    botaoFase1.setPosition(xInicio, yBotao);
    botaoFase1.setFillColor(COR_FASE1_NORMAL);

    botaoFase2.setSize(tamBotao);
    botaoFase2.setPosition(xInicio + tamBotao.x + espacamento, yBotao);
    botaoFase2.setFillColor(COR_FASE2_NORMAL);

    // Configuração do botão de Save (Abaixo do Fase 1)
    const float espacamentoY = 30.0f; // Espaço vertical entre os botões
    botaoSave.setSize(tamBotao);
    botaoSave.setPosition(xInicio, yBotao + tamBotao.y + espacamentoY);
    botaoSave.setFillColor(COR_SAVE_NORMAL);

    fontCarregada = carregarFonte();
    if (!fontCarregada) return;

    // TÃ­tulo
    textoTitulo.setFont(fonte);
    textoTitulo.setString("CASTELO MALDOSO");
    textoTitulo.setCharacterSize(64);
    textoTitulo.setFillColor(sf::Color::White);
    textoTitulo.setStyle(sf::Text::Bold);
    sf::FloatRect rT = textoTitulo.getLocalBounds();
    textoTitulo.setOrigin(rT.left + rT.width / 2.0f, rT.top + rT.height / 2.0f);
    textoTitulo.setPosition(W / 2.0f, H * 0.30f);

    // Helper para centralizar texto dentro de um botÃ£o
    auto centralizarTexto = [](sf::Text& txt, const sf::RectangleShape& botao) {
        sf::FloatRect r = txt.getLocalBounds();
        txt.setOrigin(r.left + r.width / 2.0f, r.top + r.height / 2.0f);
        txt.setPosition(
            botao.getPosition().x + botao.getSize().x / 2.0f,
            botao.getPosition().y + botao.getSize().y / 2.0f
        );
        };

    textoBotao1.setFont(fonte);
    textoBotao1.setString("Fase 1");
    textoBotao1.setCharacterSize(32);
    textoBotao1.setFillColor(sf::Color::White);
    centralizarTexto(textoBotao1, botaoFase1);

    textoBotao2.setFont(fonte);
    textoBotao2.setString("Fase 2");
    textoBotao2.setCharacterSize(32);
    textoBotao2.setFillColor(sf::Color::White);
    centralizarTexto(textoBotao2, botaoFase2);

    // Texto do botão de Save
    textoBotaoSave.setFont(fonte);
    textoBotaoSave.setString("Continuar"); // Quebra de linha para caber bem
    textoBotaoSave.setCharacterSize(22); // Fonte um pouco menor devido ao tamanho do texto
    textoBotaoSave.setFillColor(sf::Color::White);
    centralizarTexto(textoBotaoSave, botaoSave);
}

Jogo::Menu::~Menu() {}

bool Jogo::Menu::carregarFonte()
{
    if (fonte.loadFromFile("assets/arial.ttf"))         return true;
    if (fonte.loadFromFile("C:/Windows/Fonts/arial.ttf")) return true;
    if (fonte.loadFromFile("C:/Windows/Fonts/calibri.ttf")) return true;
    printf("Menu: nenhuma fonte encontrada â€” textos nao serao exibidos.\n");
    return false;
}

bool Jogo::Menu::clicouEm(const sf::RectangleShape& botao, sf::Vector2i posMouse) const
{
    return botao.getGlobalBounds().contains(
        static_cast<float>(posMouse.x),
        static_cast<float>(posMouse.y)
    );
}

void Jogo::Menu::atualizarHover(sf::Vector2i posMouse)
{
    botaoFase1.setFillColor(clicouEm(botaoFase1, posMouse) ? COR_FASE1_HOVER : COR_FASE1_NORMAL);
    botaoFase2.setFillColor(clicouEm(botaoFase2, posMouse) ? COR_FASE2_HOVER : COR_FASE2_NORMAL);
}

int Jogo::Menu::rodar()
{
    int escolha = 0;

    while (pGG->verificaJanelaAberta() && escolha == 0)
    {
        sf::Event evento;
        while (pGG->getWindow()->pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
            {
                pGG->fecharJanela();
                return -1;
            }

            if (evento.type == sf::Event::MouseMoved)
            {
                atualizarHover(sf::Vector2i(evento.mouseMove.x, evento.mouseMove.y));
            }

            if (evento.type == sf::Event::MouseButtonPressed &&
                evento.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i pos(evento.mouseButton.x, evento.mouseButton.y);
                if (clicouEm(botaoFase1, pos)) escolha = 1;
                else if (clicouEm(botaoFase2, pos)) escolha = 2;
                else if (clicouEm(botaoSave, pos)) escolha = 3;
            }

            if (evento.type == sf::Event::KeyPressed &&
                evento.key.code == sf::Keyboard::Escape)
            {
                pGG->fecharJanela();
                return -1;
            }
        }

        // Desenha o menu
        pGG->limpaJanela();
        pGG->desenhaElemento(botaoFase1);
        pGG->desenhaElemento(botaoFase2);
        pGG->desenhaElemento(botaoSave);

        if (fontCarregada)
        {
            pGG->getWindow()->draw(textoTitulo);
            pGG->getWindow()->draw(textoBotao1);
            pGG->getWindow()->draw(textoBotao2);
            pGG->getWindow()->draw(textoBotaoSave);

        }
        pGG->mostraElementos();
    }

    return escolha;
}
