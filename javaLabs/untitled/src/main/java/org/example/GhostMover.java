package org.example;
import javafx.geometry.Point2D;

public interface GhostMover {
    //void move(double tpf, Map wallMap, Point2D pacmanPos);
    void chaseMove(double tpf, Point2D pacmanPos, Direction pacmanDir);
    void scatterMove(double tpf);
    void frightenedMove(double tpf, Point2D pacmanPos, Direction pacmanDir);
}