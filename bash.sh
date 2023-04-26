#!/bin/bash

# Lê da entrada padrão
read input

# Verifica se o valor lido é igual a 0
if [ $input -eq 0 ]
then
    echo "ok"
else
    echo "outra coisa"
fi
