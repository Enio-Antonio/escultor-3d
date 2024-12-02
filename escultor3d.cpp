#include "escultor3d.h"

#include <iostream>
#include <fstream>
#include <iomanip>

Sculptor::Sculptor(int nx, int ny, int nz)
{

    this->nx = nx;
    this->ny = ny;
    this->nz = nz;

    v = new Voxel * *[nx];
    v[0] = new Voxel * [nx * ny];
    v[0][0] = new Voxel[nx * ny * nz];

    for (int i = 1; i < nx; i++)
    {
        v[i] = v[i - 1] + ny;
        v[i][0] = v[i - 1][0] + ny * nz;
    }

    for (int i = 0; i < nx; i++)
    {
        for (int c = 1; c < ny; c++)
        {
            v[i][c] = v[i][c - 1] + nz;
        }
    }

    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->a = 0;

    for (int i = 0; i < nx; i++)
    {
        for (int c = 0; c < ny; c++)
        {
            for (int k = 0; k < nz; k++)
            {
                v[i][c][k].show = false;
                v[i][c][k].r = 0;
                v[i][c][k].g = 0;
                v[i][c][k].b = 0;
                v[i][c][k].a = 0;
            }
        }
    }

}

Sculptor::~Sculptor() 
{
    delete v[0][0];
    delete v[0];
    delete v;
};

void Sculptor::setColor(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
    
};

void Sculptor::putVoxel(int x, int y, int z)
{
    v[x][y][z].show = true;
    v[x][y][z].r = this->r;
    v[x][y][z].g = this->g;
    v[x][y][z].b = this->b;
    v[x][y][z].a = this->a;
}

