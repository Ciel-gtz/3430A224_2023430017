# Grabar en un csv la información que va a mostrarse/crearse
exec > >(tee resumenCSV.csv) 2>&1


# Entrar a la carpeta uniprot y des-ocultar los archivos txt
cd uniprot_info/
mv .ACE2.txt ACE2.txt
mv .GFP.txt GFP.txt

# Mostrar y des-ocultar arhivo .borrar.txt
mv .borrar.txt borrar.txt && rm borrar.txt 

# Mover todo a la carpeta anterior (Lab_10)
mv * .. && cd ..


# Creación de archivos GO
# Archivo HEM
grep "GO;" HEM.txt > GO_HEM.csv 

# Archivo GFP
grep "GO;" GFP.txt > GO_GFP.csv

# Archivo ACE2
grep "GO;" ACE2.txt > GO_ACE2.csv


# Mostrar lineas de los archivos GO
echo "Cantidad de lineas de los archivos:"
wc -l GO*

# Creación e información del archivo GO_proteinas_de_trabajo.csv
cat *.csv > GO_proteinas_de_trabajo.csv
echo ""
echo "  lineas;palabras;caracteres;archivo"
wc -wlc GO_proteinas_de_trabajo.csv

# Borrar el archivo recién creado
rm GO_proteinas_de_trabajo.csv


# Obtención de las últimas columnas de los archivos GO
# Archivo HEM
awk 'BEGIN { FS=";" } { print $NF }' GO_HEM.csv > "FuncionesBiologica_HEM.csv"

# Archivo GFP
awk 'BEGIN { FS=";" } { print $NF }' GO_GFP.csv > "FuncionesBiologica_GFP.csv"

# Archivo ACE2
awk 'BEGIN { FS=";" } { print $NF }' GO_ACE2.csv > "FuncionesBiologica_ACE2.csv"


# Se crea carpeta Obtencion_Aminoacidos con archivos *.pdb
mkdir Obtencion_Aminoacidos && cp *.pdb Obtencion_Aminoacidos

# Mover los archivos bash correspondientes dentro de la carpeta para ejecutarlos
mv *S.bash Obtencion_Aminoacidos

# Guardar residuos de LYS utilizando otro script
cd Obtencion_Aminoacidos
bash residues-LYS.bash


# Finalización del trabajo
echo ""
echo "Trabajo finalizado."
