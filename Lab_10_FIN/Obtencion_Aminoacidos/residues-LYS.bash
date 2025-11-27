# Ejecutar para todos los archivos pdb
bash FILE_A-LYS.bash HEM_A
bash FILE_A-LYS.bash GFP_A
bash FILE_A-LYS.bash ACE2_A


# Guardar todo en 1 csv y mostrar
# HEM
cat HEM_A-Residues-Count.csv > Residues-Count.csv

# GFP
cat GFP_A-Residues-Count.csv >> Residues-Count.csv 

# ACE2
cat ACE2_A-Residues-Count.csv >> Residues-Count.csv 

echo ""
echo "Contenidos de Residues-Count.csv"
cat Residues-Count.csv


# Crea archivo aas;HEM;GFP;ACE2 y lo muestra
{
    echo "ass;HEM;GFP;ACE2"
    awk 'BEGIN { FS=";" } NR==1 { hem=$2 } NR==2 { gfp=$2 } NR==3 { ace2=$2 } END { print "LYS;" hem ";" gfp ";" ace2 }' Residues-Count.csv

} > LYS-per-PDB.csv

echo ""
echo "Contenidos de LYS-per-PDB.csv"
cat LYS-per-PDB.csv

echo ""
echo "Más residuos:"
bash count_residueS.bash HEM_A
echo ""
bash count_residueS.bash GFP_A
echo ""
bash count_residueS.bash ACE2_A

