
import makefile.*;
public class MainFile {
    final static String programVersion = "1.1-Beta";
    final static char TAB = '\t';

    static String currentPath;
    static String outputFilename = "executable";

    public static void main(String[] args) {
        // if there are not enough arguments then quit with a message.
        if(args.length != 1) {
            System.out.println("No '.cpp' file provided to create a dependency tree...");
            System.out.println("\t Syntax: AutoMakefile <filename.cpp> <flags>");
            System.out.println("\t Note: no flags are supported at the moment, using version: "+programVersion);
            System.out.println("\t Using 'g++' compiler");
            return;
        }

        String executablePath = args[0];
        currentPath = System.getProperty("user.dir"); // get current dir

        System.out.println("Starting AutoMaker Version: "+programVersion);
        System.out.println("Scanning file: "+currentPath+"\\"+executablePath);

        CPPScanner CPPS = new CPPScanner(currentPath);

        Dependency executeableDependency = CPPS.read(executablePath);

        MakefileCreator mfc  = new MakefileCreator(outputFilename);

        System.out.println("--- Here is the makefile preview: ---");
        String makefileString = mfc.createMakeFileString(executeableDependency);
        System.out.println(makefileString);
        System.out.println("--- Creating makefile: saved ---");
        CPPS.createMakeFile(makefileString);

    }

   


    

}