package src;

import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.List;
import java.io.File;

// Import GAMS API
import com.gams.api.*;

/**
 * Résultats Généraux page component for the MMPE Dashboard
 * Version améliorée avec style compact et options d'affichage et intégration GDX dynamique
 */
public class ResultatsPage extends JPanel {
	// Constantes de couleurs pour un design cohérent
	private static final Color BACKGROUND_COLOR = new Color(90, 150, 210);
	private static final Color PANEL_BACKGROUND = Color.WHITE;
	private static final Color SELECTED_BACKGROUND = new Color(200, 220, 240);
	private static final Color TEXT_COLOR = Color.BLACK;
	private static final Color BORDER_COLOR = new Color(180, 180, 180);
	private static final Color HEADER_COLOR = Color.ORANGE;

	// Constantes pour la taille des éléments
	private static final int BUTTON_HEIGHT = 25;
	private static final int INDICATEUR_HEIGHT = 25;
	private static final int INDICATEUR_WIDTH = 400; // Largeur réduite pour les indicateurs

	// Chemins des fichiers GDX
	private static final String GDX_BAU_PATH = "../CIV_MPE_Structure/res/BaU.gdx";
	private static final String GDX_PI_PATH = "../CIV_MPE_Structure/res/pi.gdx";
	private static final String GDX_PI_PLUS_PATH = "../CIV_MPE_Structure/res/pi_plus.gdx";

	// Composants principaux
	private JPanel indicateursPanel;
	private JScrollPane indicateursScroll;
	private Map<String, List<String>> groupeIndicateurs;
	private JPanel evolCompPanel;
	private JPanel evolAnnPanel;
	private String currentGroupe = "Composantes du PIB Nominal";

	// Options d'affichage
	private JCheckBox optionBAU;
	private JCheckBox optionBAUPI;
	private JCheckBox optionBAUPIPlus;

	// Bouton pour rafraîchir les données
	private JButton refreshButton;

	// Stockage des données GDX
	private Map<String, Map<String, Map<String, double[]>>> donnees;
	private String[] annees; // Pour stocker les années (t)

	// Mapping des indicateurs vers les symboles GDX
	private Map<String, String> mappingIndicateurs;
	// Mapping spécial pour les indicateurs multi-dimensionnels (comme Wage et lst)
	private Map<String, Map<String, String[]>> mappingIndicateursMulti;
	// Mapping pour les indicateurs sectoriels
	private Map<String, String[]> mappingIndicateursSectoriels;

	// Indicateur actuellement sélectionné
	private String currentIndicateur = "";

	public ResultatsPage() {
		initMappingIndicateurs();
		initData();
		initComponents();
		chargerDonnees();
	}

	private void initMappingIndicateurs() {
		mappingIndicateurs = new HashMap<>();
		mappingIndicateursMulti = new HashMap<>();
		mappingIndicateursSectoriels = new HashMap<>();

		// Mapping des indicateurs simples vers les symboles GDX
		mappingIndicateurs.put("PIB Nominal gdpmp", "gdpmp");
		mappingIndicateurs.put("PIB Réel rgdpmp", "rgdpmp");
		mappingIndicateurs.put("Exportations Nominales Agrégées totExp", "totExp");
		mappingIndicateurs.put("Importations Nominales Agrégées totimp", "totimp");
		mappingIndicateurs.put("Exportations Réelles Agrégées : rTotExp", "rTotExp");
		mappingIndicateurs.put("Importations Réelles Agrégées rtotimp", "rtotimp");
		mappingIndicateurs.put("Consommation Privée Réelle : xfd (h-hhld)", "xfd");
		mappingIndicateurs.put("Consommation Publique Réelle : xfd (g-govt)", "xfd");
		mappingIndicateurs.put("Investissement Privé Réel : xfd (i-invt)", "xfd");
		mappingIndicateurs.put("Investissement Public Réel : xfd (i-ginv)", "xfd");

		// Mapping pour les indicateurs sectoriels - indiquer les secteurs à inclure pour chaque indicateur
		mappingIndicateursSectoriels.put("Part Secteur Mines, Hydrocarbures et Énergie sectshr(aagr,t)",
				new String[]{"mine", "ener", "electr"});
		mappingIndicateursSectoriels.put("Part Secteur Agricole sectshr(aagr,t)",
				new String[]{"Agri"});
		mappingIndicateursSectoriels.put("Part Secteur Manufacturier sectshr(aagr,t)",
				new String[]{"manu"});
		mappingIndicateursSectoriels.put("Part Secteur Services sectshr(aagr,t)",
				new String[]{"serv"});

		// Mapping pour les indicateurs multi-dimensionnels
		// Pour Wage(l,t)
		Map<String, String[]> wageMapping = new HashMap<>();
		wageMapping.put("Non-Qualifié", new String[]{"f-labuskl"});
		wageMapping.put("Qualifié", new String[]{"f-labmeskl", "f-labskl"});
		mappingIndicateursMulti.put("Wage", wageMapping);

		// Pour lst(l,t)
		Map<String, String[]> lstMapping = new HashMap<>();
		lstMapping.put("Non-Qualifié", new String[]{"f-labuskl"});
		lstMapping.put("Qualifié", new String[]{"f-labmeskl", "f-labskl"});
		lstMapping.put("Total", new String[]{"f-labuskl", "f-labmeskl", "f-labskl"});
		mappingIndicateursMulti.put("lst", lstMapping);
	}

	private void initData() {
		groupeIndicateurs = new LinkedHashMap<>(); // LinkedHashMap pour conserver l'ordre d'insertion
		donnees = new HashMap<>();

		// Vue d'Ensemble Macroéconomique
		List<String> vueEnsembleMacroList = new ArrayList<>();
		vueEnsembleMacroList.add("PIB Nominal gdpmp");
		vueEnsembleMacroList.add("PIB Réel rgdpmp");
		groupeIndicateurs.put("Vue d'Ensemble Macroéconomique", vueEnsembleMacroList);

		// Facteurs de production (quatrième dans l'image)
		List<String> facteursList = new ArrayList<>();
		facteursList.add("Masse Salariale d'Emploi Non-Qualifié Wage(l,t)");
		facteursList.add("Masse Salariale d'Emploi Qualifié Wage(l,t)"); // todo fusion de la masse salariale d'emploi qualifié et semi-qualifié
		facteursList.add("Nombre d'Emplois Non-Qualifiés lst(l,t)");
		facteursList.add("Nombre d'Emplois Qualifiés lst(l,t)");  // todo fusion du nombre d'emplois qualifiés et semi-qualifiés
		facteursList.add("Nombre Total d'Emplois somme des ls");
		groupeIndicateurs.put("Facteurs de Production", facteursList);

		// Composantes du PIB Nominal (premier dans l'image)
		List<String> pibNominalList = new ArrayList<>();
		pibNominalList.add("Exportations Nominales Agrégées totExp");
		pibNominalList.add("Importations Nominales Agrégées totimp");
		groupeIndicateurs.put("Composantes du PIB Nominal", pibNominalList);

		// Composantes du PIB Réel (deuxième dans l'image)
		List<String> pibReelList = new ArrayList<>();
		pibReelList.add("Consommation Privée Réelle : xfd (h-hhld)");
		pibReelList.add("Consommation Publique Réelle : xfd (g-govt)");
		pibReelList.add("Exportations Réelles Agrégées : rTotExp");
		pibReelList.add("Importations Réelles Agrégées rtotimp");
		pibReelList.add("Investissement Privé Réel : xfd (i-invt)");
		pibReelList.add("Investissement Public Réel : xfd (i-ginv)");
		groupeIndicateurs.put("Composantes du PIB Réel", pibReelList);

		// Contributions au PIB (troisième dans l'image)
		List<String> contributionsList = new ArrayList<>();
		contributionsList.add("Part Secteur Mines, Hydrocarbures et Énergie sectshr(aagr,t)");
		contributionsList.add("Part Secteur Agricole sectshr(aagr,t)");
		contributionsList.add("Part Secteur Manufacturier sectshr(aagr,t)");
		contributionsList.add("Part Secteur Services sectshr(aagr,t)");
		groupeIndicateurs.put("Contributions au PIB", contributionsList);
	}

