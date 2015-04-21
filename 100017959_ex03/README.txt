================================================================================

Aluno: Matheus Vieira Portela
Matrícula: 10/0017959

================================================================================

CONFIGURAÇÃO:

É necessário configurar o diretório que contém os recursos de mídia do jogo.
Isso é feito no arquivo Configurations.cfg ao ajustar o valor da variável $PATH.
Por exemplo, para indicar o diretório "/test/dir", simplesmente configure:
    $PATH = /test/dir

Tal representação permite a utilização de wildcards, tais como "./" e "../"

COMPILAÇÃO:

Em ambiente Unix, execute o comando:
    $ make


EXECUÇÃO:

Em ambiente Unix, execute o comando:
    $ ./Main

================================================================================

MÓDULOS:

Alien: Personagem do jogo que contém minions.
Bullet: Tiro realizado pelos minions.
Camera: Classe estática que provê movimentação da cena do jogo.
ConfigParser: Permite leitura de valores a partir de um arquivo de configuração.
FileUtils: Funções úteis para manipulação de arquivos.
Game: Contém o código genérico da game engine.
GameObject: Classe abstrata para geração de objetos de jogo.
InputManager: Funcionalidades para tratamento de input do usuário.
Main: Gera o arquivo executável que inicializa o jogo.
Minion: Personagens que giram em torno de um Alien.
Parser: Classe abstrata para geração de parsers.
Point: Classe geométrica para representação de pontos, em 2 dimensões.
Rect: Classe geométrica para representação de retângulos, em 2 dimensões.
Resources: Gerenciador de recursos em memória.
Sprite: Provê funcionalidades para renderização de imagens no jogo.
State: Contém o código específico do jogo.
TileMap: Renderizador de mapa de jogo a partir de tiles.
TileMapParser: Permite leitura de configuração de mapas por meio de tiles.
TileSet: Gerenciador de tiles a partir de uma única imagem.
Vector: Classe geométrica para representação e operações de vetores, em 2 dimensões.

================================================================================
