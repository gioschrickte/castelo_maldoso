# Castelo Maldoso

Jogo de plataforma 2D desenvolvido em C++ com a biblioteca gráfica **SFML**, como
projeto da disciplina de Programação Orientada a Objetos (UTFPR).

O jogador controla um cavaleiro que percorre as fases do castelo enfrentando inimigos
(magos, orks, zumbis) e desviando de obstáculos (espinhos, lama). O jogo conta com duas
fases, modo para 1 ou 2 jogadores, sistema de salvamento e ranking de pontuações.

<<<<<<< HEAD
---
=======
O programa pode ser utilizado tanto em Windows ou Linux, visto sua estrutura de CMake.
>>>>>>> 70e0f080b10219ec999f17f992a20dd2814974de

## Estrutura do projeto

```
castelo_maldoso/
├── assets/         # Imagens, sprites e fonte usados no jogo
├── include/        # Cabeçalhos (.h)
├── src/            # Código-fonte (.cpp)
├── diagramasUML/   # Diagramas UML do projeto
└── CMakeLists.txt  # Configuração de build (CMake)
```

---

## Pré-requisitos

### Windows (VSCode)

| Ferramenta | Versão mínima | Como obter |
|---|---|---|
| [VSCode](https://code.visualstudio.com/) | qualquer | site oficial |
| Extensão **CMake Tools** (VSCode) | qualquer | marketplace do VSCode |
| **Visual Studio Build Tools** (compilador MSVC) | 2019 ou superior | [aka.ms/vs/buildtools](https://aka.ms/vs/buildtools) — marque "Desenvolvimento para desktop com C++" |
| **SFML** | 2.6.x | [sfml-dev.org/download](https://www.sfml-dev.org/download/sfml/2.6.0/) — baixar a versão **Windows — Visual C++ 17 (2022) — 64-bit** |
| **CMake** | 3.10+ | Já vem instalado com o Visual Studio Build Tools |

> **Atenção:** o SFML **não está incluído** neste repositório por ser grande demais. O download é obrigatório.

### Linux Debian / Ubuntu

Tudo pode ser instalado direto pelo `apt`:

```bash
sudo apt update
sudo apt install build-essential cmake libsfml-dev
```

| Pacote | O que instala |
|---|---|
| `build-essential` | GCC/G++ e Make |
| `cmake` | sistema de build |
| `libsfml-dev` | SFML 2.x (headers + bibliotecas) |

---

## Configuração antes de compilar

### 1 — Definir o caminho do SFML no CMakeLists.txt (somente Windows)

No Linux o CMake encontra o SFML automaticamente via `apt`. No Windows é preciso informar onde você extraiu o SFML.

Abra o arquivo `CMakeLists.txt` na raiz do projeto e edite a linha:

```cmake
set(SFML_DIR "[CAMINHO PARA SFML]")
```

Substitua `[CAMINHO PARA SFML]` pelo caminho real até a pasta `lib/cmake/SFML` dentro do diretório onde você extraiu o SFML. Exemplo:

```cmake
set(SFML_DIR "C:/Bibliotecas/SFML-2.6.0/lib/cmake/SFML")
```

> Use barras normais `/` no caminho, mesmo no Windows.

---

## Como compilar

### Windows — VSCode (recomendado)

1. Abra a pasta do projeto no VSCode (`Arquivo → Abrir Pasta…`).
2. Na primeira abertura, o CMake Tools pedirá para selecionar um compilador (*kit*). Escolha **Visual Studio Build Tools** com arquitetura **x64** (ou **amd64**).
3. Pressione `Ctrl+Shift+P` e execute **CMake: Configure**.
4. Pressione `Ctrl+Shift+P` e execute **CMake: Build** (ou clique no botão **Build** na barra de status inferior).

O executável será gerado em:
```
build\Debug\app.exe
```
A pasta `assets\` é copiada automaticamente para junto do executável pelo CMake.

---

### Windows — Prompt de Comando (alternativo)

Abra o **Developer Command Prompt for VS** (busque no menu Iniciar) e, a partir da raiz do projeto:

```cmd
cmake -S . -B build
cmake --build build --config Debug
```

O executável ficará em `build\Debug\app.exe`.

---

### Linux Debian — Terminal

A partir da raiz do projeto:

```bash
mkdir -p build
cd build
cmake ..
make
```

O executável ficará em `build/app`.

---

## Como executar

### Windows

```cmd
build\Debug\app.exe
```

Ou clique duas vezes no arquivo `app.exe` dentro de `build\Debug\`.

### Linux

```bash
./build/app
```

> **Importante:** execute o programa **a partir da pasta onde o executável está** (`build\Debug\` no Windows, `build\` no Linux), pois os arquivos `assets\`, `ranking.txt` e `save.txt` são procurados no diretório atual.

---

## Controles

| Ação      | Jogador 1      | Jogador 2 (modo 2 jogadores) |
|-----------|----------------|------------------------------|
| Mover     | `A` / `D`      | `←` / `→`                   |
| Pular     | `Espaço` / `W` | `↑`                          |
| Atacar    | `Z`            | `Ctrl direito`               |

| Tecla   | Ação             |
|---------|------------------|
| `Enter` | Pausar / retomar |
| `M`     | Salvar o jogo    |
| `Esc`   | Sair             |

No menu inicial é possível digitar o nome do jogador, escolher a fase, alternar
entre 1 e 2 jogadores e continuar uma partida salva.