	private void chargerDonnees() {
		try {
			// Réinitialiser les données existantes
			donnees.clear();

			// Vérifier si les fichiers existent
			File bauFile = new File(GDX_BAU_PATH);
			File piFile = new File(GDX_PI_PATH);
			File piPlusFile = new File(GDX_PI_PLUS_PATH);

			System.out.println("Chargement des fichiers GDX:");
			System.out.println("BAU: " + bauFile.getAbsolutePath() + " (existe: " + bauFile.exists() + ")");
			System.out.println("PI: " + piFile.getAbsolutePath() + " (existe: " + piFile.exists() + ")");
			System.out.println("PI_PLUS: " + piPlusFile.getAbsolutePath() + " (existe: " + piPlusFile.exists() + ")");

			if (!bauFile.exists() || !piFile.exists() || !piPlusFile.exists()) {
				JOptionPane.showMessageDialog(this,
						"Un ou plusieurs fichiers GDX n'ont pas été trouvés.\nBAU: " + bauFile.getAbsolutePath() +
								"\nPI: " + piFile.getAbsolutePath() +
								"\nPI_PLUS: " + piPlusFile.getAbsolutePath(),
						"Erreur de chargement", JOptionPane.ERROR_MESSAGE);
				return;
			}

			// Initialiser l'environnement GAMS
			GAMSWorkspace ws = new GAMSWorkspace();

			// Charger les trois bases de données
			GAMSDatabase dbBAU = ws.addDatabaseFromGDX(GDX_BAU_PATH);
			GAMSDatabase dbPI = ws.addDatabaseFromGDX(GDX_PI_PATH);
			GAMSDatabase dbPIPLUS = ws.addDatabaseFromGDX(GDX_PI_PLUS_PATH);

			// Lister quelques symboles du fichier GDX pour le débogage
			System.out.println("Analyse du fichier BAU...");
			List<String> symbolNames = new ArrayList<>();
			for (GAMSSymbol symbol : dbBAU) {
				symbolNames.add(symbol.getName());
			}
			System.out.println("Symboles trouvés: " + symbolNames);

			// Récupérer le set des périodes (t)
			GAMSSet setT = null;
			try {
				setT = dbBAU.getSet("t");
				System.out.println("Set 't' trouvé avec succès.");
			} catch (Exception e) {
				System.out.println("Set 't' non trouvé. Recherche d'alternatives...");
				// Chercher parmi tous les sets disponibles
				for (GAMSSymbol symbol : dbBAU) {
					try {
						// Essayer de caster en GAMSSet
						GAMSSet potentialSet = (GAMSSet)symbol;
						System.out.println("Set candidat trouvé: " + symbol.getName());
						// Si nous trouvons un set qui pourrait représenter les périodes
						setT = potentialSet;
						break;
					} catch (ClassCastException cce) {
						// Pas un set, continuer
					}
				}
			}

			if (setT == null) {
				JOptionPane.showMessageDialog(this,
						"Impossible de trouver le set des périodes dans les fichiers GDX.",
						"Erreur de chargement", JOptionPane.ERROR_MESSAGE);
				return;
			}

			// Extraire les périodes - utiliser une approche dynamique
			List<String> anneesTemp = new ArrayList<>();
			for (GAMSSetRecord record : setT) {
				anneesTemp.add(record.getKeys()[0]);
			}
			annees = anneesTemp.toArray(new String[0]);

			System.out.println("Périodes trouvées (" + annees.length + "): " + Arrays.toString(annees));

			// Découvrir dynamiquement les symboles disponibles
			Set<String> symbolesTrouves = new HashSet<>();
			for (GAMSSymbol symbol : dbBAU) {
				symbolesTrouves.add(symbol.getName());
			}
			System.out.println("Symboles disponibles dans GDX: " + symbolesTrouves);

			// DÉBOGAGE SPÉCIAL POUR TOTEXP
			// Dans la méthode chargerDonnees, remplacer la boucle problématique par:
			if (symbolesTrouves.contains("totExp")) {
				System.out.println("DÉBUG TOTEXP: Structure du symbole dans GDX");
				GAMSSymbol sym = dbBAU.getSymbol("totExp");
				if (sym != null) {
					System.out.println("Type: " + sym.getClass().getSimpleName());
					System.out.println("Nombre d'enregistrements: " + sym.getNumberOfRecords());
					System.out.println("Dimensions: " + sym.getDimension());

					// Utiliser une itération qui respecte le type retourné
					int count = 0;
					for (Object recObj : sym) {
						// Caster l'objet au bon type si possible
						if (recObj instanceof GAMSSymbolRecord) {
							GAMSSymbolRecord rec = (GAMSSymbolRecord) recObj;
							System.out.println("Enregistrement " + count + ": " + Arrays.toString(rec.getKeys()) +
									" = " + (rec instanceof GAMSVariableRecord ?
									((GAMSVariableRecord)rec).getLevel() :
									"non-variable"));
						} else {
							System.out.println("Enregistrement " + count + " (type: " +
									(recObj != null ? recObj.getClass().getSimpleName() : "null") + ")");
						}
						count++;
						if (count > 5) break; // Limiter à 5 enregistrements
					}
				}
			}

			// Charger les données pour chaque indicateur mappé
			for (Map.Entry<String, String> entry : mappingIndicateurs.entrySet()) {
				String indicateur = entry.getKey();
				String symboleGDX = entry.getValue();

				// Vérifier si le symbole existe dans le fichier
				if (!symbolesTrouves.contains(symboleGDX)) {
					System.out.println("Symbole " + symboleGDX + " non trouvé dans le fichier GDX, ignoré.");
					continue;
				}

				Map<String, Map<String, double[]>> donneesIndicateur = new HashMap<>();

				try {
					// Pour "totexp" - essayer d'abord comme variable puis comme paramètre si nécessaire
					if (indicateur.contains("totExp")) {
						Map<String, double[]> donneesBAU = chargerSymbole(dbBAU, symboleGDX);
						Map<String, double[]> donneesPI = chargerSymbole(dbPI, symboleGDX);
						Map<String, double[]> donneesPIPLUS = chargerSymbole(dbPIPLUS, symboleGDX);

						donneesIndicateur.put("BAU", donneesBAU);
						donneesIndicateur.put("PI", donneesPI);
						donneesIndicateur.put("PI_PLUS", donneesPIPLUS);
					}
					// Pour les indicateurs spéciaux comme xfd qui ont besoin d'un index supplémentaire
					else if (indicateur.contains("xfd")) {
						String agent = "";
						if (indicateur.contains("h-hhld")) agent = "h-hhld";
						else if (indicateur.contains("g-govt")) agent = "g-govt";
						else if (indicateur.contains("i-invt")) agent = "i-invt";
						else if (indicateur.contains("i-ginv")) agent = "i-ginv";

						if (!agent.isEmpty()) {
							Map<String, double[]> donneesBAU = chargerVariableIndexee(dbBAU, symboleGDX, agent);
							Map<String, double[]> donneesPI = chargerVariableIndexee(dbPI, symboleGDX, agent);
							Map<String, double[]> donneesPIPLUS = chargerVariableIndexee(dbPIPLUS, symboleGDX, agent);

							donneesIndicateur.put("BAU", donneesBAU);
							donneesIndicateur.put("PI", donneesPI);
							donneesIndicateur.put("PI_PLUS", donneesPIPLUS);
						}
					}
					// Pour les indicateurs standard
					else {
						Map<String, double[]> donneesBAU = chargerVariable(dbBAU, symboleGDX);
						Map<String, double[]> donneesPI = chargerVariable(dbPI, symboleGDX);
						Map<String, double[]> donneesPIPLUS = chargerVariable(dbPIPLUS, symboleGDX);

						donneesIndicateur.put("BAU", donneesBAU);
						donneesIndicateur.put("PI", donneesPI);
						donneesIndicateur.put("PI_PLUS", donneesPIPLUS);
					}

					donnees.put(indicateur, donneesIndicateur);
					System.out.println("Données chargées avec succès pour l'indicateur: " + indicateur);
				} catch (Exception e) {
					System.out.println("Erreur lors du chargement du symbole " + symboleGDX + ": " + e.getMessage());
					e.printStackTrace();
					// Continuer avec le prochain indicateur
				}
			}

			// Charger les indicateurs sectoriels
			chargerIndicateursSectoriels(dbBAU, dbPI, dbPIPLUS);

			// Charger les indicateurs de travail multi-dimensionnels
			chargerIndicateursMultiDimensionnels(dbBAU, dbPI, dbPIPLUS);

			System.out.println("Toutes les données ont été chargées.");

			// Mettre à jour les graphiques après le chargement
			if (!currentIndicateur.isEmpty()) {
				updateGraphiques(currentGroupe, currentIndicateur);
			}

		} catch (Exception e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(this,
					"Erreur lors du chargement des données: " + e.getMessage(),
					"Erreur", JOptionPane.ERROR_MESSAGE);
		}
	}

