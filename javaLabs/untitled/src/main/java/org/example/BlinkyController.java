package org.example;

import com.almasb.fxgl.entity.Entity;
import javafx.geometry.Point2D;
import java.util.List;

import static com.almasb.fxgl.dsl.FXGL.spawn;

public class BlinkyController extends GhostMoveController implements GhostMover {


    public BlinkyController(Entity blinky) {
        super(blinky);
    }

    @Override
    public void chaseMove(double tpf, Point2D pacmanPos, Direction pacmanDir) {
        Point2D target = new Point2D(
                (int)(pacmanPos.getX() / Size.WALLSIZE.size),
                (int)(pacmanPos.getY() / Size.WALLSIZE.size)
        );
        move(tpf, target);

    }

    @Override
    public void scatterMove(double tpf) {
        Point2D target = new Point2D(
                1, 1
        );
        move(tpf, target);
    }

//    @Override
//    public void frightenedMove(double tpf, Point2D pacmanPos, Direction pacmanDir) {
//        Point2D target = new Point2D(
//                1, 1
//        );
//        move(tpf, target);
//    }

    @Override
    public void offFrightenedMode() {
            Entity frightenedGhost = getEntity();
            Point2D currentPosition = frightenedGhost.getPosition();
            frightenedGhost.removeFromWorld();
            Entity colorGhost = spawn("blinky", currentPosition.getX(), currentPosition.getY());
            setEntity(colorGhost);
    }
}

