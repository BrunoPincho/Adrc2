#include "proj2.h"


int main(){
	int *buffmax=(int*)malloc(7483647*sizeof(int));
	int buffcount=0;
	int nodes;

	struct grafo* listadjacent;
	int tail;
	int head;
	int link;
	int procura;
	FILE* fp;
	fp = fopen("Network.txt","r");

	//int edgecount=0;
	

		
	/*
		while(fscanf(fp,"%d %d %d",&tail,&head,&link)!=	EOF){

			for(i=0;i<=buffcount;i++){
				if(buffmax[i]==tail){
					break;
				}else if(i==buffcount){
					buffmax[buffcount]=tail;
					buffcount++;
					break;
				}


			}
				
		}
		fclose(fp);*/

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
		fp = fopen("Network.txt","r");

		while(fscanf(fp,"%d %d %d",&tail,&head,&link)!=	EOF){
			addnode(listadjacent,tail,head,link,buffcount);	
		}
		printf("qual o nodo a procurar?");
		scanf("%d",&procura);
		djishort(listadjacent,procura);
		fclose(fp);
		while(1){
			printf("distancia para que nodo?");
			scanf("%d",&procura);
			printf("nº de Hops:%d - Nodo Prévio: %d  (ctrl-c pra sair)\n",listadjacent->array[7483647-procura].dist,listadjacent->array[7483647-procura].parent);
		}

}