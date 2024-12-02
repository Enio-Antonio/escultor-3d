#include <iostream>
#include "escultor3d.h"

int main()
{
    Sculptor* escultura = new Sculptor(8, 8, 8);

    escultura->setColor(0.0, 0.86, 0.0, 1.0);

    escultura->putBox(0, 7, 0, 7, 0, 7);
    escultura->cutBox(1, 6, 1, 6, 1, 6);

    escultura->setColor(0, 0, 0, 1.0);

    escultura->putVoxel(1, 4, 7);
    escultura->putVoxel(1, 5, 7);
    escultura->putVoxel(2, 4, 7);
    escultura->putVoxel(2, 5, 7);

    escultura->putVoxel(5, 4, 7);
    escultura->putVoxel(5, 5, 7);
    escultura->putVoxel(6, 4, 7);
    escultura->putVoxel(6, 5, 7);

    escultura->putVoxel(3, 3, 7);
    escultura->putVoxel(4, 3, 7);

    escultura->putVoxel(2, 2, 7);
    escultura->putVoxel(3, 2, 7);
    escultura->putVoxel(4, 2, 7);
    escultura->putVoxel(5, 2, 7);

    escultura->putVoxel(2, 1, 7);
    escultura->putVoxel(3, 1, 7);
    escultura->putVoxel(4, 1, 7);
    escultura->putVoxel(5, 1, 7);

    escultura->putVoxel(2, 0, 7);
    escultura->putVoxel(5, 0, 7);

    escultura->writeOFF("escultura.off");

    delete escultura;

    return 0;
}