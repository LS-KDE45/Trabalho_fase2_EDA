#include "header.h"

/**
* Autor: Luís Queirós
* Email: luisqueiros21@gmail.com
* Date 20-03-2022
* Desc: Módulo de funções
*/


#pragma warning(disable: 4996)
#include<stdio.h>
#include"header.h"

/**
* Função para criar job
*/
job* CriaJob(int cod) {
	job* x = (job*)malloc(sizeof(job));
	if (x == NULL) return NULL;	//  ver se tem espaço espaço disponível
	x->cod = cod;
	x->op = NULL;
	x->next = NULL;
	return x;
}


/**
* Função de adicionar operações
*/

op* AdicionarOperacao(int codo) {
	op* o;
	o = (op*)malloc(sizeof(op));
	if (o == NULL) return NULL; //  ver se tem espaço espaço disponível
	o->cod = codo;
	o->mt = NULL;
	o->next = NULL;
	return o;
}


/**
* Função de ordenar operações
*/

op* InserirOp(op* h, op* o) {
	if (o == NULL)return NULL; //caso não exista a operação
	if (h == NULL)		//caso a lista de operações não tenha header
	{
		h = o;
	}
	else {
		if (ExisteOp(h, o->cod) == 1)return h; //caso essa operação já exista nesse job 
		else
		{
			op* aux = h;
			while (aux->next != NULL) {
				aux = aux->next;
			}
			aux->next = o;// insere no fim uma nova operacao
		}
	}
	return h;
}

/**
* Função para ver se existe operação
*/

int ExisteOp(op* o, int codigo)
{
	op* aux = o;

	if (o == NULL) return 0; //caso não exista operações

	while (aux)
	{
		if (aux->cod == codigo)	//procurar o codigo
			return 1;
		else
		{
			aux = aux->next;
		}
	}

	return 0;
}

/**
* Função de ordenar maquina tempo
*/

maqtime* InserirMaquina(maqtime* h, maqtime* mt)
{
	if (mt == NULL) return NULL;	//se o novo maqtime não existir

	if (h == NULL)			//se não existir nenhuma maquina na operaçao,insere a maquina e respetivo tempo
	{
		h = mt;
	}
	else
	{
		if (ExisteMaq(h, mt->M) == 1) return h; //se já existir a maquina na operçao, nao insere
		else
		{
			maqtime* aux;
			aux = h;
			while (aux->next != NULL) {
				aux = aux->next;
			}
			aux->next = mt;// insere no fim uma nova operacao
		}
	}

	return h;
}


/**
* Função para ver se existe maquina
*/
int ExisteMaq(maqtime* mt, int M)
{
	if (mt == NULL) return 0;//caso não exista operações
	maqtime* aux = mt;
	while (aux != NULL)
	{
		if (aux->M == M)//procurar o codigo
		{
			return 1;
		}
		else
		{
			aux = aux->next;
		}
	}

	return 0;
}

/**
* Função de criar maquina tempo
*/
maqtime* CriarMT(int M, int T) {
	maqtime* mt;
	mt = (maqtime*)malloc(sizeof(maqtime));
	if (mt == NULL) return NULL; //  ver se tem espaço espaço disponível
	mt->M = M;
	mt->T = T;
	mt->next = NULL;
	return mt;
}


/**
* Funções de determinação de quantidade mínima de unidades de tempo
*/

/**
* Função de determinação de quantidade mínima de unidades de tempo por operação
*/

maqtime* DetMin(op* o) {
	if (o == NULL) return NULL;//caso não exista operação
	if (o->mt == NULL)return NULL;//caso não existam maquinas
	maqtime* aux = o->mt, * aux2 = aux->next;
	while (aux2 != NULL) { // procura na lista qual a maquina com menor tempo
		if (aux->T > aux2->T) {
			aux = aux2;
		}
		aux2 = aux2->next;
	}
	return aux;
}


/**
* Função de determinação de quantidade mínima de unidades de tempo por job
*/

