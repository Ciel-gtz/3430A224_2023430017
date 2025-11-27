# Fuente de nombre
source="$1"
outfile_LYS="${source}-LYS.pdb"
outfile_CA="${outfile_LYS}-CA.pdb"
outfile="${source}-Residues-Count.csv"


# Obtener Lys
grep "LYS" ${source}.pdb > "$outfile_LYS"

# Obtner los CA de Lys 
grep "CA" "$outfile_LYS" > "$outfile_CA"

# Cantidad de Lys
lys=$(wc -l "$outfile_CA" | awk 'BEGIN{FS=" "}{print $1}')

# Imprimir y redireccionar a archivo. 
echo "LYS;${lys};VAR2;VAR3;VAR4" > "$outfile" 

