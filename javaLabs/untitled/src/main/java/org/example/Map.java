package org.example;

import com.almasb.fxgl.entity.Entity;
import com.almasb.fxgl.entity.SpawnData;

import static com.almasb.fxgl.dsl.FXGL.spawn;

public class Map {
    private static final int width = Size.MAPWIDTH.size;
    private static final int height = Size.MAPHEIGHT.size;
    private static Entity[][] entitiesMap = new Entity[height][width];
    private static final MapObjects[][] defaultMap = {
            {MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.PACMANHOUSE, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.BIG_DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.GHOST_HOUSE, MapObjects.GHOST_HOUSE, MapObjects.GHOST_GATE, MapObjects.GHOST_HOUSE, MapObjects.GHOST_HOUSE, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.GHOST_HOUSE, MapObjects.GHOST_HOUSE, MapObjects.GHOST_HOUSE, MapObjects.GHOST_HOUSE, MapObjects.GHOST_HOUSE, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.BIG_DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.DOT, MapObjects.BIG_DOT, MapObjects.WALL},
            {MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL, MapObjects.WALL}
    };

    private static MapObjects[][] map = new MapObjects[height][width];


    public static Entity getEntity(int i, int j) {
        return entitiesMap[i][j];
    }

    public static void removeEntityFromGrid(int i, int j) {
        entitiesMap[i][j] = null;
    }

    public static MapObjects getCurrentMapObject(int i, int j) {
        return map[i][j];
    }

    public static void setMapObject(int i, int j, MapObjects newObject) {
        map[i][j] = newObject;
    }

    public static void init() {
        for (int i = 0; i < Size.MAPHEIGHT.size; i++) {
            for (int j = 0; j < Size.MAPWIDTH.size; j++) {
                if (defaultMap[i][j] == MapObjects.WALL) {
                    Entity wall = spawn("wall", new SpawnData(j * Size.WALLSIZE.size, i * Size.WALLSIZE.size).put("width", Size.WALLSIZE.size).put("height", Size.WALLSIZE.size));
                    entitiesMap[i][j] = wall;
                    map[i][j] = MapObjects.WALL;
                } else if (defaultMap[i][j] == MapObjects.DOT) {
                    Entity dot = spawn("dot", j * Size.WALLSIZE.size + Size.WALLSIZE.size / 2, i * Size.WALLSIZE.size + Size.WALLSIZE.size / 2);
                    entitiesMap[i][j] = dot;
                    map[i][j] = MapObjects.DOT;
                } else if (defaultMap[i][j] == MapObjects.GHOST_HOUSE) {
                    Entity ghostHouse = spawn("ghostHouse", new SpawnData(j * Size.WALLSIZE.size, i * Size.WALLSIZE.size).put("width", Size.WALLSIZE.size).put("height", Size.WALLSIZE.size));
                    entitiesMap[i][j] = ghostHouse;
                    map[i][j] = MapObjects.GHOST_HOUSE;
                } else if (defaultMap[i][j] == MapObjects.BIG_DOT) {
                    Entity bigDot = spawn("bigDot", j * Size.WALLSIZE.size + Size.WALLSIZE.size / 2, i * Size.WALLSIZE.size + Size.WALLSIZE.size / 2);
                    entitiesMap[i][j] = bigDot;
                    map[i][j] = MapObjects.BIG_DOT;
                }
            }
        }
    }

    public static void reset() {
        for (int i = 0; i < Size.MAPHEIGHT.size; i++) {
            for (int j = 0; j < Size.MAPWIDTH.size; j++) {
                if (defaultMap[i][j] == MapObjects.DOT  && entitiesMap[i][j] == null) {
                    Entity dot = spawn("dot", j * Size.WALLSIZE.size + Size.WALLSIZE.size / 2, i * Size.WALLSIZE.size + Size.WALLSIZE.size / 2);
                    entitiesMap[i][j] = dot;
                    map[i][j] = MapObjects.DOT;
                } else if (defaultMap[i][j] == MapObjects.BIG_DOT && entitiesMap[i][j] == null) {
                    Entity bigDot = spawn("bigDot", j * Size.WALLSIZE.size + Size.WALLSIZE.size / 2, i * Size.WALLSIZE.size + Size.WALLSIZE.size / 2);
                    entitiesMap[i][j] = bigDot;
                    map[i][j] = MapObjects.BIG_DOT;
                }
            }
        }
    }
}

