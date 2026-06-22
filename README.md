# Castelo Maldoso

Jogo de plataforma 2D desenvolvido em C++ com a biblioteca gráfica **SFML**, como
projeto da disciplina de Programação Orientada a Objetos (UTFPR).

O jogador controla um cavaleiro que percorre as fases do castelo enfrentando inimigos
(magos, orks, zumbis) e desviando de obstáculos (espinhos, lama). O jogo conta com duas
fases, modo para 1 ou 2 jogadores, sistema de salvamento e ranking de pontuações.

O programa pode ser utilizado tanto em Windows ou Linux, visto sua estrutura de CMake.

## Estrutura do projeto

```
castelo_maldoso/
├── assets/         # Imagens, sprites e fonte usados no jogo
├── include/        # Cabeçalhos (.h)
├── src/            # Código-fonte (.cpp)
├── diagramasUML/   # Diagramas UML do projeto
└── CMakeLists.txt  # Configuração de build (CMake)
```

## Pré-requisitos

- **Compilador C++** com suporte a C++17 (g++/clang)
- **CMake** 3.10 ou superior
- **SFML** 2.6

### Instalando as dependências (Linux / Ubuntu)

```bash
sudo apt update
sudo apt install build-essential cmake libsfml-dev
```

## Como compilar

A partir da raiz do projeto:

```bash
mkdir -p build
cd build
cmake ..
make
```

O executável `app` será gerado dentro da pasta `build/`, junto com uma cópia da
pasta `assets/` (necessária para carregar imagens e fontes).

## Como executar

Ainda dentro da pasta `build/`:

```bash
./app
```

> **Importante:** execute o programa de dentro da pasta `build/`, pois os arquivos
> de `assets/`, `ranking.txt` e `save.txt` são procurados no diretório atual.

## Controles

| Ação      | Jogador 1     | Jogador 2 (modo 2 jogadores) |
|-----------|---------------|------------------------------|
| Mover     | `A` / `D`     | `←` / `→`                    |
| Pular     | `Espaço` / `W`| `↑`                          |
| Atacar    | `Z`           | `Ctrl direito`               |

Outros comandos:

| Tecla     | Ação                  |
|-----------|-----------------------|
| `Enter`   | Pausar / retomar      |
| `M`       | Salvar o jogo         |
| `Esc`     | Sair                  |

No menu inicial é possível digitar o nome do jogador, escolher a fase, alternar
entre 1 e 2 jogadores e continuar uma partida salva.
