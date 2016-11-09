#include "proj2.h"


int main(){
	//The following is the maximum 32-bit number that you can have minus the 3 most significant bits
	int *buffmax=(int*)malloc(7483647*sizeof(int));
	int buffcount=0;
	int nodes;

	struct grafo* listadjacent;
	int tail;
	int head;
	int link;
	int procura;
	FILE* fp;
	fp = fopen("As.txt","r");


		while(fscanf(fp,"%d %d %d",&tail,&head,&link)!=	EOF){

			
				if(buffmax[7483647-tail]==0){
					buffmax[7483647-tail]=tail;
					buffcount++;					
				}	
				
		}

		fclose(fp);
		printf("%d\n",buffcount);

		nodes= 7483647;
		listadjacent = criagrafo(nodes);
		fp = fopen("As.txt","r");

		while(fscanf(fp,"%d %d %d",&tail,&head,&link)!=	EOF){
			addnode(listadjacent,tail,head,link,buffcount);	
		}

		printf("qual o nodo a procurar?");
		scanf("%d",&procura);
		comroute(listadjacent,procura);
		fclose(fp);
		while(1){
			printf("\ndistancia para que nodo?");
			scanf("%d",&procura);
			printf("nº de Hops:%d - Nodo Prévio: %d -tipo de rota:%d (ctrl-c pra sair)\n",listadjacent->array[7483647-procura].dist,listadjacent->array[7483647-procura].parent,listadjacent->array[7483647-procura].Pathtype);
		}
}