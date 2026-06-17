# 💣 Campo Minado — Multiplayer no Terminal

Jogo de Campo Minado multiplayer para terminal, desenvolvido em **C** como trabalho da disciplina de **Sistemas Operacionais**.

O projeto aplica na prática os conceitos de **threads**, **semáforos** e **sincronização entre processos**, simulando um jogo de dois jogadores que disputam turnos alternados em um tabuleiro com minas aleatórias.

---

## Objetivo Acadêmico

Demonstrar o uso de mecanismos de concorrência e sincronização do sistema operacional:

- **Threads POSIX (`pthread`)** — cada jogador é executado em uma thread independente, além de uma thread de controle de tempo.
- **Semáforos POSIX (`semaphore.h`)** — protegem as regiões críticas (acesso ao tabuleiro, variáveis de turno e placar), garantindo que apenas um jogador interaja com o jogo por vez.
- **Variáveis compartilhadas** — `turno`, `fimDeJogo`, `minasRestantes`, `minasJogadorA/B` são acessadas por múltiplas threads de forma controlada.

---

## Como Jogar

### Iniciando o Jogo

Ao executar o programa, o jogador escolhe a dificuldade:

| Dificuldade     | Tabuleiro | Minas |
|-----------------|-----------|-------|
| 1 — Fácil       | 4×4       | 2     |
| 2 — Intermediário | 6×6     | 6     |
| 3 — Difícil     | 8×8       | 10    |

### Regras

- São **2 jogadores** (A e B) jogando no mesmo terminal, alternando turnos.
- Cada jogador escolhe uma célula informando **coluna (letra) + linha (número)**, por exemplo: `A3`, `D5`.
- Células não reveladas aparecem como `#`, minas reveladas como `*`, e jogadas seguras com a letra do jogador (`A` ou `B`).
- Se o jogador revela uma **mina**, ele perde ponto. Caso contrário, é uma jogada segura.
- O jogo termina quando **todas as minas forem encontradas** ou o **tempo de 10 minutos** se esgotar.
- Vence o jogador que encontrou **menos minas** (menos erros).

### Exemplo de Tabuleiro

```
    A  B  C  D
 1  #  #  A  #
 2  #  *  #  #
 3  B  #  #  #
 4  #  #  #  A
```

---

## Conceitos de Sistemas Operacionais Utilizados

### Threads (`pthread.h`)

O programa cria **3 threads**:

| Thread          | Função              | Descrição                                              |
|-----------------|---------------------|--------------------------------------------------------|
| `t1`            | `threadJogador(&A)` | Controla as jogadas do Jogador A                       |
| `t2`            | `threadJogador(&B)` | Controla as jogadas do Jogador B                       |
| `tempoThread`   | `threadTempo`       | Conta 10 minutos e encerra o jogo se o tempo esgotar   |

### Semáforos (`semaphore.h`)

Um semáforo binário (`sem_t semaforo`) é usado para proteger as **regiões críticas**:

- Acesso e modificação do tabuleiro (`revelarCelula`)
- Leitura e escrita de variáveis compartilhadas (`turno`, `fimDeJogo`, `minasRestantes`)
- Atualização do placar (`minasJogadorA`, `minasJogadorB`)

O padrão usado é:
```c
sem_wait(&semaforo);   // Entra na região crítica
// ... acesso aos dados compartilhados ...
sem_post(&semaforo);   // Sai da região crítica
```

### Controle de Turnos

Cada thread de jogador verifica se é sua vez (`turno == jogadorID`). Se não for, libera o semáforo e aguarda com `usleep(100000)` (100ms) antes de tentar novamente — implementando um **busy-wait controlado**.

---

## Estrutura do Projeto

```
Campo-minado/
├── .vscode/                    # Configurações do VS Code
│   ├── c_cpp_properties.json   # Configuração do IntelliSense (GCC)
│   ├── launch.json             # Configuração de debug (GDB)
│   └── settings.json           # Configuração do C/C++ Runner
├── Corpo-do-codigo/
│   ├── Parte-pedro.c           # Etapa 2: Tabuleiro e lógica base
│   ├── Parte-Nicole.c          # Etapa 3: Implementação de threads (mutex/cond)
│   ├── Parte-Livia.c           # Etapa 4: Versão final com semáforos e timer
│   ├── jogo.exe                # Executável compilado
│   └── Jogo-completo.zip       # Código compactado
├── Etapas/
│   ├── 1-Planejamento e Estruturas do Jogo
│   ├── 2-Implementação do Tabuleiro e Lógica Base
│   ├── 3-Implementação de Threads para Jogadores
│   ├── 4-Sincronização com Semáforos
│   ├── 5-Testes e Ajustes Finais
│   └── 6-Preparação da Apresentação
└── README.md
```

### Evolução do Código

| Arquivo           | Etapa | Sincronização        | Descrição                                                  |
|-------------------|-------|----------------------|------------------------------------------------------------|
| `Parte-pedro.c`   | 2     | Nenhuma              | Estrutura base: tabuleiro, inicialização, minas, revelação |
| `Parte-Nicole.c`  | 3     | `pthread_mutex` + `pthread_cond` | Adiciona threads para 2 jogadores com mutex e condition variable |
| `Parte-Livia.c`   | 4     | `sem_t` (semáforo POSIX) | Substitui mutex por semáforo, adiciona timer e placar      |

---

## Compilação e Execução

### Pré-requisitos

- GCC com suporte a POSIX threads (Linux ou MSYS2/MinGW no Windows)
- Bibliotecas: `pthread`, `semaphore`

### Compilar

```bash
gcc -o jogo Corpo-do-codigo/Parte-Livia.c -lpthread
```

### Executar

```bash
./jogo
```

> **Nota:** No Windows, recomenda-se usar o **MSYS2** (MinGW) ou **WSL** para compilar, pois o código utiliza APIs POSIX (`pthread`, `semaphore`, `unistd.h`).

---

## Etapas de Desenvolvimento

| # | Etapa                                  | Responsável                              |
|---|----------------------------------------|------------------------------------------|
| 1 | Planejamento e Estruturas do Jogo      | Wemerson Conceição Silva                 |
| 2 | Implementação do Tabuleiro e Lógica Base | Pedro Braga de Lima                    |
| 3 | Implementação de Threads para Jogadores | Nicole Reinaldo de Carvalho             |
| 4 | Sincronização com Semáforos            | Lívia Fernandes Ribeiro Bezerra          |
| 5 | Testes e Ajustes Finais                | Maria Clara Paiva Oliveira Camelo        |
| 6 | Preparação da Apresentação             | Maria Clara Ferreira dos Santos          |

---

## Bibliotecas Utilizadas

| Biblioteca      | Uso no Projeto                                      |
|-----------------|-----------------------------------------------------|
| `stdio.h`       | Entrada/saída (printf, scanf)                       |
| `stdlib.h`      | Funções utilitárias (rand, srand)                   |
| `time.h`        | Semente para números aleatórios (`srand(time(NULL))`) |
| `string.h`      | Manipulação de strings                              |
| `pthread.h`     | Criação e gerenciamento de threads POSIX            |
| `semaphore.h`   | Semáforos POSIX para sincronização                  |
| `unistd.h`      | Funções `sleep()` e `usleep()` para temporização    |
| `locale.h`      | Suporte a caracteres acentuados no terminal         |
