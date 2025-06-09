package org.example;

public enum Size {
    WALLSIZE(50),
    ENTITYRADIUS(25),
    MAPHEIGHT(14),
    MAPWIDTH(20);

    int size;
    Size(int i) {
        size = i;
    }
}