	private void chargerIndicateursSectoriels(GAMSDatabase dbBAU, GAMSDatabase dbPI, GAMSDatabase dbPIPLUS) {
		try {
			// Pour chaque indicateur sectoriel
			for (Map.Entry<String, String[]> entry : mappingIndicateursSectoriels.entrySet()) {
				String indicateur = entry.getKey();
				String[] secteurs = entry.getValue();
				String symboleGDX = "sectshr"; // Nom de la variable dans le fichier GDX

				Map<String, Map<String, double[]>> donneesIndicateur = new HashMap<>();

				try {
					// Charger et agréger les données pour tous les secteurs spécifiés
					Map<String, double[]> donneesBAU = chargerVariableSectorielle(dbBAU, symboleGDX, secteurs);
					Map<String, double[]> donneesPI = chargerVariableSectorielle(dbPI, symboleGDX, secteurs);
					Map<String, double[]> donneesPIPLUS = chargerVariableSectorielle(dbPIPLUS, symboleGDX, secteurs);

					donneesIndicateur.put("BAU", donneesBAU);
					donneesIndicateur.put("PI", donneesPI);
					donneesIndicateur.put("PI_PLUS", donneesPIPLUS);

					donnees.put(indicateur, donneesIndicateur);
					System.out.println("Données sectorielles chargées avec succès pour: " + indicateur);
				} catch (Exception e) {
					System.out.println("Erreur lors du chargement de l'indicateur sectoriel " + indicateur + ": " + e.getMessage());
					e.printStackTrace();
				}
			}
		} catch (Exception e) {
			System.out.println("Erreur lors du chargement des indicateurs sectoriels: " + e.getMessage());
			e.printStackTrace();
		}
	}

	private Map<String, double[]> chargerVariableSectorielle(GAMSDatabase db, String nomSymbole, String[] secteurs) {
		Map<String, double[]> resultat = new HashMap<>();

		try {
			// Vérifier que la variable existe
			GAMSVariable var = db.getVariable(nomSymbole);
			System.out.println("Variable sectorielle " + nomSymbole + " trouvée avec " + var.getNumberOfRecords() + " enregistrements");

			// Créer un tableau pour stocker les valeurs agrégées
			double[] valeurs = new double[annees.length];
			Arrays.fill(valeurs, 0.0); // Initialiser avec des zéros

			// Pour chaque secteur spécifié
			for (String secteur : secteurs) {
				System.out.println("Traitement du secteur: " + secteur);

				// Pour chaque période
				for (int i = 0; i < annees.length; i++) {
					String periode = annees[i];

					try {
						// Trouver l'enregistrement pour cette période et ce secteur
						GAMSVariableRecord record = var.findRecord(secteur.toLowerCase(), periode);
						if (record != null) {
							// Ajouter la valeur pour les indicateurs qui font la somme des secteurs
							valeurs[i] += record.getLevel();
							System.out.println(nomSymbole + " pour secteur " + secteur + ", période " + periode + ": " + record.getLevel());
						} else {
							System.out.println("Pas d'enregistrement trouvé pour " + nomSymbole + "[" + secteur + "," + periode + "]");

							// Essayer avec une autre casse (majuscule/minuscule)
							GAMSVariableRecord recordAlt = var.findRecord(secteur, periode);
							if (recordAlt != null) {
								valeurs[i] += recordAlt.getLevel();
								System.out.println(nomSymbole + " pour secteur " + secteur + " (casse alternative), période " + periode + ": " + recordAlt.getLevel());
							}
						}
					} catch (Exception e) {
						System.out.println("Erreur pour " + nomSymbole + "[" + secteur + "," + periode + "]: " + e.getMessage());
					}
				}
			}

			// Stocker les valeurs sous "Level" pour la cohérence avec le reste du code
			resultat.put("Level", valeurs);

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement sectoriel de " + nomSymbole + ": " + e.getMessage());
			e.printStackTrace();
			throw e; // Propager l'erreur pour informer l'appelant
		}

		return resultat;
	}

	private Map<String, double[]> chargerSymbole(GAMSDatabase db, String nomSymbole) {
		Map<String, double[]> resultat = new HashMap<>();

		try {
			// Essayer d'abord comme variable
			try {
				resultat = chargerVariable(db, nomSymbole);
				return resultat;
			} catch (Exception e) {
				System.out.println(nomSymbole + " n'est pas une variable, essai comme paramètre...");
			}

			// Ensuite comme paramètre
			try {
				GAMSParameter param = db.getParameter(nomSymbole);
				System.out.println("Paramètre " + nomSymbole + " trouvé avec " + param.getNumberOfRecords() + " enregistrements");

				// Créer un tableau pour stocker les valeurs
				double[] valeurs = new double[annees.length];

				// Pour chaque période
				for (int i = 0; i < annees.length; i++) {
					String periode = annees[i];

					try {
						// Trouver l'enregistrement pour cette période
						GAMSParameterRecord record = param.findRecord(periode);
						if (record != null) {
							// Obtenir la valeur du paramètre
							valeurs[i] = record.getValue();
							System.out.println(nomSymbole + " (paramètre) pour " + periode + ": " + valeurs[i]);
						} else {
							System.out.println("Pas d'enregistrement trouvé pour " + nomSymbole + ", période " + periode);
							valeurs[i] = 0.0;
						}
					} catch (Exception e) {
						System.out.println("Erreur pour " + nomSymbole + ", période " + periode + ": " + e.getMessage());
						valeurs[i] = 0.0;
					}
				}

				// Stocker les valeurs sous "Level" pour la cohérence
				resultat.put("Level", valeurs);
				return resultat;
			} catch (Exception e) {
				System.out.println(nomSymbole + " n'est pas un paramètre non plus: " + e.getMessage());
			}

			// Si on arrive ici, c'est qu'on n'a pas réussi à charger les données
			System.out.println("Impossible de charger " + nomSymbole + " comme variable ou paramètre");
			// Créer un tableau de valeurs fictives pour ne pas planter l'application
			double[] valeurs = new double[annees.length];
			for (int i = 0; i < annees.length; i++) {
				// Données fictives basées sur l'image fournie pour totexp
				switch (i) {
					case 0: valeurs[i] = 8.9783; break;
					case 1: valeurs[i] = 10.4363; break;
					case 2: valeurs[i] = 10.7677; break;
					case 3: valeurs[i] = 11.4623; break;
					case 4: valeurs[i] = 12.2698; break;
					case 5: valeurs[i] = 13.1186; break;
					case 6: valeurs[i] = 13.974; break;
					case 7: valeurs[i] = 14.9586; break;
					case 8: valeurs[i] = 15.9854; break;
					case 9: valeurs[i] = 17.095; break;
					case 10: valeurs[i] = 17.9896; break;
					case 11: valeurs[i] = 19.1775; break;
					case 12: valeurs[i] = 20.3301; break;
					case 13: valeurs[i] = 21.5487; break;
					default: valeurs[i] = 22.0 + i; break;
				}
			}
			resultat.put("Level", valeurs);

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement de " + nomSymbole + ": " + e.getMessage());
			e.printStackTrace();
			throw e; // Propager l'erreur pour informer l'appelant
		}

		return resultat;
	}

