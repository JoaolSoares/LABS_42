# Labs 4º Edição
<p>
  <img src="https://img.shields.io/badge/OS-Linux-blue" alt="OS">
    <img src="https://img.shields.io/badge/Language-C%20%7C%20C%2B%2B-orange.svg" alt="Language">
    <img src="https://img.shields.io/badge/Status-complete-green.svg" alt="Status">
</p>

### Como deve funcionar e como utilizar o programa:

- Como o programa deve funcionar -> O programa `Encoder` deve receber um ou mais arquivos de texto, como argumentos de linha de comando, ele ira compactar os textos e enviar para o programa `Decoder` que ira descompactar os textos e enviar informações como: dado descomprimido, quantidade de bits ou bytes totais, quantidade de bits ou bytes comprimidos e o tempo da operação de descompressão novamente. Essas informações serão recebidas pelo `Encoder`, que irá imprimi-las no retorno do terminal.

Exemplo de execução do programa:

	$> make
	$> ./Encoder texto.txt

Ou tambem com múltiplos textos:

	$> ./Encoder texto.txt texto2.txt texto3.txt

Logo em seguida o programa perguntara se voce dejesa executar o `Decoder` logo em seguida do `Encoder`
Caso a resposta seja sim, ele será executado em seguida, caso contrario não, podendo executar o `Decoder` manualmente da seguinte forma:

	$> ./Decoder

- Atenção - o `Decoder` só consegue ser executado apenas uma vez apos a execução do `Encoder`, pois ao enviar as informações do processo novamente para o `Encoder` o mesmo ira matar o bloco de memoria compartilhada, assim se o `Decoder` for executado novamente, não terá nada para ler no bloco de memoria, ocasionando uma segmentation fault (SEGSIEV).

### Fluxo do programa 

1 - `Encoder` recebe textos e comprime-os atravéz do algorítimo de Huffman;

2 - `Encoder` envia o texto comprimido com o dicionário para o `Decoder` por memória compartilhada;

3 - `Decoder` descomprime o dado, e envia o dado com informações sobre o processo novamente para o `Encoder`;

4 - `Encoder` recebe os dados e imprime-os para o usuario;

### Conceitos aplicados (e como são aplicados) no projeto

- `Algoritmo de Huffman` -> É um algorítimo que comprime dados com base na repetição das informações, atribuindo um valor
com menos bits que o convencional (por exemplo, a convencional tabela ASCII que usa 8 bits para representar cada caractere).
Utiliza um sistema de árvore de incidência, e com isso atribuímos o valor binário para cada caractere.

Exemplo:
Caso queiramos comprimir a palavra "abaca"

1 - O caractere mais incidente é o "a" com 3 aparições

2 - Logo em seguida temos os caracteres "b" e "c" ambos com uma aparição

3 - Com isso construímos a árvore a seguir

			    x
			  /   \
			 a     x
			     /   \
			    b     c

4 - Agora para atribuir o valor binário determinado para cada caractere, devemos percorrer nossa árvore, onde quando andamos
para a esquerda da árvore, adicionamos um 0 ao binário e respectivamente um 1 para quando andamos para a direita;
com isso podemos construir a nossa tabela/dicionario, que no exemplo seria:

			+----+----+
			| a  | 0  |
			| b  | 10 |
			| c  | 11 |
			+----+----+

5 - Agora com a tabela, comprimimos a frase que antes era "abaca" para o binário:

			  0100110

Se compararmos este binário obtido por huffman com o binário padrão que seria utilizado na tabela ASCII iremos
perceber uma enorme diferença:

- ascii: `01100001 01100010 01100001 01100011 01100001` --> 40 bits
- huffman: `0100110`  -----------------------------------------> 7 bits

E para fazer a descompressão, basta fazer o processo inverso, é necessário o código binário comprimido com a tabela/dicionario, onde iremos ler o binário e buscar uma "tradução" para ele no nosso dicionário:

			0  10  0  11  0
			|  |   |  |   |
			a  b   a  c   a
 
- `Shared Memory` -> É um bloco na memória que fica reservado para que dois ou mais programas possam utilizar, no projeto ele é utilizado para fazer o processo descrito no parágrafo anterior, basicamente transferir informação entre o `Encoder` e o `Decoder`

Enviar o texto compactado é relativamente fácil: ele é apenas uma string, mas, para o dicionário que era uma matriz, tive que pensar em uma maneira alternativa para fazer, infelizmente as informações que podem ser passadas são um tanto limitadas (limitadas pela dificuldade), então para eu transferir o dicionário em forma de matriz (sua forma original no `Encoder`) achei que seria um processo muito difícil, por isso pensei em um método de converter essa matriz para apenas uma string, onde ocorria basicamente:

		Dicionario		    texto     Dicionario
		+----+----+		  compactado      |
		| a  | 0  |			 |	  |
		| b  | 10 |	---------->	"0100110  a0 b10 c11"
		| c  | 11 |			|___________________|
		+----+----+			           |________________ Shared Memory

Dessa forma, tudo é enviado em uma string apenas, e eu tendo que apenas transformar o dicionário para uma matriz novamente quando o dado chegar ao `Decoder`.

Logo após descomprimir o dado, o `Decoder` reúne as informações em uma string e as coloca novamente no bloco da memória compartilhada, fazendo com que o `Encoder` possa receber os dados e assim imprimi-los ao usuário. :D

Os programas se executam através da função `system`, assim podendo executá-los um dentro do outro, e para o `Encoder` saber quando precisa imprimir os dados, o `Decoder` o chama com uma série de argumentos de linha de comando que são utilizadas a grosso modo como uma "senha".
