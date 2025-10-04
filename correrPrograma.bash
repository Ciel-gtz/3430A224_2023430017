#!/bin/bash

# Exit if something goes wrong
set -e  

INPUT="proteinasEjemplo.pdb"

./actividad_2 "${INPUT%.pdb}.pdb"
