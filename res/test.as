void main() {

    Vec2 A, B(1,2), C;
    Rect D, E(1,2,3,4), F(E);

    Rect G(C);
    Vec2 H(F);

    C = B;
    E.at(1) = E[2];
    C.at(0) = A[1]+2;

    //Rect I;
    //I = E + F;

    print(A); print('\n');
    print(B); print('\n');
    print(C); print('\n');
    print(D); print('\n');
    print(E); print('\n');
    print(F); print('\n');
    print(G); print('\n');
    print(H); print('\n');
    print(E.Collide(F));
    flush();
}