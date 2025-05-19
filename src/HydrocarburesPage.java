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
 * Hydrocarbures page component for the MMPE Dashboard
 */
public class HydrocarburesPage extends JPanel {
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
	private String currentGroupe = "Vue d'Ensemble";
	private String currentIndicateur = "";

	// Options d'affichage
	private JCheckBox optionBAU;
	private JCheckBox optionBAUPI;
	private JCheckBox optionBAUPIPlus;

	// Bouton pour rafraîchir les données
	private JButton refreshButton;

	// Stockage des données GDX
	private Map<String, Map<String, Map<String, double[]>>> donnees;
	private String[] annees; // Pour stocker les années (t)

	// Mappings spécifiques pour les hydrocarbures
	private Map<String, String> mappingIndicateurs;
	private Map<String, Map<String, String[]>> mappingColonnes;

	public HydrocarburesPage() {
		initMappings();
		initData();
		initComponents();
		chargerDonnees();
	}

	private void initMappings() {
		mappingIndicateurs = new HashMap<>();
		mappingColonnes = new HashMap<>();

		// Mapping des indicateurs vers les expressions GDX
		mappingIndicateurs.put("Exportations pwe(i,t) * xe(i,t)", "export_hydrocarbures");
		mappingIndicateurs.put("Importations pwm(i,t) * (xm(i,t) + mdelst(i,t))", "import_hydrocarbures");
		mappingIndicateurs.put("Masse Salariale d'Emploi Non-Qualifié Swage(a,l,t)", "swage_nq");
		mappingIndicateurs.put("Masse Salariale d'Emploi Qualifié Swage(a,l,t)", "swage_q");
		mappingIndicateurs.put("Nombre d'Emplois Non-Qualifiés Ls (a,l,t)", "ls_nq");
		mappingIndicateurs.put("Nombre d'Emplois Qualifiés Ls (a,l,t)", "ls_q");
		mappingIndicateurs.put("Nombre Total d'Emplois somme des ls", "ls_total");
		mappingIndicateurs.put("Valeur du Capital sum(cap,pk_pt(a,v,t)*xf(a,cap,t))", "capital_value");

		// Mapping pour les colonnes à utiliser
		// Pour les exportations et importations
		Map<String, String[]> mappingProduits = new HashMap<>();
		mappingProduits.put("hydrocarbures", new String[]{"c-oil", "c-gas", "c-rafoil"});
		mappingColonnes.put("i", mappingProduits);

		// Pour les activités (secteurs) des hydrocarbures
		Map<String, String[]> mappingActivites = new HashMap<>();
		mappingActivites.put("hydrocarbures", new String[]{"a-oil", "a-gas", "a-rafoil"});
		mappingColonnes.put("a", mappingActivites);

		// Pour les types de main d'oeuvre
		Map<String, String[]> mappingLabor = new HashMap<>();
		mappingLabor.put("Non-Qualifié", new String[]{"f-labuskl"});
		mappingLabor.put("Qualifié", new String[]{"f-labmeskl", "f-labskl"});
		mappingLabor.put("Total", new String[]{"f-labuskl", "f-labmeskl", "f-labskl"});
		mappingColonnes.put("l", mappingLabor);
	}

	private void initData() {
		// Structure de données pour les groupes et leurs indicateurs
		groupeIndicateurs = new LinkedHashMap<>(); // LinkedHashMap pour conserver l'ordre d'insertion
		donnees = new HashMap<>();

		// Vue d'Ensemble du Secteur des Hydrocarbures
		List<String> vueEnsembleList = new ArrayList<>();
		vueEnsembleList.add("Exportations pwe(i,t) * xe(i,t)");
		vueEnsembleList.add("Importations pwm(i,t) * (xm(i,t) + mdelst(i,t))");
		groupeIndicateurs.put("Vue d'Ensemble", vueEnsembleList);

		// Facteurs de production
		List<String> facteursList = new ArrayList<>();
		facteursList.add("Masse Salariale d'Emploi Non-Qualifié Swage(a,l,t)");
		facteursList.add("Masse Salariale d'Emploi Qualifié Swage(a,l,t)");
		facteursList.add("Nombre d'Emplois Non-Qualifiés Ls (a,l,t)");
		facteursList.add("Nombre d'Emplois Qualifiés Ls (a,l,t)");
		facteursList.add("Nombre Total d'Emplois somme des ls");
		facteursList.add("Valeur du Capital sum(cap,pk_pt(a,v,t)*xf(a,cap,t))");
		groupeIndicateurs.put("Facteurs de Production", facteursList);
	}

