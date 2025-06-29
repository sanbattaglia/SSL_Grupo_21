# Generador de Palabras para Gramáticas Regulares

## Descripción
Programa en C que valida y genera palabras a partir de gramáticas regulares. Soporta gramáticas regulares izquierdas y derechas.

## Requisitos
- Compilador de C (gcc)

## Compilación
```bash
gcc *.c -Wall -o generador 
```

##Módulos del programa
├── generador.c         # Implementación del generador de palabras
├── productores.c       # Implementación del parser de producciones
├── validacion.c        # Implementación del validador de gramáticas

## Ejecución
./generador "NO_TERMINALES" "TERMINALES" "PRODUCCIONES" "AXIOMA_INICIAL"

- **No terminales**  
  - Símbolos en mayúsculas
  - Para ingresar {S, A, B}  
  - Ejemplo: `"SAB"`

- **Terminales**  
  - Símbolos en minúsculas  
  - Para ingresar {a, b, c}  
  - Ejemplo: `"abc"`

- **Producciones**  
  - Formato: `NoTerminal->alternativa1|alternativa2`  
  - Múltiples producciones separadas por comas  
  - Ejemplo: `"S->aA|b,A->aA|c"`

- **Axioma inicial**  
  - Un único símbolo no terminal  
  - Debe estar incluido en los no terminales  
  - Ejemplo: `"S"`
 
- **Palabra vacía**
  -El programa acepta el ingreso de la palabra vacía representada por el carácter `~`

##Ejemplos de ejecución y Resultado Esperado
  - Ejemplo 1: "S" "ab" "S->a|b" "S"
    Gramática válida
  - Ejemplo 2: "ST" "ab" "S->aT|~,T->b|bT" "S"
    Gramática válida
  - Ejemplo 3: "SAB" "ab" "S->aA|Bb,A->a,B->b" "S"
    Gramática inválida

##Funcionamiento
graph TD
    A[Argumentos CLI] --> B[Productor<br>parsear_productores]
    B --> C[Validación<br>es_gramatica_regular]
    C -->|Válida| D[Generador<br>generar_palabra]
    C -->|Inválida| E[Error]
    D --> F[Salida<br>palabra generada]
