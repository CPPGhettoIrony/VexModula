void main() {

    Vec2 A, B(1,2), C(B);
    Rect D, E(1,2,3,4), F(E);

    Rect G(C);
    Vec2 H(F);

    print(A); print('\n');
    print(B); print('\n');
    print(C); print('\n');
    print(D); print('\n');
    print(E); print('\n');
    print(F); print('\n');
    print(G); print('\n');
    print(H); print('\n');
    // print(0);
    flush();
}