void main() {

    Vec2 A, B(1,2), C;
    Rect D, E(.1,2,.3,4), F(E);

    Rect G(C);
    Vec2 H(F);

    C = B*Vec2(2,2)/Vec2(1,3) + A;

    E.at(1) = E[2];
    E += E;
    E = E * F;
    F /= E;

    print(A); print('\n');
    print(B); print('\n');
    print(C); print('\n');
    print(D); print('\n');
    print(E); print('\n');
    print(F); print('\n');
    print(G); print('\n');
    print(H); print('\n');
    print(E + F - A);
    flush();
}