int DetMinO(job* j) {
	if (j == NULL)return -1;//caso não existam jobs
	if (j->op == NULL)return -1;//caso não existam operações
	op* o = j->op;
	if (o->mt == NULL)return -1;//caso não existam maquinas
	maqtime* mt;
	int soma = 0;
	while (o != NULL) {
		mt = DetMin(o);
		printf("op: %d, maq: %d, temp: %d", o->cod, mt->M, mt->T);//diz a operação, a maquina com menor tempo e o respetivo tempo
		soma += mt->T;
		o = o->next;
	}
	return soma;
}

/**
* Funções de determinação de quantidade máxima de unidades de tempo
*/

/**
* Função de determinação de quantidade máxima de unidades de tempo por operação
*/

maqtime* DetMax(op* o) {
	if (o == NULL) return NULL;//caso não exista operação
	if (o->mt == NULL)return NULL;//caso não existam maquinas
	maqtime* aux = o->mt, * aux2 = aux->next;
	while (aux2 != NULL) { // procura na lista qual a maquina com maior tempo
		if (aux->T < aux2->T) {
			aux = aux2;
		}
		aux2 = aux2->next;
	}
	return aux;
}


/**
* Função de determinação de quantidade máxima de unidades de tempo por job
*/

int DetMaxO(job* j) {
	if (j == NULL)return -1;//caso não existam jobs
	if (j->op == NULL)return -1;//caso não existam operações
	op* o = j->op;
	if (o->mt == NULL)return -1;//caso não existam maquinas
	maqtime* mt;
	int soma = 0;
	while (o != NULL) {
		mt = DetMax(o);
		printf("op: %d, maq: %d, temp: %d", o->cod, mt->M, mt->T);//diz a operação, a maquina com maior tempo e o respetivo tempo
		soma += mt->T;
		o = o->next;
	}
	return soma;
}


/**
* Função de determinação de quantidade média de unidades de tempo por operação
*/

float DetMediaTemp(op* o) {
	if (o->mt == NULL) return 0;//caso não existam maquinas tempo
	maqtime* mt;
	mt = o->mt;
	int soma = 0, contador = 0;
	float media;
	while (mt != NULL) {
		soma = soma + mt->T;
		mt = mt->next;
		contador++;
	}
	media = soma / contador;
	return media;

}


/**
* Função de Remoção de operações
*/

op* RemoverOp(op* h, int codo) {
	if (h == NULL) return NULL;		//se a lista for vazia
	op* aux;
	if (h->cod == codo) {// se for na primeira posição
		if (h->mt != NULL) {								//
			h->mt = RemoverTodasMaq(h);						//alteração segunda fase
		}													//
		aux = h;
		h = h->next;
		free(aux);
	}
	else {
		aux = h;
		op* Ant_aux = aux;
		while (aux && aux->cod != codo) {// procurar o codigo
			Ant_aux = aux;
			aux = aux->next;
		}
		if (aux != NULL) {					//se encontrou, remove
			if (aux->mt != NULL) {								//
				aux->mt = RemoverTodasMaq(aux);					//alteração segunda fase
			}													//
			Ant_aux->next = aux->next;
			free(aux);
		}

	}
	return h;
}

/**
* Função para alterar maqtime
*/

maqtime* AlterarMT(maqtime* h, int M, int nM, int nT) {
	if (h == NULL) return NULL;//caso õ header não exista
	maqtime* aux = h;
	while (aux->M != M && aux != NULL) {
		aux = aux->next;
	}
	if (aux == NULL)return NULL; //caso não exista essa maquina
	aux->M = nM;
	aux->T = nT;
	return h;
}


/**
* Função para retirar maqtime
*/

maqtime* ApagarMT(maqtime* h, int M) {
	if (h == NULL) return NULL;// caso não exista maquina tempo
	maqtime* aux;
	if (h->M == M) {// se for na primeira posição
		aux = h;
		h = h->next;
		free(aux);
	}
	else {
		aux = h;
		maqtime* Ant_aux;
		Ant_aux = aux;
		while (aux && aux->M != M) {// procurar a maquina
			Ant_aux = aux;
			aux = aux->next;
		}
		if (aux != NULL) {					//se encontrou, remove
			Ant_aux->next = aux->next;
			free(aux);
		}

	}
	return h;
}


/**
* Função de alteração de operações
*/

