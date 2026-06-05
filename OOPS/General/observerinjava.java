import java.util.ArrayList;
import java.util.List;

interface Iobserver{
    void update(String title);
}
class observer implements Iobserver{
    private String name;
    observer(String name){
        this.name = name;
    }
    public void update(String title){
        System.out.println(name + " listen a new video added of " + title + " is uploaded");
    }
}

interface Iobservable{
    void add(Iobserver o);
    void remove(Iobserver o);

    void update();

}

class observable implements Iobservable{
    public List<Iobserver>ts = new ArrayList<>();

    public String change;


    public void add(Iobserver o){
        ts.add(o);
    }
    public void remove(Iobserver o){
        ts.remove(o);
    }
    public void update(){
        for(Iobserver o:ts){
            o.update(change);
        }
    }
    public void addvideo(String title){
        change = title;
        System.out.println("Channel uploaded: " + title);
        update();
    }
}

public class observerinjava {
    public static void main(String[] args){
        observable channel1 = new observable();

        Iobserver s1 = new observer("Piyush");
        Iobserver s2 = new observer("Rahul");

        channel1.add(s1);
        channel1.add(s2);

        channel1.addvideo("Humsaath saath hain");
    }
}
