package org.example;

import javafx.geometry.Point2D;

public class PositionController {
    public static Point2D correctGrid(double x, double y, int gridX, int gridY) {
        double wallLeft = gridX * Size.WALLSIZE.size;
        double wallRight = (gridX + 1) * Size.WALLSIZE.size;
        double wallTop = gridY * Size.WALLSIZE.size;
        double wallBottom = (gridY + 1) * Size.WALLSIZE.size;
        double entityLeft = x - Size.ENTITYRADIUS.size;
        double entityRight = x + Size.ENTITYRADIUS.size;
        double entityTop = y - Size.ENTITYRADIUS.size;
        double entityBottom = y + Size.ENTITYRADIUS.size;
        if (entityRight > wallLeft && entityLeft < wallRight &&
                entityBottom > wallTop && entityTop < wallBottom) {
            double dxLeft = entityRight - wallLeft;
            double dxRight = wallRight - entityLeft;
            double dyTop = entityBottom - wallTop;
            double dyBottom = wallBottom - entityTop;
            double minPenetration = Math.min(Math.min(dxLeft, dxRight), Math.min(dyTop, dyBottom));
            if (minPenetration == dxLeft) {
                x = wallLeft - Size.ENTITYRADIUS.size;
            } else if (minPenetration == dxRight) {
                x = wallRight + Size.ENTITYRADIUS.size;
            } else if (minPenetration == dyTop) {
                y = wallTop - Size.ENTITYRADIUS.size;
            } else if (minPenetration == dyBottom) {
                y = wallBottom + Size.ENTITYRADIUS.size;
            }
        }
        return new Point2D(x, y);
    }

    public static boolean isAtGridCenter(double x, double y) {
        double indexX = Math.floor(x / Size.WALLSIZE.size);
        double indexY = Math.floor(y / Size.WALLSIZE.size);
        double centerX = indexX * Size.WALLSIZE.size + Size.WALLSIZE.size / 2;
        double centerY = indexY * Size.WALLSIZE.size + Size.WALLSIZE.size / 2;
        boolean atCenter = Math.abs(x - centerX) < 2 && Math.abs(y - centerY) < 2;
        return atCenter;
    }

    public static boolean canTurn(Direction direction, double x, double y) {
        if (direction == null) {

            return false;
        }
        int gridX = (int) Math.floor(x / Size.WALLSIZE.size);
        int gridY = (int) Math.floor(y / Size.WALLSIZE.size);
        int nextX = gridX + (int) direction.getDx();
        int nextY = gridY + (int) direction.getDy();
        if (nextX < 0 || nextX >= Size.MAPWIDTH.size || nextY < 0 || nextY >= Size.MAPHEIGHT.size) {
            return false;
        }
        boolean canTurn = Map.getCurrentMapObject(nextY, nextX) != MapObjects.WALL && Map.getCurrentMapObject(nextY, nextX) != MapObjects.GHOST_HOUSE;
        return canTurn;
    }
}
