
# Fuente de nombre
source="ACE2_A"

# Obtener Lys
grep "LYS" ${source}.pdb > ACE2_A-LYS.pdb

# Obtner los CA de Lys 
grep "CA" ACE2_A-LYS.pdb > ACE2_A-LYS-CA.pdb

# Cantidad de Lys
ace2_lys=$(wc -l ACE2_A-LYS-CA.pdb | awk 'BEGIN{FS=" "}{print $1}')

# Imprimir y redireccionar a archivo. 
echo "LYS;${ace2_lys};VAR2;VAR3;VAR4" > ACE2_A-Residues-Count.csv 

