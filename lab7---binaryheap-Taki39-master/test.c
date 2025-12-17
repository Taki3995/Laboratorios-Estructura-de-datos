#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.c"

char * _strdup(const char * str) {
    char * aux = (char *)malloc(strlen(str) + 1);
    strcpy(aux, str);
    return aux;
}

char msg[300];
int test_id = -1;


int success(){
  printf("SUCCESS\n");
  exit(0);
}

void err_msg(char* msg){
    //if(test_id!=-1) return;
    printf("   [FAILED] ");
    printf("%s\n",msg);
    //print_trace();
}

void ok_msg(char* msg){
    //if(test_id!=-1) return;
    printf ("   [OK] ");
    printf("%s\n",msg);
}

void info_msg(char* msg){
    //if(test_id!=-1) return;
    printf ("   [ INFO ] %s\n",msg);
}

int test_suite(int(*test)(), char* msg, int max_score, int id, int req_id){
    if(test_id==-1 || test_id==id){
        printf("\n%s\n", msg);
        int score=test();

        if(id==req_id && score == max_score) success();

        printf("   partial_score: %d/%d\n", score, max_score); 
        
        return score;
    }
    return 0;
}


/*************  TESTS  ******************/
void view_array(Heap* h){
    int i;
    printf("\t[");
    for(i=0; i<h->size; i++){
        printf("%d ",h->heapArray[i].priority);
    }
    printf("]\n");
}

Heap* initialize_heap(){
    info_msg("Inicializando el Heap como en la figura de ejemplo");
    Heap* heap = (Heap*) malloc (sizeof(Heap));
    heap->heapArray = (heapElem*) calloc (7,sizeof(heapElem));
    heap->capac = 7;
    heap->heapArray[0].priority=11;
    heap->heapArray[1].priority=5;
    heap->heapArray[2].priority=8;
    heap->heapArray[3].priority=3;
    heap->heapArray[4].priority=4;
    int i;
    for(i=0;i<4;i++) heap->heapArray[i].data = &heap->heapArray[i].priority;
    heap->size = 5;
    return heap;
}

int test_create(){
    info_msg("Heap* h = createHeap()");

    Heap* h = createHeap();

    if(h==NULL){
        err_msg("h==NULL");
        return 0;
    }

    if(h->size!=0){
        err_msg("h->size!=0");
        return 0;
    }

    if(h->capac!=3){
        err_msg("h->capac!=3");
        return 0;
    }

    info_msg("seteando casillas en priority=0 y data=NULL");
    int i;
    for(i=0; i<3; i++){
        h->heapArray[i].priority=1;
        h->heapArray[i].data=NULL;
    }

    if(h->size!=0 || h->capac!=3){
        err_msg("se borraron datos! mal asignamiento de memoria ");
        return 0;
    }

    ok_msg("createHeap parece implementada correctamente");
    return 10;
}

int test_top(){

    Heap* h= initialize_heap();
    if (heap_top(h) != h->heapArray[0].data){
        err_msg("Deberia retornar dato con prioridad 11");
        return 0;
    }

    info_msg("Seteando mayor elemento en NULL");
    h->heapArray[0].data=NULL;
    if(heap_top(h)!=NULL){
        err_msg("heap_top deberia retornar NULL");
        return 0;
    }

    h= initialize_heap();
    info_msg("seteando size en 0");
    h->size = 0;
    if(heap_top(h)!=NULL){
        err_msg("heap_top deberia retornar NULL");
        return 0;
    }

    ok_msg("obtencion del top correcta");

    return 10;

}

int test_push(){

    Heap* h= initialize_heap();

    info_msg("insertando dato con prioridad 7");
    heap_push(h, strdup("push_data"), 7);

    if(h->heapArray[5].priority!=7){
        err_msg("elemento no queda en la casilla correcta o prioridad no seteada");
        return 0;
    }

    if( strcmp((char*) h->heapArray[5].data, "push_data")!=0 ){
        err_msg("dato insertado no coincide");
        return 0;   
    }

    if( h->size != 6){
        err_msg("no actualiza size");
        return 0; 
    }


    ok_msg("elemento correctamente insertado");

    h= initialize_heap();

    info_msg("insertando dato con prioridad 10");
    heap_push(h, strdup("push_data"), 10);

    if(h->heapArray[2].priority!=10 || h->heapArray[5].priority!=8){
        err_msg("insercion incorrecta");
        view_array(h);
        return 5;
    }
    ok_msg("elemento correctamente insertado");


    h= initialize_heap();
    info_msg("insertando dato con prioridad 15");
    heap_push(h, strdup("push_data"), 15);

    if(h->heapArray[0].priority!=15 || h->heapArray[2].priority!=11 || h->heapArray[5].priority!=8){
        err_msg("insercion incorrecta");
        view_array(h);
        return 10;
    }

    ok_msg("elemento correctamente insertado");

    info_msg("insertando dato con prioridad 2");
    heap_push(h, strdup("push_data"), 2);
    info_msg("insertando dato con prioridad 20");
    heap_push(h, strdup("push_data"), 20);

    if(h->capac != 15){
        err_msg("deberia aumentar el tamanno del arreglo a capac*2+1 (realloc) ");
        return 15;
    }

    ok_msg("se expande el arreglo");

    if(h->heapArray[0].priority!=20 || h->heapArray[1].priority!=15 || h->heapArray[3].priority!=5 || h->heapArray[7].priority!=3){
        err_msg("elemento no fue correctamente insertado");
        view_array(h);
        return 15;
    }

    ok_msg("se inserta correctamente el elemento");


    return 25;


    
}

int test_pop(){

    Heap* h= initialize_heap();

    info_msg("Eliminando un dato");
    heap_pop(h);
    if(h->heapArray[0].priority!=8){
        err_msg("heapArray[0].priority!=8: el dato no fue eliminado correctamente");
        view_array(h);
        return 0;
    }

    if(h->size != 4){
        err_msg("el size no fue actualizado");
        return 0;
    }

    info_msg("Eliminando otro dato");
    heap_pop(h);
    if(h->heapArray[0].priority!=5){
        err_msg("heapArray[0].priority!=5: el dato no fue eliminado correctamente");
        view_array(h);
        return 5;
    }


    info_msg("Eliminando otro dato");
    heap_pop(h);
    if(h->heapArray[0].priority!=4){
        err_msg("heapArray[0].priority!=4: el dato no fue eliminado correctamente");
        view_array(h);
        return 10;
    }

    info_msg("Eliminando otro dato");
    heap_pop(h);
    if(h->heapArray[0].priority!=3){
        err_msg("heapArray[0].priority!=3: el dato no fue eliminado correctamente");
        view_array(h);
        return 15;
    }

    info_msg("Eliminando otro dato");
    heap_pop(h);
    if(h->size!=0){
        err_msg("h->size!=0");
        return 20;
    }

    ok_msg("datos eliminados correctamente");
    return 25;    

}

int main( int argc, char *argv[] ) {
    
    if(argc>1) test_id=atoi(argv[1]);

    int total_score=0;
    total_score+=test_suite(test_create, "Test Create...", 10, 0, test_id);
    total_score+=test_suite(test_top, "Test Top...", 10, 1, test_id);
    total_score+=test_suite(test_push, "Test Push...", 25, 2, test_id);
    total_score+=test_suite(test_pop, "Test Pop...", 25, 3, test_id);

    if(argc==1)
      printf("\ntotal_score: %d/70\n", total_score);

    

    return 0;
}
