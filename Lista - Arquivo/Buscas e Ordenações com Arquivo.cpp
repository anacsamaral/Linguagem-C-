/*

|| -- || -- AVISO IMPORTANTE! -- || -- ||

Todas as fun��es de busca abaixo precisam que os arquivos sejam abertos como "rb" ou "rb+", e as ordena��es EXCLUSIVAMENTE como "rb+".
Aberturas com "w" e "a" escrevem os arquivos APENAS no final, e por isso devem ser usadas somente em substitui��es de arquivos (para "w") e em cadastros (no caso de "a")

*/

// ### BUSCAS ###

// Busca exaustiva

int buscaExaustiva(FILE *Ptr, int id) {
	struct minhaStruct aux;
	rewind(Ptr); 													// Volta para o come�o do arquivo
	fread(&aux, sizeof(minhaStruct), 1, Ptr);						// L� o in�cio
	while(!feof(Ptr) && !(id == aux.id && aux.status == 1)) {		// Enquanto (n�o for fim de arquivo) E n�o for verdade que (o registro atual (tem ID igual ao buscado) e (o registro � v�lido))
		fread(&aux, sizeof(minhaStruct), 1, Ptr);					// Continua lendo
	}
	if (id == aux.id && aux.status == 1) {							// Se o registro estiver com status v�lido e o ID for igual ao buscado
		return ftell(Ptr) - sizeof(minhaStruct);					// Retorne a posi��o onde a �ltima leitura ocorreu (posi��o atual do ponteiro - tamanho da struct)
	}
	else return -1;													// Caso contr�rio, retorne -1 (N�o encontrado)
}

// OBS: Sem vers�o com sentinela. D� pra fazer, mas achei que gastaria tempo demais por ser arquivo bin�rio.

// Busca sequencial indexada

int buscaSequencialIndexada(FILE *Ptr, int id) {
	struct minhaStruct aux;
	rewind(Ptr);
	fread(&aux, sizeof(minhaStruct), 1, Ptr);
	while(!feof(Ptr) && !(aux.id >= id && aux.status == 1)) {	// Quase a mesma coisa que a exaustiva, s� muda as condi��es daqui... --> Enquanto (n�o for fim de arquivo) E n�o for verdade que ((o ID do registro atual � MAIOR OU IGUAL AO ID buscado) E (o registro � v�lido))
		fread(&aux, sizeof(minhaStruct), 1, Ptr);
	}
	if (id == aux.id && aux.status == 1) {
		return ftell(Ptr) - sizeof(minhaStruct);
	}
	else return -1;
}

// Busca bin�ria

int buscaBinaria(FILE *Ptr, int id) {
	int inicio, meio, fim;
	struct minhaStruct aux;
	rewind(Ptr);													// Volta para o come�o do arquivo
	inicio = ftell(Ptr) / sizeof(minhaStruct);						// Registra a posi��o L�GICA inicial (normalmente n�o precisa do sizeof() por causa da rewind(), mas prefiro deixar mesmo assim)
	fseek(Ptr, 0, SEEK_END);										// Busca o final do arquivo
	fim = ftell(Ptr) / sizeof(minhaStruct);							// Registra a posi��o L�GICA final (Aqui PRECISA do sizeof())
	do {
		meio = (inicio + fim) / 2;									// Registra a posi��o L�GICA do meio do arquivo (OBS: SEMPRE REGISTRAR A *POSI��O L�GICA*; se buscar a posi��o em bits (sem dividir o in�cio e o fim por sizeof()), pode ser que seja salva a posi��o do meio de um registro)
		fseek(Ptr, meio * sizeof(minhaStruct), SEEK_SET);			// Busca a posi��o onde o registro do meio se encontra
		fread(&aux, sizeof(minhaStruct), 1, Ptr);					// L� o registro localizado no meio da �rea de busca
		if (!(aux.id == id && aux.status == 1)) {					// Se n�o for verdade que ((o ID do registro atual condiz com o buscado) E (o registro atual � v�lido))
			if (aux.id < id)										// Se o ponteiro de busca est� localizado ANTES do ID buscado
				inicio = meio + 1;									// Redefine o IN�CIO da �rea de busca para o meio MAIS 1
			else fim = meio;										// Se o ponteiro est� localizado DEPOIS do ID buscado, redefine o FIM da �rea de busca para o meio (sem somar 1)
		}
	} while (inicio < fim && !(aux.id == id && aux.status == 1));	// Repete o processo enquanto (a posi��o de in�cio da busca for menor que a final) E (n�o for verdade que (o ID foi encontrado) E (o registro atual � v�lido))
	if (aux.id == id && aux.status == 1)							// Se (o ID foi encontrado) E (o registro atual � v�lido)
		return meio * sizeof(minhaStruct);							// Retorna a posi��o do meio VEZES o tamanho em bits da struct
	else return -1;													// Caso contr�rio, retorna -1 (n�o encontrado)
}

