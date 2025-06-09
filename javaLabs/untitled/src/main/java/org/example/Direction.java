package org.example;

public enum Direction {
        RIGHT(0, 1, 0), // вообще то тут speed
        LEFT(180, -1, 0),
        UP(-90, 0, -1),
        DOWN(90, 0, 1),
        NONE(0,0,0);

        private final double rotation;
        private final double dx;
        private final double dy;

        Direction(double rotation, double dx, double dy) {
            this.rotation = rotation;
            this.dx = dx;
            this.dy = dy;
        }

        public double getRotation() {
            return rotation;
        }

        public double getDx() {
            return dx;
        }

        public double getDy() {
            return dy;
        }
}

