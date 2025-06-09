package org.example;

import com.almasb.fxgl.entity.Entity;
import com.almasb.fxgl.entity.EntityFactory;
import com.almasb.fxgl.entity.SpawnData;
import com.almasb.fxgl.entity.Spawns;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;

import static com.almasb.fxgl.dsl.FXGL.*;

public class PacManFactory implements EntityFactory {

    @Spawns("pacman")
    public Entity newPacMan(SpawnData data) {
        return entityBuilder(data)
                .type(EntityType.PACMAN)
                .view(new Circle(Size.ENTITYRADIUS.size, Color.YELLOW))
                .build();
    }

    @Spawns("frightenedGhost")
    public Entity newfrightenedGhost(SpawnData data) {
        return entityBuilder(data)
                .type(EntityType.GHOST)
                .view(new Circle(Size.ENTITYRADIUS.size, Color.GRAY))
                .build();
    }

    @Spawns("blinky")
    public Entity newBlinky(SpawnData data) {
        return entityBuilder(data)
                .type(EntityType.GHOST)
                .view(new Circle(Size.ENTITYRADIUS.size, Color.RED))
                .build();
    }

    @Spawns("pinky")
    public Entity newPinky(SpawnData data) {
        return entityBuilder(data)
                .type(EntityType.GHOST)
                .view(new Circle(Size.ENTITYRADIUS.size, Color.PINK))
                .build();
    }

    @Spawns("clyde")
    public Entity newClyde(SpawnData data) {
        return entityBuilder(data)
                .type(EntityType.GHOST)
                .view(new Circle(Size.ENTITYRADIUS.size, Color.ORANGE))
                .build();
    }

    @Spawns("wall")
    public Entity newWall(SpawnData data) {
        double width = Size.WALLSIZE.size;
        double height = Size.WALLSIZE.size;
        return entityBuilder(data)
                .type(EntityType.WALL)
                .view(new Rectangle(width, height, Color.BLUE))
                .build();
    }

    @Spawns("ghostHouse")
    public Entity newGhostHouse(SpawnData data) {
        double width = Size.WALLSIZE.size;
        double height = Size.WALLSIZE.size;
        return entityBuilder(data)
                .type(EntityType.GHOST_HOUSE)
                .view(new Rectangle(width, height, Color.GOLD))
                .build();
    }



    @Spawns("dot")
    public Entity newDot(SpawnData data) {
        return entityBuilder(data)
                .type(EntityType.DOT)
                .view(new Circle(2, Color.WHITE))
                .build();
    }


    @Spawns("bigDot")
    public Entity newBigDot(SpawnData data) {
        return entityBuilder(data)
                .type(EntityType.BIG_DOT)
                .view(new Circle(6, Color.WHITE))
                .build();
    }


}

enum EntityType {
    PACMAN, GHOST, WALL, DOT, BIG_DOT, CHERRY, GHOST_HOUSE
}