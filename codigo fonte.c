#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TIMES_TO_RUN 30
#define RUN_SORT(function) \
    for(int i = 0; i < TIMES_TO_RUN; i++){\
        allocate_copy(&sorted, vet);\
        clock_gettime(CLOCK_MONOTONIC, &inicio);\
        function;\
        clock_gettime(CLOCK_MONOTONIC, &fim); \
        time_taken[k] += (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;\
    }\
	k++;\
    


int N = 100;
int *vet, *sorted;


void create_array(int** array);
void allocate_copy(int** destination, int* origin);
void print_array(int array[]);
void move_element(int start, int end, int* array);
void switch_elements(int array[], int i, int j);
void insert_sort(int array[]);
void bubble_sort(int sorted[]);
void quick_sort(int start_index, int last_index, int sorted[]);
void heapify(int array[], int last_node);
void heapify_down(int array[], int node, int last_node);
void heap_sort(int array[]);
void sort_subarrays(int array[], int start, int middle, int end);
void merge_sort(int array[], int start, int end);
void count_sort(int array[]);
void radix_sort(int array[]);
void aux_radix_sort(int array[], int exp);
void bucket_sort(int array[]);
void aux_bucket_sort(int array[], int tamanho);
int find_max_value(int array[], int start, int end);
int selection_sort(int array[]);

int main(){
    struct timespec inicio, fim;
    double time_taken[9] = {0};
    int k = 0;
	char sort[][30] = {
		"bubble", "selection", "insertion", "merge", "quick", "heap", "counting", "radix", "bucket"
	};

    scanf("%i", &N);
    create_array(&vet);
    
 //           RUN_SORT(bubble_sort(sorted));
//	    RUN_SORT(selection_sort(sorted));
  //  	    RUN_SORT(insert_sort(sorted));     
    //        RUN_SORT(merge_sort(sorted, 0, N-1));
            RUN_SORT(quick_sort(0, N-1, sorted));
      //      RUN_SORT(heap_sort(sorted));
        //    RUN_SORT(count_sort(sorted));
          //  RUN_SORT(radix_sort(sorted));
        //    RUN_SORT(bucket_sort(sorted));

      print_array(sorted);

  time_taken[0] /= TIMES_TO_RUN;
    printf("%s Demorou %fms para executar.\n", "quick", time_taken[0]*1e3);

    free(vet);
    free(sorted);
    return 0;
}

void create_array(int** array){
    *array = (int*)malloc(N*sizeof(int));
    
    for(int i = 0; i < N; i++)
        (*array)[i] = rand() % 100001;
        
}

void allocate_copy(int** destination, int* origin){
    free(*destination);
    *destination = (int*)malloc(N*sizeof(int));
    memcpy(*destination, origin, N*sizeof(int));
}

void print_array(int array[]){
        for(int i = 0; i < N; i++)
            printf("%i\n", array[i]);
}

void move_element(int start, int end, int* array){
    int x = array[start];
    if(start > end)
        for(int i = start; i > end; i--) 
            array[i] = array[i-1];
    else
        for(int i = start; i < end; i++)
            array[i] = array[i+1];
    
    array[end] = x;
}

void switch_elements(int array[], int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void insert_sort(int sorted[]) {
    for (int i = 1; i < N; i++)
        for (int j = 0; j < i; j++) 
            if (sorted[i] < sorted[j]){
                move_element(i, j, sorted);
	    	break;
            }
}

void bubble_sort(int sorted[]){
    int x;
    for (int i=0;i<N-1;i++) 
    {
        for (int j=0;j<N-i-1;j++)
        {
            if (sorted[j]>sorted[j+1])
            {
                x=sorted[j];
                sorted[j]=sorted[j+1];
                sorted[j+1]=x;
            }
        }
    }
}

void quick_sort(int start_index, int last_index, int sorted[]) {
    if (start_index >= last_index)
        return;

    int pivot_index = start_index + (last_index - start_index)/2;
    int pivot = sorted[pivot_index];

    int left = start_index, right = last_index;
    while (1) {
        while (sorted[left] < pivot)
            left++;
        while (sorted[right] > pivot)
            right--;

        if (left >= right)
            break;

        switch_elements(sorted, left++, right--);
    }

    quick_sort(start_index, right, sorted); // left
    quick_sort(right+1, last_index, sorted); // right
}

void heapify(int array[], int last_node) {
    int node = (last_node - 1) / 2;
    while (1) {
        if (node < 0)
            break;

        heapify_down(array, node, last_node);
        node--;
    }
}

void heapify_down(int array[], int node, int last_node) {
    while (1) {
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        if (left_child > last_node)
            break;

        int greater = left_child;
        if (right_child <= last_node && array[greater] < array[right_child])
            greater = right_child;

        if (array[node] < array[greater]) {
            switch_elements(array, node, greater);
            node = greater;
        }
        else
            break;
    }
}

void heap_sort(int array[]) {
    int last_node = N - 1;
    heapify(array, last_node);

    while (1) {
        switch_elements(array, 0, last_node);
        last_node--;

        if (last_node == 0)
            break;

        heapify_down(array, 0, last_node);
    }
}

void sort_subarrays(int array[], int start, int middle, int end) {
    if (start == end)
        return;

    int position1 = start;
    int position2 = middle+1;
    int size = end - start + 1;
    int* aux = (int *)malloc(size * sizeof(int));

    if (aux == NULL) {
        printf("erro alocação de memoria");
        return;
    }

    for (int i = 0;i < size; i++) {
        if (position2 > end || (position1 <= middle && array[position1] <= array[position2]))
            aux[i] = array[position1++];
        else
            aux[i] = array[position2++];
    }
    for (int i = 0; i < size; i++)
        array[start + i] = aux[i];

    free(aux);
}

void merge_sort(int array[], int start, int end) {
    int middle = (end + start) / 2;
    if (middle != start){
        merge_sort(array, start, middle);
        merge_sort(array, middle+1, end);
    }

    sort_subarrays(array, start, middle, end);
}

void count_sort(int array[]) {
    int max=array[find_max_value(array, 0, N - 1)];
    int *count =(int *) calloc(max+1, sizeof(int));//alocação com máximo+1 
    if(count == NULL){
        printf("Erro ao alocar memoria");
        return;
    }
    for(int i=0;i<N;i++)
    {
        count[array[i]]++;//percorre v e usa o valor encontrado como índice do vetor count e incrementa-o.
    }
    int c=0;
    for(int i=0;i<=max;i++){
        while(count[i]>0){//se o valor no count for maior que zero.
            array[c]=i;//sobreescreve o valor do vetor v com o valor do índice de count.
            c++;//incrementa o índice após isso.
            count[i]--;//decrementa o valor de count até zerar(caso tenha número repetido gerado).
        }
    }
    free(count);
}

void aux_radix_sort(int array[], int exp){
    int count[10]={0};//vetor aúxiliar inicializado em zero.
    int *output =(int *) calloc(N, sizeof(int));
    if(output == NULL){
        printf("Erro ao alocar memoria");
        return;
    }
    for(int i=0;i<N;i++){
        count[(array[i]/exp)%10]++;//transforma o valor extraido, com base em exp, no índice de count e o incrementa.
    }
    for(int i=1;i<10;i++){
    count[i]+=count[i-1];//pega o valor anterior deste loop, que seria a quantidade de numeros separados no loop anterior, e soma com o atual deste loop.
}
    for(int i=N-1;i>=0;i--){//loop inverso.
        int digito=(array[i]/exp)%10;//pega o vetor original e separa o digito com base no em exp e atribui a variável digito.
        output[count[digito]-1]=array[i];//atribui os valores orignais de v em output: um loop inverso que verifica em count(com base no vetor digito)-1 qual sera o índice dos valores.
        count[digito]--;//subtraí do acumulador com base no índice do loop.
    }
    for(int i=0;i<N;i++){
        array[i]=output[i];//atribui os valores de output ao vetor original.
    }
    free(output);
}

void radix_sort(int array[]){
    int max = array[find_max_value(array, 0, N - 1)];
    for (int exp=1;max/exp>0;exp*=10){//loop que define exp com base no valor máximo. 
        aux_radix_sort(array, exp);//chama a auxiliar
    }
}

void bucket_sort(int array[]){
    int max = array[find_max_value(array, 0, N - 1)], num_baldes = 10;
    int *qtd =(int *) calloc(num_baldes, sizeof(int));//vetor auxuliar para contar quantos itens caem em cada balde
    if(qtd == NULL){
        printf("Erro ao alocar memoria");
        return;
    }
    int **baldes =(int **) calloc(num_baldes, sizeof(int*));//cria os ponteiros para cada balde(linha).
    for(int i=0;i<num_baldes;i++){
        baldes[i]= (int *) calloc(N, sizeof(int));//cria o espaço de cada balde(coluna).
    }
    for(int i=0;i<N;i++){
        int indice=((long long)array[i]*(num_baldes-1))/max;//calcula proporcionalmente em qual balde o valor vai cair
        baldes[indice][qtd[indice]]=array[i];//guarda o valor dentro do balde escolhido, na próxima posição livre
        qtd[indice]++;
    }
    for(int i=0;i<num_baldes;i++){
        if(qtd[i]>1){
        aux_bucket_sort(baldes[i], qtd[i]);//ordena individualmente os elementos que caíram dentro deste balde
    }
}    

    int c=0;
    for(int i=0;i<num_baldes;i++){
        for(int j=0;j< qtd[i]; j++){//passa por todos os itens guardados dentro daquele balde
            array[c]=baldes[i][j];//devolve o elemento ordenado de volta para o vetor original
            c++;
        }
        
    }
    
    for (int i=0;i<num_baldes;i++){
      free(baldes[i]);
      }
      free(baldes);
      free(qtd);
}

void aux_bucket_sort(int array[], int tamanho){
    for(int i=1;i<tamanho;i++)
        for(int j=0;j<i;j++)
            if(array[i]<array[j])
                move_element(i, j, array);
}

int find_max_value(int array[], int start, int end) {
    int max = 0;

    for (int i = start + 1; i <= end; i++)
        if (array[i] > array[max])
            max = i;

    return max;
}

int selection_sort(int array[]) {
    for (int i = N-1; i >= 0; i--) {
        int max = find_max_value(array, 0, i);

        switch_elements(array, i, max);
    }

    return 0;
}
