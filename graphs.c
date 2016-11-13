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
	struct node* temp;
	struct node* aux;


		if(ref->array[100000-tail].num == tail)
		{
			ref->array[100000-tail].len++;
			//nesta situação estamos a adicionar uma ligação nova a um nodo já existente
			aux = ref->array[100000-tail].pointer;
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
		else if(ref->array[100000-tail].num == -1){
				ref->array[100000-tail].num = tail;
				ref->array[100000-tail].dist = INT_MAX;
				temp = (struct node*)malloc(sizeof(struct node));
				ref->array[100000-tail].pointer = temp;
				temp->id=head;
				temp->Linktype = linktype;
				temp->next = NULL; 
				return;
		}

}

int pathtype(int caminho,int novo){

if(caminho==0 && novo==0)
		return 2;
	if(caminho==1 && novo==1)
		return 1;
	if(caminho==1 && novo==0)
		return 2;
	if(caminho==2 && novo==2)
		return 0;
	if(caminho==2 && novo==1)
		return 1;
	if(caminho==2 && novo == 0)
		return 2;


	return -1;
}

/****************************************************Algoritmo de caminhos comerciais*******************************************************************************/

void* comroute(){
	int destination = procura;
	struct grafo*ref = listadjacent;
	int *nodeVect;
	int *nodeAtt;
	struct lista core;
	struct node* aux;
	ref->array[100000-destination].dist=0;
	ref->array[100000-destination].extension=2;
	core = ref->array[100000-destination];
	core.dist = 0;
	int i=0;
	int relaxante;
	int min = INT_MAX;
	int unseen=0;
	int compRota;
	int countsimplx=0;
	

	while(1){
					
					for(i=0;i<buffcount;i++){
							if(ref->array[100000-Counterbuffer[i]].num!=-1 && ref->array[100000-Counterbuffer[i]].dist < min && ref->array[100000-Counterbuffer[i]].seen == 0){
								min = ref->array[100000-Counterbuffer[i]].dist;
								relaxante = Counterbuffer[i];
							}
					}

					if(countsimplx == buffcount-1){
						sem_post(&sem);
						sem_wait(&sem);
						pthread_exit(NULL);
					}

					core = ref->array[100000-relaxante];

					nodeVect = (int	*)malloc((core.len+1)*sizeof(int));
					nodeAtt = (int *)malloc((core.len+1)*sizeof(int));

					aux = core.pointer;

					while(aux!=NULL){
						if(ref->array[100000-(aux->id)].seen==0 && CRP[core.extension][(aux->Linktype)-1]!=-1){
							nodeVect[unseen] = aux->id;
							nodeAtt[unseen]= aux->Linktype-1;
							unseen++;
						}
						aux=aux->next;
					}

					for(i=0;i<unseen;i++){

						if(core.num == destination){
								compRota = pathtype(nodeAtt[i],nodeAtt[i]);
							}else{
								compRota = pathtype(core.extension,nodeAtt[i]);
							}

						if(((ref->array[100000-nodeVect[i]].dist)>(core.dist+1)) || (compRota < ref->array[100000-nodeVect[i]].Pathtype)){
							ref->array[100000-nodeVect[i]].dist=(core.dist+1);
							ref->array[100000-nodeVect[i]].parent = core.num;
							ref->array[100000-nodeVect[i]].extension=nodeAtt[i];
							ref->array[100000-nodeVect[i]].Pathtype = compRota;
							}
					}

					ref->array[100000-(core.num)].seen = 1;
					
					free(nodeVect);
					free(nodeAtt);
					unseen=0;
					min = INT_MAX;
					countsimplx++;
			}
	}

/****************************************************Algoritmo de caminhos mais curtos*******************************************************************************/
	void* djishort(){
	int destination = procura;
	struct grafo*ref = listadjacent2;	
	int *nodeVect;
	struct lista core;
	struct node* aux;
	ref->array[100000-destination].dist=0;
	core = ref->array[100000-destination];
	core.dist = 0;
	int i=0;
	int relaxante;
	int min = INT_MAX;
	int unseen=0;
	int countsimplx=0;

	while(1){
					
					for(i=0;i<buffcount;i++){
							if(ref->array[100000-Counterbuffer[i]].num!=-1 && ref->array[100000-Counterbuffer[i]].dist < min && ref->array[100000-Counterbuffer[i]].seen == 0){
								min = ref->array[100000-Counterbuffer[i]].dist;
								relaxante = Counterbuffer[i];
							}
					}
					if(countsimplx == buffcount-1){
						sem_post(&sem);
						sem_wait(&sem);
						pthread_exit(NULL);
					}

					core = ref->array[100000-relaxante];

					nodeVect = (int	*)malloc((core.len+1)*sizeof(int));

					aux = core.pointer;

					while(aux!=NULL){
						if(ref->array[100000-(aux->id)].seen==0 ){
							nodeVect[unseen] = aux->id;
							unseen++;
						}
						aux=aux->next;
					}

					for(i=0;i<unseen;i++){
						if((ref->array[100000-nodeVect[i]].dist)>(core.dist+1)){
							ref->array[100000-nodeVect[i]].dist=(core.dist+1);
							ref->array[100000-nodeVect[i]].parent = core.num;
							}
					}

					ref->array[100000-(core.num)].seen = 1;
					
					free(nodeVect);
					unseen=0;
					min = INT_MAX;
					countsimplx++;

				}
}			