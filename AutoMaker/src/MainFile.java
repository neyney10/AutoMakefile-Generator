import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

class MainFile {
    final static String programVersion = "1.1-Beta";
    final static char TAB = '\t';

    static String currentPath;
    static ArrayList<String> filenames;
    static String outputFilename = "executable";

    public static void main(String[] args) {
        // if there are not enough arguments then quit with a message.
        if(args.length != 1) {
            System.out.println("No '.cpp' file provided to create a dependency tree...");
            System.out.println("\t Syntax: AutoMakefile <filename.cpp> <flags>");
            System.out.println("\t Note: no flags are supported at the moment, using version: "+programVersion);
            return;
        }

        String executablePath = args[0];
        currentPath = System.getProperty("user.dir"); // get current dir
        filenames = new ArrayList<>();

        System.out.println("Starting AutoMaker Version: "+programVersion);
        System.out.println("Scanning file: "+currentPath+"\\"+executablePath);

        Dependency executeableDependency = read(executablePath);

        MakefileCreator mfc  = new MakefileCreator(outputFilename);

        System.out.println("--- Here is the makefile preview: ---");
        String makefileString = mfc.createMakeFileString(executeableDependency);
        System.out.println(makefileString);
        System.out.println("--- Creating makefile: saved ---");
        createMakeFile(makefileString);

    }

    public static Dependency read(String filename) {
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

    public static void createMakeFile(String makefileString) {
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

    
    public static String getFilenameFormat(String line) {
        int beginIndex = line.indexOf("\"")+1;
        int endIndex = line.indexOf("\"",beginIndex);
        
        String filename = line.substring(beginIndex, endIndex);
        filename = filename.replace(".hpp", ".cpp");

        return filename;
    }

    
    public static String toHPP(String name) {
        int index = name.lastIndexOf('.');
        return name.substring(0, index)+".hpp"; 
    }


    

}