package makefile;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class CPPScanner {

    private String currentPath; // directory to scan
    private ArrayList<String> filenames;

    public CPPScanner(String path) {
        this.currentPath = path;
        filenames = new ArrayList<>();
    }

    public Dependency read(String filename) {
        int maxRowToScan = 48;

        Dependency fileDependency = null;

        File file = new File(currentPath+"\\"+filename);
        Boolean isCPPExists = file.exists();

        File headerFile = new File(currentPath+"\\"+toHPP(filename));
        Boolean isHeaderExists = headerFile.exists();

        fileDependency = new Dependency(filename, isHeaderExists, isCPPExists);

        try {
            Scanner scanner = new Scanner(file);

            filenames.add(filename);

            // now read the file line by line...
            int lineNum = 0;
            while (scanner.hasNextLine() && lineNum < maxRowToScan) {
                String line = scanner.nextLine();
                //System.out.println(line);
                lineNum++;
                if (line.contains("include \"")) {
                    String dependencyName = getFilenameFormat(line);
                    if(filenames.contains(dependencyName))
                        continue;
                    
                    System.out.println("found dependency on line: " + lineNum + ", dependency: "+line);
                    fileDependency.addDependency(read(dependencyName));
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("An error occured while scanning the file: "+filename+", for dependancies.");
            //e.printStackTrace();
        } 

        return fileDependency;
    }

    public void createMakeFile(String makefileString) {
        File file = new File("makefile");
        PrintWriter pw = null;

        try {
            pw = new PrintWriter(file);
            pw.print(makefileString);
        } catch (Exception e) {
            System.out.println("Error while saving makefile to file system.");
        } finally {
            try {
                pw.close();
            } catch (Exception e) {
                System.out.println("Error, couldn't close the file writing stream of makefile.");
            }
        }
    }

    
    public String getFilenameFormat(String line) {
        int beginIndex = line.indexOf("\"")+1;
        int endIndex = line.indexOf("\"",beginIndex);
        
        String filename = line.substring(beginIndex, endIndex);
        filename = filename.replace(".hpp", ".cpp");

        return filename;
    }

    
    public String toHPP(String name) {
        int index = name.lastIndexOf('.');
        return name.substring(0, index)+".hpp"; 
    }
}