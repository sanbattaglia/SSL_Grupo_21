# Generador de Palabras para Gramáticas Regulares

## Descripción
Programa en C que valida y genera palabras a partir de gramáticas regulares. Soporta gramáticas regulares izquierdas y derechas.
Su función principal es:

- Validar que una gramática ingresada cumpla con los requisitos de gramática regular:
  - Todas las producciones son consistentes (todas izquierdas O todas derechas)
  - Formato correcto de producciones (A→a, A→aB, o A→Ba)
  - Símbolos bien definidos (terminales vs. no terminales)

- Generar palabras mediante derivaciones aleatorias:
  - Comienza desde el axioma inicial
  - Sustituye no terminales usando producciones seleccionadas aleatoriamente
  - Continúa hasta obtener una palabra compuesta solo por terminales
 
- Soporta ambos tipos de gramáticas regulares:
  - Derechas: Sustitución no terminal → terminal + no_terminal (A→aB)
  - Izquierdas: Sustitución no terminal → no_terminal + terminal (A→Ba)

## Requisitos
- gcc (última versión estable)

## Compilación
```bash
gcc main.c src/*.c -Wall -o generador 
```

## Módulos del programa
- generador.c -- Implementación del generador de palabras
- productores.c -- Implementación del parser de producciones
- validacion.c -- Implementación del validador de gramáticas

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
  - Nota: tener en cuenta que si una producción tiene varios resultados, deben estar ingresados con notación de |, no como dos instancias separadas.

- **Axioma inicial**  
  - Un único símbolo no terminal  
  - Debe estar incluido en los no terminales  
  - Ejemplo: `"S"`
 
- **Palabra vacía**
  -El programa acepta el ingreso de la palabra vacía representada por el carácter `~`

## Ejemplos de ejecución y Resultado Esperado
  - Ejemplo 1: "S" "ab" "S->a|b" "S"
    Gramática válida
  - Ejemplo 2: "ST" "ab" "S->aT|~,T->b|bT" "S"
    Gramática válida
  - Ejemplo 3: "SAB" "ab" "S->aA|Bb,A->a,B->b" "S"
    Gramática inválida