	private void chargerDonnees() {
		try {
			// Réinitialiser les données existantes
			donnees.clear();

			// Vérifier si les fichiers existent
			File bauFile = new File(GDX_BAU_PATH);
			File piFile = new File(GDX_PI_PATH);
			File piPlusFile = new File(GDX_PI_PLUS_PATH);

			System.out.println("Chargement des fichiers GDX pour Hydrocarbures:");
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
			GAMSDatabase dbPIPLUS = null;

			try {
				dbPIPLUS = ws.addDatabaseFromGDX(GDX_PI_PLUS_PATH);
			} catch (Exception e) {
				System.out.println("Erreur lors du chargement de PI_PLUS: " + e.getMessage());
				dbPIPLUS = null;
			}

			// Lister quelques symboles du fichier GDX pour le débogage
			System.out.println("Analyse du fichier BAU pour Hydrocarbures...");
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

			// Charger les données pour chaque indicateur
			chargerDonneesExportationsImportations(dbBAU, dbPI, dbPIPLUS);
			chargerDonneesMasseSalariale(dbBAU, dbPI, dbPIPLUS);
			chargerDonneesEmploi(dbBAU, dbPI, dbPIPLUS);
			chargerDonneesCapital(dbBAU, dbPI, dbPIPLUS);

			System.out.println("Toutes les données des hydrocarbures ont été chargées.");

			// Mettre à jour les graphiques après le chargement
			if (!currentIndicateur.isEmpty()) {
				updateGraphiques(currentGroupe, currentIndicateur);
			}

		} catch (Exception e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(this,
					"Erreur lors du chargement des données des hydrocarbures: " + e.getMessage(),
					"Erreur", JOptionPane.ERROR_MESSAGE);
		}
	}

	private void chargerDonneesExportationsImportations(GAMSDatabase dbBAU, GAMSDatabase dbPI, GAMSDatabase dbPIPLUS) {
		try {
			// Obtenir les produits d'hydrocarbures à prendre en compte
			String[] produitsHydrocarbures = mappingColonnes.get("i").get("hydrocarbures");

			// Pour les exportations
			chargerIndicateurExportImport(dbBAU, dbPI, dbPIPLUS,
					"Exportations pwe(i,t) * xe(i,t)",
					"pwe", "xe", produitsHydrocarbures);

			// Pour les importations
			chargerIndicateurExportImport(dbBAU, dbPI, dbPIPLUS,
					"Importations pwm(i,t) * (xm(i,t) + mdelst(i,t))",
					"pwm", new String[]{"xm", "mdelst"}, produitsHydrocarbures);

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement des données d'exportations/importations: " + e.getMessage());
			e.printStackTrace();
		}
	}

	private void chargerIndicateurExportImport(GAMSDatabase dbBAU, GAMSDatabase dbPI, GAMSDatabase dbPIPLUS,
	                                           String indicateur, String varPrix, String varQuantite, String[] produits) {
		chargerIndicateurExportImport(dbBAU, dbPI, dbPIPLUS, indicateur, varPrix, new String[]{varQuantite}, produits);
	}

