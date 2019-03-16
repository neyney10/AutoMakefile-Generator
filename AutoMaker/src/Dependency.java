import java.util.ArrayList;

class Dependency {
    private String filepath;
    private Boolean hppExists;
    private Boolean cppExists;
    private ArrayList<Dependency> dependencies;

    Dependency(String filepath) {
        this(filepath, false, false);
    }

    Dependency(String filepath, Boolean isHeaderExist) {
        this(filepath, isHeaderExist, false);
    }

    Dependency(String filepath, Boolean isHeaderExist, Boolean isCodeExist) {
        this.filepath = filepath;
        this.hppExists = isHeaderExist;
        this.cppExists = isCodeExist;
        dependencies = new ArrayList<>();
    }

    public String getFilepath() {
        return this.filepath;
    }

    public void setFilepath(String filepath) {
        this.filepath = filepath;
    }

    public Boolean isHeaderExist() {
        return hppExists;
    }

    public Boolean isCPPExist() {
        return cppExists;
    }

    public ArrayList<Dependency> getDependencies() {
        return new ArrayList<Dependency>(dependencies);
    }

    public void addDependency(Dependency d) {
        dependencies.add(d);
    }

    public Boolean isExist(String fileDependancy)  {
        for(Dependency d : dependencies) {
            if(d.getFilepath().equals(fileDependancy))
                return true;
        }

        return false;
    }

}