package org.example;

import com.almasb.fxgl.entity.Entity;
import javafx.geometry.Point2D;

import java.util.List;

import static com.almasb.fxgl.dsl.FXGL.spawn;

public class PinkyController extends GhostMoveController {
    private final double SPAWN_DELAY = 2.0;

    public PinkyController(Entity pinky) {
        super(pinky);
        setSpawnDelay(SPAWN_DELAY);
    }

    @Override
    public void chaseMove(double tpf, Point2D pacmanPos, Direction pacmanDir) {
        revive(tpf);
        if (!isAlive()) {
            return;
        }
        Point2D target = new Point2D(
                (int)(pacmanPos.getX() / Size.WALLSIZE.size) + pacmanDir.getDx() * 4,
                (int)(pacmanPos.getY() / Size.WALLSIZE.size) + pacmanDir.getDy() * 4

        );
        move(tpf, target);
    }

    @Override
    public void scatterMove(double tpf) {
        revive(tpf);
        if (!isAlive()) {
            return;
        }
        Point2D target = new Point2D(
                (int)(Size.MAPWIDTH.size - 2),
                (int)(1)

        );
        move(tpf, target);
    }

//    @Override
//    public void frightenedMove(double tpf, Point2D pacmanPos, Direction pacmanDir) {
//        Point2D target = new Point2D(
//                (int)(Size.MAPWIDTH.size - 2),
//                (int)(1)
//
//        );
//        move(tpf, target);
//    }

    @Override
    public void offFrightenedMode() {
        Entity frightenedGhost = getEntity();
        Point2D currentPosition = frightenedGhost.getPosition();
        frightenedGhost.removeFromWorld();
        Entity colorGhost = spawn("pinky", currentPosition.getX(), currentPosition.getY());
        setEntity(colorGhost);
    }

}

