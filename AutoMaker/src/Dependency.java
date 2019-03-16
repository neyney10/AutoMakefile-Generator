import java.util.ArrayList;

class Dependency {
    private String filepath;
    private ArrayList<Dependency> dependencies;

    Dependency(String filepath) {
        this.filepath = filepath;
        dependencies = new ArrayList<>();
    }

    public String getFilepath() {
        return this.filepath;
    }

    public void setFilepath(String filepath) {
        this.filepath = filepath;
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