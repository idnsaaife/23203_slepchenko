import java.lang.reflect.Method;
import java.lang.annotation.Annotation;

public class Main {
    public static void main(String[] args) throws Exception { //так плохо
        System.out.println("main started");
        String neededClass = args[0];
        String neededMethod = args[1];
        Class c = Class.forName(neededClass);
        System.out.println("Loaded class: " + c.getName());

        Method[] methods = c.getDeclaredMethods();

        for (Method method : methods) {
           
            System.out.println("Method: " + method.getName());
            Annotation[] annotations = method.getAnnotations();
            for (Annotation a : annotations) {
                System.out.println(a.getName());
            }
        }

        
        //
        //; //в лабе не надо вызывать методы главное делать классы и загружать их по имени
        Object o = c.newInstance();
        Method m = c.getMethod(neededMethod);
        m.invoke(o);
       // Object o = c.getConstructor().newInstance();
        //ClassToLoad cmnd = (ClassToLoad) o;
        //cmnd.execute();

    }
}
//junit4 junit4 runner

/* import org.junit javac MainTests.java -cp juinit-4.12.jar
@Test
 * public void test1{
 * assertEquals()
 * }
 */

//sofya@MacBook-Air-sofya-2 src % java -classpath .:trash Main ClassToLoad  execute

/*после того как добавили пакет sofya@MacBook-Air-sofya-2 src % javac ClassToLoad.java
sofya@MacBook-Air-sofya-2 src % mv ClassToLoad.class trash
sofya@MacBook-Air-sofya-2 src % java -classpath .:trash Main ClassToLoad  execute

main started
Exception in thread "main" java.lang.NoClassDefFoundError: ClassToLoad (wrong name: mypackage/nsu/ClassToLoad)
        at java.base/java.lang.ClassLoader.defineClass1(Native Method)
        at java.base/java.lang.ClassLoader.defineClass(ClassLoader.java:1017)
        at java.base/java.security.SecureClassLoader.defineClass(SecureClassLoader.java:150)
        at java.base/jdk.internal.loader.BuiltinClassLoader.defineClass(BuiltinClassLoader.java:862)
        at java.base/jdk.internal.loader.BuiltinClassLoader.findClassOnClassPathOrNull(BuiltinClassLoader.java:760)
        at java.base/jdk.internal.loader.BuiltinClassLoader.loadClassOrNull(BuiltinClassLoader.java:681)
        at java.base/jdk.internal.loader.BuiltinClassLoader.loadClass(BuiltinClassLoader.java:639)
        at java.base/jdk.internal.loader.ClassLoaders$AppClassLoader.loadClass(ClassLoaders.java:188)
        at java.base/java.lang.ClassLoader.loadClass(ClassLoader.java:525)
        at java.base/java.lang.Class.forName0(Native Method)
        at java.base/java.lang.Class.forName(Class.java:375)
        at Main.main(Main.java:8) */