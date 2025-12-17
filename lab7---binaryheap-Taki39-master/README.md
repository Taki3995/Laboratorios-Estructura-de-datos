
Implementando un Montículo Binario (Heap)
=====

---
**ANTES DE COMENZAR**

* Abra su cuenta en repl.it
* En el home de repl.it busque el lab y clónelo para comenzar a trabajar
* Seleccione el lenguaje (C) y escriba el comando para el botón run: `bash test.sh`
* Sólo puede modificar los archivos *heap.c* y *main.c*
* Para testear sus códigos basta con que apriete el botón **Run**
* Actualice seguido sus cambios, debe ingresar su contraseña de github y [token](https://drive.google.com/file/d/1s3PyI_HCn0HAx5dm7h0jRiC-G9Cq2p-g/view?usp=sharing)
* No está permitido usar comandos de git (a menos que el profesor lo indique)

---


En este laboratorio implementaremos una **cola con prioridad**. Para ello usaremos la siguiente estructura (montículo binario o heap):

````c
typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;
````

![image](https://i.ibb.co/VM5CM3H/image.png)

Como se pueden dar cuenta, el montículo no es más que un arreglo de datos de tipo `heapElem`. Cada dato almacena el dato (`void*`) y un valor o *prioridad* (`int`).

Ejercicios
----

1. Implemente la función `Heap* createHeap()`. Esta función crea un nuevo dato de tipo Heap inicializando sus variables. Considere que la capacidad incial es de 3 casillas para el arreglo.
   > Recuerde reservar memoria para el Heap y también para el arreglo `heapArray`.

2. Implemente la función `void* heap_top(Heap* pq)`. Esta función retorna el dato con mayor prioridad del montículo. 
    > Recuerde que este dato se encuentra en la raíz el montículo, es decir, en la primera casilla del arreglo.

3. Implemente la función `void heap_push(Heap* pq, void* data, int p)`. Esta función inserta un nuevo dato con prioridad `p` en el montículo. Si no recuerda como insertar datos en el montículo puede ver las [diapositivas](https://docs.google.com/presentation/d/1ZjXWMf6g05WdICqvno_oyRvorjAThABgbRGbEqc7mYU/edit#slide=id.g55ac49ed61_0_167).

    > Si el arreglo está lleno aumente la capacidad al **doble + 1** usando la función `realloc` así:
    > `arreglo = realloc(arreglo, nueva_capacidad)`

4. Implemente la función `void heap_pop(Heap* pq)`. Esta función elimina el mayor elemento del montículo (la raíz). Si no recuerda el procedimiento puede ver las [diapositivas](https://docs.google.com/presentation/d/1ZjXWMf6g05WdICqvno_oyRvorjAThABgbRGbEqc7mYU/edit#slide=id.g10c6e3d52b_0_98).

Ya tiene implementado su montículo.
Para probarlo puede usar el siguiente código de ejemplo en `main.c`:
````c
Heap* heap = createHeap();

int i;
char j[3];
printf("Se ingresan elementos a la cola con prioridad\n");
for(i=0;i<10;i++){
    int p=rand()%100;
    itoa(p,j,10); //se convierte el número en string j
    heap_push(heap,strdup(j),p);  //se guarda el string con prioridad p
    printf("%s,",j);
}
printf("\n");

printf("Se extraen elementos ordenados de la cola con prioridad\n");
while(heap_top(heap)){
    printf("%s,",(char*) heap_top(heap));
    heap_pop(heap);
}
printf("\n");
````

Luego para compilar y ejecutar:

    gcc main.c heap.c -o main
    ./main 

Y listo!