	private void chargerIndicateurExportImport(GAMSDatabase dbBAU, GAMSDatabase dbPI, GAMSDatabase dbPIPLUS,
	                                           String indicateur, String varPrix, String[] varsQuantite, String[] produits) {
		try {
			Map<String, Map<String, double[]>> donneesIndicateur = new HashMap<>();

			// Charger pour chaque scénario
			Map<String, double[]> donneesBAU = calculerExportImport(dbBAU, varPrix, varsQuantite, produits);
			Map<String, double[]> donneesPI = calculerExportImport(dbPI, varPrix, varsQuantite, produits);
			Map<String, double[]> donneesPIPLUS = null;

			// Vérifier si dbPIPLUS est disponible avant de tenter de l'utiliser
			if (dbPIPLUS != null) {
				try {
					donneesPIPLUS = calculerExportImport(dbPIPLUS, varPrix, varsQuantite, produits);
				} catch (Exception e) {
					System.out.println("Erreur lors du calcul pour PI_PLUS: " + e.getMessage());
					donneesPIPLUS = null;
				}
			}

			donneesIndicateur.put("BAU", donneesBAU);
			donneesIndicateur.put("PI", donneesPI);
			if (donneesPIPLUS != null) {
				donneesIndicateur.put("PI_PLUS", donneesPIPLUS);
			}

			donnees.put(indicateur, donneesIndicateur);
			System.out.println("Données chargées avec succès pour: " + indicateur +
					" (avec PI_PLUS: " + (donneesPIPLUS != null) + ")");

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement de l'indicateur " + indicateur + ": " + e.getMessage());
			e.printStackTrace();
		}
	}

	private Map<String, double[]> calculerExportImport(GAMSDatabase db, String varPrix, String[] varsQuantite, String[] produits) {
		Map<String, double[]> resultat = new HashMap<>();

		try {
			// Créer un tableau pour stocker les valeurs
			double[] valeurs = new double[annees.length];
			Arrays.fill(valeurs, 0.0);

			// Obtenir les variables
			GAMSVariable varP = db.getVariable(varPrix);

			// Pour chaque période
			for (int i = 0; i < annees.length; i++) {
				String periode = annees[i];

				// Pour chaque produit d'hydrocarbure
				for (String produit : produits) {
					double prix = 0;
					double qteTotal = 0;

					// Obtenir le prix
					GAMSVariableRecord recP = varP.findRecord(produit, periode);
					if (recP != null) {
						prix = recP.getLevel();
					}

					// Obtenir les quantités et les additionner
					for (String varQ : varsQuantite) {
						GAMSVariable varQuantite = db.getVariable(varQ);
						GAMSVariableRecord recQ = varQuantite.findRecord(produit, periode);
						if (recQ != null) {
							qteTotal += recQ.getLevel();
						}
					}

					// Calculer la valeur (prix * quantité)
					valeurs[i] += prix * qteTotal;
				}
			}

			// Stocker les valeurs
			resultat.put("Level", valeurs);

		} catch (Exception e) {
			System.out.println("Erreur lors du calcul export/import: " + e.getMessage());
			e.printStackTrace();

			// Créer un tableau avec des valeurs par défaut pour ne pas planter l'application
			double[] valeurs = new double[annees.length];
			Arrays.fill(valeurs, 0.0);
			resultat.put("Level", valeurs);
		}

		return resultat;
	}

