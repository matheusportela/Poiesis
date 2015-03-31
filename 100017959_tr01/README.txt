================================================================================

Aluno: Matheus Vieira Portela
Matrícula: 10/0017959

================================================================================

CONFIGURAÇÃO:

É necessário configurar o diretório que contém os recursos de mídia do jogo.
Isso é feito no arquivo Configurations.cfg ao ajustar o valor da variável $PATH.
Por exemplo, para indicar o diretório "/test/dir", simplesmente configure:
    $PATH = /test/dir


COMPILAÇÃO:

Em ambiente Unix, execute o comando:
    $ make


EXECUÇÃO:

Em ambiente Unix, execute o comando:
    $ ./Main

================================================================================

MÓDULOS:

Main: Gera o arquivo executável que inicializa o jogo.
Game: Contém o código genérico da game engine.
State: Contém o código específico do jogo.
Sprite: Provê funcionalidades para renderização de imagens no jogo.
Config: Permite leitura de valores a partir de um arquivo de configuração.
FileUtils: Funções úteis para manipulação de arquivos.

================================================================================