void main() {

    Vec2 A, B(1,2), C(B);
    Rect D, E(1,1,2,2), F(E);

    F += 1;
    Rect G(C);
    Vec2 H(F);

    print(A + 1); print('\n');
    print(B - 1); print('\n');
    print(C * 2); print('\n');
    print(D / 2); print('\n');
    print(E + 1); print('\n');
    print(F - 1); print('\n');
    print(G * 2); print('\n');
    print(H / 2); print('\n');
    print(E + F - A); print('\n');

    print(B.getDegrees()); print('\n');
    print(F.getPos()); print('\n');
    print(F.getDim()); print('\n');
    print(F.getMidPoint()); print('\n');
    print(F.Collide(Rect(0,1,2,2))); print('\n');
    print(F.isColliding(E)); print('\n');
    print(F.getTriAngle()); print('\n');

    print(getSprite("Player")); flush();

}