op* AlteracaoOp(op* h, int cod, int codnovo) {
	if (h == NULL) return NULL;// caso não exista header
	op* aux = h;
	while (aux != NULL && aux->cod != cod) {
		aux = aux->next;
	}
	if (aux == NULL)return NULL;//caso não exista o codigo
	aux->cod = codnovo;
	return h;
}


/**
* Função para guardar dados em ficheiros txt
*/

//ligeiras alterações para fase 2
int GuardarDadosFicheiro(char* nomefile, job** ht) {
	FILE* fp;

	if (ht == NULL) return -1;//caso não existam jobs
	job* j;
	op* o;
	maqtime* mt;
	fp = fopen(nomefile, "w");
	for (int i = 0; i < MAX; i++) {		//alteração
		j = ht[i];
		while (j != NULL) {
			fprintf(fp, "j\n%d\n", j->cod);//coloca-se a letra j para identificar o codigo, e escrevo o codigo do job
			o = j->op;
			while (o != NULL) {
				fprintf(fp, "o\n%d\n", o->cod);//coloca-se a letra o para identificar o codigo, e escrevo o codigo do o
				mt = o->mt;
				while (mt != NULL) {
					fprintf(fp, "m\n%d;%d\n", mt->M, mt->T);//coloca-se a letra m para identificar o codigo, e escrevo o numero da maquina e o tempo
					mt = mt->next;
				}
				o = o->next;
			}
			j = j->next;
		}
	}
	fprintf(fp, "e");//coloca-se a letra e para saber o fim do ficheiro
	fclose(fp);
	return 0;
}

/**
* Função para ler dados em ficheiros txt
*/

//ligeiras alterações para fase 2
job** LerDadosFicheiro(char* nomefile, job** ht) {
	char sitio = NULL;
	int temp_m, temp_t, temp_codj, temp_codo;
	FILE* fp;
	if ((fp = fopen(nomefile, "r")) == NULL) return -1;//caso não exista o file
	job* j;
	j = NULL;
	op* o;
	o = NULL;
	maqtime* mt;
	mt = NULL;
	while (sitio != 'e') {//enquanto não chegue ao fim do file
		fscanf(fp, "%c", &sitio);
		if (sitio == 'm') {//caso a letra seja m escreve no maquina tempo
			fscanf(fp, "%d;%d", &temp_m, &temp_t);
			mt = CriarMT(temp_m, temp_t);
			o->mt = InserirMaquina(o->mt, mt);
		}
		else {
			if (sitio == 'o') {//caso a letra seja o escreve nas operações
				fscanf(fp, "%d", &temp_codo);
				o = AdicionarOperacao(temp_codo);
				j->op = InserirOp(j->op, o);
			}
			else {
				if (sitio == 'j') {//caso a letra seja j escreve nos jobs
					fscanf(fp, "%d", &temp_codj);
					j = CriaJob(temp_codj);
					//alteração
					*ht = InsertJobHash(j, ht);
				}
			}
		}


	}
	//alteração
	return *ht;
}

/**
* FASE2							//////////////////////////////////////////////////////////////////////////////////////
*/

/**
* Determina a função hash
*/
int FuncaoHash(int num) {
	if (num > 0) {
		return (num % MAX);
	}
	return 0;
}

/**
* Inicia a hash table
*/
job** IniciaHash(job* ht[]) {
	int i;
	for (i = 0; i < MAX; i++) {
		ht[i] = NULL;
	}
	return *ht;
}

/**
* Procura um job numa lista de jobs
*/
job* Find(int cod, job* h) {
	if (h == NULL)return NULL;
	while (h != NULL && h->cod != cod) {
		h = h->next;
	}
	return h;
}

/**
* Procura um job numa hash table
*/
job* Procurajob(int cod, job* ht[]) {

	int pos = FuncaoHash(cod);

	if (ht[pos] == NULL)return NULL;
	return(Find(cod, ht[pos]));
}

/**
* Insere um job na hash table
*/
job** InsertJobHash(job* j, job* ht[]) {
	if (j == NULL)return NULL;
	if (Procurajob(j->cod, ht) != NULL)return NULL; //caso exista

	//index 
	int pos = FuncaoHash(j->cod);
	if (ht[pos] == NULL) {
		ht[pos] = j;
	}
	else {
		j->next = ht[pos];
		ht[pos] = j;
	}
	return *ht;
}

