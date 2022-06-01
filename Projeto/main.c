/**
* Autor: Luís Queirós
* Email: luisqueiros21@gmail.com
* Date 20-03-2022
* Desc: Função main
*/
#include "header.h"

job* ht[MAX];
CelulaPlano matriz[maq][time];

int main() {
	IniciarPlano(matriz);
	*ht = IniciaHash(ht);
	job* j;
	j = NULL;
	j = CriaJob(616);
	*ht = InsertJobHash(j, ht);
	int index = FuncaoHash(j->cod);
	job* aux;
	aux = ht[index];
	printf("%d", aux->cod);

	aux = Procurajob(616, ht);
	printf("%d", aux->cod);
	//*ht = ApagaJob(616, ht);
	*ht = CriarOpJobHash(ht, 616, 1);
	printf("\n%d", aux->op->cod);
	//*ht = RemoverOpJobHash(ht, 616, 1);
	/**ht = AlterarOpJobHash(ht, 616, 1, 2);
	printf("\n%d", aux->op->cod);*/
	/*job* jobe;
	jobe = NULL;
	jobe = CriaJob(1);
	op* o1 = NULL;
	o1 = AdicionarOperacao(1);
	op* o2 = NULL;
	o2 = AdicionarOperacao(2);
	op* o3 = NULL;
	o3 = AdicionarOperacao(3);
	jobe->op = InserirOp(jobe->op, o1);
	jobe->op = InserirOp(jobe->op, o2);
	jobe->op = InserirOp(jobe->op, o3);
	jobe->op = RemoverTodasOp(jobe);
	*/
	*ht = CriarMaqJobHash(ht, 616, 1, 1, 3);
	*ht = CriarMaqJobHash(ht, 616, 1, 2, 2);
	//*ht = RemoverMaqJobHash(ht, 616, 1, 1);
	//*ht = AlterarMaqJobHash(ht, 616, 1, 1, 2, 2);
	PosicaoOcupa(ht, 616, 1, matriz);
	MostrarPlano(matriz);
}