// ### ORDENA��ES ###

// Ordena��o por inser��o direta

void insercaoDireta(FILE *Ptr) {
	int tamanho;
	struct minhaStruct auxA, auxB;
	fseek(Ptr, 0, SEEK_END);												// Busca o final do arquivo
	tamanho = ftell(Ptr) / sizeof(minhaStruct);								// Define o tamanho l�gico do arquivo
	if (tamanho > 1) {														// Verifica se � preciso realizar a ordena��o (� preciso ter no m�nimo DOIS registros)
		do {
			fseek(Ptr, (tamanho - 2) * sizeof(minhaStruct), SEEK_SET);		// Busca a pen�ltima posi��o antes do final do tamanho pr�-estabelecido
			fread(&auxA, sizeof(minhaStruct), 1, Ptr);						// Copia para a vari�vel auxiliar A o pen�ltimo registro
			fread(&auxB, sizeof(minhaStruct), 1, Ptr);						// Copia para a vari�vel auxiliar B o �ltimo registro
			if (auxA.id > auxB.id) {										// Se (o ID da auxiliar A for maior que o da auxiliar B)
				fseek(Ptr, (tamanho - 2) * sizeof(minhaStruct), SEEK_SET);	// Volta para a pen�ltima posi��o antes do final do tamanho pr�-estabelecido
				fread(&auxB, sizeof(minhaStruct), 1, Ptr);					// Passa os conte�dos da auxiliar B para a pen�ltima posi��o
				fread(&auxA, sizeof(minhaStruct), 1, Ptr);					// Passa os conte�dos da auxiliar A para a �ltima posi��o
			}
			tamanho--;														// Reduz o tamanho l�gico para ordena��o em 1
		} while (tamanho > 1 && auxA.id > auxB.id);							// Repete o processo enquanto o tamanho l�gico for maior que 1 E o registro inserido de forma direta n�o estiver em sua posi��o
	}
}

// Ordena��o por permuta��o (N�O CONFUNDIR COM A POR BOLHAS)

void ordenacaoPermutacao(FILE *Ptr) {
	int a, b, tamanho;
	struct minhaStruct auxA, auxB;
	fseek(Ptr, 0, SEEK_END);									// Busca o final do arquivo
	tamanho = ftell(Ptr) / sizeof(minhaStruct);					// Define o tamanho l�gico do arquivo
	for (a = 0; a < tamanho - 1; a++) {							// Primeira repeti��o: come�ando de 0, ir� percorrer at� o pen�ltimo elemento do arquivo
		for (b = a + 1; b < tamanho; b++) {						// Segunda repeti��o: come�ando da posi��o "a" + 1, ir� percorrer at� o �ltimo elemento do arquivo
			fseek(Ptr, a * sizeof(minhaStruct), SEEK_SET);		// Busca a posi��o "a" do arquivo
			fread(&auxA, sizeof(minhaStruct), 1, Ptr);			// Salva o elemento da posi��o "a" do arquivo em uma vari�vel auxiliar
			fseek(Ptr, b * sizeof(minhaStruct), SEEK_SET);		// Busca a posi��o "b" do arquivo
			fread(&auxB, sizeof(minhaStruct), 1, Ptr);			// Salva o elemento da posi��o "b" do arquivo em uma vari�vel auxiliar
			if (auxA.id > auxB.id) {							// Se (o ID do elemento da posi��o "a" FOR MAIOR QUE o elemento da posi��o "b")
				fseek(Ptr, a * sizeof(minhaStruct), SEEK_SET);	// Busca a posi��o "a" do arquivo
				fwrite(&auxB, sizeof(minhaStruct), 1, Ptr);		// Sobrep�e os dados da posi��o "a" com os da posi��o "b"
				fseek(Ptr, b * sizeof(minhaStruct), Ptr);		// Busca a posi��o "b" do arquivo
				fwrite(&auxA, sizeof(minhaStruct), 1, Ptr);		// Sobrep�e os dados da posi��o "b" com os da posi��o "a"
			}
		}
	}
}

// Ordena��o por bolhas

