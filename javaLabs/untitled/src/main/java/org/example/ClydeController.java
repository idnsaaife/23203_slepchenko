package org.example;

import com.almasb.fxgl.entity.Entity;
import javafx.geometry.Point2D;

import static com.almasb.fxgl.dsl.FXGL.spawn;

public class ClydeController extends GhostMoveController {
    private static final double SPAWN_DELAY = 4.0;
    private static final double CHASE_DISTANCE = 6 * Size.WALLSIZE.size;

    public ClydeController(Entity clyde) {
        super(clyde);
        setSpawnDelay(SPAWN_DELAY);
    }

    @Override
    public void chaseMove(double tpf, Point2D pacmanPos, Direction pacmanDir) {
        revive(tpf);
        if (!isAlive()) {
            return;
        }
        Point2D ghostPos = new Point2D(getEntity().getX(), getEntity().getY());
        double dx = pacmanPos.getX() - ghostPos.getX();
        double dy = pacmanPos.getY() - ghostPos.getY();
        double distance = Math.sqrt(dx * dx + dy * dy);
        Point2D target;
        if (distance > CHASE_DISTANCE) {
            target = new Point2D(
                    (int)(pacmanPos.getX() / Size.WALLSIZE.size),
                    (int)(pacmanPos.getY() / Size.WALLSIZE.size)
            );
        } else {
            target = new Point2D(2, Size.MAPHEIGHT.size - 2);
        }
        move(tpf, target);
    }

    @Override
    public void scatterMove(double tpf) {
        revive(tpf);
        if (!isAlive()) {
            return;
        }
        Point2D target = new Point2D(2, Size.MAPHEIGHT.size - 2);
        move(tpf, target);
    }


    @Override
    public void offFrightenedMode() {
        Entity frightenedGhost = getEntity();
        Point2D currentPosition = frightenedGhost.getPosition();
        frightenedGhost.removeFromWorld();
        Entity colorGhost = spawn("clyde", currentPosition.getX(), currentPosition.getY());
        setEntity(colorGhost);
    }
}