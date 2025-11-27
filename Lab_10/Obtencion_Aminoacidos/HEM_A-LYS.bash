
# Fuente de nombre
source="HEM_A"

# Obtener Lys
grep "LYS" ${source}.pdb > HEM_A-LYS.pdb

# Obtner los CA de Lys 
grep "CA" HEM_A-LYS.pdb > HEM_A-LYS-CA.pdb

# Cantidad de Lys
hem_lys=$(wc -l HEM_A-LYS-CA.pdb | awk 'BEGIN{FS=" "}{print $1}')

# Imprimir y redireccionar a archivo. 
echo "LYS;${hem_lys};VAR2;VAR3;VAR4" > HEM_A-Residues-Count.csv 