	private void chargerDonneesMasseSalariale(GAMSDatabase dbBAU, GAMSDatabase dbPI, GAMSDatabase dbPIPLUS) {
		try {
			// Obtenir les activités d'hydrocarbures et types de main d'œuvre à prendre en compte
			String[] activitesHydrocarbures = mappingColonnes.get("a").get("hydrocarbures");
			String[] laborNonQualifie = mappingColonnes.get("l").get("Non-Qualifié");
			String[] laborQualifie = mappingColonnes.get("l").get("Qualifié");

			// Pour la masse salariale non qualifiée
			Map<String, Map<String, double[]>> donneesNQ = new HashMap<>();
			Map<String, double[]> donneesBAU_NQ = chargerMasseSalariale(dbBAU, activitesHydrocarbures, laborNonQualifie);
			Map<String, double[]> donneesPI_NQ = chargerMasseSalariale(dbPI, activitesHydrocarbures, laborNonQualifie);
			Map<String, double[]> donneesPIPLUS_NQ = null;

			if (dbPIPLUS != null) {
				try {
					donneesPIPLUS_NQ = chargerMasseSalariale(dbPIPLUS, activitesHydrocarbures, laborNonQualifie);
				} catch (Exception e) {
					System.out.println("Erreur lors du chargement de la masse salariale NQ pour PI_PLUS: " + e.getMessage());
					donneesPIPLUS_NQ = null;
				}
			}

			donneesNQ.put("BAU", donneesBAU_NQ);
			donneesNQ.put("PI", donneesPI_NQ);
			if (donneesPIPLUS_NQ != null) {
				donneesNQ.put("PI_PLUS", donneesPIPLUS_NQ);
			}
			donnees.put("Masse Salariale d'Emploi Non-Qualifié Swage(a,l,t)", donneesNQ);

			// Pour la masse salariale qualifiée
			Map<String, Map<String, double[]>> donneesQ = new HashMap<>();
			Map<String, double[]> donneesBAU_Q = chargerMasseSalariale(dbBAU, activitesHydrocarbures, laborQualifie);
			Map<String, double[]> donneesPI_Q = chargerMasseSalariale(dbPI, activitesHydrocarbures, laborQualifie);
			Map<String, double[]> donneesPIPLUS_Q = null;

			if (dbPIPLUS != null) {
				try {
					donneesPIPLUS_Q = chargerMasseSalariale(dbPIPLUS, activitesHydrocarbures, laborQualifie);
				} catch (Exception e) {
					System.out.println("Erreur lors du chargement de la masse salariale Q pour PI_PLUS: " + e.getMessage());
					donneesPIPLUS_Q = null;
				}
			}

			donneesQ.put("BAU", donneesBAU_Q);
			donneesQ.put("PI", donneesPI_Q);
			if (donneesPIPLUS_Q != null) {
				donneesQ.put("PI_PLUS", donneesPIPLUS_Q);
			}
			donnees.put("Masse Salariale d'Emploi Qualifié Swage(a,l,t)", donneesQ);

			System.out.println("Données de masse salariale chargées avec succès.");

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement des masses salariales: " + e.getMessage());
			e.printStackTrace();
		}
	}

	private Map<String, double[]> chargerMasseSalariale(GAMSDatabase db, String[] activites, String[] laborTypes) {
		Map<String, double[]> resultat = new HashMap<>();

		try {
			// Créer un tableau pour stocker les valeurs
			double[] valeurs = new double[annees.length];
			Arrays.fill(valeurs, 0.0);

			// Obtenir la variable Swage
			GAMSVariable varSwage = db.getVariable("swage");

			// Pour chaque période
			for (int i = 0; i < annees.length; i++) {
				String periode = annees[i];

				// Pour chaque activité d'hydrocarbure
				for (String activite : activites) {
					// Pour chaque type de main d'œuvre
					for (String labor : laborTypes) {
						GAMSVariableRecord rec = varSwage.findRecord(activite, labor, periode);
						if (rec != null) {
							valeurs[i] += rec.getLevel();
						}
					}
				}
			}

			// Stocker les valeurs
			resultat.put("Level", valeurs);

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement de la masse salariale: " + e.getMessage());
			e.printStackTrace();

			// Créer un tableau avec des valeurs par défaut
			double[] valeurs = new double[annees.length];
			Arrays.fill(valeurs, 0.0);
			resultat.put("Level", valeurs);
		}

		return resultat;
	}

