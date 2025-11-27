# Plan de Commits para el Proyecto MICRO

Aquí tienes una propuesta para dividir el trabajo en 6 commits lógicos, ordenados desde la base hasta el producto final.

## Commit 1: Pruebas y Validación
Agrega archivos de prueba para verificar el funcionamiento del intérprete.
*   **Archivos:**
    *   `prueba.micro`
*   **Mensaje sugerido:** "Caso de prueba micro" 

## Commit 2: Módulo de Tabla de Símbolos
Implementa la gestión de memoria y almacenamiento de variables y constantes.
*   **Archivos:**
    *   `tabla/tabla_simbolos.h`
    *   `tabla/tabla_simbolos.c`
*   **Mensaje sugerido:** "Implementar tabla de símbolos con listas enlazadas"

## Commit 3: Analizador Léxico (Scanner)
Agrega la capacidad de reconocer tokens, palabras clave y literales.
*   **Archivos:**
    *   `parser/scanner.l`
*   **Mensaje sugerido:** "Agregar analizador léxico (Flex) para reconocimiento de tokens"

## Commit 4: Analizador Sintáctico (Parser)
Implementa la gramática, reglas semánticas y la lógica de ejecución (operaciones matemáticas, asignaciones).
*   **Archivos:**
    *   `parser/parser.y`
*   **Mensaje sugerido:** "Implementar parser (Bison) y lógica de ejecución"

## Commit 5: Driver Principal
Integra todos los módulos y provee la interfaz de usuario para seleccionar el modo de entrada.
*   **Archivos:**
    *   `main.c`
*   **Mensaje sugerido:** "Agregar main driver y selección de entrada (Archivo/Consola)"

## Commit 6: Infraestructura y Definiciones Base
Establece los cimientos del proyecto con los tipos de datos comunes y el sistema de construcción.
*   **Archivos:**
    *   `include/defs.h`
    *   `Makefile`
*   **Mensaje sugerido:** "Defs y Makefile"
