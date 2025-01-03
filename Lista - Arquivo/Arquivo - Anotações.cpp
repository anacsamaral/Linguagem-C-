// persist�ncia dos dados = gravar ele em algum lugar e levar para onde quiser
/* 
	caractere: fgetc(), fputc(); - para arquivo texto (caracter puro, nao tem marca��o)
	string: fgets(), fputs(); - para arquivo texto (caracter puro, nao tem marca��o)
	formatada: fscanf(), fprint() - para arquivo texto (caracter puro, nao tem marca��o)
	- arquivo de texto serve para mostrar os dados
	
	registros - para arquivo bin�rio (armazena os dados)
			  - se n�o tiver o programa que criou o arquivo, n�o d� para acessar ele;
			  - arquivo robusto
	
	- quando precisa ler ou gravar coisas no arquivo, s�o fun��es diferentes
	para arq texto e bin�rio;
	
	- s�o diferentes as formas de manipular o arquivo
	- para criar, apagar, renomear, onde est�, s�o os mesmos comandos para os 2 tipos
	
	- precisamos criar uma se��o para que consiga usar esse arquivo
	- colocar extens�o: dados.dat ou dados.txt
	- para mandar os dados para o arquivo, tem que ter uma vari�vel
	do tipo FIlE, que ter� um ponteiro, ou seja, guarda o endere�o de um arquivo.
		- Ela n�o � o arquivo, s� guarda o endere�o de onde o arquivo est�;
		- � uma vari�vel hexadecimal.;
		- � pego o ponteiro e associa com o arquivo de fora;
		- O programa precisa ter algu�m que vincula o arquivo que est� l� fora;
		- � como se houvesse um buffer intermediando entre o programa e o arquivo
		ele descarrega os dados. � o momento em que abre uma se��o.
		As vezes � necess�rio for�ar o descarregamento
		- Ponteiro - Nome F�sico
		- Toda vez que usar o aquivo, vai abrir uma se��o;
		- Se n�o fechar a sess�o, podem ficar dados no buffer e eles se perderem;
		- O que enche o buffer vai pro arquivo, o que n�o enche n�o vai
		- O arquivo pode acabar sendo corrompido e n�o ter� como us�-lo mais.
		- Onde voc� abre, voc� fecha;
		- Objetivo = integridade dos dados, mesmo que perca tempo;
	
	- Abrir o arquivo = fopen(); 
	- Vai estar associado a uma vari�vel FILE *Ptr
	- Usou o nome, atualiza no arquivo;
	- FILE *Ptr = fopen("Dados.dat", "" -> tipo de abertura);
	- Banco de dados = mandar gravar e recuperar; Grava e l�;
	- Algo f�sico, pega da mem�ria e manda pro lugar ou pega do lugar e manda pra mem�ria
	- A linguagem C tem 12 tipos de abertura de arquivo:
		- 6 para arquivo texto;
		- 6 para arquivo bin�rio;
	- O arquivo s� vai ser criado/manipulado, s� depois do comando fopen(), a�
	pode ser utilizado
	- � recomendado estar no mesmo diret�rio do programa
	- quando o usu�rio for digitar o caminho, ela s� ir� digitar uma barra
	- quando for fixo, s�o duas barras;
	- se criar um arquivo ja existente, ele zera o arquivo;
	- quando abre um arquivo, uma se��o, o ponteiro est� em algum lugar;
	- EOF - end of file = indica onde o arquivo est�, um endere�o nulo
	em C, que significa que o arquivo acabou;
	- a marca de final de arquivo est� onde acabou de criar o arquivo, toda vez que 
	� gravado, grava a partir dessa marca; n�o deixa observar o que j� foi gravado;
	se abrir um arquivo com wb, n�o consegue ver se o dado � repetido ou n�o
	porque com WB o ponteiro sempre est� no fim do arquivo;
	- quando abrimos com RB, o ponteiro do arquivo � colocado no in�cio
	podendo andar no arquivo, mas n�o consegue gravar (buscas);
	- s� d� para abortar o arquivo se abrir o arquivo e n�o tiver nada
	- AB grava no final; se o arquivo nao existe, ele cria, se ja existe
	mantem os dados e posiciona o ponteiro no final
	- os plus fazem a mesma coisa, mas nao deixa gravar, deixa gravar em qualquer lugar
	e atualizar o que ja tem (RB+), se colocar o ponteiro no fim, ele grava. mas 
	na teoria nao
	- se arq existe, zera, senao, ele cria (WB+)
	- AB+ para buscas;
	
	fclose() - como um "salvar"
	
 */