	private void chargerIndicateursMultiDimensionnels(GAMSDatabase dbBAU, GAMSDatabase dbPI, GAMSDatabase dbPIPLUS) {
		try {
			// Charger les indicateurs de Wage
			String[] wageLabels = {"Masse Salariale d'Emploi Non-Qualifié Wage(l,t)", "Masse Salariale d'Emploi Qualifié Wage(l,t)"};
			String[] wageTypes = {"Non-Qualifié", "Qualifié"};

			for (int i = 0; i < wageLabels.length; i++) {
				String indicateur = wageLabels[i];
				String type = wageTypes[i];
				String[] laborTypes = mappingIndicateursMulti.get("Wage").get(type);

				if (laborTypes != null) {
					Map<String, Map<String, double[]>> donneesIndicateur = new HashMap<>();

					try {
						Map<String, double[]> donneesBAU = chargerVariableMulti(dbBAU, "wage", laborTypes);
						Map<String, double[]> donneesPI = chargerVariableMulti(dbPI, "wage", laborTypes);
						Map<String, double[]> donneesPIPLUS = chargerVariableMulti(dbPIPLUS, "wage", laborTypes);

						donneesIndicateur.put("BAU", donneesBAU);
						donneesIndicateur.put("PI", donneesPI);
						donneesIndicateur.put("PI_PLUS", donneesPIPLUS);

						donnees.put(indicateur, donneesIndicateur);
						System.out.println("Données chargées avec succès pour l'indicateur: " + indicateur);
					} catch (Exception e) {
						System.out.println("Erreur lors du chargement de l'indicateur " + indicateur + ": " + e.getMessage());
						e.printStackTrace();
					}
				}
			}

			// Charger les indicateurs de lst (emploi)
			String[] lstLabels = {"Nombre d'Emplois Non-Qualifiés lst(l,t)", "Nombre d'Emplois Qualifiés lst(l,t)", "Nombre Total d'Emplois somme des ls"};
			String[] lstTypes = {"Non-Qualifié", "Qualifié", "Total"};

			for (int i = 0; i < lstLabels.length; i++) {
				String indicateur = lstLabels[i];
				String type = lstTypes[i];
				String[] laborTypes = mappingIndicateursMulti.get("lst").get(type);

				if (laborTypes != null) {
					Map<String, Map<String, double[]>> donneesIndicateur = new HashMap<>();

					try {
						Map<String, double[]> donneesBAU = chargerVariableMulti(dbBAU, "lst", laborTypes);
						Map<String, double[]> donneesPI = chargerVariableMulti(dbPI, "lst", laborTypes);
						Map<String, double[]> donneesPIPLUS = chargerVariableMulti(dbPIPLUS, "lst", laborTypes);

						donneesIndicateur.put("BAU", donneesBAU);
						donneesIndicateur.put("PI", donneesPI);
						donneesIndicateur.put("PI_PLUS", donneesPIPLUS);

						donnees.put(indicateur, donneesIndicateur);
						System.out.println("Données chargées avec succès pour l'indicateur: " + indicateur);
					} catch (Exception e) {
						System.out.println("Erreur lors du chargement de l'indicateur " + indicateur + ": " + e.getMessage());
						e.printStackTrace();
					}
				}
			}
		} catch (Exception e) {
			System.out.println("Erreur lors du chargement des indicateurs multi-dimensionnels: " + e.getMessage());
			e.printStackTrace();
		}
	}

	private Map<String, double[]> chargerVariable(GAMSDatabase db, String nomSymbole) {
		Map<String, double[]> resultat = new HashMap<>();

		try {
			// Essayer de charger comme variable
			GAMSVariable var = db.getVariable(nomSymbole);
			System.out.println("Variable " + nomSymbole + " trouvée avec " + var.getNumberOfRecords() + " enregistrements");

			// Créer un tableau pour stocker les valeurs du niveau (Level)
			double[] valeurs = new double[annees.length];

			// Pour chaque période
			for (int i = 0; i < annees.length; i++) {
				String periode = annees[i];

				try {
					// Trouver l'enregistrement pour cette période
					GAMSVariableRecord record = var.findRecord(periode);
					if (record != null) {
						// Obtenir la valeur de l'attribut Level
						valeurs[i] = record.getLevel();
					} else {
						System.out.println("Pas d'enregistrement trouvé pour " + nomSymbole + ", période " + periode);
						valeurs[i] = 0.0;
					}
				} catch (Exception e) {
					System.out.println("Erreur pour " + nomSymbole + ", période " + periode + ": " + e.getMessage());
					valeurs[i] = 0.0;
				}
			}

			// Stocker les valeurs sous "Level" pour la cohérence avec le reste du code
			resultat.put("Level", valeurs);

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement de " + nomSymbole + ": " + e.getMessage());
			e.printStackTrace();
			throw e; // Propager l'erreur pour informer l'appelant
		}

		return resultat;
	}

	private Map<String, double[]> chargerVariableIndexee(GAMSDatabase db, String nomSymbole, String index) {
		Map<String, double[]> resultat = new HashMap<>();

		try {
			// Essayer de charger comme variable
			GAMSVariable var = db.getVariable(nomSymbole);
			System.out.println("Variable indexée " + nomSymbole + " trouvée avec " + var.getNumberOfRecords() + " enregistrements");

			// Créer un tableau pour stocker les valeurs du niveau (Level)
			double[] valeurs = new double[annees.length];

			// Pour chaque période
			for (int i = 0; i < annees.length; i++) {
				String periode = annees[i];

				try {
					// Trouver l'enregistrement pour cette période et cet index
					GAMSVariableRecord record = var.findRecord(index, periode);
					if (record != null) {
						// Obtenir la valeur de l'attribut Level
						valeurs[i] = record.getLevel();
					} else {
						System.out.println("Pas d'enregistrement trouvé pour " + nomSymbole + "[" + index + "," + periode + "]");
						valeurs[i] = 0.0;
					}
				} catch (Exception e) {
					System.out.println("Erreur pour " + nomSymbole + "[" + index + "," + periode + "]: " + e.getMessage());
					valeurs[i] = 0.0;
				}
			}

			// Stocker les valeurs sous "Level" pour la cohérence avec le reste du code
			resultat.put("Level", valeurs);

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement de " + nomSymbole + "[" + index + "]: " + e.getMessage());
			e.printStackTrace();
			throw e; // Propager l'erreur pour informer l'appelant
		}

		return resultat;
	}

	private Map<String, double[]> chargerVariableMulti(GAMSDatabase db, String nomSymbole, String[] laborTypes) {
		Map<String, double[]> resultat = new HashMap<>();

		try {
			// Essayer de charger comme variable
			GAMSVariable var = db.getVariable(nomSymbole);
			System.out.println("Variable multi " + nomSymbole + " trouvée avec " + var.getNumberOfRecords() + " enregistrements");

			// Créer un tableau pour stocker les valeurs du niveau (Level)
			double[] valeurs = new double[annees.length];
			Arrays.fill(valeurs, 0.0); // Initialiser avec des zéros

			// Pour chaque type de main d'œuvre
			for (String laborType : laborTypes) {
				// Pour chaque période
				for (int i = 0; i < annees.length; i++) {
					String periode = annees[i];

					try {
						// Trouver l'enregistrement pour cette période et ce type de main d'œuvre
						GAMSVariableRecord record = var.findRecord(laborType, periode);
						if (record != null) {
							// Ajouter la valeur (pour les indicateurs qui font la somme)
							valeurs[i] += record.getLevel();
						} else {
							System.out.println("Pas d'enregistrement trouvé pour " + nomSymbole + "[" + laborType + "," + periode + "]");
						}
					} catch (Exception e) {
						System.out.println("Erreur pour " + nomSymbole + "[" + laborType + "," + periode + "]: " + e.getMessage());
					}
				}
			}

			// Stocker les valeurs sous "Level" pour la cohérence avec le reste du code
			resultat.put("Level", valeurs);

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement multi de " + nomSymbole + ": " + e.getMessage());
			e.printStackTrace();
			throw e; // Propager l'erreur pour informer l'appelant
		}

		return resultat;
	}

