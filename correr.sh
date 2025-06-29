#!/bin/bash

EJECUTABLE="generador"

gcc main.c src/*.c -o "$EJECUTABLE"

echo "PROBANDO GRAMATICA POR DER"
./$EJECUTABLE "PQT" "abe" "P->aQ,Q->bT,T->e|eT|bP" "T"

echo "PROBANDO GRAMATICA POR IZQ"
./$EJECUTABLE "PQT" "xyz" "P->Qx,Q->Ty,T->z|Tz|Py" "T"
