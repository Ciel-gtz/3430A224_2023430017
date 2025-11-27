
# Fuente de nombre
source="GFP_A"

# Obtener Lys
grep "LYS" ${source}.pdb > GFP_A-LYS.pdb

# Obtner los CA de Lys 
grep "CA" GFP_A-LYS.pdb > GFP_A-LYS-CA.pdb

# Cantidad de Lys
gfp_lys=$(wc -l GFP_A-LYS-CA.pdb | awk 'BEGIN{FS=" "}{print $1}')

# Imprimir y redireccionar a archivo. 
echo "LYS;${gfp_lys};VAR2;VAR3;VAR4" > GFP_A-Residues-Count.csv 

