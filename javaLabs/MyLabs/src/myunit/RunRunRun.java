package myunit;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Retention;

@Retention(value = RetentionPolicy.RUNTIME)
public @interface RunRunRun {
    String why() default "";
    int chance() default 1;
}
