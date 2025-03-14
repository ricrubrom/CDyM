## A)

Investigue sobre los distintos tipos de variables en C y sus modificadores: static, volatile, register, const. ¿Cuáles son los tipos de datos por defecto en el compilador que utilizaremos?

- Los tipos de datos disponibles en c son:

  |      Tipo      | #bits |                         Rango                          |
  | :------------: | :---: | :----------------------------------------------------: |
  |  signed char   |   8   |                      [-128 ; 127]                      |
  | unsigned char  |   8   |                       [0 ; 255]                        |
  |   short int    |  16   |                    [-32768 ; 32767]                    |
  | unsigned short |  16   |                      [0 ; 65535]                       |
  |      int       |  ???  |                 Depende del compilador                 |
  |      long      |  32   |               [-2147483648 ; 2147483647]               |
  | unsigned long  |  32   |                    [0 ; 4294967295]                    |
  |     float      |  32   |  [$1.17549 \cdot 10^{-38}$ ; $3.40282 \cdot 10^{38}$]  |
  |     double     |  64   | [$2.22507 \cdot 10^{-308}$ ; $1.79769 \cdot 10^{308}$] |

- Los modificadores son:

  | Modificador |                                                                 Descripcion                                                                 |
  | :---------: | :-----------------------------------------------------------------------------------------------------------------------------------------: |
  |   Static    | Variable local -> direccion fija en ram \| Variable Global o Funcion -> privada, solo puede utilizarse en el archivo .c donde esta definida |
  |  Volatile   |               Advierte al compilador que la variable puede ser modificada por accion externa y no debe aplicar optimizaciones               |
  |    Const    |        Avisa al compilador que la variable es read only, no se puede modificar. Permite almacenar el dato en ROM, optimizando la RAM        |
  |   Extern    |          Avisa que la variable esta definida en otro archivo .c pero se desea utilizarla en ese archivo, solo a variables globales          |
  |  Register   |                Sugiere al compilador que la variable local sea guardada en algun registro de la CPU para optimizar el acceso                |

- Utilizaremos los datos de tipo signed char o unsigned char si la arquitectura es de 8 bits, en cambio si es de 32 bits utilizaremos long int o unsigned long int.

## B)

Investigue sobre las sentencias del pre-procesador de C, entre ellas: #include, #define, #ifdef y typedef.

- Las sentencias son las siguientes:

  |               Tipo                |                        Definicion                         |
  | :-------------------------------: | :-------------------------------------------------------: |
  |             #include              |                   Incluir otro archivo                    |
  | #ifdef #ifndef #else #elif #endif |                  Compilacion condicional                  |
  |              #define              | Definicion de macros (constantes o funciones) y expansion |
  |          #error #warning          |   Inserta mensaje de error en la salida del compilador    |
  |              typedef              |     Darle un "alias" a un tipo de datos ya existente      |

## C)

¿Qué es una constante de carácter? ¿qué es una cadena de caracteres?

- Una constante de caracter es un unico caracter ASCII, mientras que una cadena de caracteres es un string de texto

## D)

¿Cuál es la diferencia entre una variable local y una global? ¿Por qué utilizaría una u otra?

- Las variables locales:

  - Viven dentro del ambito de la funcion
  - Se alojan en registros CPU o en la stack. Solo funciones en la que son declaradas conocen su ubicacion
  - Al finalizar la funcion se descartan, liberan memoria
  - Permite modularidad y reutilizacion de codigo

- Las variables globales:

  - Pueden ser accedidas desde cualquier parte del programa
  - Declaradas fuera de cualquier funcion
  - Se alojan en direcciones especificas de la RAM
  - Pueden ser accedidas y modificadas por cualquier funcion
  - Se inicializan durante la ejecucion del codigo de startup

- Las variables locales se pueden utilizar cuando sabemos que un dato no debe ser accedido desde otra parte y para dar mas robustes al programa, mientras que las globales se pueden utilizar cuando es un dato que toda funcion debe saber.

## E)

Describa todos los operadores lógicos de C. ¿cúal es la diferencia entre los operadores && y &, || y |? ¿Qué es una máscara de bits?

| Operador |       Definicion       |
| :------: | :--------------------: |
|    &&    |          AND           |
|   \|\|   |           OR           |
|    !     |          NOT           |
|    <     |          LESS          |
|    <=    |     LESS or EQUAL      |
|    >     |        GREATER         |
|    >=    |    GREATER or EQUAL    |
|    !=    |       DIFFERENT        |
|    ==    |         EQUALS         |
|    &     |      BITWISE AND       |
|    \|    |       BITWISE OR       |
|    ^     |      BITWISE XOR       |
|    ~     |      BITWISE NOT       |
|    <<    |       LEFT SHIFT       |
|    >>    |      RIGHT SHIFT       |
|    &=    | BITWISE AND ASSIGNMENT |
|   \|>    | BITWISE OR ASSIGNMENT  |
|    ^=    | BITWISE XOR ASSIGNMENT |
|   <<=    | LEFT SHIFT ASSIGNMENT  |
|   >>=    | RIGHT SHIFT ASSIGNMENT |

## F)

¿Qué es un prototipo de función en C? ¿Cuáles son las alternativas para pasar argumentos a una función? ¿Cómo se retorna un valor desde una función?

- Un prototipo de funcion es la declaracion de la funcion especificando el tipo de dato que devuelve, su nombre asi como cantidad y tipo de parametros, pero no su implementacion.
- Se puede pasar el dato en si o un puntero al dato (se puede modificar el dato dentro de la funcion).
- Se puede retornar utilizando la sentencia `return dato` o pasar a la funcion un puntero a una variable y modificar la direccion a la que apunta dicho puntero

## G)

Repase el concepto de punteros y arreglos. Explique con ejemplos la relación entre ambos.

- Puntero: almacena la direccion en la que se almacena el dato
- Arreglo: almacena una cantidad n de datos

- Se relacionan ya que se pueden realizar arreglos utilizando punteros. Por ej:
  ```
  double *A = (double*)malloc(sizeof(double)*N)
  ...
  printf("%.2f", A[N/2])
  ```
- Aqui se esta declarando un arreglo de doubles de tamaño N, y luego imprimiendo el dato en la posicion N/2, accediendo a este de la misma forma que con un arreglo.

## H)

Investigue sobre los tipos de variables struct y union (estructuras y uniones) en C. De un ejemplo de cada caso.

- Struct: permite agrupar distintos tipos de datos de manera logica, para formar otro tipo de dato, accediendo a cada dato poniendo un punto y el nombre del dato. Almacena todos los datos en ubicaciones distintas de memoria. Por ej:

  ```
  struct persona{
    unsigned int dni;   // 4 bytes
    char Nombre[30];    // 30 bytes -- Una variable de tipo persona ocupa 64 bytes
    char Apellido[30];  // 30 bytes
  }
  ```

- Union: Similar al struct, pero almacena todos los datos en la misma ubicacion en memoria, cuya longitud es igual al dato que mas ocupa de ellas. Por ej:

  ```
  union persona{
    unsigned int dni;   // 4 bytes
    char Nombre[30];    // 30 bytes -- Una variable de tipo persona ocupa 30 bytes
    char Apellido[30];  // 30 bytes
  }
  ```

## I)

¿Qué son los campos de bit de una estructura?

- Sirven para asignar una cantidad especifica de bits a un campo del struct.
