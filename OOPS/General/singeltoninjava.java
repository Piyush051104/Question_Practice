class singelton{
    private static singelton instance;

    private singelton(){};



    public static  singelton getinstance(){
        if(instance == null){
            synchronized(singelton.class){
                if(instance == null){
                    instance = new singelton();
                }
            }
        }
        return instance;
    }
}

public class singeltoninjava {
    public static void main(String[] args){

        singelton s1 = singelton.getinstance();
        singelton s2 = singelton.getinstance();

        System.out.print(s1 == s2);
    }
}
