package makefile;
import java.util.ArrayList;

public class MakefileCreator {
    final char TAB = '\t';
    private String outputFilename;

    public MakefileCreator(String outputFilename) {
        this.outputFilename = outputFilename;
    }

    public String createObjectDependency(Dependency dependency) {
        StringBuilder sb = new StringBuilder();

        ArrayList<Dependency> dep = dependency.getDependencies();

        sb.append(toO(dependency.getFilepath())+":");

        StringBuilder sbd = new StringBuilder(); //string builder dependencies.
        sbd.append(" "+dependency.getFilepath()); // object file depends on his CPP file.
        for(Dependency d : dep) { // and depends of other cpp files.
            sbd.append(" "+toHPP(d.getFilepath()));
        }

        StringBuilder sbd2 = new StringBuilder();  // string cuilder dependencies 2 - extra header files.
        if(dependency.isHeaderExist())
            sbd2.append(" "+toHPP(dependency.getFilepath()));

        sb.append(sbd.toString()+sbd2.toString()+" "+"\n");
        sb.append(TAB + "g++ -std=c++1z -c "+dependency.getFilepath() + " -o " + toO(dependency.getFilepath()));

        for(Dependency d : dep) {
            if(!d.isCPPExist())
                continue;

            sb.append("\n\n");
            sb.append(createObjectDependency(d));
        }

        return sb.toString();
    }


    public String createObjectCleaner() {
        StringBuilder sb = new StringBuilder();

        sb.append("clean:\n");
        sb.append(TAB +"rm -f *.o "+outputFilename);

        return sb.toString();
    }

    public String createMakeFileString(Dependency rootFile) {
        StringBuilder sb = new StringBuilder();
        ArrayList<Dependency> dep = rootFile.getDependencies();

        if(dep.size() > 0)
            sb.append(outputFilename+":");


        StringBuilder sbd = new StringBuilder();
        sbd.append(" "+toO(rootFile.getFilepath()));
        for(Dependency d : dep) {
            if(!d.isCPPExist())
                continue;

            sbd.append(" "+toO(d.getFilepath()));
        }

        sb.append(sbd.toString()+"\n");
        sb.append(TAB + "g++ -std=c++1z"+sbd.toString() + " -o " + outputFilename);

        sb.append("\n\n");
        sb.append(createObjectDependency(rootFile));
        
        sb.append("\n\n");
        sb.append(createObjectCleaner());

        return sb.toString();
    }

    

    public String toO(String name) {
        int index = name.lastIndexOf('.');
        return name.substring(0, index)+".o";
    }

    public String toCPP(String name) {
        int index = name.lastIndexOf('.');
        return name.substring(0, index)+".cpp";
    }

    public String toHPP(String name) {
        int index = name.lastIndexOf('.');
        return name.substring(0, index)+".hpp"; 
    }
}