void ordenacaoBolhas(FILE *Ptr) {
	int tamanho, pos, encerrado = 0;
	struct minhaStruct auxA, auxB;
	fseek(Ptr, 0, SEEK_END);																	// Busca o final do arquivo
	for (tamanho = ftell(Ptr) / sizeof(minhaStruct); tamanho > 1 && !encerrado; tamanho--) {	// Ap�s definir o tamanho l�gico do arquivo, uma repeti��o se iniciar� subtraindo 1 do tamanho enquanto (o tamanho FOR MAIOR QUE 1) E (a ordena��o n�o estiver encerrada)
		encerrado = 1;																			// Pr�-define a repeti��o como encerrada, para caso nenhuma troca ocorra
		for (pos = 0; pos < tamanho - 1; pos++) {												// A partir de 0, percorre o arquivo at� o tamanho l�gico atual - 1
			fseek(Ptr, pos * sizeof(minhaStruct), SEEK_SET);									// Busca a posi��o atual da repeti��o no arquivo
			fread(&auxA, sizeof(minhaStruct), 1, Ptr);											// L� dois registros seguidos em auxiliares
			fread(&auxB, sizeof(minhaStruct), 1, Ptr);
			if (auxA.id > auxB.id) {															// Se (o ID do registro A FOR MAIOR QUE o do B)
				fseek(Ptr, pos * sizeof(minhaStruct), SEEK_SET);								// Volta para a posi��o atual da repeti��o
				fwrite(&auxB, sizeof(minhaStruct), 1, Ptr);										// Troca os registros das duas posi��es anteriormente lidas com as auxiliares
				fwrite(&auxA, sizeof(minhaStruct), 1, Ptr);
				encerrado = 0;																	// Determina que a ordena��o ainda n�o foi encerrada
			}
		}
	}
}

// Ordena��o por sele��o direta

int buscarMaiorID(FILE *Ptr, int tamanho) { // Fun��o ESSENCIAL para essa ordena��o
	int maior_pos, maior, cont;
	struct minhaStruct aux;
	rewind(Ptr);											// Volta o arquivo para o in�cio
	fread(&aux, sizeof(minhaStruct), 1, Ptr);				// L� a primeira entrada e registra na vari�vel auxiliar
	maior_pos = 0;											// Define a primeira posi��o como a com o maior ID registrado
	maior = aux.id;											// Define o ID da primeira posi��o como o maior
	for (cont = 1; cont < tamanho; cont++) {				// Come�a uma repeti��o at� o tamanho desejado A PARTIR DA SEGUNDA POSI��O
		fseek(Ptr, cont * sizeof(minhaStruct), SEEK_SET);	// Busca o registro da posi��o atual
		fread(&aux, sizeof(minhaStruct), 1, Ptr);			// Insere o registro atual sobre a auxiliar
		if (maior < aux.id) {								// Se o maior ID salvo FOR MENOR QUE o ID da struct auxiliar
			maior = aux.id;									// Registra o novo maior ID
			maior_pos = cont;								// Registra a posi��o do novo maior ID
		}
	}
	return maior_pos;										// Retorna a maior posi��o
}

void selecaoDireta(FILE *Ptr) {
	int maior_pos, tamanho, encerrado = 0;
	struct minhaStruct auxA, auxB;
	fseek(Ptr, 0, SEEK_END);											// Busca o final do arquivo
	tamanho = ftell(Ptr) / sizeof(minhaStruct);							// Define o tamanho l�gico do arquivo
	while (tamanho > 0 && !encerrado) {									// Enquanto (o tamanho l�gico for maior que 0 E a repeti��o n�o estiver encerrada)
		maior_pos = buscarMaiorID(Ptr, tamanho);						// Procura se ainda h� registros fora de posi��o
		if (maior_pos < tamanho - 1) {									// Se encontrar um registro fora de posi��o
			fseek(Ptr, maior_pos * sizeof(minhaStruct), SEEK_SET);		// Busca e salva o maior registro encontrado na �rea de busca em uma auxiliar
			fread(&auxA, sizeof(minhaStruct), 1, Ptr);
			fseek(Ptr, (tamanho - 1) * sizeof(minhaStruct), SEEK_SET);	// Busca e salva o �ltimo registro da �rea de busca em outra auxiliar
			fread(&auxB, sizeof(minhaStruct), 1, Ptr);
			fseek(Ptr, maior_pos * sizeof(minhaStruct), SEEK_SET);		// Busca o registro maior registro e o sobrep�e com o da �ltima posi��o da �rea de busca
			fwrite(&auxB, sizeof(minhaStruct), 1, Ptr);
			fseek(Ptr, (tamanho - 1) * sizeof(minhaStruct), SEEK_SET);	// Busca a �ltima posi��o da �rea de busca e o sobrep�e com o maior registro
			fwrite(&auxA, sizeof(minhaStruct), 1, Ptr);
			tamanho--;													// Decrementa 1 do tamanho l�gico
		}
		else encerrado = 1;												// Se a maior posi��o encontrada for igual � �ltima do tamanho l�gico atual, o arquivo j� est� ordenado e o processo � finalizado
	}
}

