package src;

import com.gams.api.*;
import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

import org.apache.poi.ss.usermodel.*;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

public class GdxExtractor {

	public static void main(String[] args) {
		String gdxFile = "../CIV_MPE_Structure\\res\\BaU.gdx";
		String outputDir = "gdx_extracts";
		Map<String, List<Map<String, Object>>> dfs = new HashMap<>();

		new File(outputDir).mkdirs();

		try {
			GAMSWorkspace ws = new GAMSWorkspace();
			GAMSDatabase db = ws.addDatabaseFromGDX(gdxFile);

			dfs.put("gdpmp", extractVariable(db, "gdpmp", 2));
			dfs.put("rgdpmp", extractVariable(db, "rgdpmp", 2));
			dfs.put("Wage", extractVariable(db, "Wage", 3));
			dfs.put("lsT", extractVariable(db, "lsT", 3));
			dfs.put("ls", extractVariable(db, "ls", 4));

			// Somme de 'ls' par (l, t)
			List<Map<String, Object>> lsData = dfs.get("ls");
			Map<String, Double> lsSum = new HashMap<>();

			for (Map<String, Object> row : lsData) {
				String l = (String) row.get("l");
				String t = (String) row.get("t");
				Double level = (Double) row.get("Level");

				String key = l + "|" + t;
				lsSum.put(key, lsSum.getOrDefault(key, 0.0) + level);
			}

			List<Map<String, Object>> lsSumList = new ArrayList<>();
			for (Map.Entry<String, Double> entry : lsSum.entrySet()) {
				String[] parts = entry.getKey().split("\\|");
				Map<String, Object> record = new LinkedHashMap<>();
				record.put("l", parts[0]);
				record.put("t", parts[1]);
				record.put("Sum_Level", entry.getValue());
				lsSumList.add(record);
			}
			dfs.put("ls_sum", lsSumList);

			// Sauvegarde CSV et Excel
			saveAsExcel(outputDir + "/all_variables.xlsx", dfs);
			for (Map.Entry<String, List<Map<String, Object>>> entry : dfs.entrySet()) {
				saveAsCSV(outputDir + "/" + entry.getKey() + ".csv", entry.getValue());
			}

			System.out.println("Extraction terminée. Données sauvegardées dans le dossier " + outputDir);

		} catch (Exception e) {
			System.err.println("Une erreur s'est produite: " + e.getMessage());
			e.printStackTrace();
		}
	}

	public static List<Map<String, Object>> extractVariable(GAMSDatabase db, String name, int dimensions) {
		List<Map<String, Object>> records = new ArrayList<>();
		GAMSVariable var = db.getVariable(name);

		String[] dimNames;
		switch (dimensions) {
			case 1: dimNames = new String[]{"t"}; break;
			case 2: dimNames = name.equals("gdpmp") || name.equals("rgdpmp") ? new String[]{"t", "Level"} : new String[]{"l", "t"}; break;
			case 3: dimNames = new String[]{"l", "t", "Level"}; break;
			case 4: dimNames = new String[]{"a", "l", "t", "Level"}; break;
			default: dimNames = new String[dimensions];
		}

		for (GAMSVariableRecord rec : var) {
			Map<String, Object> row = new LinkedHashMap<>();
			String[] keys = rec.getKeys(); // keys est un tableau String[]

			for (int i = 0; i < keys.length; i++) {
				if (i < dimNames.length) {
					row.put(dimNames[i], keys[i]);
				}
			}

			row.put("Level", rec.getLevel());
			row.put("Marginal", rec.getMarginal());
			row.put("Lower", rec.getLower());
			row.put("Upper", rec.getUpper());
			row.put("Scale", rec.getScale());
			records.add(row);
		}


		return records;
	}

	public static void saveAsCSV(String path, List<Map<String, Object>> data) throws IOException {
		if (data.isEmpty()) return;
		try (BufferedWriter writer = new BufferedWriter(new FileWriter(path))) {
			// Header
			List<String> headers = new ArrayList<>(data.get(0).keySet());
			writer.write(String.join(",", headers));
			writer.newLine();
			// Rows
			for (Map<String, Object> row : data) {
				List<String> line = headers.stream()
						.map(h -> String.valueOf(row.getOrDefault(h, "")))
						.collect(Collectors.toList());
				writer.write(String.join(",", line));
				writer.newLine();
			}
		}
	}

	public static void saveAsExcel(String path, Map<String, List<Map<String, Object>>> dfs) throws IOException {
		try (Workbook workbook = new XSSFWorkbook()) {
			for (Map.Entry<String, List<Map<String, Object>>> entry : dfs.entrySet()) {
				Sheet sheet = workbook.createSheet(entry.getKey());
				List<Map<String, Object>> data = entry.getValue();
				if (data.isEmpty()) continue;

				Row headerRow = sheet.createRow(0);
				List<String> headers = new ArrayList<>(data.get(0).keySet());
				for (int i = 0; i < headers.size(); i++) {
					headerRow.createCell(i).setCellValue(headers.get(i));
				}

				int rowIndex = 1;
				for (Map<String, Object> row : data) {
					Row excelRow = sheet.createRow(rowIndex++);
					for (int i = 0; i < headers.size(); i++) {
						Object value = row.get(headers.get(i));
						if (value instanceof Number) {
							excelRow.createCell(i).setCellValue(((Number) value).doubleValue());
						} else {
							excelRow.createCell(i).setCellValue(String.valueOf(value));
						}
					}
				}
			}
			try (FileOutputStream fileOut = new FileOutputStream(path)) {
				workbook.write(fileOut);
			}
		}
	}
}

