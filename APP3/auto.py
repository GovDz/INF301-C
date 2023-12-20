import subprocess

def executer_tests(acte_numero, nom_fichier_sortie):
    commande = f"make tests_acte{acte_numero}"
    resultat = subprocess.run(commande, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    
    # Enregistrement des résultats dans le fichier de sortie commun
    with open(nom_fichier_sortie, 'a') as fichier_sortie:
        fichier_sortie.write(f"=== Acte {acte_numero} ===\n")
        fichier_sortie.write(resultat.stdout)
        fichier_sortie.write(resultat.stderr)
        fichier_sortie.write("\n\n")

def principal():
    # Obtenir le nom du fichier de sortie commun de l'utilisateur
    nom_fichier_sortie = input("Entrez le nom du fichier de sortie commun pour tous les tests : ")
    
    for x in range(1, 5):
        executer_tests(x, nom_fichier_sortie)

if __name__ == "__main__":
    principal()
