#include "proj2.h"
#include "string.h"

char* tipoRota(int x){
	if(x==0)
		return ("cliente");
	if(x==1)
		return ("Peer");
	if(x==2)
		return ("Provider");
	else
		return("Invalid");

}

void tipoRotaEst(int x, float *stat){
	if(x==0){
		stat[x]++;
		return;
	}else if(x==1){
		stat[x]++;
		return;
	}else if(x==2){
		stat[x]++;
		return;
	}else{
		stat[4]++;
		return;
	}
}

void statistic(int numCaminhos,float* dif,float* tipos){

	int k;

	for(k=0;k<30;k++){
		printf("\nProbability to differ: %f  Difference in Hops:%d \n",dif[k]/numCaminhos,k);
	}

	printf("\nProbabilidade de caminho mais curto < Caminho Comercial: %f\n", (1-(dif[0]/numCaminhos)));
	printf("\nNumero Rotas -> Cliente: %f   Peer: %f    Provider: %f    Invalidas: %f\n",((tipos[0]/numCaminhos)*100),((tipos[1]/numCaminhos)*100),((tipos[2]/numCaminhos)*100),((tipos[3]/numCaminhos)*100));
}

int main(){
	//The following is the maximum 32-bit number that you can have minus the 3 most significant bits
	int *buffmax=(int*)malloc(100000*sizeof(int));
	Counterbuffer=(int*)malloc(100000*sizeof(int));
	
	int nodes;
	int diferenca;
	int opcao;
	float dif[30];
	int i,j,procurado;
	int numCaminhos=0;
	pthread_t thread[2];
	float tipos[4];
	
	int tail;
	int head;
	int link;

	sem_init(&sem,0,1);
	
	FILE* fp;
	fp = fopen("As.txt","r");

	for(i=0;i<30;i++){
		dif[i]=0;
	}

		while(fscanf(fp,"%d %d %d",&tail,&head,&link)!=	EOF){

				if(buffmax[100000-tail]==0){
					buffmax[100000-tail]=tail;
					Counterbuffer[buffcount]= tail;
					buffcount++;					
				}			
		}

		fclose(fp);
		printf("%d\n",buffcount);

		nodes= 100000;
		listadjacent = criagrafo(nodes);
		listadjacent2 = criagrafo(nodes);
		fp = fopen("As.txt","r");

		while(fscanf(fp,"%d %d %d",&tail,&head,&link)!=	EOF){
			addnode(listadjacent,tail,head,link,buffcount);
			addnode(listadjacent2,tail,head,link,buffcount);	
		}
		
		fclose(fp);		

		printf("1 -> para fazer todos para todos, ou entao 2 -> para fazer todos para 1\n");
		scanf("%d",&procurado);

		switch(procurado){

			case 1:
					/************************************************************************COMECA AQUI O CICLO DE TODOS PARA TODOS***********************************/
					for(j=0;j<=buffcount;j++){

						/*Este if e para verificar se ja fez os caminhos de todos para todos*/
						if(j!=buffcount){
							procura=Counterbuffer[j];

							pthread_create(&thread[0],NULL,djishort,NULL);
							pthread_create(&thread[1],NULL,comroute,NULL);
									
						
							for(i=0; i < 2; i++)
							   {
							      pthread_join(thread[i], NULL); 
							   }

						
							for(i=0;i<buffcount;i++){
									
									if((listadjacent->array[100000-Counterbuffer[i]].dist < INT_MAX) && (listadjacent2->array[100000-Counterbuffer[i]].num!=-1) && procura != Counterbuffer[i]){

										diferenca=listadjacent->array[100000-Counterbuffer[i]].dist - listadjacent2->array[100000-Counterbuffer[i]].dist;

										tipoRotaEst(listadjacent->array[100000-Counterbuffer[i]].Pathtype,tipos);
										
										numCaminhos++;

										dif[diferenca]++;
										
									}else if((listadjacent->array[100000-Counterbuffer[i]].dist == INT_MAX))
												tipos[3]++;

										listadjacent->array[100000-Counterbuffer[i]].dist=INT_MAX;
										listadjacent->array[100000-Counterbuffer[i]].extension=0;
										listadjacent->array[100000-Counterbuffer[i]].parent=0;
										listadjacent->array[100000-Counterbuffer[i]].seen=0;
										listadjacent->array[100000-Counterbuffer[i]].previous=0;
										listadjacent->array[100000-Counterbuffer[i]].Pathtype=0;
										

										listadjacent2->array[100000-Counterbuffer[i]].dist=INT_MAX;
										listadjacent2->array[100000-Counterbuffer[i]].extension=0;
										listadjacent2->array[100000-Counterbuffer[i]].parent=0;
										listadjacent2->array[100000-Counterbuffer[i]].seen=0;
										listadjacent2->array[100000-Counterbuffer[i]].previous=0;
										listadjacent2->array[100000-Counterbuffer[i]].Pathtype=0;
								}
								/*Se ja fez de todos para todos, entao fazer agora para o destino escolhido MAS NAO CONTA PARA ESTATISTICAS*/
							}else{
								procura=procurado;
								sem_wait(&sem);
								pthread_create(&thread[0],NULL,djishort,NULL);
								pthread_create(&thread[1],NULL,comroute,NULL);
										
							
								for(i=0; i < 2; i++)
								   {
								      pthread_join(thread[i], NULL); 
								   }
							}
					}

					statistic(numCaminhos,dif,tipos);
					exit(0);
					break;
				case 2:

						printf("qual o nodo a procurar?");
						scanf("%d",&procura);

						pthread_create(&thread[0],NULL,djishort,NULL);
						pthread_create(&thread[1],NULL,comroute,NULL);
								
					
						for(i=0; i < 2; i++)
						   {
						      pthread_join(thread[i], NULL); 
						   }
						   break;
			}

		while(1){
			printf("Digite 1 para ver distancias, 2 para ver estatisticas ou 3 para sair\n");
			scanf("%d",&opcao);

			switch(opcao){
				case 1:
						printf("\ndistancia para que nodo?");
						scanf("%d",&procura);
						printf("ROTA COMERCIAL: nº de Hops:%d - Nodo Prévio: %d - Tipo de rota:%s \n",listadjacent->array[100000-procura].dist,listadjacent->array[100000-procura].parent,tipoRota(listadjacent->array[100000-procura].Pathtype));
						printf("\nCAMINHO MAIS RAPIDO: nº de Hops:%d - Nodo Prévio: %d \n",listadjacent2->array[100000-procura].dist,listadjacent2->array[100000-procura].parent);
						break;
				case 2:
						statistic(numCaminhos,dif,tipos);
						break;
				case 3:
						exit(0);
						break;
			}
		}
}