	private void chargerDonneesEmploi(GAMSDatabase dbBAU, GAMSDatabase dbPI, GAMSDatabase dbPIPLUS) {
		try {
			// Obtenir les activités d'hydrocarbures et types de main d'œuvre à prendre en compte
			String[] activitesHydrocarbures = mappingColonnes.get("a").get("hydrocarbures");
			String[] laborNonQualifie = mappingColonnes.get("l").get("Non-Qualifié");
			String[] laborQualifie = mappingColonnes.get("l").get("Qualifié");
			String[] laborTotal = mappingColonnes.get("l").get("Total");

			// Pour l'emploi non qualifié
			Map<String, Map<String, double[]>> donneesNQ = new HashMap<>();
			Map<String, double[]> donneesBAU_NQ = chargerEmploi(dbBAU, activitesHydrocarbures, laborNonQualifie);
			Map<String, double[]> donneesPI_NQ = chargerEmploi(dbPI, activitesHydrocarbures, laborNonQualifie);
			Map<String, double[]> donneesPIPLUS_NQ = null;

			if (dbPIPLUS != null) {
				try {
					donneesPIPLUS_NQ = chargerEmploi(dbPIPLUS, activitesHydrocarbures, laborNonQualifie);
				} catch (Exception e) {
					System.out.println("Erreur lors du chargement de l'emploi NQ pour PI_PLUS: " + e.getMessage());
					donneesPIPLUS_NQ = null;
				}
			}

			donneesNQ.put("BAU", donneesBAU_NQ);
			donneesNQ.put("PI", donneesPI_NQ);
			if (donneesPIPLUS_NQ != null) {
				donneesNQ.put("PI_PLUS", donneesPIPLUS_NQ);
			}
			donnees.put("Nombre d'Emplois Non-Qualifiés Ls (a,l,t)", donneesNQ);

			// Pour l'emploi qualifié
			Map<String, Map<String, double[]>> donneesQ = new HashMap<>();
			Map<String, double[]> donneesBAU_Q = chargerEmploi(dbBAU, activitesHydrocarbures, laborQualifie);
			Map<String, double[]> donneesPI_Q = chargerEmploi(dbPI, activitesHydrocarbures, laborQualifie);
			Map<String, double[]> donneesPIPLUS_Q = null;

			if (dbPIPLUS != null) {
				try {
					donneesPIPLUS_Q = chargerEmploi(dbPIPLUS, activitesHydrocarbures, laborQualifie);
				} catch (Exception e) {
					System.out.println("Erreur lors du chargement de l'emploi Q pour PI_PLUS: " + e.getMessage());
					donneesPIPLUS_Q = null;
				}
			}

			donneesQ.put("BAU", donneesBAU_Q);
			donneesQ.put("PI", donneesPI_Q);
			if (donneesPIPLUS_Q != null) {
				donneesQ.put("PI_PLUS", donneesPIPLUS_Q);
			}
			donnees.put("Nombre d'Emplois Qualifiés Ls (a,l,t)", donneesQ);

			// Pour l'emploi total
			Map<String, Map<String, double[]>> donneesTotal = new HashMap<>();
			Map<String, double[]> donneesBAU_Total = chargerEmploi(dbBAU, activitesHydrocarbures, laborTotal);
			Map<String, double[]> donneesPI_Total = chargerEmploi(dbPI, activitesHydrocarbures, laborTotal);
			Map<String, double[]> donneesPIPLUS_Total = null;

			if (dbPIPLUS != null) {
				try {
					donneesPIPLUS_Total = chargerEmploi(dbPIPLUS, activitesHydrocarbures, laborTotal);
				} catch (Exception e) {
					System.out.println("Erreur lors du chargement de l'emploi total pour PI_PLUS: " + e.getMessage());
					donneesPIPLUS_Total = null;
				}
			}

			donneesTotal.put("BAU", donneesBAU_Total);
			donneesTotal.put("PI", donneesPI_Total);
			if (donneesPIPLUS_Total != null) {
				donneesTotal.put("PI_PLUS", donneesPIPLUS_Total);
			}
			donnees.put("Nombre Total d'Emplois somme des ls", donneesTotal);

			System.out.println("Données d'emploi chargées avec succès.");

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement des données d'emploi: " + e.getMessage());
			e.printStackTrace();
		}
	}

	private Map<String, double[]> chargerEmploi(GAMSDatabase db, String[] activites, String[] laborTypes) {
		Map<String, double[]> resultat = new HashMap<>();

		try {
			// Créer un tableau pour stocker les valeurs
			double[] valeurs = new double[annees.length];
			Arrays.fill(valeurs, 0.0);

			// Obtenir la variable Ls
			GAMSVariable varLs = db.getVariable("ls");

			// Pour chaque période
			for (int i = 0; i < annees.length; i++) {
				String periode = annees[i];

				// Pour chaque activité d'hydrocarbure
				for (String activite : activites) {
					// Pour chaque type de main d'œuvre
					for (String labor : laborTypes) {
						GAMSVariableRecord rec = varLs.findRecord(activite, labor, periode);
						if (rec != null) {
							valeurs[i] += rec.getLevel();
						}
					}
				}
			}

			// Stocker les valeurs
			resultat.put("Level", valeurs);

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement de l'emploi: " + e.getMessage());
			e.printStackTrace();

			// Créer un tableau avec des valeurs par défaut
			double[] valeurs = new double[annees.length];
			Arrays.fill(valeurs, 0.0);
			resultat.put("Level", valeurs);
		}

		return resultat;
	}

