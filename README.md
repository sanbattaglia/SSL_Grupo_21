# Generador de Palabras para Gramáticas Regulares

## Descripción
Programa en C que valida y genera palabras a partir de gramáticas regulares. Soporta gramáticas regulares izquierdas y derechas.

## Requisitos
- Compilador de C (gcc)

## Compilación
```bash
gcc *.c -Wall -o generador 
```

## Ejecución
./generador "NO_TERMINALES" "TERMINALES" "PRODUCCIONES" "AXIOMA_INICIAL"

- **No terminales**  
  - Símbolos en mayúsculas  
  - Separados por comas  
  - Ejemplo: `"S,A,B"`

- **Terminales**  
  - Símbolos en minúsculas  
  - Separados por comas  
  - Ejemplo: `"a,b,c"`

- **Producciones**  
  - Formato: `NoTerminal->alternativa1|alternativa2`  
  - Múltiples producciones separadas por comas  
  - Ejemplo: `"S->aA|b,A->aA|c"`

- **Axioma inicial**  
  - Un único símbolo no terminal  
  - Debe estar incluido en los no terminales  
  - Ejemplo: `"S"`