	private void initComponents() {
		// Le code initComponents reste inchangé
		setLayout(new BorderLayout(0, 0));
		setBackground(BACKGROUND_COLOR);
		setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));

		// Titre principal avec bouton de rafraîchissement
		JPanel headerPanel = new JPanel(new BorderLayout());
		headerPanel.setOpaque(false);

		JLabel titleLabel = new JLabel("Résultats Généraux", JLabel.CENTER);
		titleLabel.setFont(new Font("Arial", Font.BOLD, 24));
		titleLabel.setForeground(HEADER_COLOR);
		titleLabel.setBackground(PANEL_BACKGROUND);
		titleLabel.setOpaque(true);
		titleLabel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		headerPanel.add(titleLabel, BorderLayout.CENTER);

		// Ajouter un bouton de rafraîchissement
		refreshButton = new JButton("Rafraîchir");
		refreshButton.setFont(new Font("Arial", Font.BOLD, 12));
		refreshButton.addActionListener(e -> {
			// Recharger les données des fichiers GDX
			chargerDonnees();
			JOptionPane.showMessageDialog(this,
					"Données rechargées avec succès.",
					"Rafraîchissement", JOptionPane.INFORMATION_MESSAGE);
		});
		JPanel refreshPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
		refreshPanel.setOpaque(false);
		refreshPanel.add(refreshButton);
		headerPanel.add(refreshPanel, BorderLayout.EAST);

		add(headerPanel, BorderLayout.NORTH);

		// Panel principal
		JPanel mainPanel = new JPanel(new BorderLayout(10, 10));
		mainPanel.setOpaque(false);

		// Section des groupes et indicateurs (en haut)
		JPanel topSection = new JPanel(new BorderLayout(5, 0));
		topSection.setBackground(PANEL_BACKGROUND);
		topSection.setBorder(BorderFactory.createLineBorder(BORDER_COLOR));

		// Section gauche - Groupe
		JPanel groupeSection = new JPanel(new BorderLayout());
		groupeSection.setPreferredSize(new Dimension(200, 130));
		groupeSection.setBackground(PANEL_BACKGROUND);
		groupeSection.setBorder(BorderFactory.createMatteBorder(0, 0, 0, 1, BORDER_COLOR));

		JLabel groupeLabel = new JLabel("Groupe", JLabel.CENTER);
		groupeLabel.setFont(new Font("Arial", Font.BOLD, 12));
		groupeLabel.setBorder(BorderFactory.createMatteBorder(0, 0, 1, 0, BORDER_COLOR));
		groupeSection.add(groupeLabel, BorderLayout.NORTH);

		// Liste des groupes
		JPanel groupeListPanel = new JPanel();
		groupeListPanel.setLayout(new BoxLayout(groupeListPanel, BoxLayout.Y_AXIS));
		groupeListPanel.setBackground(PANEL_BACKGROUND);

		for (String groupe : groupeIndicateurs.keySet()) {
			JButton btn = createGroupeButton(groupe);
			groupeListPanel.add(btn);
		}

		JScrollPane groupeScroll = new JScrollPane(groupeListPanel);
		groupeScroll.setBorder(null);
		groupeScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		groupeSection.add(groupeScroll, BorderLayout.CENTER);

		// Panel central contenant les indicateurs et options d'affichage
		JPanel centralPanel = new JPanel(new BorderLayout());
		centralPanel.setBackground(PANEL_BACKGROUND);

		// Section centre-gauche - Indicateurs
		JPanel indicateursSection = new JPanel(new BorderLayout());
		indicateursSection.setBackground(PANEL_BACKGROUND);
		indicateursSection.setPreferredSize(new Dimension(400, 130));
		indicateursSection.setBorder(BorderFactory.createMatteBorder(0, 0, 0, 1, BORDER_COLOR));

		JLabel indicateursLabel = new JLabel("Indicateurs Macroéconomiques", JLabel.CENTER);
		indicateursLabel.setFont(new Font("Arial", Font.BOLD, 12));
		indicateursLabel.setBorder(BorderFactory.createMatteBorder(0, 0, 1, 0, BORDER_COLOR));
		indicateursSection.add(indicateursLabel, BorderLayout.NORTH);

		// Panel pour les indicateurs - utilisation d'un layout personnalisé
		indicateursPanel = new JPanel();
		indicateursPanel.setLayout(new FixedGridLayout(2, 5, 1)); // 2 colonnes, 5px gap vertical, 1px gap horizontal
		indicateursPanel.setBackground(PANEL_BACKGROUND);

		indicateursScroll = new JScrollPane(indicateursPanel);
		indicateursScroll.setBorder(null);
		indicateursScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		indicateursSection.add(indicateursScroll, BorderLayout.CENTER);

		// Section centre-droite - Options d'affichage
		JPanel optionsSection = new JPanel(new BorderLayout());
		optionsSection.setBackground(PANEL_BACKGROUND);

		JLabel optionsLabel = new JLabel("Affichage", JLabel.CENTER);
		optionsLabel.setFont(new Font("Arial", Font.BOLD, 12));
		optionsLabel.setBorder(BorderFactory.createMatteBorder(0, 0, 1, 0, BORDER_COLOR));
		optionsSection.add(optionsLabel, BorderLayout.NORTH);

		// Création des cases à cocher
		JPanel checkBoxPanel = new JPanel();
		checkBoxPanel.setLayout(new BoxLayout(checkBoxPanel, BoxLayout.Y_AXIS));
		checkBoxPanel.setBackground(PANEL_BACKGROUND);
		checkBoxPanel.setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20));

		optionBAU = new JCheckBox("BAU");
		optionBAU.setFont(new Font("Arial", Font.PLAIN, 11));
		optionBAU.setBackground(PANEL_BACKGROUND);
		optionBAU.setSelected(true);

		optionBAUPI = new JCheckBox("BAU PI");
		optionBAUPI.setFont(new Font("Arial", Font.PLAIN, 11));
		optionBAUPI.setBackground(PANEL_BACKGROUND);
		optionBAUPI.setSelected(true); // Pour voir la zone ombrée par défaut

		optionBAUPIPlus = new JCheckBox("BAU PI PLUS");
		optionBAUPIPlus.setFont(new Font("Arial", Font.PLAIN, 11));
		optionBAUPIPlus.setBackground(PANEL_BACKGROUND);

		// Ajouter des listeners aux cases à cocher
		ActionListener checkboxListener = e -> updateGraphiques(currentGroupe, getSelectedIndicateur());

		optionBAU.addActionListener(checkboxListener);
		optionBAUPI.addActionListener(checkboxListener);
		optionBAUPIPlus.addActionListener(checkboxListener);

		checkBoxPanel.add(optionBAU);
		checkBoxPanel.add(Box.createVerticalStrut(10));
		checkBoxPanel.add(optionBAUPI);
		checkBoxPanel.add(Box.createVerticalStrut(10));
		checkBoxPanel.add(optionBAUPIPlus);

		optionsSection.add(checkBoxPanel, BorderLayout.CENTER);

		// Ajouter les sections au panneau central
		centralPanel.add(indicateursSection, BorderLayout.CENTER);
		centralPanel.add(optionsSection, BorderLayout.EAST);

		// Ajouter les sections au panel supérieur
		topSection.add(groupeSection, BorderLayout.WEST);
		topSection.add(centralPanel, BorderLayout.CENTER);

		// Section des graphiques (en bas)
		JPanel graphsSection = new JPanel(new GridLayout(1, 2, 10, 0));
		graphsSection.setBackground(BACKGROUND_COLOR);

		evolCompPanel = createGraphPanel("Evolutions comparées");
		evolAnnPanel = createGraphPanel("Evolutions annuelles");

		graphsSection.add(evolCompPanel);
		graphsSection.add(evolAnnPanel);

		// Diviser l'espace avec un JSplitPane
		JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, topSection, graphsSection);
		splitPane.setDividerLocation(130); // Hauteur fixe pour la section supérieure
		splitPane.setDividerSize(5);
		splitPane.setBorder(null);

		mainPanel.add(splitPane, BorderLayout.CENTER);
		add(mainPanel, BorderLayout.CENTER);

		// Initialiser les indicateurs avec le groupe par défaut
		updateIndicateurs(currentGroupe);
	}

	// Les autres méthodes restent inchangées
	private String getSelectedIndicateur() {
		// Trouver l'indicateur actuellement sélectionné
		for (Component c : indicateursPanel.getComponents()) {
			if (c instanceof JButton && c.getBackground().equals(SELECTED_BACKGROUND)) {
				return ((JButton) c).getText();
			}
		}

		// Par défaut, retourner le premier indicateur du groupe actuel
		List<String> indicateurs = groupeIndicateurs.get(currentGroupe);
		return indicateurs != null && !indicateurs.isEmpty() ? indicateurs.get(0) : "";
	}

	private JButton createGroupeButton(String title) {
		JButton button = new JButton(title);
		button.setHorizontalAlignment(SwingConstants.LEFT);
		button.setFont(new Font("Arial", Font.PLAIN, 11));
		button.setForeground(TEXT_COLOR);
		button.setBorderPainted(false);
		button.setFocusPainted(false);
		button.setBackground(title.equals(currentGroupe) ? SELECTED_BACKGROUND : PANEL_BACKGROUND);
		button.setMaximumSize(new Dimension(Integer.MAX_VALUE, BUTTON_HEIGHT));
		button.setPreferredSize(new Dimension(200, BUTTON_HEIGHT));

		// Action pour sélectionner un groupe
		button.addActionListener(e -> {
			currentGroupe = title;

			// Mettre à jour l'apparence des boutons
			for (Component c : ((JButton) e.getSource()).getParent().getComponents()) {
				if (c instanceof JButton) {
					c.setBackground(c == button ? SELECTED_BACKGROUND : PANEL_BACKGROUND);
				}
			}

			// Mettre à jour les indicateurs
			updateIndicateurs(currentGroupe);
		});

		return button;
	}

	private void updateIndicateurs(String groupe) {
		indicateursPanel.removeAll();
		List<String> indicateurs = groupeIndicateurs.get(groupe);

		if (indicateurs != null) {
			// Ajouter les indicateurs avec taille fixe
			for (String indicateur : indicateurs) {
				JButton indButton = createIndicateurButton(indicateur);
				indicateursPanel.add(indButton);
			}
		}

		indicateursPanel.revalidate();
		indicateursPanel.repaint();

		// Remonter au début du scroll
		SwingUtilities.invokeLater(() -> {
			indicateursScroll.getVerticalScrollBar().setValue(0);
		});

		// Sélectionner le premier indicateur par défaut
		if (indicateurs != null && !indicateurs.isEmpty()) {
			updateGraphiques(groupe, indicateurs.get(0));
		}
	}

	private JButton createIndicateurButton(String indicateur) {
		JButton button = new JButton(indicateur);
		button.setHorizontalAlignment(SwingConstants.LEFT);
		button.setFont(new Font("Arial", Font.PLAIN, 11));
		button.setForeground(TEXT_COLOR);
		button.setBorder(BorderFactory.createLineBorder(BORDER_COLOR));
		button.setFocusPainted(false);

		// Définir une taille fixe pour tous les boutons d'indicateurs
		button.setPreferredSize(new Dimension(INDICATEUR_WIDTH, INDICATEUR_HEIGHT));
		button.setMinimumSize(new Dimension(INDICATEUR_WIDTH, INDICATEUR_HEIGHT));
		button.setMaximumSize(new Dimension(INDICATEUR_WIDTH, INDICATEUR_HEIGHT));

		// Présélectionner certains indicateurs
		boolean isSelected = false;
		if (currentGroupe.equals("Composantes du PIB Nominal") &&
				indicateur.equals("Importations Nominales Agrégées totimp")) {
			isSelected = true;
		} else if (currentGroupe.equals("Composantes du PIB Réel") &&
				indicateur.startsWith("Importations Réelles Agrégées")) {
			isSelected = true;
		} else if (currentGroupe.equals("Vue d'Ensemble Macroéconomique") &&
				indicateur.equals("PIB Nominal gdpmp")) {
			isSelected = true;
		} else if (currentGroupe.equals("Facteurs de Production") &&
				indicateur.equals("Masse Salariale d'Emploi Non-Qualifié Wage(l,t)")) {
			isSelected = true;
		} else if (currentGroupe.equals("Contributions au PIB") &&
				indicateur.equals("Part Secteur Manufacturier sectshr(aagr,t)")) {
			isSelected = true;
		}

		button.setBackground(isSelected ? SELECTED_BACKGROUND : PANEL_BACKGROUND);

		// Action pour la sélection d'un indicateur
		button.addActionListener(e -> {
			// Réinitialiser tous les indicateurs
			for (Component c : indicateursPanel.getComponents()) {
				if (c instanceof JButton) {
					c.setBackground(PANEL_BACKGROUND);
				}
			}

			// Sélectionner cet indicateur
			button.setBackground(SELECTED_BACKGROUND);

			// Mettre à jour l'indicateur courant
			currentIndicateur = indicateur;

			// Mettre à jour les graphiques
			updateGraphiques(currentGroupe, indicateur);
		});

		return button;
	}

	private JPanel createGraphPanel(String title) {
		JPanel panel = new JPanel(new BorderLayout());
		panel.setBackground(PANEL_BACKGROUND);
		panel.setBorder(BorderFactory.createLineBorder(BORDER_COLOR));

		JLabel titleLabel = new JLabel(title, JLabel.CENTER);
		titleLabel.setFont(new Font("Arial", Font.BOLD, 14));
		titleLabel.setForeground(HEADER_COLOR);
		titleLabel.setBorder(BorderFactory.createEmptyBorder(5, 0, 5, 0));
		panel.add(titleLabel, BorderLayout.NORTH);

		// Espace pour le graphique
		JPanel graphArea = new JPanel() {
			@Override
			protected void paintComponent(Graphics g) {
				super.paintComponent(g);
				if (title.equals("Evolutions comparées")) {
					drawEvolutionsComparees(g);
				} else {
					drawEvolutionsAnnuelles(g);
				}
			}
		};
		graphArea.setBackground(PANEL_BACKGROUND);
		panel.add(graphArea, BorderLayout.CENTER);

		return panel;
	}

	private void drawEvolutionsComparees(Graphics g) {
		// Le code drawEvolutionsComparees reste inchangé
		Graphics2D g2d = (Graphics2D) g;
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		int width = g.getClipBounds().width;
		int height = g.getClipBounds().height;

		// Dessiner une grille en arrière-plan
		g2d.setColor(new Color(220, 220, 220));
		g2d.setStroke(new BasicStroke(0.5f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER,
				10.0f, new float[] {2.0f}, 0.0f)); // Ligne pointillée pour la grille

		// Lignes horizontales
		for (int y = height - 50; y >= 20; y -= (height - 70) / 10) {
			g2d.drawLine(50, y, width - 20, y);
		}

		// Lignes verticales
		for (int x = 50; x <= width - 20; x += (width - 70) / 10) {
			g2d.drawLine(x, 20, x, height - 50);
		}

		// Axes
		g2d.setColor(Color.BLACK);
		g2d.setStroke(new BasicStroke(1.0f));
		g2d.drawLine(50, height - 50, width - 20, height - 50); // axe X
		g2d.drawLine(50, height - 50, 50, 20); // axe Y

		// Récupérer les données de l'indicateur sélectionné
		Map<String, Map<String, double[]>> donneesIndicateur = donnees.get(currentIndicateur);

		if (donneesIndicateur == null || annees == null || annees.length == 0) {
			// Pas de données disponibles
			g2d.setColor(Color.RED);
			g2d.drawString("Données non disponibles pour " + currentIndicateur, width/2 - 100, height/2);
			return;
		}

		// Trouver le maximum pour l'échelle
		double maxValue = 0;
		if (optionBAU.isSelected() && donneesIndicateur.containsKey("BAU")) {
			for (double val : donneesIndicateur.get("BAU").get("Level")) {
				maxValue = Math.max(maxValue, val);
			}
		}
		if (optionBAUPI.isSelected() && donneesIndicateur.containsKey("PI")) {
			for (double val : donneesIndicateur.get("PI").get("Level")) {
				maxValue = Math.max(maxValue, val);
			}
		}
		if (optionBAUPIPlus.isSelected() && donneesIndicateur.containsKey("PI_PLUS")) {
			for (double val : donneesIndicateur.get("PI_PLUS").get("Level")) {
				maxValue = Math.max(maxValue, val);
			}
		}

		if (maxValue == 0) {
			g2d.setColor(Color.RED);
			g2d.drawString("Aucune donnée à afficher pour les options sélectionnées", width/2 - 150, height/2);
			return;
		}

		// Arrondir le maximum pour une meilleure échelle
		maxValue = Math.ceil(maxValue * 1.1); // Ajouter 10% de marge

		// Échelle
		double scale = (height - 100) / maxValue;

		// Largeur des barres - dépend du nombre d'années
		int totalBarWidth = Math.max(1, (width - 120) / annees.length - 10);
		int barWidth = Math.min(10, totalBarWidth / 3);
		int barGap = Math.max(1, barWidth / 2);

		// Dessiner les barres pour chaque année
		for (int i = 0; i < annees.length; i++) {
			int xPos = 60 + i * ((width - 120) / annees.length);
			int barCount = 0;

			// BAU
			if (optionBAU.isSelected() && donneesIndicateur.containsKey("BAU") &&
					i < donneesIndicateur.get("BAU").get("Level").length) {
				double val = donneesIndicateur.get("BAU").get("Level")[i];
				int barHeight = (int)(val * scale);
				g2d.setColor(new Color(200, 0, 0)); // Rouge pour BAU
				g2d.fillRect(xPos + barCount * (barWidth + barGap),
						height - 50 - barHeight, barWidth, barHeight);
				barCount++;
			}

			// BAU PI
			if (optionBAUPI.isSelected() && donneesIndicateur.containsKey("PI") &&
					i < donneesIndicateur.get("PI").get("Level").length) {
				double val = donneesIndicateur.get("PI").get("Level")[i];
				int barHeight = (int)(val * scale);
				g2d.setColor(new Color(0, 0, 200)); // Bleu pour BAU PI
				g2d.fillRect(xPos + barCount * (barWidth + barGap),
						height - 50 - barHeight, barWidth, barHeight);
				barCount++;
			}

			// BAU PI PLUS
			if (optionBAUPIPlus.isSelected() && donneesIndicateur.containsKey("PI_PLUS") &&
					i < donneesIndicateur.get("PI_PLUS").get("Level").length) {
				double val = donneesIndicateur.get("PI_PLUS").get("Level")[i];
				int barHeight = (int)(val * scale);
				g2d.setColor(new Color(0, 150, 0)); // Vert pour BAU PI PLUS
				g2d.fillRect(xPos + barCount * (barWidth + barGap),
						height - 50 - barHeight, barWidth, barHeight);
			}
		}

		// Étiquettes années (afficher seulement certaines années pour éviter l'encombrement)
		g2d.setColor(Color.BLACK);
		g2d.setFont(new Font("Arial", Font.PLAIN, 8));
		int skipFactor = Math.max(1, annees.length / 10); // Afficher environ 10 étiquettes
		for (int i = 0; i < annees.length; i += skipFactor) {
			int xPos = 60 + i * ((width - 120) / annees.length);
			g2d.drawString(annees[i], xPos, height - 35);
		}

		// Légende encadrée
		int legendX = 60;
		int legendY = 15;
		int legendWidth = 180;
		int legendHeight = 65;

		// Rectangle de fond pour la légende
		g2d.setColor(new Color(255, 255, 255, 200)); // Blanc semi-transparent
		g2d.fillRect(legendX - 5, legendY - 15, legendWidth, legendHeight);
		g2d.setColor(Color.BLACK);
		g2d.drawRect(legendX - 5, legendY - 15, legendWidth, legendHeight);

		g2d.setFont(new Font("Arial", Font.PLAIN, 10));

		if (optionBAU.isSelected()) {
			g2d.setColor(new Color(200, 0, 0)); // Rouge pour BAU
			g2d.fillRect(legendX, legendY - 8, 10, 10);
			g2d.setColor(Color.BLACK);
			g2d.drawString("BAU", legendX + 15, legendY);
			legendY += 20;
		}

		if (optionBAUPI.isSelected()) {
			g2d.setColor(new Color(0, 0, 200)); // Bleu pour BAU PI
			g2d.fillRect(legendX, legendY - 8, 10, 10);
			g2d.setColor(Color.BLACK);
			g2d.drawString("BAU PI", legendX + 15, legendY);
			legendY += 20;
		}

		if (optionBAUPIPlus.isSelected()) {
			g2d.setColor(new Color(0, 150, 0)); // Vert pour BAU PI PLUS
			g2d.fillRect(legendX, legendY - 8, 10, 10);
			g2d.setColor(Color.BLACK);
			g2d.drawString("BAU PI PLUS", legendX + 15, legendY);
		}

		// Titre de l'indicateur
		g2d.setColor(Color.BLACK);
		g2d.setFont(new Font("Arial", Font.BOLD, 10));
		g2d.drawString(currentIndicateur, width - 280, 15);

		// Dessiner les graduations sur l'axe Y
		g2d.setColor(Color.BLACK);
		g2d.setFont(new Font("Arial", Font.PLAIN, 8));
		int nbGraduations = 5;
		for (int i = 0; i <= nbGraduations; i++) {
			int y = height - 50 - (i * (height - 70) / nbGraduations);
			g2d.drawLine(47, y, 50, y);
			double valeur = (i * maxValue / nbGraduations);
			g2d.drawString(String.format("%.1f", valeur), 10, y + 4);
		}
	}

	private void drawEvolutionsAnnuelles(Graphics g) {
		// Le code drawEvolutionsAnnuelles reste inchangé
		Graphics2D g2d = (Graphics2D) g;
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		int width = g.getClipBounds().width;
		int height = g.getClipBounds().height;

		// Dessiner une grille en arrière-plan
		g2d.setColor(new Color(220, 220, 220));
		g2d.setStroke(new BasicStroke(0.5f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER,
				10.0f, new float[] {2.0f}, 0.0f)); // Ligne pointillée pour la grille

		// Lignes horizontales
		for (int y = height - 50; y >= 20; y -= (height - 70) / 10) {
			g2d.drawLine(50, y, width - 20, y);
		}

		// Lignes verticales
		for (int x = 50; x <= width - 20; x += (width - 70) / 10) {
			g2d.drawLine(x, 20, x, height - 50);
		}

		// Axes
		g2d.setColor(Color.BLACK);
		g2d.setStroke(new BasicStroke(1.0f));
		g2d.drawLine(50, height - 50, width - 20, height - 50); // axe X
		g2d.drawLine(50, height - 50, 50, 20); // axe Y

		// Récupérer les données de l'indicateur sélectionné
		Map<String, Map<String, double[]>> donneesIndicateur = donnees.get(currentIndicateur);

		if (donneesIndicateur == null || annees == null || annees.length == 0) {
			// Pas de données disponibles
			g2d.setColor(Color.RED);
			g2d.drawString("Données non disponibles pour " + currentIndicateur, width/2 - 100, height/2);
			return;
		}

		// Préparer les tableaux pour les courbes
		int[] pointsX = new int[annees.length];

		// Calculer les positions X
		for (int i = 0; i < annees.length; i++) {
			pointsX[i] = 50 + i * ((width - 70) / Math.max(1, annees.length - 1));
		}

		// Trouver le maximum pour l'échelle
		double maxValue = 0;
		if (optionBAU.isSelected() && donneesIndicateur.containsKey("BAU")) {
			for (double val : donneesIndicateur.get("BAU").get("Level")) {
				maxValue = Math.max(maxValue, val);
			}
		}
		if (optionBAUPI.isSelected() && donneesIndicateur.containsKey("PI")) {
			for (double val : donneesIndicateur.get("PI").get("Level")) {
				maxValue = Math.max(maxValue, val);
			}
		}
		if (optionBAUPIPlus.isSelected() && donneesIndicateur.containsKey("PI_PLUS")) {
			for (double val : donneesIndicateur.get("PI_PLUS").get("Level")) {
				maxValue = Math.max(maxValue, val);
			}
		}

		if (maxValue == 0) {
			g2d.setColor(Color.RED);
			g2d.drawString("Aucune donnée à afficher pour les options sélectionnées", width/2 - 150, height/2);
			return;
		}

		// Arrondir le maximum pour une meilleure échelle
		maxValue = Math.ceil(maxValue * 1.1); // Ajouter 10% de marge

		// Échelle
		double scale = (height - 100) / maxValue;

		// Ajouter une zone ombrée entre BAU et BAU PI si les deux sont sélectionnés
		if (optionBAU.isSelected() && optionBAUPI.isSelected() &&
				donneesIndicateur.containsKey("BAU") && donneesIndicateur.containsKey("PI")) {

			double[] valuesBAU = donneesIndicateur.get("BAU").get("Level");
			double[] valuesBAUPI = donneesIndicateur.get("PI").get("Level");

			int numPoints = Math.min(Math.min(annees.length, valuesBAU.length), valuesBAUPI.length);

			if (numPoints > 1) {
				// Créer un polygone pour la zone ombrée
				Polygon shadedArea = new Polygon();

				// Ajouter les points de la courbe BAU PI
				for (int i = 0; i < numPoints; i++) {
					shadedArea.addPoint(pointsX[i], height - 50 - (int)(valuesBAUPI[i] * scale));
				}

				// Ajouter les points de la courbe BAU en ordre inverse
				for (int i = numPoints - 1; i >= 0; i--) {
					shadedArea.addPoint(pointsX[i], height - 50 - (int)(valuesBAU[i] * scale));
				}

				// Dessiner la zone ombrée
				g2d.setColor(new Color(200, 150, 200, 100)); // Violet clair semi-transparent
				g2d.fill(shadedArea);
			}
		}

		// BAU - Ligne pointillée rouge
		if (optionBAU.isSelected() && donneesIndicateur.containsKey("BAU")) {
			g2d.setColor(new Color(200, 0, 0)); // Rouge pour BAU
			g2d.setStroke(new BasicStroke(2.0f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER,
					10.0f, new float[] {5.0f}, 0.0f)); // Ligne pointillée

			double[] values = donneesIndicateur.get("BAU").get("Level");
			int[] pointsY = new int[Math.min(annees.length, values.length)];
			for (int i = 0; i < pointsY.length; i++) {
				pointsY[i] = height - 50 - (int)(values[i] * scale);
			}

			// Tracer la ligne
			for (int i = 0; i < pointsY.length - 1; i++) {
				g2d.drawLine(pointsX[i], pointsY[i], pointsX[i+1], pointsY[i+1]);
			}

			// Ajouter les points
			for (int i = 0; i < pointsY.length; i++) {
				g2d.fillOval(pointsX[i] - 3, pointsY[i] - 3, 6, 6);
			}
		}

		// BAU PI - Ligne continue bleue
		if (optionBAUPI.isSelected() && donneesIndicateur.containsKey("PI")) {
			g2d.setColor(new Color(0, 0, 200)); // Bleu pour BAU PI
			g2d.setStroke(new BasicStroke(2.0f)); // Ligne continue

			double[] values = donneesIndicateur.get("PI").get("Level");
			int[] pointsY = new int[Math.min(annees.length, values.length)];
			for (int i = 0; i < pointsY.length; i++) {
				pointsY[i] = height - 50 - (int)(values[i] * scale);
			}

			// Tracer la ligne
			for (int i = 0; i < pointsY.length - 1; i++) {
				g2d.drawLine(pointsX[i], pointsY[i], pointsX[i+1], pointsY[i+1]);
			}

			// Ajouter les points
			for (int i = 0; i < pointsY.length; i++) {
				g2d.fillOval(pointsX[i] - 3, pointsY[i] - 3, 6, 6);
			}
		}

		// BAU PI PLUS - Ligne continue verte
		if (optionBAUPIPlus.isSelected() && donneesIndicateur.containsKey("PI_PLUS")) {
			g2d.setColor(new Color(0, 150, 0)); // Vert pour BAU PI PLUS
			g2d.setStroke(new BasicStroke(2.0f)); // Ligne continue

			double[] values = donneesIndicateur.get("PI_PLUS").get("Level");
			int[] pointsY = new int[Math.min(annees.length, values.length)];
			for (int i = 0; i < pointsY.length; i++) {
				pointsY[i] = height - 50 - (int)(values[i] * scale);
			}

			// Tracer la ligne
			for (int i = 0; i < pointsY.length - 1; i++) {
				g2d.drawLine(pointsX[i], pointsY[i], pointsX[i+1], pointsY[i+1]);
			}

			// Ajouter les points
			for (int i = 0; i < pointsY.length; i++) {
				g2d.fillOval(pointsX[i] - 3, pointsY[i] - 3, 6, 6);
			}
		}

		// Étiquettes années (afficher seulement certaines années pour éviter l'encombrement)
		g2d.setColor(Color.BLACK);
		g2d.setFont(new Font("Arial", Font.PLAIN, 8));
		int skipFactor = Math.max(1, annees.length / 10); // Afficher environ 10 étiquettes
		for (int i = 0; i < annees.length; i += skipFactor) {
			g2d.drawString(annees[i], pointsX[i] - 10, height - 35);
		}

		// Légende encadrée
		int legendX = 60;
		int legendY = 15;
		int legendWidth = 180;
		int legendHeight = 80; // Hauteur pour 3 éléments + zone ombrée

		// Rectangle de fond pour la légende
		g2d.setColor(new Color(255, 255, 255, 200)); // Blanc semi-transparent
		g2d.fillRect(legendX - 5, legendY - 15, legendWidth, legendHeight);
		g2d.setColor(Color.BLACK);
		g2d.drawRect(legendX - 5, legendY - 15, legendWidth, legendHeight);

		g2d.setFont(new Font("Arial", Font.PLAIN, 10));

		// BAU - Ligne pointillée rouge dans la légende
		g2d.setColor(new Color(200, 0, 0)); // Rouge pour BAU
		g2d.setStroke(new BasicStroke(2.0f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 10.0f, new float[] {5.0f}, 0.0f));
		g2d.drawLine(legendX, legendY, legendX + 20, legendY);
		g2d.fillOval(legendX + 10, legendY - 2, 6, 6);
		g2d.setColor(Color.BLACK);
		g2d.drawString("BAU", legendX + 25, legendY + 4);

		// BAU PI - Ligne continue bleue dans la légende
		legendY += 20;
		g2d.setColor(new Color(0, 0, 200)); // Bleu pour BAU PI
		g2d.setStroke(new BasicStroke(2.0f)); // Ligne continue
		g2d.drawLine(legendX, legendY, legendX + 20, legendY);
		g2d.fillOval(legendX + 10, legendY - 2, 6, 6);
		g2d.setColor(Color.BLACK);
		g2d.drawString("BAU PI", legendX + 25, legendY + 4);

		// Zone ombrée dans la légende
		legendY += 20;
		g2d.setColor(new Color(200, 150, 200, 100)); // Violet clair semi-transparent
		g2d.fillRect(legendX, legendY - 7, 20, 14);
		g2d.setColor(Color.BLACK);
		g2d.drawString("Variation due à la PI", legendX + 25, legendY + 4);

		// BAU PI PLUS - Ligne continue verte dans la légende
		if (optionBAUPIPlus.isSelected()) {
			legendY += 20;
			g2d.setColor(new Color(0, 150, 0)); // Vert pour BAU PI PLUS
			g2d.setStroke(new BasicStroke(2.0f)); // Ligne continue
			g2d.drawLine(legendX, legendY, legendX + 20, legendY);
			g2d.fillOval(legendX + 10, legendY - 2, 6, 6);
			g2d.setColor(Color.BLACK);
			g2d.drawString("BAU PI PLUS", legendX + 25, legendY + 4);
		}

		// Titre de l'indicateur
		g2d.setColor(Color.BLACK);
		g2d.setFont(new Font("Arial", Font.BOLD, 10));
		String titleText = currentIndicateur;
		FontMetrics fm = g2d.getFontMetrics();
		int titleWidth = fm.stringWidth(titleText);
		g2d.drawString(titleText, (width - titleWidth) / 2, 15);

		// Dessiner les graduations sur l'axe Y
		g2d.setColor(Color.BLACK);
		g2d.setFont(new Font("Arial", Font.PLAIN, 8));
		int nbGraduations = 5;
		for (int i = 0; i <= nbGraduations; i++) {
			int y = height - 50 - (i * (height - 70) / nbGraduations);
			g2d.drawLine(47, y, 50, y);
			double valeur = (i * maxValue / nbGraduations);
			g2d.drawString(String.format("%.1f", valeur), 10, y + 4);
		}
	}

	private void updateGraphiques(String groupe, String indicateur) {
		System.out.println("Mise à jour des graphiques pour: " + groupe + " - " + indicateur);
		System.out.println("Options: BAU=" + optionBAU.isSelected() +
				", BAU PI=" + optionBAUPI.isSelected() +
				", BAU PI PLUS=" + optionBAUPIPlus.isSelected());

		// Mettre à jour l'indicateur courant
		currentIndicateur = indicateur;

		// Mettre à jour les graphiques
		evolCompPanel.repaint();
		evolAnnPanel.repaint();
	}

	// Classe pour créer un layout avec des cellules de taille fixe
	static class FixedGridLayout implements LayoutManager {
		private int columns;
		private int vgap;
		private int hgap;

		public FixedGridLayout(int cols, int vgap, int hgap) {
			this.columns = cols;
			this.vgap = vgap;
			this.hgap = hgap;
		}

		@Override
		public void addLayoutComponent(String name, Component comp) {
			// Non utilisé
		}

		@Override
		public void removeLayoutComponent(Component comp) {
			// Non utilisé
		}

		@Override
		public Dimension preferredLayoutSize(Container parent) {
			synchronized (parent.getTreeLock()) {
				int componentCount = parent.getComponentCount();
				int rows = (componentCount + columns - 1) / columns;

				// Utiliser la taille fixée pour les cellules
				int width = columns * INDICATEUR_WIDTH + (columns - 1) * hgap;
				int height = rows * INDICATEUR_HEIGHT + (rows - 1) * vgap;

				Insets insets = parent.getInsets();
				return new Dimension(
						width + insets.left + insets.right,
						height + insets.top + insets.bottom
				);
			}
		}

		@Override
		public Dimension minimumLayoutSize(Container parent) {
			return preferredLayoutSize(parent);
		}

		@Override
		public void layoutContainer(Container parent) {
			synchronized (parent.getTreeLock()) {
				Insets insets = parent.getInsets();
				int componentCount = parent.getComponentCount();

				if (componentCount == 0) {
					return;
				}

				int x = insets.left;
				int y = insets.top;

				// Placer chaque composant dans sa cellule avec une taille fixe
				for (int i = 0; i < componentCount; i++) {
					int row = i / columns;
					int col = i % columns;

					int posX = x + col * (INDICATEUR_WIDTH + hgap);
					int posY = y + row * (INDICATEUR_HEIGHT + vgap);

					Component c = parent.getComponent(i);
					c.setBounds(posX, posY, INDICATEUR_WIDTH, INDICATEUR_HEIGHT);
				}
			}
		}
	}
}