	private void chargerDonneesCapital(GAMSDatabase dbBAU, GAMSDatabase dbPI, GAMSDatabase dbPIPLUS) {
		try {
			// Obtenir les activités d'hydrocarbures
			String[] activitesHydrocarbures = mappingColonnes.get("a").get("hydrocarbures");

			// Pour la valeur du capital
			Map<String, Map<String, double[]>> donneesCapital = new HashMap<>();
			Map<String, double[]> donneesBAU = chargerCapital(dbBAU, activitesHydrocarbures);
			Map<String, double[]> donneesPI = chargerCapital(dbPI, activitesHydrocarbures);
			Map<String, double[]> donneesPIPLUS = null;

			if (dbPIPLUS != null) {
				try {
					donneesPIPLUS = chargerCapital(dbPIPLUS, activitesHydrocarbures);
				} catch (Exception e) {
					System.out.println("Erreur lors du chargement du capital pour PI_PLUS: " + e.getMessage());
					donneesPIPLUS = null;
				}
			}

			donneesCapital.put("BAU", donneesBAU);
			donneesCapital.put("PI", donneesPI);
			if (donneesPIPLUS != null) {
				donneesCapital.put("PI_PLUS", donneesPIPLUS);
			}
			donnees.put("Valeur du Capital sum(cap,pk_pt(a,v,t)*xf(a,cap,t))", donneesCapital);

			System.out.println("Données de capital chargées avec succès.");

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement du capital: " + e.getMessage());
			e.printStackTrace();
		}
	}

	private Map<String, double[]> chargerCapital(GAMSDatabase db, String[] activites) {
		Map<String, double[]> resultat = new HashMap<>();

		try {
			// Créer un tableau pour stocker les valeurs
			double[] valeurs = new double[annees.length];
			Arrays.fill(valeurs, 0.0);

			// Obtenir les variables pour le capital
			GAMSVariable varPkPt = db.getVariable("pk_pt");
			GAMSVariable varXf = db.getVariable("xf");

			// Pour chaque période
			for (int i = 0; i < annees.length; i++) {
				String periode = annees[i];

				// Pour chaque activité d'hydrocarbure
				for (String activite : activites) {
					// Le capital peut être représenté par différentes facteurs (cap)
					// Essayer avec f-cap1, f-cap2, etc., ou simplement "cap" selon la structure du modèle
					double valeurTotaleCapital = 0;

					try {
						// Essayer avec des indices spécifiques pour le capital
						String[] indicesCapitaux = {"f-cap"};
						for (String cap : indicesCapitaux) {
							// Obtenir le prix relatif du capital
							GAMSVariableRecord recPkPt = varPkPt.findRecord(activite, cap, periode);
							double prixRelatif = (recPkPt != null) ? recPkPt.getLevel() : 0;

							// Obtenir la quantité de capital
							GAMSVariableRecord recXf = varXf.findRecord(activite, cap, periode);
							double quantite = (recXf != null) ? recXf.getLevel() : 0;

							// Calculer la valeur
							valeurTotaleCapital += prixRelatif * quantite;
						}
					} catch (Exception e) {
						System.out.println("Erreur lors du calcul du capital pour " + activite + ": " + e.getMessage());
						// Si erreur, essayer une approche alternative selon la structure du modèle
					}

					valeurs[i] += valeurTotaleCapital;
				}
			}

			// Stocker les valeurs
			resultat.put("Level", valeurs);

		} catch (Exception e) {
			System.out.println("Erreur lors du chargement du capital: " + e.getMessage());
			e.printStackTrace();

			// Créer un tableau avec des valeurs par défaut
			double[] valeurs = new double[annees.length];
			Arrays.fill(valeurs, 0.0);
			resultat.put("Level", valeurs);
		}

		return resultat;
	}

