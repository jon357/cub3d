
dossier_images="catjam"
extension_source="png"

for fichier in "$dossier_images"/*."$extension_source"; do
    if [ -f "$fichier" ]; then
        nom_fichier=$(basename "$fichier")
        nom_sans_extension="${nom_fichier%.*}"
        convert "$fichier" "$dossier_images/$nom_sans_extension.xpm"
        echo "Conversion de $nom_fichier terminée."
    fi
done
