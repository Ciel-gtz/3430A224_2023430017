# Correr todos los archivos bash
# HEM
bash HEM_A-LYS.bash

# GFP
bash GFP_A-LYS.bash

# ACE2
bash ACE2_A-LYS.bash


# Guardar todo en 1 csv
# HEM
cat HEM_A-Residues-Count.csv > Residues-Count.csv

# GFP
cat GFP_A-Residues-Count.csv >> Residues-Count.csv 

# ACE2
cat ACE2_A-Residues-Count.csv >> Residues-Count.csv 

# Mostrar
cat Residues-Count.csv
