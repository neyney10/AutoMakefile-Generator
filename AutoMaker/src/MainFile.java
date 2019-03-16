import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FilenameFilter;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

class MainFile {
    final static String programVersion = "1.0-Beta";
    final static char TAB = '\t';

    static String currentPath;
    static ArrayList<String> filenames;
    static String outputFilename = "executable";

    public static void main(String[] args) {
        String executablePath = args[0];
        currentPath = System.getProperty("user.dir");
        filenames = new ArrayList<>();

        System.out.println("Starting AutoMaker Version: "+programVersion);
        System.out.println("Scanning file: "+currentPath+"\\"+executablePath);

        Dependency executeableDependency = read(executablePath);

        // File f = new File(currentPath);
        // File[] matchingFiles = f.listFiles(new FilenameFilter() {
        //     public boolean accept(File dir, String name) {
        //         return name.endsWith(".cpp");
        //     }
        // });

        System.out.println("--- Here is the makefile preview: ---");
        String makefileString = createMakeFileString(executeableDependency);
        System.out.println(makefileString);
        System.out.println("--- Creating makefile: saved ---");
        createMakeFile(makefileString);

    }

    public static Dependency read(String filename) {
        int maxRowToScan = 48;

        Dependency fileDependency = new Dependency(filename);

        File file = new File(currentPath+"\\"+filename);

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

                    System.out.println("found dependancy on line: " + lineNum + ", dependancy: "+line);
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
            //TODO: handle exception
        } finally {
            try {
                pw.close();
            } catch (Exception e) {
                //TODO: handle exception
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

    public static String createMakeFileString(Dependency rootFile) {
        StringBuilder sb = new StringBuilder();
        
        sb.append(rootFile.getFilepath()+":");
        ArrayList<Dependency> dep = rootFile.getDependencies();

        StringBuilder sbd = new StringBuilder();
        for(Dependency d : dep) {
            sbd.append(" "+d.getFilepath());
        }

        sb.append(sbd.toString()+"\n");
        sb.append(TAB + "g++ -std=c++1z"+sbd.toString() +" "+ rootFile.getFilepath() + " -o " + outputFilename);

        for(Dependency d : dep) {
            sb.append("\n\n");
            sb.append(createMakeFileString(d));
        }
        

        return sb.toString();
    }

}