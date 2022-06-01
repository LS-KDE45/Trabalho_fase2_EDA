#include<stdio.h>
/**
* Autor: Luís Queirós
* Email: luisqueiros21@gmail.com
* Date 20-03-2022
* Desc: Módulo de conteúdos globais
*/


#ifndef DADOSGLOBAIS
#define DADOSGLOBAIS

typedef struct maqtime {
	int M;
	int T;
	struct maqtime* next;
}maqtime;

typedef struct op {
	int cod;
	struct maqtime* mt;
	struct op* next;
}op;

typedef struct job {
	int cod;
	struct op* op;
	struct job* next;
}job;

job* CriaJob(int cod);
op* AdicionarOperacao(int codo);
op* InserirOp(op* h, op* o);
int ExisteOp(op* o, int codigo);
int ExisteMaq(maqtime* mt, int M);
maqtime* InserirMaquina(maqtime* h, maqtime* mt);
maqtime* CriarMT(int M, int T);
maqtime* DetMin(op* o);
int DetMinO(job* j);
maqtime* DetMax(op* o);
int DetMaxO(job* j);
float DetMediaTemp(op* o);
op* RemoverOp(op* h, int codo);
maqtime* AlterarMT(maqtime* h, int M, int nM, int nT);
maqtime* ApagarMT(maqtime* h, int M);
op* AlteracaoOp(op* h, int cod, int codnovo);
int GuardarDadosFicheiro(char* nomefile, job** ht);
job** LerDadosFicheiro(char* nomefile, job** ht);



/**
* FASE 2					//////////////////////////////////////////////////////////////////////////
*/
#define MAX 7
#define maq 10
#define time 10

extern job* ht[MAX];


typedef struct CelulaPlano {
	int codj;
	int codo;
}CelulaPlano;

CelulaPlano matriz[maq][time];

typedef struct InformacaoMatriz {
	int maquina;
	int tempo;
	int codj;
	int codo;
}InformacaoMatriz;


int FuncaoHash(int num);
job** IniciaHash(job* ht[]);
job** InsertJobHash(job* j, job* ht[]);
job* Find(int num, job* h);
job* Procurajob(int num, job* ht[]);
job** ApagaJob(int cod, job* ht[]);
job** CriarOpJobHash(job* ht[], int codj, int codo);
job** RemoverOpJobHash(job* ht[], int codj, int codo);
job** AlterarOpJobHash(job* ht[], int codj, int codo, int codnovo);
job** CriarMaqJobHash(job* ht[], int codj, int codo, int M, int T);
job** RemoverMaqJobHash(job* ht[], int codj, int codo, int M);
job** AlterarMaqJobHash(job* ht[], int codj, int codo, int M, int Mnovo, int Tnovo);
op* RemoverTodasOp(job* j);
maqtime* RemoverTodasMaq(op* o);
void IniciarPlano(CelulaPlano matriz[][time]);
int Ocupa(int codj, int codo, int maquina, int tempo, int posinicial, CelulaPlano matriz[][time]);
int DetPosicaoInicial(int codj, CelulaPlano matriz[][time]);
int VerificarOcupa(int maquina, int tempo, int posinicial, CelulaPlano matriz[][time]);
maqtime* RetirarMinAux(maqtime* haux, int maquina);
int PosicaoOcupa(job* ht[], int codj, int codo, CelulaPlano matriz[][time]);
void MostrarPlano(CelulaPlano matriz[][time]);
int OcupaFicheiro(int codj, int codo, int maquina, int tempo, CelulaPlano matriz[][time]);
int GravarDadosMatriz(char* nomefile, CelulaPlano matriz[][time]);
int LerDadosMatriz(char* nomefile, CelulaPlano matriz[][time]);
#endif