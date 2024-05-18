#pragma once

/**
 * Struct usada para servir como "pixel" da imagem 3D a ser feita.\n
 * Guarda a cor, opacidade e decisao se o pixel sera desenhado ou nao.
 */
struct Voxel
{
    float r, g, b;
    float a;
    bool show;
};

/**
 * Classe principal.\n
 * Possui todos metodos para desenhar e mudar a cor do desenho. Alem da matriz que servira como quadro.
 */
class Sculptor
{
    /*! Matriz 3D. */
    Voxel*** v;

    /*! Dimensoes da matriz.*/
    int nx, ny, nz; 

    /*! Atributos de cor e opacidade. */
    float r, g, b, a; 

public:
    /**
     * Construtor padrao da classe.\n
     * Sera alocada uma matriz 3D com base nos parametros passados para o construtor.
     */
    Sculptor(int nx, int ny, int nz);

    /**
     * Destrutor padrao.
     */
    ~Sculptor();

    /**
     * Define a cor dos atributos rgb e opacidade, os quais serao passados para os todos elementos da matriz.
     */
    void setColor(float r, float g, float b, float a);

    /**
     * Ativa um voxel localizado nas coordenadas passadas como argumento.\n
     */
    void putVoxel(int x, int y, int z);

    /**
     * Desativa um voxel localizado nas coordenadas passadas como argumento.
     */
    void cutVoxel(int x, int y, int z);

    /**
     * Ativa todos os voxels no volume passado como argumento.
     */
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);

    /**
     * Desativa todos os voxels no volume passado como argumento.
     */
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);

    /**
     * Ativa todos os voxels ao redor centro de acordo com o raio, ambos passados pelos argumentos.\n
     * Aviso:\n
     * E necessario uma grande quantidade de voxels para que efetivamente lembre uma esfera.\n
     */
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);

    /**
     * Desativa todos os voxels ao redor centro de acordo com o raio, ambos passados pelos argumentos.
     */
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

    /**
     * Ativa todos os voxel ao redor do centro de acordo com a formula da elipsoide.\n
     * Aviso:\n
     * E necessario uma grande quantidade de voxels para que efetivamente lembre uma elipsoide.
     */
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

    /**
     * Desativa todos os voxel ao redor do centro de acordo com a formula da elipsoide.
     */
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

    /**
     * Escreve um arquivo .OFF de acordo com voxels ativos.\n
     * O arquivo pode ser lido por qualquer software de visualizacao de objetos 3D.\n
     * Exemplos: Meshlab, Geomview.
     */
    void writeOFF(const char* filename);
};