void Sculptor::cutVoxel(int x, int y, int z)
{
    v[x][y][z].show = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for (int i = 0; i < nx; i++)
    {
        for (int c = 0; c < ny; c++)
        {
            for (int k = 0; k < nz; k++)
            {
                if ((i >= x0 && i <= x1) && (c >= y0 && c <= y1) && (k >= z0 && k <= z1))
                {
                    v[i][c][k].show = true;
                    v[i][c][k].r = this->r;
                    v[i][c][k].g = this->g;
                    v[i][c][k].b = this->b;
                    v[i][c][k].a = this->a;
                }
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for (int i = 0; i < nx; i++)
    {
        for (int c = 0; c < ny; c++)
        {
            for (int k = 0; k < nz; k++)
            {
                if ((i >= x0 && i <= x1) && (c >= y0 && c <= y1) && (k >= z0 && k <= z1))
                {
                    v[i][c][k].show = false;
                }
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{

    for (int i = 0; i < nx; i++)
    {
        for (int c = 0; c < ny; c++)
        {
            for (int k = 0; k < nz; k++)
            {
                if ((i - xcenter) * (i - xcenter) +
                    (c - ycenter) * (c - ycenter) +
                    (k - zcenter) * (k - zcenter) <= radius * radius)
                {
                    v[i][c][k].show = true;
                    v[i][c][k].r = this->r;
                    v[i][c][k].g = this->g;
                    v[i][c][k].b = this->b;
                    v[i][c][k].a = this->a;
                }
            }
        }
    }

}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for (int i = 0; i < nx; i++)
    {
        for (int c = 0; c < ny; c++)
        {
            for (int k = 0; k < nz; k++)
            {
                if ((i - xcenter) * (i - xcenter) +
                    (c - ycenter) * (c - ycenter) +
                    (k - zcenter) * (k - zcenter) <= radius * radius)
                {
                    v[i][c][k].show = false;
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    for (int i = 0; i < nx; i++)
    {
        for (int c = 0; c < ny; c++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (((i - xcenter) * (i - xcenter)) / (float)(rx * rx) +
                    ((c - ycenter) * (c - ycenter)) / (float)(ry * ry) +
                    ((k - zcenter) * (k - zcenter)) / (float)(rz * rz) <= 1)
                {
                    v[i][c][k].show = true;
                    v[i][c][k].r = this->r;
                    v[i][c][k].g = this->g;
                    v[i][c][k].b = this->b;
                    v[i][c][k].a = this->a;
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    for (int i = 0; i < nx; i++)
    {
        for (int c = 0; c < ny; c++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (((i - xcenter) * (i - xcenter)) / (float)(rx * rx) +
                    ((c - ycenter) * (c - ycenter)) / (float)(ry * ry) +
                    ((k - zcenter) * (k - zcenter)) / (float)(rz * rz) <= 1)
                {
                    v[i][c][k].show = false;
                }
            }
        }
    }
}

void Sculptor::writeOFF(const char * filename)
{
    std::ofstream sculptorWriter;
    int contadorVox = 0;

    int auxV1 = 0;
    int auxV2 = 1;
    int auxV3 = 2;
    int auxV4 = 3;
    int auxV5 = 4;
    int auxV6 = 5;
    int auxV7 = 6;
    int auxV8 = 7;

    int soma8 = 0;

    for (int i = 0; i < nx; i++)
    {
        for (int c = 0; c < ny; c++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (v[i][c][k].show == true)
                {
                    contadorVox += 1;
                }
            }
        }
    }

    int nVertices = contadorVox * 8;
    int nFaces = contadorVox * 6;

    sculptorWriter.open(filename);
    sculptorWriter << std::fixed;
    sculptorWriter << std::setprecision(2);

    sculptorWriter << "OFF" << "\n";
    sculptorWriter << nVertices << " " << nFaces << " 0\n";

    for (int i = 0; i < nx; i++)
    {
        for (int c = 0; c < ny; c++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (v[i][c][k].show == true)
                {
                    sculptorWriter << i - 1 << " " << c << " " << k - 1 << "\n";
                    sculptorWriter << i - 1 << " " << c - 1 << " " << k - 1 << "\n";
                    sculptorWriter << i << " " << c - 1 << " " << k - 1 << "\n";
                    sculptorWriter << i << " " << c << " " << k - 1 << "\n";
                    sculptorWriter << i - 1 << " " << c << " " << k << "\n";
                    sculptorWriter << i - 1 << " " << c - 1 << " " << k << "\n";
                    sculptorWriter << i << " " << c - 1 << " " << k << "\n";
                    sculptorWriter << i << " " << c << " " << k << "\n";
                }
            }
        }
    }

    for (int i = 0; i < nx; i++)
    {
        for (int c = 0; c < ny; c++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (v[i][c][k].show == true)
                {
                    sculptorWriter << "4 " << auxV1 + soma8 << " " << auxV4 + soma8 << " " << auxV3 + soma8 << " " << auxV2 + soma8 << " " << v[i][c][k].r << " " << v[i][c][k].g << " " << v[i][c][k].b << " " << v[i][c][k].a << "\n";

                    sculptorWriter << "4 " << auxV5 + soma8 << " " << auxV6 + soma8 << " " << auxV7 + soma8 << " " << auxV8 + soma8 << " " << v[i][c][k].r << " " << v[i][c][k].g << " " << v[i][c][k].b << " " << v[i][c][k].a << "\n";

                    sculptorWriter << "4 " << auxV1 + soma8 << " " << auxV2 + soma8 << " " << auxV6 + soma8 << " " << auxV5 + soma8 << " " << v[i][c][k].r << " " << v[i][c][k].g << " " << v[i][c][k].b << " " << v[i][c][k].a << "\n";

                    sculptorWriter << "4 " << auxV1 + soma8 << " " << auxV5 + soma8 << " " << auxV8 + soma8 << " " << auxV4 + soma8 << " " << v[i][c][k].r << " " << v[i][c][k].g << " " << v[i][c][k].b << " " << v[i][c][k].a << "\n";

                    sculptorWriter << "4 " << auxV4 + soma8 << " " << auxV8 + soma8 << " " << auxV7 + soma8 << " " << auxV3 + soma8 << " " << v[i][c][k].r << " " << v[i][c][k].g << " " << v[i][c][k].b << " " << v[i][c][k].a << "\n";

                    sculptorWriter << "4 " << auxV2 + soma8 << " " << auxV3 + soma8 << " " << auxV7 + soma8 << " " << auxV6 + soma8 << " " << v[i][c][k].r << " " << v[i][c][k].g << " " << v[i][c][k].b << " " << v[i][c][k].a << "\n";

                    soma8 += 8;

                }
            }
        }
    }

    sculptorWriter.close();

}