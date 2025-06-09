package org.example;

import javafx.geometry.Point2D;

import com.almasb.fxgl.entity.Entity;

public abstract class MoveController {
    private Direction currentDirection = Direction.NONE;
    private Direction futureDirection = currentDirection;
    private Entity entity;

    public Entity getEntity() {
        return entity;
    }

    public void setEntity(Entity entity) {
        this.entity = entity;
    }

    public MoveController(Entity entity) {
        this.entity = entity;
    }

    protected Point2D countGrid(double x, double y) {
        int gridX = (int) Math.floor((x + currentDirection.getDx() * Size.ENTITYRADIUS.size)/ Size.WALLSIZE.size);
        int gridY = (int) Math.floor((y + currentDirection.getDy() * Size.ENTITYRADIUS.size) / Size.WALLSIZE.size);
        return new Point2D(gridX, gridY);
    }

    public void setFutureDirection(Direction futureDirection) {
        this.futureDirection = futureDirection;
    }

    protected void changeRotation() {
        this.currentDirection = futureDirection;
        entity.setRotation(currentDirection.getRotation());
    }

    protected Direction getCurrentDirection() {
        return currentDirection;
    }

    protected Direction getFutureDirection() {
        return futureDirection;
    }

    protected void snapToGrid(double x, double y) {
        int gridX = (int) Math.floor(x / Size.WALLSIZE.size);
        int gridY = (int) Math.floor(y / Size.WALLSIZE.size);
        double centerX = gridX * Size.WALLSIZE.size + Size.WALLSIZE.size / 2;
        double centerY = gridY * Size.WALLSIZE.size + Size.WALLSIZE.size / 2;
        entity.setPosition(centerX, centerY);
    }

    protected abstract void reset();

}
