#include "proj2.h"

int CRP[3][4]={{0,-1,-1,-1},{1,-1,-1,-1},{2,2,2,-1}};

struct grafo* criagrafo(int nodes){

	int i;
	struct grafo* ref = (struct grafo*)malloc(sizeof(struct grafo));
	ref->array = (struct lista*)malloc(nodes * sizeof(struct lista));

	for(i=0;i<nodes;i++){
		ref->array[i].num = -1;
		ref->array[i].pointer=NULL;
	}

	return ref;
}



void addnode(struct grafo*ref,int tail,int head,int linktype,int Vertices){
	int i;
	struct node* temp;
	struct node* aux;
	//i = (*ref)->array[0].num;
	//prova de existência da tail


		if(ref->array[7483647-tail].num == tail)
		{
			ref->array[7483647-tail].len++;
			//nesta situação estamos a adicionar uma ligação nova a um nodo já existente
			aux = ref->array[7483647-tail].pointer;
				while(aux->next!=NULL){
					aux = aux->next;
				}
				//neste momento estamos no ultimo elemento da lista referente ao nodo de tail
				temp =(struct node*)malloc(sizeof(struct node));
				temp->id = head;
				temp->Linktype = linktype;
				temp->next = NULL;
				aux->next = temp;
				return;

		}
		else if(ref->array[7483647-tail].num == -1){
				ref->array[7483647-tail].num = tail;
				ref->array[7483647-tail].dist = INT_MAX;
				temp = (struct node*)malloc(sizeof(struct node));
				ref->array[7483647-tail].pointer = temp;
				temp->id=head;
				temp->Linktype = linktype;
				temp->next = NULL; 
				return;
		}

	/*for(i=0;i<Vertices;i++){

		if(ref->array[i].num == tail){
			ref->array[i].len++;
			//nesta situação estamos a adicionar uma ligação nova a um nodo já existente
			aux = ref->array[i].pointer;
				while(aux->next!=NULL){
					aux = aux->next;
				}
				//neste momento estamos no ultimo elemento da lista referente ao nodo de tail
				temp =(struct node*)malloc(sizeof(struct node));
				temp->id = head;
				temp->Linktype = linktype;
				temp->next = NULL;
				aux->next = temp;
				return;

		}

		//inserção nova na lista
		if(ref->array[i].num == -1){
				ref->array[i].num = tail;
				temp = (struct node*)malloc(sizeof(struct node));
				ref->array[i].pointer = temp;
				temp->id=head;
				temp->Linktype = linktype;
				temp->next = NULL; 
				return;
		}
	}*/




}


void djishort(struct grafo*ref,int destination){
	int *nodeVect;
	struct lista core;
	struct node* aux;
	core = ref->array[7483647-destination];
	core.dist = 0;
	int i=0;
	
	int unseen=0;

	while(1){
					
					nodeVect = (int	*)malloc((core.len+1)*sizeof(int));

					aux = core.pointer;

					while(aux!=NULL){
						if(ref->array[7483647-(aux->id)].seen==0){
							nodeVect[unseen] = aux->id;//esta parte pode ser optimizada, é preferivel que a lista de unseens seja guardada no nodo do que ser reconstruida cada vez que se volta ao nodo
							unseen++;
						}
						aux=aux->next;
					}
					if(unseen==0){
						if(core.num == destination)
							return;
						//neste ponto retorna da funcao se o destino ja nao tiver nada para onde saltar, o que indica que ja se mapeou os caminhos mais curtos todos para 
						ref->array[7483647-(core.num)].seen = 1;
						core = ref->array[7483647-core.previous];
					}else{

					for(i=0;i<unseen;i++){
						if((ref->array[7483647-nodeVect[i]].dist)>(core.dist+1)){
							ref->array[7483647-nodeVect[i]].dist=(core.dist+1);
							ref->array[7483647-nodeVect[i]].parent = core.num;
						}
					}

					ref->array[7483647-(core.num)].seen = 1;
					
					/*for(i=0;i<=core.len;i++){
						if(ref->array[7483647-nodeVect[i]].seen!=0){
							j++;
							break;
						}
					}*/
					

					
						ref->array[7483647-nodeVect[0]].previous=ref->array[7483647-(core.num)].num;
						core = ref->array[7483647-nodeVect[0]];
					}
					free(nodeVect);
					unseen=0;


	}






}