	private void initComponents() {
		setLayout(new BorderLayout(0, 0));
		setBackground(BACKGROUND_COLOR);
		setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));

		// Titre principal avec bouton de rafraîchissement
		JPanel headerPanel = new JPanel(new BorderLayout());
		headerPanel.setOpaque(false);

		JLabel titleLabel = new JLabel("Secteur des Hydrocarbures", JLabel.CENTER);
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
					"Données des hydrocarbures rechargées avec succès.",
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
		optionBAUPI.setSelected(true); // Sélectionné par défaut

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
			currentIndicateur = indicateurs.get(0);
			updateGraphiques(groupe, currentIndicateur);
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
		if (currentGroupe.equals("Vue d'Ensemble") && indicateur.equals("Exportations pwe(i,t) * xe(i,t)")) {
			isSelected = true;
		} else if (currentGroupe.equals("Facteurs de Production") && indicateur.equals("Masse Salariale d'Emploi Non-Qualifié Swage(a,l,t)")) {
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
			Map<String, double[]> bauData = donneesIndicateur.get("BAU");
			if (bauData != null && bauData.containsKey("Level") && bauData.get("Level") != null) {
				for (double val : bauData.get("Level")) {
					maxValue = Math.max(maxValue, val);
				}
			}
		}
		if (optionBAUPI.isSelected() && donneesIndicateur.containsKey("PI")) {
			Map<String, double[]> piData = donneesIndicateur.get("PI");
			if (piData != null && piData.containsKey("Level") && piData.get("Level") != null) {
				for (double val : piData.get("Level")) {
					maxValue = Math.max(maxValue, val);
				}
			}
		}
		if (optionBAUPIPlus.isSelected() && donneesIndicateur.containsKey("PI_PLUS")) {
			Map<String, double[]> piPlusData = donneesIndicateur.get("PI_PLUS");
			if (piPlusData != null && piPlusData.containsKey("Level") && piPlusData.get("Level") != null) {
				for (double val : piPlusData.get("Level")) {
					maxValue = Math.max(maxValue, val);
				}
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
			if (optionBAU.isSelected() && donneesIndicateur.containsKey("BAU")) {
				Map<String, double[]> bauData = donneesIndicateur.get("BAU");
				if (bauData != null && bauData.containsKey("Level") && bauData.get("Level") != null) {
					double[] values = bauData.get("Level");
					if (i < values.length) {
						double val = values[i];
						int barHeight = (int)(val * scale);
						g2d.setColor(new Color(200, 0, 0)); // Rouge pour BAU
						g2d.fillRect(xPos + barCount * (barWidth + barGap),
								height - 50 - barHeight, barWidth, barHeight);
						barCount++;
					}
				}
			}

			// BAU PI
			if (optionBAUPI.isSelected() && donneesIndicateur.containsKey("PI")) {
				Map<String, double[]> piData = donneesIndicateur.get("PI");
				if (piData != null && piData.containsKey("Level") && piData.get("Level") != null) {
					double[] values = piData.get("Level");
					if (i < values.length) {
						double val = values[i];
						int barHeight = (int)(val * scale);
						g2d.setColor(new Color(0, 0, 200)); // Bleu pour BAU PI
						g2d.fillRect(xPos + barCount * (barWidth + barGap),
								height - 50 - barHeight, barWidth, barHeight);
						barCount++;
					}
				}
			}

			// BAU PI PLUS
			if (optionBAUPIPlus.isSelected() && donneesIndicateur.containsKey("PI_PLUS")) {
				Map<String, double[]> piPlusData = donneesIndicateur.get("PI_PLUS");
				if (piPlusData != null && piPlusData.containsKey("Level") && piPlusData.get("Level") != null) {
					double[] values = piPlusData.get("Level");
					if (i < values.length) {
						double val = values[i];
						int barHeight = (int)(val * scale);
						g2d.setColor(new Color(0, 150, 0)); // Vert pour BAU PI PLUS
						g2d.fillRect(xPos + barCount * (barWidth + barGap),
								height - 50 - barHeight, barWidth, barHeight);
					}
				}
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
			Map<String, double[]> bauData = donneesIndicateur.get("BAU");
			if (bauData != null && bauData.containsKey("Level") && bauData.get("Level") != null) {
				for (double val : bauData.get("Level")) {
					maxValue = Math.max(maxValue, val);
				}
			}
		}
		if (optionBAUPI.isSelected() && donneesIndicateur.containsKey("PI")) {
			Map<String, double[]> piData = donneesIndicateur.get("PI");
			if (piData != null && piData.containsKey("Level") && piData.get("Level") != null) {
				for (double val : piData.get("Level")) {
					maxValue = Math.max(maxValue, val);
				}
			}
		}
		if (optionBAUPIPlus.isSelected() && donneesIndicateur.containsKey("PI_PLUS")) {
			Map<String, double[]> piPlusData = donneesIndicateur.get("PI_PLUS");
			if (piPlusData != null && piPlusData.containsKey("Level") && piPlusData.get("Level") != null) {
				for (double val : piPlusData.get("Level")) {
					maxValue = Math.max(maxValue, val);
				}
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

			Map<String, double[]> bauData = donneesIndicateur.get("BAU");
			Map<String, double[]> piData = donneesIndicateur.get("PI");

			if (bauData != null && bauData.containsKey("Level") && bauData.get("Level") != null &&
					piData != null && piData.containsKey("Level") && piData.get("Level") != null) {

				double[] valuesBAU = bauData.get("Level");
				double[] valuesBAUPI = piData.get("Level");

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
		}

		// BAU - Ligne pointillée rouge
		if (optionBAU.isSelected() && donneesIndicateur.containsKey("BAU")) {
			Map<String, double[]> bauData = donneesIndicateur.get("BAU");
			if (bauData != null && bauData.containsKey("Level") && bauData.get("Level") != null) {
				g2d.setColor(new Color(200, 0, 0)); // Rouge pour BAU
				g2d.setStroke(new BasicStroke(2.0f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER,
						10.0f, new float[] {5.0f}, 0.0f)); // Ligne pointillée

				double[] values = bauData.get("Level");
				// Vérifier que nous avons des données
				if (values.length > 0) {
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
			}
		}

		// BAU PI - Ligne continue bleue
		if (optionBAUPI.isSelected() && donneesIndicateur.containsKey("PI")) {
			Map<String, double[]> piData = donneesIndicateur.get("PI");
			if (piData != null && piData.containsKey("Level") && piData.get("Level") != null) {
				g2d.setColor(new Color(0, 0, 200)); // Bleu pour BAU PI
				g2d.setStroke(new BasicStroke(2.0f)); // Ligne continue

				double[] values = piData.get("Level");
				// Vérifier que nous avons des données
				if (values.length > 0) {
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
			}
		}

		// BAU PI PLUS - Ligne continue verte
		if (optionBAUPIPlus.isSelected() && donneesIndicateur.containsKey("PI_PLUS")) {
			// Vérifier que les données existent et ne sont pas null
			Map<String, double[]> piPlusData = donneesIndicateur.get("PI_PLUS");
			if (piPlusData != null && piPlusData.containsKey("Level") && piPlusData.get("Level") != null) {
				g2d.setColor(new Color(0, 150, 0)); // Vert pour BAU PI PLUS
				g2d.setStroke(new BasicStroke(2.0f)); // Ligne continue

				double[] values = piPlusData.get("Level");
				// Vérifier que nous avons des données
				if (values.length > 0) {
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
				} else {
					g2d.setColor(Color.RED);
					g2d.drawString("Données BAU PI PLUS vides", width/2 - 80, height/2 + 20);
				}
			} else {
				g2d.setColor(Color.RED);
				g2d.drawString("Données BAU PI PLUS non disponibles", width/2 - 100, height/2 + 20);
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

		// Vérification des données pour PI_PLUS
		Map<String, Map<String, double[]>> donneesIndicateur = donnees.get(indicateur);
		if (donneesIndicateur != null) {
			System.out.println("Scénarios disponibles: " + donneesIndicateur.keySet());

			if (donneesIndicateur.containsKey("PI_PLUS")) {
				Map<String, double[]> piPlusData = donneesIndicateur.get("PI_PLUS");
				System.out.println("PI_PLUS existe, clés disponibles: " + (piPlusData != null ? piPlusData.keySet() : "piPlusData est null"));

				if (piPlusData != null && piPlusData.containsKey("Level")) {
					double[] values = piPlusData.get("Level");
					System.out.println("Level existe, longueur: " + (values != null ? values.length : "values est null"));
				}
			}
		}

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