/**
* Apaga um job na hash table
*/

job** ApagaJob(int cod, job* ht[]) {
	int pos = FuncaoHash(cod);
	if (ht[pos] == NULL)return NULL;
	else {
		job* h = ht[pos];
		job* aux;
		if (h->cod == cod) {// se for na primeira posição
			if (h->op != NULL) {
				h->op = RemoverTodasOp(h);
			}
			aux = h;
			h = h->next;
			free(aux);
		}
		else {
			aux = h;
			job* Ant_aux = aux;
			while (aux && aux->cod != cod) {// procurar o codigo
				Ant_aux = aux;
				aux = aux->next;
			}
			if (aux != NULL) {					//se encontrou, remove
				if (aux->op != NULL) {
					aux->op = RemoverTodasOp(aux);
				}
				Ant_aux->next = aux->next;
				free(aux);
			}

		}
		ht[pos] = h;
		return *ht;
	}
}

/**
* Insere uma operação num job na hash table
*/

job** CriarOpJobHash(job* ht[], int codj, int codo) {
	job* aux;
	aux = Procurajob(codj, ht);
	op* auxo;
	auxo = NULL;
	auxo = AdicionarOperacao(codo);
	aux->op = InserirOp(aux->op, auxo);
	return *ht;
}

/**
* Remove uma operação num job na hash table
*/

job** RemoverOpJobHash(job* ht[], int codj, int codo) {
	job* aux;
	aux = Procurajob(codj, ht);
	aux->op = RemoverOp(aux->op, codo);
	return *ht;
}

/**
* Altera uma operação num job na hash table
*/

job** AlterarOpJobHash(job* ht[], int codj, int codo, int codnovo) {
	job* aux;
	aux = Procurajob(codj, ht);
	aux->op = AlteracaoOp(aux->op, codo, codnovo);
	return *ht;
}


/**
* Insere uma máquina e tempo numa operação num job na hash table
*/

job** CriarMaqJobHash(job* ht[], int codj, int codo, int M, int T) {
	job* auxj;
	auxj = Procurajob(codj, ht);
	if (auxj == NULL)return NULL;
	op* auxo;
	auxo = auxj->op;
	while (auxo != NULL && auxo->cod != codo) {
		auxo = auxo->next;
	}
	if (auxo == NULL)return NULL;
	maqtime* auxmt;
	auxmt = CriarMT(M, T);
	auxo->mt = InserirMaquina(auxo->mt, auxmt);
	return *ht;
}

/**
* Remove uma máquina e tempo de uma operação num job na hash table
*/

job** RemoverMaqJobHash(job* ht[], int codj, int codo, int M) {
	job* auxj;
	auxj = Procurajob(codj, ht);
	if (auxj == NULL)return NULL;
	op* auxo;
	auxo = auxj->op;
	while (auxo != NULL && auxo->cod != codo) {
		auxo = auxo->next;
	}
	if (auxo == NULL)return NULL;
	auxo->mt = ApagarMT(auxo->mt, M);
	return *ht;
}

/**
* Altera uma máquina e tempo de uma operação de num job na hash table
*/

job** AlterarMaqJobHash(job* ht[], int codj, int codo, int M, int Mnovo, int Tnovo) {
	job* auxj;
	auxj = Procurajob(codj, ht);
	if (auxj == NULL)return NULL;
	op* auxo;
	auxo = auxj->op;
	while (auxo != NULL && auxo->cod != codo) {
		auxo = auxo->next;
	}
	if (auxo == NULL)return NULL;
	auxo->mt = AlterarMT(auxo->mt, M, Mnovo, Tnovo);
	return *ht;
}

/**
* Remove todas as operações de um job
*/
op* RemoverTodasOp(job* j) {
	if (j == NULL)return NULL;
	if (j->op == NULL)return NULL;
	op* h;
	op* aux;
	h = j->op;
	aux = h;
	while (h != NULL) {
		if (h->mt != NULL) {
			h->mt = RemoverTodasMaq(h);
		}
		h = h->next;
		free(aux);
		aux = h;
	}
	return h;
}

