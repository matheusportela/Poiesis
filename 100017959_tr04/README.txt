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

Action: Interface para ações de GameObjects reutilizáveis.
ActionScheduler: Escalonador que executa ações sequencialmente.
Alien: Personagem do jogo que contém minions.
AnimatedGameObject: Classe abstrata para criação de objetos de jogo que possuem animações.
AnimatedSprite: Provê funcionalidades para renderização de animações no jogo.
Bullet: Tiro realizado por instâncias de GameObject.
Camera: Classe estática que provê movimentação da cena do jogo.
CameraDownCommand: Comando para mover a câmera para baixo.
CameraLeftCommand: Comando para mover a câmera para a esquerda.
CameraRightCommand: Comando para mover a câmera para a direita.
CameraUpCommand: Comando para mover a câmera para cima.
CollisionSimulator: Simulador de colisões entre GameObjects.
Command: Classe abstrata para comandos utilizados para inputs do usuário.
CommandFactory: Provê funcionalidades para criação de Command.
ConfigParser: Permite leitura de valores a partir de um arquivo de configuração.
FileUtils: Funções úteis para manipulação de arquivos.
Game: Contém o código genérico da game engine.
GameObject: Classe abstrata para geração de objetos de jogo.
GameObjectContainer: Container para instâncias de GameObject.
GameObjectManager: Gerenciador do ciclo de vida de instâncias de GameObject no jogo.
InputManager: Funcionalidades para tratamento de input do usuário.
Logger: Provê funcionalidades de log, com diferentes níveis e cores.
Main: Ponto de entrada que inicializa o jogo.
Minion: Personagens que giram em torno de um Alien.
MinionBullet: Tiro realizado pelos minions.
MoveAction: Ação de movimento realizado pelo Alien.
Parser: Classe abstrata para geração de parsers.
Penguins: Personagem que representa o jogador no jogo.
PenguinsBullet: Tiro realizado pelos penguins.
PeguinsLeftRotationCommand: Comando para Penguins virar à esquerda.
PeguinsRightRotationCommand: Comando para Penguins virar à direita.
PeguinsShootCommand: Comando para Penguins atirar.
PeguinsSlowDownCommand: Comando para Penguins desacelerar.
PeguinsSpeedUpCommand: Comando para Penguins acelerar.
Point: Classe geométrica para representação de pontos, em 2 dimensões.
QuitCommand: Comando para sair do jogo.
Rect: Classe geométrica para representação de retângulos, em 2 dimensões.
Resources: Gerenciador de recursos em memória.
ShootAction: Ação para Alien atirar.
Sprite: Provê funcionalidades para renderização de imagens no jogo.
State: Contém o código específico do jogo.
StillAnimation: GameObject que representa uma animação estática no jogo.
TileMap: Renderizador de mapa de jogo a partir de tiles.
TileMapParser: Permite leitura de configuração de mapas por meio de tiles.
TileSet: Gerenciador de tiles a partir de uma única imagem.
Timer: Relógio regressivo.
Vector: Classe geométrica para representação e operações de vetores, em 2 dimensões.

================================================================================
