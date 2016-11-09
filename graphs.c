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
				
				
				    /*FAZER A VERIFICACAO DISTO PARA NAO DAR SEGFAULT*/
				ref->array[7483647-tail].extension = -1;
				ref->array[7483647-tail].Pathtype = 10;
				
				
				
				temp = (struct node*)malloc(sizeof(struct node));
				ref->array[7483647-tail].pointer = temp;
				temp->id=head;
				temp->Linktype = linktype;
				temp->next = NULL; 
				return;
		}
}

int pathtype(int caminho,int novo){
	/*
		switch (caminho){
			case 0:{
					 switch(novo){
					 		case 0: {	
					 					return 2;
					 					break;
					 				}
					 		case 1:{
					 					
					 					return 1;
					 					break;
					 		}
					 		case 2:{    
					 					return -1;
					 					break;

					 				}

					 	}
					
					 	break;

					}

			case 1:{
						if(novo == 0){
							return 2;
							break;
							}else{
								return 1;
								break;
							}
					}

			case 2:{
						if(novo == 1){
							return 1;
						}else{
						return 2;
						break;
						}
					}

			default: return -1;
		}
		return -1;*/
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


void comroute(struct grafo*ref,int destination){
	int *nodeVect;
	int *nodeAtt;
	struct lista core;
	struct node* aux;
	ref->array[7483647-destination].extension = 2;
	ref->array[7483647-destination].dist = 0;
	core = ref->array[7483647-destination];
	int i=0;
	int min=5;
	int pos=0;
	int k;
	int compRota;
	int unseen=0;

	while(1){
					//nodeVect guarda os possiveis saltos
					nodeVect = (int	*)malloc((core.len+1)*sizeof(int));
					nodeAtt = (int *)malloc((core.len+1)*sizeof(int));


					aux = core.pointer;
					if(core.num == 5)
						puts("cenas\n");

					while(aux!=NULL){
					  	if(aux->id == core.previous || aux->id == destination){
					  		aux->seen = 1;
					  	}
						  /*Aqui registamos não só os nodos possiveis para saltar, como também o seu valor comercial*/
					  	
						if(aux->seen==0 && CRP[core.extension][(aux->Linktype)-1]!=-1 && aux->id != core.previous){
							nodeVect[unseen] = aux->id;
							nodeAtt[unseen]= aux->Linktype-1;
							unseen++;
						}
						aux=aux->next;
					}

					




					if(unseen==0){
						if(core.num == destination && ref->array[7483647-(core.num)].seen==ref->array[7483647-(core.num)].len+1){
							return;
						}
						//neste ponto retorna da funcao se o destino ja nao tiver nada para onde saltar, o que indica que ja se mapeou os caminhos mais curtos todos para 
						ref->array[7483647-(core.num)].seen++;
						core = ref->array[7483647-core.previous];
					}else{

						

					for(i=0;i<unseen;i++){

						if(core.num == destination){
								compRota = pathtype(nodeAtt[i],nodeAtt[i]);
							}else{
								compRota = pathtype(core.extension,nodeAtt[i]);
							}

						if((ref->array[7483647-nodeVect[i]].dist)>(core.dist+1) ){
							ref->array[7483647-nodeVect[i]].dist=(core.dist+1);
							ref->array[7483647-nodeVect[i]].parent = core.num;

							//nesta parte temos o tipo de rota, como o algoritmo corre do nodo destino para os restantes ha uma inversao do tipo de rota 
							ref->array[7483647-nodeVect[i]].Pathtype = compRota;
							//&&  compRota<=ref->array[7483647-nodeVect[i]].Pathtype   &&  core.Pathtype <= ref->array[7483647-nodeVect[i]].Pathtype

							
						} else if((ref->array[7483647-nodeVect[i]].dist+1)<(core.dist) && CRP[nodeAtt[i]][ref->array[7483647-nodeVect[i]].Pathtype]!=-1){
							ref->array[7483647-core.num].dist = ref->array[7483647-nodeVect[i]].dist + 1;
							ref->array[7483647-core.num].parent = nodeVect[i];
							core = ref->array[7483647-core.num];
							i = -1;
						}
					}



					ref->array[7483647-(core.num)].seen++;
					
					
						
						
						/*Aqui comparamos todos os caminhos para achar o que tem rota comercial preferencial*/
						for(k =0; k < unseen; k++){						
						  if(nodeAtt[k]<min){
						      min=nodeAtt[k];
						      pos=k;
						    }
						}
									

						ref->array[7483647-nodeVect[pos]].previous=ref->array[7483647-(core.num)].num;
						ref->array[7483647-nodeVect[pos]].extension = min;

						
						aux = core.pointer;
						while(aux!=NULL){
							if(aux->id == nodeVect[pos]){
								aux->seen=1;
								break;
							}
									
							aux=aux->next;
						}



						core = ref->array[7483647-nodeVect[pos]];

						
						
					}
					free(nodeVect);
					free(nodeAtt);
					unseen=0;
					min = 5;
	}
}