/**
* Remove todas as máquinas de uma operação
*/
maqtime* RemoverTodasMaq(op* o) {
	if (o == NULL)return NULL;
	if (o->mt == NULL)return NULL;
	maqtime* h;
	maqtime* aux;
	h = o->mt;
	aux = h;
	while (h != NULL) {
		h = h->next;
		free(aux);
		aux = h;
	}
	return h;
}
/**
* Inicializa a matriz de planeamento
*/

void IniciarPlano(CelulaPlano matriz[][time]) {
	for (int i = 0; i < maq; i++) {
		for (int j = 0; j < time; j++) {
			matriz[i][j].codj = 0;
			matriz[i][j].codo = 0;
		}
	}
}

/**
* Ocupa uma posição da matriz de planeamento com um codigo de job e um codigo de operação
*/

int Ocupa(int codj, int codo, int maquina, int tempo, int posinicial, CelulaPlano matriz[][time]) {		
	if (codj == 0 || codo == 0 || maquina <= 0 || tempo <= 0 || posinicial < 0 || tempo > time)return -1;
	else {
		int posicao = posinicial;
		while (posicao < time && matriz[maquina - 1][posicao].codj > 0) {
			if (matriz[maquina - 1][posicao].codj > 0) {
				posicao++;
			}
		}
		for (int i = 0; i < tempo; i++) {
			matriz[maquina - 1][posicao].codj = codj;
			matriz[maquina - 1][posicao].codo = codo;
			posicao++;
		}
		return 1;
	}
}

/**
* Determina a posição no tempo de uma operação anterior de um job na matriz de planeamento 
*/

int DetPosicaoInicial(int codj, CelulaPlano matriz[][time]) {
	int tempo = 0;
	int tempt = 0;
	for (int i = 0; i < maq; i++) {
		for (int j = 0; j < time; j++) {
			if (matriz[i][j].codj == codj && matriz[i][j].codo > tempo) {
				tempo = matriz[i][j].codo;
				tempt = j;
			}
		}
	}
	return tempt;

}

/**
* verifica se é possivel realizar uma operação com uma máquina específica no planeamento
*/

int VerificarOcupa(int maquina, int tempo, int posinicial, CelulaPlano matriz[][time]) {
	int tempt = 1;
	int postempo = posinicial;
	int temppos = 0;
	while (tempt <= time && (postempo - 1) + tempo < time && postempo < time && tempt <= tempo ) {

		if (matriz[maquina][postempo].codj > 0) {
			postempo++;
		}
		else{
			while (tempt <= tempo && ((tempt - 1) + tempo) <= time) {
				temppos = tempt + postempo;
				if (matriz[maquina][temppos].codj == 0) {
					tempt++;
				}
				else {
					postempo = tempt + 1 + postempo;
					tempt = 1;
					break;
				}
			}
		}
	}
	if ((postempo - 1 + tempo) < time) {
		return 1;
	}
	else {
		return -1;
	}
}

/**
* Retira uma máquina e tempo de uma lista auxiliar para determinar o menor tempo para realizar o planeamento
*/

maqtime* RetirarMinAux(maqtime* haux,int maquina) {
	if (haux == NULL) return NULL;// caso não exista maquina tempo
	maqtime* aux;
	if (haux->M == maquina) {// se for na primeira posição
		haux = haux->next;
	}
	else {
		aux = haux;
		maqtime* Ant_aux;
		Ant_aux = aux;
		while (aux && aux->M != maquina) {// procurar a maquina
			Ant_aux = aux;
			aux = aux->next;
		}
		if (aux != NULL) {					//se encontrou, remove
			Ant_aux->next = aux->next;
		}

	}
	return haux;
}

/**
* Ocupa uma posição se possível na matriz de planeamento com a máquina de menor tempo possível de uma operação
*/

