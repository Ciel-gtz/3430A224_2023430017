source="$1"
outfile="${source}_Charges.csv"

# LYS
grep "LYS" ${source}.pdb | grep "CA" > ${source}-LYS-CA.pdb
lys=$(wc -l ${source}-LYS-CA.pdb | awk '{ print $1 }')
echo "LYS;${lys}" > "$outfile"

# ARG
grep "ARG" ${source}.pdb | grep "CA" > ${source}-ARG-CA.pdb
arg=$(wc -l ${source}-ARG-CA.pdb | awk '{ print $1 }')
echo "ARG;${arg}" >> "$outfile"

# HIS
grep "HIS" ${source}.pdb | grep "CA" > ${source}-HIS-CA.pdb
his=$(wc -l ${source}-HIS-CA.pdb | awk '{ print $1 }')
echo "HIS;${his}" >> "$outfile"

# GLU
grep "GLU" ${source}.pdb | grep "CA" > ${source}-GLU-CA.pdb
glu=$(wc -l ${source}-GLU-CA.pdb | awk '{ print $1 }')
echo "GLU;${glu}" >> "$outfile"

# ASP
grep "ASP" ${source}.pdb | grep "CA" > ${source}-ASP-CA.pdb
asp=$(wc -l ${source}-ASP-CA.pdb | awk '{ print $1 }')
echo "ASP;${asp}" >> "$outfile"

echo "Residuos de ${source}.pdb:"
cat "$outfile"
