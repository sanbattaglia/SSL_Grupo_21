#!/bin/bash

EJECUTABLE="generador"

gcc main.c src/*.c -o "$EJECUTABLE"

echo "=== CASOS VÁLIDOS BÁSICOS ==="
./$EJECUTABLE "S" "ab" "S->a|b" "S"
./$EJECUTABLE "SA" "ab" "S->aA,A->b" "S"
./$EJECUTABLE "SA" "ab" "S->Ab,A->a" "S"

echo ""
echo "=== CASOS CON PALABRA VACÍA VÁLIDOS ==="
./$EJECUTABLE "S" "a" "S->a|~" "S"
./$EJECUTABLE "SA" "ab" "S->aA|~,A->b" "S"
./$EJECUTABLE "ST" "ab" "S->aT|~,T->b|bT" "S"

echo ""
echo "=== CASOS VÁLIDOS MÁS COMPLEJOS ==="
./$EJECUTABLE "SABC" "xyz" "S->xA,A->yB,B->zC,C->x|y|z" "S"
./$EJECUTABLE "ST" "ab" "S->aT,T->bS|a|b" "S"
./$EJECUTABLE "SABC" "ab" "S->Ab,A->Ba,B->Cb,C->a" "S"

echo ""
echo "=== CASOS VÁLIDOS RECURSIVOS ==="
./$EJECUTABLE "S" "a" "S->aS|a" "S"
./$EJECUTABLE "SA" "ab" "S->Aa,A->Sa|b" "S"

echo ""
echo "=== CASOS LÍMITE - UN SOLO SÍMBOLO ==="
./$EJECUTABLE "S" "a" "S->a" "S"
./$EJECUTABLE "S" "a" "S->~" "S"

echo ""
echo "=== CASOS INVÁLIDOS - MEZCLA DE LADOS ==="
./$EJECUTABLE "SAB" "ab" "S->aA,A->Bb,B->a" "S"
./$EJECUTABLE "ST" "ab" "S->aT,T->Sa" "S"
./$EJECUTABLE "SAB" "ab" "S->aA|Bb,A->a,B->b" "S"

echo ""
echo "=== CASOS INVÁLIDOS - MÚLTIPLES PALABRAS VACÍAS ==="
./$EJECUTABLE "SA" "a" "S->a|~,A->~" "S"
./$EJECUTABLE "SAB" "ab" "S->~,A->a|~,B->b" "S"

echo ""
echo "=== CASOS INVÁLIDOS - PALABRA VACÍA NO EN AXIOMA INICIAL ==="
./$EJECUTABLE "SA" "a" "S->aA,A->a|~" "S"
./$EJECUTABLE "SAB" "ab" "S->aA,A->bB,B->a|~" "S"

echo ""
echo "=== CASOS INVÁLIDOS - AXIOMA INICIAL CON PALABRA VACÍA EN OTROS RESULTADOS ==="
./$EJECUTABLE "SA" "a" "S->a|~,A->aS" "S"
./$EJECUTABLE "SAB" "ab" "S->a|~,A->bS,B->a" "S"

echo ""
echo "=== CASOS INVÁLIDOS - FORMATO INCORRECTO ==="
./$EJECUTABLE "SA" "ab" "S->abc,A->a" "S"
./$EJECUTABLE "SA" "ab" "S->AA,A->a" "S"
./$EJECUTABLE "S" "ab" "S->12" "S"