int PosicaoOcupa(job* ht[], int codj, int codo, CelulaPlano matriz[][time]) {
	job* j;
	j = Procurajob(codj, ht);
	op* h;										
	h = j->op;
	while (h != NULL && h->cod != codo) {
		h = h->next;
	}
	if (h == NULL)return NULL;//caso não exista essa operação
	int posinicial = DetPosicaoInicial(codj, matriz);
	maqtime* min;
	maqtime* haux = h->mt;
	op* oaux = h;
	min = DetMin(h);
	int v = 0;
	v = VerificarOcupa(min->M, min->T, posinicial, matriz);
	if (v == 1) {
		return Ocupa(codj, codo, min->M, min->T, posinicial, matriz);
	}
	else {
		while (v != 1 && haux != NULL) {
			haux = RetirarMinAux(haux, min->M);
			oaux->mt = haux;
			min = DetMin(oaux);
			v = VerificarOcupa(min->M, min->T, posinicial, matriz);
		}
		if (v == 1) {
			return Ocupa(codj, codo, min->M, min->T, posinicial, matriz);
		}
		else {
			return -1;
		}
	}
}

/**
* Faz um planeamento se possivel de todos os jobs e operações
*/

int PlaneamentoTotal(job* ht[], CelulaPlano matriz[][time]) {
	job* hj;
	for (int i = 0; i < MAX; i++) {
		hj = ht[i];
		while (hj != NULL) {
			op* ho;
			ho = hj->op;
			while (ho != NULL) {
				int posinicial = DetPosicaoInicial(hj->cod, matriz);
				maqtime* min;
				maqtime* maux = ho->mt;
				op* oaux = ho;
				min = DetMin(ho);
				int v = 0;
				v = VerificarOcupa(min->M, min->T, posinicial, matriz);
				if (v == 1) {
					return Ocupa(hj->cod, ho->cod, min->M, min->T, posinicial, matriz);
				}
				else {
					while (v != 1 && maux != NULL) {
						maux = RetirarMinAux(maux, min->M);
						oaux->mt = maux;
						min = DetMin(oaux);
						v = VerificarOcupa(min->M, min->T, posinicial, matriz);
					}
					if (v == 1) {
						return Ocupa(hj->cod, ho->cod, min->M, min->T, posinicial, matriz);
					}
					else {
						return -1;
					}
				}
				ho = ho->next;
			}
			hj = hj->next;
		}
	}
}
/**
* Mostra a matriz de planeamento
*/

void MostrarPlano(CelulaPlano matriz[][time]) {
	for (int i = 0; i < maq; i++) {
		printf("\n");
		for (int j = 0; j < time; j++) {
			printf("Job: %d; Operacao: %d\t", matriz[i][j].codj, matriz[i][j].codo);
		}
	}
}

/**
* Funcao de ocupar a matriz para ficheiros
*/

int OcupaFicheiro(int codj, int codo, int maquina, int tempo, CelulaPlano matriz[][time]) {	
	if (codj == 0 || codo == 0 || maquina <= 0 || tempo <= 0)return -1;
	else {
		matriz[maquina - 1][tempo - 1].codj = codj;
		matriz[maquina - 1][tempo - 1].codo = codo;
		}
		return 1;
}

/**
* Grava os dados da matriz de planeamento em dados binários
*/

int GravarDadosMatriz(char* nomefile, CelulaPlano matriz[][time]) {
	FILE* fp;
	if ((fp = fopen(nomefile, "wb")) == NULL) return -1;
	InformacaoMatriz auxFile;	//struct para gravar em ficheiro
	for (int i = 0; i < maq; i++) {
		for(int j = 0; j < time; j++) {
		//Colocar no registo de ficheiro a inf que está no registo de memória
			auxFile.maquina = i;
			auxFile.tempo = j;
			auxFile.codj = matriz[i][j].codj;
			auxFile.codo = matriz[i][j].codo;
			fwrite(&auxFile, sizeof(auxFile), 1, fp);
		}
	}
	fclose(fp);
	return 0;
}

/**
* lê os dados da matriz de planeamento em dados binários
*/

int LerDadosMatriz(char* nomefile, CelulaPlano matriz[][time]) {
	FILE* fp;
	int v = 0;
	if ((fp = fopen(nomefile, "rb")) == NULL) return -1;
	InformacaoMatriz auxFile;
	while (fread(&auxFile, sizeof(auxFile), 1, fp)) {
		v = OcupaFicheiro(auxFile.codj, auxFile.codo, (auxFile.maquina) + 1, (auxFile.tempo) + 1, matriz);
	}
	fclose(fp);
	return v;
}