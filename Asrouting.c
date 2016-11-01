#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int CRP[3][4]={{0,-1,-1,-1},{1,-1,-1,-1},{2,2,2,-1}};


int nodes;
struct node{
	int id;
	int Linktype;
	struct node* next;
};

struct lista{
	int num;
	struct node* pointer;
};

struct grafo{
	struct lista* array;
};



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



void addnode(struct grafo*ref,int tail,int head,int linktype){
	int i;
	struct node* temp;
	struct node* Toinsert;
	struct node* aux;
	//i = (*ref)->array[0].num;
	//prova de existência da tail
	for(i=0;i<nodes;i++){

		if(ref->array[i].num == tail){
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
	}
}



void heapify(int array[][2], int n);
void adjust(int array[][2], int n);
 

  void heapsort(int array[][2], int n)
{
 int i;
 int t;
 int simbol;
 
 heapify(array,n);
 
 for(i=n-1 ; i>0 ; i--)
 {

  simbol = array[0][0];
  array[0][0] = array[i][0];
  array[i][0] = simbol;
  	
  t = array[0][1];
  array[0][1] = array[i][1];
  array[i][1] = t;
  
  adjust(array,i);
 }
}
 
 
void heapify(int array[][2], int n)
{
 int item;
 int simbol;
 int i,j,k;
 
     for(k=1 ; k<n ; k++)
     {
      item = array[k][1];
      simbol = array[k][0];
      i = k;
      j = (i-1)/2;
     
      while( (i>0) && (item>array[j][1]) )
      {
       array[i][1] = array[j][1];
       array[i][0] = array[j][0];
       i = j;
       j = (i-1)/2;
      }
      array[i][1] = item;
      array[i][0] = simbol;
     }
}
 
void adjust(int array[][2], int n)
{
       int item;
       int simbol;
       int i,j;
       
       j = 0;
       item = array[j][1];
       simbol = array[j][0];
       i = 2*j+1;
       
            while(i<=n-1)
           {
            if(i+1 <= n-1)
             if(array[i][1] < array[i+1][1])
              i++;
            if(item < array[i][1])
            {
             array[j][1] = array[i][1];
             array[j][0] = array[i][0];
             j = i;
             i = 2*j+1;
            }
            else
             break;
           }
       array[j][1] = item;
       array[j][0] = simbol;
}




void removeNodeHeap2(int array[][2],int Toremove,int length){
  int i;
  

  for(i=0;i<length;i++){
    if(array[i][0]==Toremove){
      array[i][0] = -1;
      array[i][1] = -1;
      heapsort(array,length);
      
      
      break;
    }

  }

}


int hopglobal = INT_MAX;
int* bestpath;

void pathfinder(struct grafo*ref,int origem,int destino,int path[],int hop,int extension){

int i=0;
int k;
struct node* aux;
struct node* aux2;
struct node* aux3;
struct node* endereco;
struct node *Q = NULL;
struct node *temp;
int saltaCiclo=0;
int min = INT_MAX;
int atribute;
int min_node;
int countQ=0;
int counter1=0;

			while(ref->array[i].num!=origem){
					i++;
				}

			aux = ref->array[i].pointer;

			while(aux != NULL){
					countQ++;
					aux = aux->next;
				}

			int heap[countQ][2];

			aux = ref->array[i].pointer;
			i = 0;
			
			while(aux != NULL){
					heap[i][0] = aux->id;
					heap[i][1] = aux->Linktype;
					i++;
					aux = aux->next;
			}

			heapsort(heap,countQ);
			
			

			while(counter1!=countQ){
				
				for(i=0;i<countQ;i++){
					if(heap[i][0]>-1){
						atribute = heap[i][1]-1;
						min_node = heap[i][0];
						break;
					}

				}

				for(k=0;k<hop;k++){
					if(path[k] == min_node){
						saltaCiclo=1;
					}
				}

				if(min_node == destino){
					path[hop]=origem;
					hop++;
					path[hop]=destino;
					if(hop<hopglobal){
						free(bestpath);
						bestpath = (int*)malloc(hop*sizeof(int));
						for(i=0;i<=hop;i++)
							bestpath[i]=path[i];
					}
					bestpath[hop+1]='\0';
					return;
				}

				

				if(min_node != origem && saltaCiclo == 0){
					if(hop == 0){
								extension = atribute;
								if(CRP[extension][0]>-1){
									path[hop]=origem;
									hop++;
									pathfinder(ref,min_node,destino,path,hop,atribute);
									hop--;
								}

					 }else{
							if(CRP[extension][atribute]>-1){
									path[hop]=origem;
									hop++;
									pathfinder(ref,min_node,destino,path,hop,atribute);
									hop--;
								}
							}
				}
				removeNodeHeap2(heap,min_node,countQ);

				counter1++;
				saltaCiclo = 0;

			}


}



int main(){


/*
	CRP[0][0] = 0;
	CRP[0][1] = -1;
	CRP[0][2] = -1; 
	CRP[0][3] = -1; 
	CRP[1][0] = 1;
	CRP[1][1] =-1; 
	CRP[1][2] =-1;
	CRP[1][3] =-1;
	CRP[2][0] = 2;
	CRP[2][1] = 2;
	CRP[2][2] = 2;
	CRP[2][3] =-1;
*/




	struct grafo* listadjacent;
	nodes= 350;
	listadjacent = criagrafo(nodes);

	FILE* fp;
	fp = fopen("As.txt","r");
	int tail,j,i;
	int head;
	int link;
	int edgecount=0;

	while(fscanf(fp,"%d %d %d",&tail,&head,&link)!=	EOF){
		addnode(listadjacent,tail,head,link);
		edgecount++;	
	}

	//addnode(listadjacent,2,1,2);
	int path[5];
	i=0;
	while(i<(edgecount/2 -1)){

		pathfinder(listadjacent,listadjacent->array[i].num,9,path,0,-1);

		printf("Melhor caminho de %d para 9",listadjacent->array[i].num);
		j=0;
		while(bestpath[j]!='\0'){
			printf("%d",bestpath[j]);
		}

	}
	fclose(fp);
}